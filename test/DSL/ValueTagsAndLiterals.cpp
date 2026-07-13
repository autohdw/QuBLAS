#include "QuBLAS.h"

#include <gtest/gtest.h>

#include <type_traits>

using namespace QuBLAS;

namespace {

using Modern = Q<8_i, 4_f, signed_, rnd::conv, sat::tcpl>;
using Legacy = Qu<intBits<8>, fracBits<4>, isSigned<true>,
                  QuMode<RND::CONV>, OfMode<SAT::TCPL>>;
static_assert(std::is_same_v<Modern, Legacy>);

using Shuffled = Q<wrp::tcpl_sat<2>, -3_f, 6_i, trn::smgn, unsigned_>;
using ShuffledLegacy =
    Qu<intBits<6>, fracBits<-3>, isSigned<false>, QuMode<TRN::SMGN>,
       OfMode<WRP::TCPL_SAT<2>>>;
static_assert(std::is_same_v<Shuffled, ShuffledLegacy>);

static_assert(QValueTagPack<>);
static_assert(!QValueTagPack<8_i, 9_i>);
static_assert(!QValueTagPack<4_f, -3_f>);
static_assert(!QValueTagPack<signed_, unsigned_>);
static_assert(!QValueTagPack<rnd::conv, trn::tcpl>);
static_assert(!QValueTagPack<sat::tcpl, wrp::tcpl>);
static_assert(!QValueTagPack<42>);

constexpr auto exact = "1101.101"_bq | to<Modern>;
constexpr auto negative = "-1.101"_bq | to<Modern>;
constexpr auto decimal = "3.1415"_dq | to<Modern>;
static_assert(exact.data == decltype(exact.data){218}); // 13.625 * 2^4
static_assert(negative.data == decltype(negative.data){-26}); // -1.625 * 2^4
static_assert(decimal.data == decltype(decimal.data){50}); // convergent round(3.1415 * 16)

TEST(ValueTagDsl, MapsToTheLegacyTypeGrammar)
{
    EXPECT_DOUBLE_EQ(exact.toDouble(), 13.625);
    EXPECT_DOUBLE_EQ(negative.toDouble(), -1.625);
}

TEST(DecimalLiteralDsl, QuantizesAnExactCompileTimeRational)
{
    using Fine = Q<4_i, 10_f, signed_, rnd::conv, sat::tcpl>;
    constexpr auto pi = "3.1415"_dq | to<Fine>;
    constexpr auto negativePi = "-3.1415"_dq | to<Fine>;

    EXPECT_DOUBLE_EQ(pi.toDouble(), 3.1416015625);
    EXPECT_DOUBLE_EQ(negativePi.toDouble(), -3.1416015625);
}

TEST(DecimalLiteralDsl, HasNoMachineIntegerLengthLimit)
{
    using Huge = Q<100_i, 3_f, signed_, rnd::conv, sat::tcpl>;
    constexpr auto huge =
        "123456789012345678901234567890.125"_dq | to<Huge>;
    constexpr auto longFraction =
        "0.1250000000000000000000000000000000000000"_dq |
        to<Q<1_i, 3_f, signed_, rnd::conv, sat::tcpl>>;

    EXPECT_EQ(huge.data.toString(), "987654312098765431209876543121");
    EXPECT_EQ(longFraction.data.toString(), "1");
}

TEST(BinaryLiteralDsl, AppliesTheTargetQuantizationAndOverflowPolicies)
{
    using RoundedUp = Q<1_i, 2_f, signed_, rnd::pos_inf, sat::tcpl>;
    using Saturated = Q<2_i, 0_f, signed_, trn::tcpl, sat::tcpl>;

    const auto rounded = ".001"_bq | to<RoundedUp>;
    const auto saturated = "101"_bq | to<Saturated>;

    EXPECT_DOUBLE_EQ(rounded.toDouble(), 0.25);
    EXPECT_DOUBLE_EQ(saturated.toDouble(), 3.0);
}

TEST(BinaryLiteralDsl, DoesNotRoundThroughDouble)
{
    using Wide = Q<64_i, 0_f, signed_, trn::tcpl, sat::tcpl>;
    constexpr auto wide =
        "100000000000000000000000000000000000000000000000000001"_bq |
        to<Wide>;

    EXPECT_EQ(wide.data.toString(), "9007199254740993");
}

} // namespace
