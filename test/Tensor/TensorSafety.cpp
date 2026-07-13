#include <gtest/gtest.h>

#include <atomic>
#include <thread>

#include "QuBLAS.h"

namespace {

using Scalar = Qu<intBits<8>, fracBits<0>>;
using WiderScalar = Qu<intBits<9>, fracBits<0>>;
using Shape2 = Qu<dim<2>, Scalar>;
using Shape3 = Qu<dim<3>, Scalar>;

template <typename Left, typename Right>
concept TensorAddable = requires(Left &left, Right &right) {
    Qadd(left, right);
};

static_assert(TensorAddable<Shape2, Shape2>);
static_assert(TensorAddable<Shape2, Scalar>);
static_assert(TensorAddable<Scalar, Shape2>);
static_assert(!TensorAddable<Shape2, Shape3>);

using SliceMatrix = Qu<dim<3, 4>, Scalar>;
using StaticBlock =
    decltype(std::declval<SliceMatrix &>()[slice<1, 3>, all]);
using ConstStaticBlock =
    decltype(std::declval<const SliceMatrix &>()[all, slice<1, 3>]);
using DroppedAxis =
    decltype(std::declval<SliceMatrix &>()[1, all]);
using SliceCube = Qu<dim<2, 3, 5>, Scalar>;
using MixedSlice =
    decltype(std::declval<SliceCube &>()[1, all, slice<0, 5>]);
using LazyMatrix =
    decltype(std::declval<SliceMatrix &>() + std::declval<Scalar>());

static_assert(std::is_same_v<typename StaticBlock::size, dim<2, 4>>);
static_assert(std::is_same_v<typename ConstStaticBlock::size, dim<3, 2>>);
static_assert(std::is_same_v<typename DroppedAxis::size, dim<4>>);
static_assert(std::is_same_v<typename MixedSlice::size, dim<3, 5>>);
static_assert(std::is_same_v<decltype(std::declval<StaticBlock &>()[0, 0]),
                             Scalar &>);
static_assert(
    std::is_same_v<decltype(std::declval<ConstStaticBlock &>()[0, 0]),
                   const Scalar &>);

template <typename T>
concept AcceptsTooFewSelectors = requires(T &tensor) {
    tensor[all];
};

static_assert(!AcceptsTooFewSelectors<SliceMatrix>);

template <typename T>
concept AcceptsBadLazyArity = requires(T &expression) {
    expression[0, 0, 0];
};

template <typename T>
concept AcceptsLazySlice = requires(T &&expression) {
    std::forward<T>(expression)[all, 1];
};

static_assert(!AcceptsBadLazyArity<LazyMatrix>);
static_assert(AcceptsLazySlice<LazyMatrix>);

TEST(TensorStorage, HeapBackedConversionMoveAndGetKeepFixedExtent)
{
    using Source = Qu<dim<1001>, Scalar>;
    using Destination = Qu<dim<1001>, WiderScalar>;

    Source source;
    source[1000] = Scalar(7.0);

    Destination destination(std::move(source));
    EXPECT_EQ(destination.data.size(), 1001u);
    EXPECT_DOUBLE_EQ(destination.template get<1000>().toDouble(), 7.0);
}

TEST(TensorStorage, MovedFromHeapTensorCanBeAssignedAgain)
{
    using Tensor = Qu<dim<1001>, Scalar>;

    Tensor source;
    source[5] = Scalar(3.0);
    Tensor destination(std::move(source));

    EXPECT_EQ(source.data.size(), 1001u);
    EXPECT_DOUBLE_EQ(destination[5].toDouble(), 3.0);

    Tensor replacement;
    replacement[1000] = Scalar(9.0);
    source = replacement;
    EXPECT_DOUBLE_EQ(source[1000].toDouble(), 9.0);
}

TEST(TensorStorage, ClearUsesElementAssignment)
{
    using Complex = Qcomplex<Scalar, Scalar>;
    Qu<dim<2>, Complex> tensor;
    tensor[0].real = Scalar(4.0);
    tensor[0].imag = Scalar(-3.0);

    tensor.clear();

    EXPECT_DOUBLE_EQ(tensor[0].real.toDouble(), 0.0);
    EXPECT_DOUBLE_EQ(tensor[0].imag.toDouble(), 0.0);
}

TEST(TensorExpression, OwnsTemporaryTensorAndScalarOperands)
{
    using Vec = Qu<dim<3>, Scalar>;

    auto expression = Qadd(Vec{Scalar(1.0), Scalar(2.0), Scalar(3.0)}, Scalar(4.0));

    EXPECT_DOUBLE_EQ(expression[0].toDouble(), 5.0);
    EXPECT_DOUBLE_EQ(expression[2].toDouble(), 7.0);
}

TEST(TensorExpression, KeepsNamedOperandsLazyByReference)
{
    using Vec = Qu<dim<2>, Scalar>;
    Vec left{Scalar(1.0), Scalar(2.0)};
    Vec right{Scalar(3.0), Scalar(4.0)};
    auto expression = Qadd(left, right);

    left[0] = Scalar(8.0);
    EXPECT_DOUBLE_EQ(expression[0].toDouble(), 11.0);
}

TEST(TensorExpression, ComposesSameShapeLazyExpressions)
{
    Shape2 left{Scalar(1.0), Scalar(2.0)};
    Shape2 middle{Scalar(3.0), Scalar(4.0)};
    Shape2 right{Scalar(5.0), Scalar(6.0)};

    auto expression = (left + middle) - right;

    left[0] = Scalar(2.0);
    EXPECT_DOUBLE_EQ(expression[0].toDouble(), 0.0);
    EXPECT_DOUBLE_EQ(expression[1].toDouble(), 0.0);
}

TEST(TensorExpression, BroadcastsScalarsOnBothSidesOfNestedExpressions)
{
    Shape2 values{Scalar(1.0), Scalar(3.0)};

    auto scalarOnLeft = Scalar(10.0) + (values + Scalar(2.0));
    auto scalarOnRight = (Scalar(2.0) + values) + Scalar(10.0);

    EXPECT_DOUBLE_EQ(scalarOnLeft[0].toDouble(), 13.0);
    EXPECT_DOUBLE_EQ(scalarOnLeft[1].toDouble(), 15.0);
    EXPECT_DOUBLE_EQ(scalarOnRight[0].toDouble(), 13.0);
    EXPECT_DOUBLE_EQ(scalarOnRight[1].toDouble(), 15.0);
}

TEST(TensorExpression, OwnsAChainOfTemporaryIntermediateNodes)
{
    auto makeValues = [] {
        return Shape2{Scalar(1.0), Scalar(-3.0)};
    };

    auto expression = Qabs(-Qadd(makeValues(), Scalar(4.0)));

    EXPECT_DOUBLE_EQ(expression[0].toDouble(), 5.0);
    EXPECT_DOUBLE_EQ(expression[1].toDouble(), 1.0);
}

TEST(Slice, StaticSelectorsExposeShapeAndColumnMajorMapping)
{
    SliceMatrix matrix;
    for (size_t column = 0; column < 4; ++column)
    {
        for (size_t row = 0; row < 3; ++row)
        {
            matrix[row, column] =
                Scalar(static_cast<double>(10 * column + row));
        }
    }

    auto rows = matrix[slice<1, 3>, all];

    EXPECT_DOUBLE_EQ((rows[0, 0].toDouble()), 1.0);
    EXPECT_DOUBLE_EQ((rows[1, 2].toDouble()), 22.0);
    EXPECT_DOUBLE_EQ(rows[4].toDouble(), 21.0);
}

TEST(Slice, MutableViewWritesThroughAndConstViewReads)
{
    SliceMatrix matrix;
    matrix[1, 2] = Scalar(12.0);
    matrix[2, 2] = Scalar(22.0);

    auto writable = matrix[slice<1, 3>, slice<1, 3>];
    writable[0, 1] = Scalar(77.0);
    writable[3] = Scalar(88.0);

    EXPECT_DOUBLE_EQ((matrix[1, 2].toDouble()), 77.0);
    EXPECT_DOUBLE_EQ((matrix[2, 2].toDouble()), 88.0);

    const SliceMatrix &constMatrix = matrix;
    auto readonly = constMatrix[all, 2];
    static_assert(std::is_same_v<typename decltype(readonly)::size, dim<3>>);
    EXPECT_DOUBLE_EQ(readonly[1].toDouble(), 77.0);
    EXPECT_DOUBLE_EQ(readonly[2].toDouble(), 88.0);
}

TEST(Slice, IntegralSelectorsDropTheirAxes)
{
    SliceMatrix matrix;
    matrix[1, 2] = Scalar(12.0);

    auto row = matrix[1, all];
    auto column = matrix[all, 2];

    static_assert(std::is_same_v<typename decltype(row)::size, dim<4>>);
    static_assert(std::is_same_v<typename decltype(column)::size, dim<3>>);
    EXPECT_DOUBLE_EQ(row[2].toDouble(), 12.0);
    EXPECT_DOUBLE_EQ(column[1].toDouble(), 12.0);
}

TEST(Slice, OwnsTemporaryTensor)
{
    auto makeMatrix = [] {
        SliceMatrix matrix;
        for (size_t column = 0; column < 4; ++column)
        {
            for (size_t row = 0; row < 3; ++row)
            {
                matrix[row, column] =
                    Scalar(static_cast<double>(10 * column + row));
            }
        }
        return matrix;
    };

    auto owned = makeMatrix()[slice<1, 3>, slice<1, 3>];

    EXPECT_DOUBLE_EQ((owned[0, 0].toDouble()), 11.0);
    EXPECT_DOUBLE_EQ((owned[1, 1].toDouble()), 22.0);
    owned[1, 1] = Scalar(42.0);
    EXPECT_DOUBLE_EQ(owned[3].toDouble(), 42.0);
}

TEST(Slice, OwnsTemporaryLazyExpression)
{
    auto view = (SliceMatrix{Scalar(0), Scalar(1), Scalar(2),
                             Scalar(10), Scalar(11), Scalar(12),
                             Scalar(20), Scalar(21), Scalar(22),
                             Scalar(30), Scalar(31), Scalar(32)} +
                 Scalar(1))[all, 1];

    static_assert(std::is_same_v<typename decltype(view)::size, dim<3>>);
    EXPECT_DOUBLE_EQ(view[0].toDouble(), 11.0);
    EXPECT_DOUBLE_EQ(view[1].toDouble(), 12.0);
    EXPECT_DOUBLE_EQ(view[2].toDouble(), 13.0);
}

TEST(Slice, ViewsCanBeSlicedAgain)
{
    SliceMatrix matrix;
    for (size_t column = 0; column < 4; ++column)
        for (size_t row = 0; row < 3; ++row)
            matrix[row, column] =
                Scalar(static_cast<double>(10 * column + row));

    auto chained = matrix[all, slice<0, 4>][1, slice<1, 3>];

    static_assert(std::is_same_v<typename decltype(chained)::size, dim<2>>);
    EXPECT_DOUBLE_EQ(chained[0].toDouble(), 11.0);
    EXPECT_DOUBLE_EQ(chained[1].toDouble(), 21.0);

    chained[1] = Scalar(77);
    EXPECT_DOUBLE_EQ((matrix[1, 2].toDouble()), 77.0);
}

TEST(Slice, MapsHigherRankSelectorsInColumnMajorOrder)
{
    using Tensor = Qu<dim<2, 3, 4>, Scalar>;
    Tensor tensor;
    tensor[1, 0, 1] = Scalar(17.0);
    tensor[0, 1, 1] = Scalar(23.0);

    auto view = tensor[all, slice<0, 2>, 1];

    static_assert(
        std::is_same_v<typename decltype(view)::size, dim<2, 2>>);
    EXPECT_DOUBLE_EQ((view[1, 0].toDouble()), 17.0);
    EXPECT_DOUBLE_EQ(view[2].toDouble(), 23.0);
}

TEST(Slice, RejectsIndicesOutsideTheView)
{
    SliceMatrix matrix;
    auto view = matrix[slice<1, 3>, slice<1, 3>];

    EXPECT_THROW((void)view[4], std::out_of_range);
    EXPECT_THROW((static_cast<void>(view[2, 0])), std::out_of_range);
}

TEST(Reducer, VariadicOddTailMatchesVectorLayerQuantization)
{
    using Narrow = Qu<intBits<1>, fracBits<0>, OfMode<SAT::TCPL>>;
    using Wide = Qu<intBits<3>, fracBits<0>, OfMode<SAT::TCPL>>;
    using Layers = TypeList<Narrow, Wide, Wide>;
    Qu<dim<5>, Wide> values{Wide(1.0), Wide(1.0), Wide(1.0), Wide(1.0), Wide(1.0)};

    const auto vectorResult = Qreduce<Layers>(values);
    const auto variadicResult = Qreduce<Layers>(values[0], values[1], values[2], values[3], values[4]);

    EXPECT_DOUBLE_EQ(vectorResult.toDouble(), 3.0);
    EXPECT_DOUBLE_EQ(variadicResult.toDouble(), vectorResult.toDouble());
}

TEST(Reducer, ConcurrentCallsDoNotShareScratchTensors)
{
    using Value = Qu<intBits<8>, fracBits<0>, OfMode<SAT::TCPL>>;
    using Values = Qu<dim<17>, Value>;
    std::atomic<bool> correct = true;

    auto worker = [&correct](int input) {
        Values values;
        for (auto &value : values.data)
        {
            value = Value(static_cast<double>(input));
        }

        for (size_t iteration = 0; iteration < 1000; ++iteration)
        {
            if (Qreduce<Value>(values).toDouble() != static_cast<double>(17 * input))
            {
                correct = false;
            }
        }
    };

    std::thread first(worker, 1);
    std::thread second(worker, 2);
    first.join();
    second.join();

    EXPECT_TRUE(correct.load());
}

} // namespace
