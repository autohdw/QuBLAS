#include "QuBLAS.h"

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <type_traits>
#include <utility>

using namespace QuBLAS;

namespace {

using Unsigned = Qu<intBits<3>, fracBits<0>, isSigned<false>>;
using Vector = Qu<dim<4>, Unsigned>;
using Complex = Qcomplex<Unsigned, Unsigned>;

static_assert(std::is_same_v<decltype(std::declval<ArbiInt<65> &>().fill()),
                             ArbiInt<65> &>);
static_assert(std::is_same_v<decltype(std::declval<Unsigned &>().fill()),
                             Unsigned &>);
static_assert(std::is_same_v<decltype(std::declval<Unsigned &>().fill(1)),
                             Unsigned &>);
static_assert(std::is_same_v<decltype(std::declval<Complex &>().fill()),
                             Complex &>);
static_assert(std::is_same_v<decltype(std::declval<Vector &>().clear()),
                             Vector &>);
static_assert(std::is_same_v<decltype(std::declval<Vector &>().fill()),
                             Vector &>);
static_assert(std::is_same_v<decltype(std::declval<Vector &>().shuffle()),
                             Vector &>);
static_assert(dim<2, 3>::absoluteIndex<1, 2> == 5);

TEST(IntegralConstruction, WideUnsignedValuesStayPositiveAndExact)
{
    constexpr auto maximum = std::numeric_limits<uint64_t>::max();

    const ArbiInt<65> raw(maximum);
    EXPECT_FALSE(raw.isNegative());
    EXPECT_EQ(raw.toString(), "18446744073709551615");

    using U64 = Qu<intBits<64>, fracBits<0>, isSigned<false>>;
    EXPECT_EQ(U64(maximum).data.toString(), "18446744073709551615");
    EXPECT_EQ(U64(uint64_t{9007199254740993}).data.toString(),
              "9007199254740993");
}

TEST(IntegralConstruction, NegativeSignedValuesStillSignExtend)
{
    const ArbiInt<65> value(int64_t{-1});
    EXPECT_TRUE(value.isNegative());
    EXPECT_EQ(value.toString(), "-1");
}

TEST(Mutators, ReturnTheirObjectAndUnsignedFillNeverCreatesANegativeValue)
{
    Unsigned scalar;
    for (int i = 0; i < 256; ++i)
    {
        EXPECT_EQ(&scalar.fill(), &scalar);
        EXPECT_FALSE(scalar.data.isNegative());
    }

    EXPECT_EQ(&scalar.fill(-1), &scalar);
    EXPECT_FALSE(scalar.data.isNegative());
    EXPECT_DOUBLE_EQ(scalar.toDouble(), 7.0);

    Vector vector;
    EXPECT_EQ(&vector.fill(), &vector);
    for (const auto &value : vector.data)
        EXPECT_FALSE(value.data.isNegative());
    EXPECT_EQ(&vector.shuffle(), &vector);
    EXPECT_EQ(&vector.clear(), &vector);
}

TEST(FullPrecision, SignedMinimumTimesItselfKeepsThePositiveEndpoint)
{
    using SignBit =
        Qu<intBits<0>, fracBits<0>, isSigned<true>, OfMode<WRP::TCPL>>;

    const auto product = Qmul<FullPrec>(SignBit(-1), SignBit(-1));
    static_assert(decltype(product)::intB == 1);
    static_assert(decltype(product)::isS);
    EXPECT_DOUBLE_EQ(product.toDouble(), 1.0);
}

TEST(FullPrecision, UnsignedSubtractionProducesAnExactSignedResult)
{
    using U2 = Qu<intBits<2>, fracBits<0>, isSigned<false>>;

    const auto difference = Qsub<FullPrec>(U2(1), U2(2));
    static_assert(decltype(difference)::intB == 2);
    static_assert(decltype(difference)::isS);
    EXPECT_DOUBLE_EQ(difference.toDouble(), -1.0);
}

TEST(Negation, UnsignedInputBecomesSignedAndExplicitOutputTagsAreHonored)
{
    using U2 = Qu<intBits<2>, fracBits<0>, isSigned<false>>;

    const auto inferred = Qneg(U2(3));
    static_assert(decltype(inferred)::intB == 2);
    static_assert(decltype(inferred)::isS);
    EXPECT_DOUBLE_EQ(inferred.toDouble(), -3.0);

    using Explicit =
        Qu<intBits<5>, fracBits<2>, isSigned<true>, QuMode<RND::CONV>,
           OfMode<SAT::TCPL>>;
    const auto explicitResult = Qneg<Explicit>(U2(3));
    static_assert(std::is_same_v<decltype(explicitResult), const Explicit>);
    EXPECT_DOUBLE_EQ(explicitResult.toDouble(), -3.0);
}

TEST(ComplexMultiplication, ThreeMultiplyFormHonorsTheBaIntermediateTag)
{
    using Scalar =
        Qu<intBits<4>, fracBits<0>, isSigned<true>, OfMode<SAT::TCPL>>;
    using Narrow =
        Qu<intBits<1>, fracBits<0>, isSigned<true>, OfMode<SAT::TCPL>>;
    using C = Qcomplex<Scalar, Scalar>;

    const auto result = Qmul<TFComplexMul<baT<Narrow>>>(
        C{Scalar(-7), Scalar(7)}, C{Scalar(0), Scalar(1)});

    EXPECT_DOUBLE_EQ(result.real.toDouble(), -7.0);
    EXPECT_DOUBLE_EQ(result.imag.toDouble(), 6.0);
}

} // namespace
