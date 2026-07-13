#include "QuBLAS.h"
#include <gtest/gtest.h>

#include <array>
#include <limits>
#include <type_traits>

using namespace QuBLAS;

static_assert(std::is_same_v<decltype(ArbiInt<1>{}.data),
                             std::array<uint64_t, 1>>);
static_assert(std::is_same_v<decltype(ArbiInt<65>{}.data),
                             std::array<uint64_t, 2>>);
static_assert(std::is_same_v<decltype(ArbiInt<129>{}.data),
                             std::array<uint64_t, 3>>);

constexpr ArbiInt<1> arbiHeadroomOne(1);
static_assert(!arbiHeadroomOne.isNegative());
static_assert(arbiHeadroomOne.data[0] == 1);

constexpr ArbiInt<65> arbiUnsigned64Maximum(
    std::numeric_limits<uint64_t>::max());
constexpr auto arbiCarryAcrossLimb = arbiUnsigned64Maximum + ArbiInt<2>(1);
static_assert(decltype(arbiCarryAcrossLimb)::num_bits == 66);
static_assert(arbiCarryAcrossLimb.data[0] == 0);
static_assert(arbiCarryAcrossLimb.data[1] == 1);

constexpr auto arbiWideSquare = arbiUnsigned64Maximum * arbiUnsigned64Maximum;
static_assert(decltype(arbiWideSquare)::num_bits == 130);
static_assert(arbiWideSquare.data[0] == 1);
static_assert(arbiWideSquare.data[1] ==
              std::numeric_limits<uint64_t>::max() - 1);
static_assert(arbiWideSquare.data[2] == 0);

static_assert(ArbiInt<8>::allZeros() == ArbiInt<8>(0));
static_assert(ArbiInt<8>::allOnes() == ArbiInt<8>(-1));
static_assert(ArbiInt<65>::allZeros() == ArbiInt<65>(0));
static_assert(ArbiInt<65>::allOnes() == ArbiInt<65>(-1));

TEST(ArbiIntCore, LimbBoundaryMasksAreWellDefined)
{
    EXPECT_EQ(ArbiInt<8>::allOnes().toString(), "-1");
    EXPECT_EQ(ArbiInt<8>::allZeros().toString(), "0");
    EXPECT_EQ(ArbiInt<64>::allOnes().toString(), "-1");
    EXPECT_EQ(ArbiInt<64>::allZeros().toString(), "0");
    EXPECT_EQ(ArbiInt<65>::allOnes().toString(), "-1");
    EXPECT_EQ(ArbiInt<65>::allZeros().toString(), "0");
    EXPECT_EQ(ArbiInt<128>::allOnes().toString(), "-1");
    EXPECT_EQ(ArbiInt<128>::allZeros().toString(), "0");
}

TEST(ArbiIntCore, LeftShiftAtLimbBoundaryDoesNotWritePastResult)
{
    EXPECT_EQ(staticShiftLeft<31>(ArbiInt<8>(-1)).toString(), "-2147483648");
    EXPECT_EQ(staticShiftLeft<64>(ArbiInt<64>(1)).toString(),
              "18446744073709551616");
    EXPECT_EQ(staticShiftLeft<64>(ArbiInt<64>(-1)).toString(),
              "-18446744073709551616");
    EXPECT_EQ(staticShiftLeft<64>(ArbiInt<65>(-1)).toString(),
              "-18446744073709551616");
    EXPECT_EQ(staticShiftLeft<128>(ArbiInt<65>(-1)).toString(),
              "-340282366920938463463374607431768211456");
}

TEST(ArbiIntCore, SmallStringConstructionSignExtendsWithoutSignedShift)
{
    EXPECT_EQ(ArbiInt<8>("-1").toString(), "-1");
    EXPECT_EQ(ArbiInt<8>("127").toString(), "127");
    EXPECT_EQ(ArbiInt<8>("128").toString(), "-128");
}

TEST(ArbiIntCore, IntegralConstructionDoesNotRoundThroughDouble)
{
    constexpr uint64_t above_double_integer_precision = 9007199254740993ULL;
    const ArbiInt<64> value(above_double_integer_precision);
    EXPECT_EQ(value.toString(), "9007199254740993");
}

TEST(ArbiIntCore, MixedWidthArithmeticUsesSignExtension)
{
    const auto one = ArbiInt<128>(0) - ArbiInt<8>(-1);
    EXPECT_EQ(one.toString(), "1");

    const auto wide = staticShiftLeft<64>(ArbiInt<2>(1));
    EXPECT_NE(wide, ArbiInt<2>(0));
    EXPECT_GT(wide, ArbiInt<2>(0));

    const ArbiInt<128> value("18446744073709551616");
    EXPECT_EQ((value & ArbiInt<8>(-1)).toString(), value.toString());
    EXPECT_EQ((value | ArbiInt<8>(-1)).toString(), "-1");
    EXPECT_EQ((value ^ ArbiInt<8>(-1)).toString(), "-18446744073709551617");
}

TEST(ArbiIntCore, UnifiedLimbsKeepCarryBorrowAndSignedProductExact)
{
    EXPECT_EQ(arbiCarryAcrossLimb.toString(), "18446744073709551616");

    const auto borrowed = ArbiInt<65>(0) - arbiUnsigned64Maximum;
    EXPECT_EQ(borrowed.toString(), "-18446744073709551615");

    EXPECT_EQ(arbiWideSquare.toString(),
              "340282366920938463426481119284349108225");

    const auto positiveEndpoint = ArbiInt<65>::minimum() * ArbiInt<2>(-1);
    EXPECT_EQ(positiveEndpoint.toString(), "18446744073709551616");
}

TEST(ArbiIntCore, WideNegationSignExtendsIntoPromotedBit)
{
    EXPECT_EQ((-ArbiInt<128>(1)).toString(), "-1");
    EXPECT_EQ((-ArbiInt<128>(-1)).toString(), "1");
}

TEST(ArbiIntCore, DivmodSupportsWideSignedOperands)
{
    const ArbiInt<128> positive("123456789012345678901234567890");
    const ArbiInt<64> negative_divisor(-1234567891LL);
    const auto result = divmod(positive, negative_divisor);
    EXPECT_EQ(result.quotient.toString(), "-99999999928999999321");
    EXPECT_EQ(result.remainder.toString(), "506165879");

    const ArbiInt<128> negative("-123456789012345678901234567890");
    const auto negative_result = divmod(negative, ArbiInt<64>(1234567891LL));
    EXPECT_EQ(negative_result.quotient.toString(), "-99999999928999999321");
    EXPECT_EQ(negative_result.remainder.toString(), "-506165879");
}

TEST(ArbiIntCore, DivmodHasRoomForMinimumDividedByMinusOne)
{
    const auto result = divmod(ArbiInt<128>::minimum(), ArbiInt<2>(-1));
    EXPECT_EQ(result.quotient.toString(),
              "170141183460469231731687303715884105728");
    EXPECT_EQ(result.remainder.toString(), "0");
}

TEST(ArbiIntCore, DivisionByZeroThrows)
{
    EXPECT_THROW((void)divmod(ArbiInt<128>(7), ArbiInt<8>(0)), std::domain_error);
}
