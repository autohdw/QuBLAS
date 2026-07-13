#include "QuBLAS.h"

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

using namespace QuBLAS;

namespace {

using Input =
    Qu<intBits<8>, fracBits<0>, isSigned<true>, QuMode<TRN::TCPL>,
       OfMode<SAT::TCPL>>;
using Layer0 =
    Qu<intBits<10>, fracBits<0>, isSigned<true>, QuMode<TRN::TCPL>,
       OfMode<SAT::TCPL>>;
using Layer1 =
    Qu<intBits<11>, fracBits<0>, isSigned<true>, QuMode<TRN::TCPL>,
       OfMode<SAT::TCPL>>;
using Layer2 =
    Qu<intBits<12>, fracBits<0>, isSigned<true>, QuMode<TRN::TCPL>,
       OfMode<SAT::TCPL>>;
using Layers = TypeList<Layer0, Layer1, Layer2>;

using Vector1 = Qu<dim<1>, Input>;
using Vector2 = Qu<dim<2>, Input>;
using Vector3 = Qu<dim<3>, Input>;
using Vector4 = Qu<dim<4>, Input>;
using Vector5 = Qu<dim<5>, Input>;
using Vector7 = Qu<dim<7>, Input>;
using Matrix2x3 = Qu<dim<2, 3>, Input>;

// These are compile-only compatibility checks.  Keep them valid against the
// pre-fix header as well as the current implementation.
static_assert(requires(Input a, Input b, Input c, Input d, Input e) {
    Qreduce<>(a);
    Qreduce(a, b);
    Qreduce<Layer0>(a, b, c);
    Qreduce<Layer0, Layer1>(a, b, c, d);
    Qreduce<TypeList<Layer0, Layer1, Layer2>>(a, b, c, d, e);
});

static_assert(requires(Vector1 v1, Vector2 v2, Vector3 v3, Vector4 v4,
                       Vector5 v5, Vector7 v7, Matrix2x3 matrix) {
    Qreduce<>(v1);
    Qreduce<Layer0>(v2);
    Qreduce<TypeList<Layer0, Layer1>>(v3);
    Qreduce<Layer0, Layer1>(v4);
    Qreduce<Layers>(v5);
    Qreduce<Layers>(v7);
    Qreduce<Layers>(matrix);
});

static_assert(std::is_same_v<decltype(Qreduce<Layers>(Input{})), Input>);
static_assert(
    std::is_same_v<decltype(Qreduce<Layers>(std::declval<Vector1>())), Input>);
static_assert(std::is_same_v<
              decltype(Qreduce<Layer0, Layer1>(Input{}, Input{}, Input{},
                                               Input{})),
              Layer1>);
static_assert(
    std::is_same_v<decltype(Qreduce<Layers>(std::declval<Vector5>())),
                   Layer2>);

#ifndef QUBLAS_COMPARE_PRE_FIX_BASELINE
// The old variadic odd-tail implementation applied Layer0 again after the
// recursive tree and therefore returned the wrong public Qu type.
static_assert(std::is_same_v<
              decltype(Qreduce<Layers>(Input{}, Input{}, Input{}, Input{},
                                       Input{})),
              Layer2>);
#endif

TEST(ReducerCompatibility, DefaultQuTypeListAndTypePackForms)
{
    const Input one(1.0);
    const Input two(2.0);
    const Input three(3.0);
    const Input four(4.0);
    const Input five(5.0);

    EXPECT_DOUBLE_EQ(Qreduce<>(one, two).toDouble(), 3.0);
    EXPECT_DOUBLE_EQ(Qreduce<Layer0>(one, two, three).toDouble(), 6.0);
    EXPECT_DOUBLE_EQ(
        (Qreduce<Layer0, Layer1>(one, two, three, four).toDouble()), 10.0);
    EXPECT_DOUBLE_EQ(
        Qreduce<Layers>(Vector5{one, two, three, four, five}).toDouble(),
        15.0);
    EXPECT_DOUBLE_EQ(
        Qreduce<Layers>(Matrix2x3{one, two, three, four, five, Input(6.0)})
            .toDouble(),
        21.0);
}

TEST(ReducerCompatibility, SingletonKeepsHistoricalInputTypeAndValue)
{
    const Input value(37.0);
    const auto scalarResult = Qreduce<Layers>(value);
    const auto vectorResult = Qreduce<Layers>(Vector1{value});

    static_assert(std::is_same_v<decltype(scalarResult), const Input>);
    static_assert(std::is_same_v<decltype(vectorResult), const Input>);
    EXPECT_DOUBLE_EQ(scalarResult.toDouble(), 37.0);
    EXPECT_DOUBLE_EQ(vectorResult.toDouble(), 37.0);
}

TEST(ReducerCorrectness, OddAndEvenTreesShareLayerQuantization)
{
    using Narrow =
        Qu<intBits<1>, fracBits<0>, isSigned<true>, QuMode<TRN::TCPL>,
           OfMode<SAT::TCPL>>;
    using Middle =
        Qu<intBits<3>, fracBits<0>, isSigned<true>, QuMode<TRN::TCPL>,
           OfMode<SAT::TCPL>>;
    using Wide =
        Qu<intBits<5>, fracBits<0>, isSigned<true>, QuMode<TRN::TCPL>,
           OfMode<SAT::TCPL>>;
    using QuantizedLayers = TypeList<Narrow, Middle, Wide>;

    const Wide one(1.0);
    const Qu<dim<3>, Wide> three{one, one, one};
    const Qu<dim<4>, Wide> four{one, one, one, one};
    const Qu<dim<5>, Wide> five{one, one, one, one, one};
    const Qu<dim<7>, Wide> seven{one, one, one, one, one, one, one};

    const auto variadic3 = Qreduce<QuantizedLayers>(one, one, one);
    const auto variadic4 = Qreduce<Narrow, Middle, Wide>(one, one, one, one);
    const auto variadic5 =
        Qreduce<QuantizedLayers>(one, one, one, one, one);
    const auto variadic7 =
        Qreduce<QuantizedLayers>(one, one, one, one, one, one, one);

    static_assert(std::is_same_v<decltype(variadic4), const Middle>);
#ifndef QUBLAS_COMPARE_PRE_FIX_BASELINE
    static_assert(std::is_same_v<decltype(variadic3), const Middle>);
    static_assert(std::is_same_v<decltype(variadic5), const Wide>);
    static_assert(std::is_same_v<decltype(variadic7), const Wide>);
#endif

    EXPECT_DOUBLE_EQ(variadic3.toDouble(), Qreduce<QuantizedLayers>(three).toDouble());
    EXPECT_DOUBLE_EQ(variadic4.toDouble(), Qreduce<QuantizedLayers>(four).toDouble());
    EXPECT_DOUBLE_EQ(variadic5.toDouble(), Qreduce<QuantizedLayers>(five).toDouble());
    EXPECT_DOUBLE_EQ(variadic7.toDouble(), Qreduce<QuantizedLayers>(seven).toDouble());
    EXPECT_DOUBLE_EQ(variadic3.toDouble(), 2.0);
    EXPECT_DOUBLE_EQ(variadic4.toDouble(), 2.0);
    EXPECT_DOUBLE_EQ(variadic5.toDouble(), 3.0);
    EXPECT_DOUBLE_EQ(variadic7.toDouble(), 4.0);
}

#ifndef QUBLAS_COMPARE_PRE_FIX_BASELINE
TEST(ReducerCorrectness, ReducesTemporaryNestedTensorExpression)
{
    const auto result = Qreduce<Layers>(Qadd(
        Qadd(Vector5{Input(1.0), Input(2.0), Input(3.0), Input(4.0),
                     Input(5.0)},
             Input(1.0)),
        Input(2.0)));

    static_assert(std::is_same_v<decltype(result), const Layer2>);
    EXPECT_DOUBLE_EQ(result.toDouble(), 30.0);
}

TEST(ReducerCorrectness, OddVariadicTensorTailIsQuantizedElementwise)
{
    const auto result = Qreduce<Layer0>(
        Vector3{Input(1.0), Input(2.0), Input(3.0)},
        Vector3{Input(4.0), Input(5.0), Input(6.0)},
        Vector3{Input(7.0), Input(8.0), Input(9.0)});

    static_assert(isTensorOperand<decltype(result)>);
    static_assert(std::is_same_v<tensorSize<decltype(result)>, dim<3>>);
    static_assert(std::is_same_v<
                  std::remove_cvref_t<decltype(result[size_t{}])>, Layer0>);

    const auto values = result.eval();
    EXPECT_DOUBLE_EQ(values[0].toDouble(), 12.0);
    EXPECT_DOUBLE_EQ(values[1].toDouble(), 15.0);
    EXPECT_DOUBLE_EQ(values[2].toDouble(), 18.0);
}
#endif

} // namespace
