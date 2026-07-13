#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

#include "QuBLAS.h"

namespace {

using Scalar = Qu<intBits<8>, fracBits<0>, OfMode<SAT::TCPL>>;
using Wide = Qu<intBits<12>, fracBits<0>, OfMode<SAT::TCPL>>;
using Vector = Qu<dim<3>, Scalar>;

template <typename Left, typename Closure>
concept Pipeable = requires(Left &&left, Closure &&closure) {
    std::forward<Left>(left) | std::forward<Closure>(closure);
};

using AddScalarPipe = decltype(Qadd(Scalar{}));
static_assert(Pipeable<Vector &, AddScalarPipe>);
static_assert(!Pipeable<int, AddScalarPipe>);

template <typename Left>
auto addTemporaryRightHandSide(Left &left)
{
    return left | Qadd(Vector{Scalar(4), Scalar(5), Scalar(6)});
}

template <typename First, typename Second>
auto reuseNamedOwningPipe(First &first, Second &second)
{
    auto addOffsets =
        Qadd(Vector{Scalar(10), Scalar(20), Scalar(30)});

    // Both expressions escape the pipe closure's lifetime.  Applying an
    // lvalue closure must therefore copy its owned operand into each AST,
    // rather than leave either AST referring to a member of addOffsets.
    return std::pair{first | addOffsets, second | addOffsets};
}

TEST(PipeDSL, ChainedPipelineMatchesTheDirectQApi)
{
    Vector left{Scalar(1), Scalar(-2), Scalar(3)};
    Vector addend{Scalar(4), Scalar(5), Scalar(-6)};
    Vector multiplier{Scalar(-2), Scalar(3), Scalar(-4)};

    auto piped = left | Qadd(addend) | Qmul(multiplier) | Qabs();
    auto direct = Qabs(Qmul(Qadd(left, addend), multiplier));

    static_assert(std::is_same_v<typename decltype(piped)::size, dim<3>>);
    for (size_t index = 0; index < Vector::size::elemSize; ++index)
    {
        EXPECT_DOUBLE_EQ(piped[index].toDouble(), direct[index].toDouble());
    }
}

TEST(PipeDSL, BorrowsNamedEntityOperands)
{
    Vector left{Scalar(1), Scalar(2), Scalar(3)};
    Vector right{Scalar(4), Scalar(5), Scalar(6)};
    auto expression = left | Qadd(right);

    left[0] = Scalar(20);
    right[0] = Scalar(30);
    right[2] = Scalar(-10);

    EXPECT_DOUBLE_EQ(expression[0].toDouble(), 50.0);
    EXPECT_DOUBLE_EQ(expression[2].toDouble(), -7.0);
}

TEST(PipeDSL, OwnsATemporaryRightHandSide)
{
    Vector left{Scalar(1), Scalar(2), Scalar(3)};
    auto expression = addTemporaryRightHandSide(left);

    left[1] = Scalar(12);

    EXPECT_DOUBLE_EQ(expression[0].toDouble(), 5.0);
    EXPECT_DOUBLE_EQ(expression[1].toDouble(), 17.0);
    EXPECT_DOUBLE_EQ(expression[2].toDouble(), 9.0);
}

TEST(PipeDSL, NamedOwningClosureIsReusableAndDoesNotLeakItsLifetime)
{
    Vector first{Scalar(1), Scalar(2), Scalar(3)};
    Vector second{Scalar(-1), Scalar(-2), Scalar(-3)};
    auto [firstExpression, secondExpression] =
        reuseNamedOwningPipe(first, second);

    first[1] = Scalar(7);
    second[2] = Scalar(8);

    EXPECT_DOUBLE_EQ(firstExpression[0].toDouble(), 11.0);
    EXPECT_DOUBLE_EQ(firstExpression[1].toDouble(), 27.0);
    EXPECT_DOUBLE_EQ(secondExpression[0].toDouble(), 9.0);
    EXPECT_DOUBLE_EQ(secondExpression[2].toDouble(), 38.0);
}

TEST(PipeDSL, ExplicitOutputTypeMatchesTheDirectQApi)
{
    Vector left{Scalar(40), Scalar(-30), Scalar(20)};
    Vector right{Scalar(5), Scalar(7), Scalar(-9)};

    auto piped = left | Qadd<Wide>(right);
    auto direct = Qadd<Wide>(left, right);

    static_assert(
        std::is_same_v<std::remove_cvref_t<decltype(piped[0])>, Wide>);
    for (size_t index = 0; index < Vector::size::elemSize; ++index)
    {
        EXPECT_DOUBLE_EQ(piped[index].toDouble(), direct[index].toDouble());
    }
}

TEST(PipeDSL, SubDivNegAndReduceComposeAsClosures)
{
    Vector values{Scalar(9), Scalar(5), Scalar(1)};

    auto transformed =
        values | Qsub(Scalar(1)) | Qdiv(Scalar(2)) | Qneg();
    auto direct = Qneg(Qdiv(Qsub(values, Scalar(1)), Scalar(2)));

    for (size_t index = 0; index < Vector::size::elemSize; ++index)
    {
        EXPECT_DOUBLE_EQ(transformed[index].toDouble(),
                         direct[index].toDouble());
    }

    auto pipedTotal = transformed | Qreduce<Wide>();
    auto directTotal = Qreduce<Wide>(transformed);
    EXPECT_DOUBLE_EQ(pipedTotal.toDouble(), directTotal.toDouble());
}

} // namespace
