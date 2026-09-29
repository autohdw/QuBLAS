#include <gtest/gtest.h>

#include <array>
#include <bit>
#include <cmath>
#include <cstdint>
#include <limits>
#include <random>
#include <thread>
#include <vector>

#include "QuBLAS.h"

using namespace QuBLAS;

namespace {

// Keep the former, exact 2099-bit conversion as a structurally independent
// oracle. The production path must not need this intermediate any more.
template <typename Value>
auto wideReference(double input)
{
    ArbiInt<2099> exact;
    exact.template loadFromDouble<1074>(input);
    const auto quantized =
        fracConvert<1074, Value::fracB, QuMode<typename Value::QuM_t>>::convert(exact);
    return intConvert<Value::intB, Value::fracB, Value::isS,
                      OfMode<typename Value::OfM_t>>::convert(quantized);
}

const auto &conversionInputs()
{
    static const auto inputs = [] {
        std::vector<double> result;
        // Includes both zeros, subnormal / normal boundaries, infinities and
        // quiet / signaling NaNs, with both signs and nonzero payloads.
        for (uint64_t raw : {0ull, 1ull, 2ull, 0x000fffffffffffffull,
                             0x0010000000000000ull, 0x0010000000000001ull,
                             0x7fefffffffffffffull, 0x7ff0000000000000ull,
                             0x7ff0000000000001ull, 0x7ff8000000001234ull})
        {
            result.push_back(std::bit_cast<double>(raw));
            result.push_back(std::bit_cast<double>(raw | (uint64_t{1} << 63)));
        }
        std::mt19937_64 random(0x51624c4153);
        for (int i = 0; i < 1024; ++i)
            result.push_back(std::bit_cast<double>(random()));
        return result;
    }();
    return inputs;
}

template <int I, int F, bool Signed, typename Q, typename O>
void expectMatchesWideReference()
{
    using Value = Qu<intBits<I>, fracBits<F>, isSigned<Signed>, QuMode<Q>, OfMode<O>>;
    SCOPED_TRACE((::testing::Message() << "I=" << I << ", F=" << F
                  << ", signed=" << Signed << ", Q=" << Q::value << ", O=" << O::value));
    auto inputs = conversionInputs();
    // Exact ties, their two neighbors, rounding carries, and both range
    // boundaries. Also exercise negative intBits and negative fracBits.
    for (double raw : {0.5, 1.0, 1.5, 2.5, 3.5})
        inputs.push_back(std::ldexp(raw, -F));
    inputs.push_back(std::ldexp(1.0, I));
    inputs.push_back(std::ldexp(1.0, I) - std::ldexp(0.5, -F));
    const size_t boundaries = inputs.size();
    for (size_t i = conversionInputs().size(); i < boundaries; ++i)
    {
        const double value = inputs[i];
        inputs.push_back(-value);
        inputs.push_back(std::nextafter(value, 0.0));
        inputs.push_back(-std::nextafter(value, 0.0));
        inputs.push_back(std::nextafter(value, std::numeric_limits<double>::infinity()));
        inputs.push_back(-std::nextafter(value, std::numeric_limits<double>::infinity()));
    }
    for (double input : inputs)
    {
        const auto expected = wideReference<Value>(input);
        const Value actual(input);
        ASSERT_EQ(actual.data.data, expected.data)
            << "input bits: " << std::hex << std::bit_cast<uint64_t>(input);
    }
}

template <typename Q, bool Signed>
void expectAllOverflowModes()
{
    expectMatchesWideReference<5, 8, Signed, Q, SAT::TCPL>();
    expectMatchesWideReference<5, 8, Signed, Q, SAT::ZERO>();
    expectMatchesWideReference<5, 8, Signed, Q, SAT::SMGN>();
    expectMatchesWideReference<5, 8, Signed, Q, WRP::TCPL>();
    expectMatchesWideReference<5, 8, Signed, Q, WRP::TCPL_SAT<2>>();
}

template <typename Q>
void expectBothSignsAndAllOverflowModes()
{
    expectAllOverflowModes<Q, true>();
    expectAllOverflowModes<Q, false>();
}

template <int Width>
void expectStorageBoundary()
{
    expectMatchesWideReference<5, Width - 6, true, RND::CONV, SAT::TCPL>();
    expectMatchesWideReference<5, Width - 6, true, TRN::TCPL, WRP::TCPL>();
    expectMatchesWideReference<5, Width - 6, false, RND::INF, WRP::TCPL>();
    expectMatchesWideReference<5, Width - 6, true, TRN::SMGN, WRP::TCPL_SAT<70>>();
    expectMatchesWideReference<5, Width - 6, false, RND::ZERO, WRP::TCPL_SAT<70>>();
}

using ConstexprValue = Qu<intBits<4>, fracBits<0>, QuMode<RND::CONV>, OfMode<SAT::TCPL>>;
static_assert(ConstexprValue(2.5).data.data[0] == 2);
static_assert(ConstexprValue(3.5).data.data[0] == 4);
static_assert(ConstexprValue(-2.5).data.data[0] == uint64_t(-2));
static_assert(ConstexprValue(16.0).data.data[0] == 15);
static_assert(ConstexprValue(-16.0).data.data[0] == uint64_t(-16));
static_assert(ConstexprValue(std::numeric_limits<double>::infinity()).data.isZero());
static_assert(ConstexprValue(std::numeric_limits<double>::quiet_NaN()).data.isZero());

} // namespace

TEST(DoubleConversion, AllQuantizationAndOverflowModesMatchExactWideReference)
{
    expectBothSignsAndAllOverflowModes<RND::POS_INF>();
    expectBothSignsAndAllOverflowModes<RND::NEG_INF>();
    expectBothSignsAndAllOverflowModes<RND::ZERO>();
    expectBothSignsAndAllOverflowModes<RND::INF>();
    expectBothSignsAndAllOverflowModes<RND::CONV>();
    expectBothSignsAndAllOverflowModes<TRN::TCPL>();
    expectBothSignsAndAllOverflowModes<TRN::SMGN>();
}

TEST(DoubleConversion, LogicalAndPhysicalWidthBoundariesMatchExactWideReference)
{
    expectStorageBoundary<1>();
    expectStorageBoundary<2>();
    expectStorageBoundary<31>();
    expectStorageBoundary<32>();
    expectStorageBoundary<33>();
    expectStorageBoundary<63>();
    expectStorageBoundary<64>();
    expectStorageBoundary<65>();
    expectStorageBoundary<127>();
    expectStorageBoundary<128>();
    expectStorageBoundary<129>();
}

TEST(DoubleConversion, ExtremeScalesMatchExactWideReference)
{
    expectMatchesWideReference<0, 1073, true, RND::CONV, SAT::SMGN>();
    expectMatchesWideReference<0, 1074, false, TRN::TCPL, SAT::TCPL>();
    expectMatchesWideReference<1, 1300, true, RND::POS_INF, WRP::TCPL>();
    expectMatchesWideReference<-1290, 1300, true, RND::NEG_INF, SAT::ZERO>();
    expectMatchesWideReference<1310, -1300, true, TRN::TCPL, SAT::TCPL>();
    expectMatchesWideReference<1310, -1300, true, TRN::SMGN, SAT::TCPL>();
    expectMatchesWideReference<1310, -1300, false, RND::INF, WRP::TCPL>();
    expectMatchesWideReference<2010, -2000, true, RND::ZERO, SAT::SMGN>();
}

TEST(DoubleConversion, WrapSaturationCountsRetainTheirExistingMeaning)
{
    expectMatchesWideReference<3, 2, true, TRN::TCPL, WRP::TCPL_SAT<0>>();
    expectMatchesWideReference<3, 2, false, TRN::TCPL, WRP::TCPL_SAT<-2>>();
    expectMatchesWideReference<3, 2, true, TRN::TCPL, WRP::TCPL_SAT<1>>();
    expectMatchesWideReference<3, 2, false, TRN::TCPL, WRP::TCPL_SAT<1>>();
    expectMatchesWideReference<3, 2, true, TRN::TCPL, WRP::TCPL_SAT<100>>();
    expectMatchesWideReference<3, 2, false, TRN::TCPL, WRP::TCPL_SAT<100>>();
}

TEST(DoubleConversion, EveryExponentAndSignMatchExactWideReference)
{
    using FloorWrap = Qu<intBits<5>, fracBits<8>>;
    using EvenSaturate = Qu<intBits<5>, fracBits<8>, QuMode<RND::CONV>, OfMode<SAT::TCPL>>;
    for (uint64_t exponent = 0; exponent < 2048; ++exponent)
    {
        for (uint64_t fraction : {0ull, 1ull, 0x000aaaaaaaaaaaaaull, 0x000fffffffffffffull})
        {
            for (uint64_t sign : {0ull, 1ull})
            {
                const uint64_t bits = (sign << 63) | (exponent << 52) | fraction;
                const double input = std::bit_cast<double>(bits);
                ASSERT_EQ(FloorWrap(input).data.data, wideReference<FloorWrap>(input).data)
                    << "input bits: " << std::hex << bits;
                ASSERT_EQ(EvenSaturate(input).data.data, wideReference<EvenSaturate>(input).data)
                    << "input bits: " << std::hex << bits;
            }
        }
    }
}

TEST(DoubleConversion, LoadsNormalValuesWithPositiveAndNegativeBinaryScales)
{
    ArbiInt<128> positive;
    positive.template loadFromDouble<20>(1.5);
    EXPECT_EQ(positive.toString(), "1572864");

    ArbiInt<128> negative;
    negative.template loadFromDouble<20>(-1.5);
    EXPECT_EQ(negative.toString(), "-1572864");

    ArbiInt<128> belowOne;
    belowOne.template loadFromDouble<-20>(1.0);
    EXPECT_TRUE(belowOne.isZero());
}

TEST(DoubleConversion, DoesNotAddAnImplicitBitToSubnormals)
{
    ArbiInt<128> tooCoarse;
    tooCoarse.template loadFromDouble<0>(std::numeric_limits<double>::denorm_min());
    EXPECT_TRUE(tooCoarse.isZero());

    ArbiInt<1152> exact;
    exact.template loadFromDouble<1074>(std::numeric_limits<double>::denorm_min());
    EXPECT_EQ(exact.toString(), "1");

    ArbiInt<1152> exactNegative;
    exactNegative.template loadFromDouble<1074>(-std::numeric_limits<double>::denorm_min());
    EXPECT_EQ(exactNegative.toString(), "-1");
}

TEST(DoubleConversion, ConstructsExactSmallestSubnormalAtFrac1074)
{
    using Value = Qu<intBits<0>, fracBits<1074>, isSigned<false>,
                     QuMode<TRN::TCPL>, OfMode<SAT::TCPL>>;

    const Value value(std::numeric_limits<double>::denorm_min());
    EXPECT_EQ(value.data.toString(), "1");
    EXPECT_EQ(value.toDouble(), std::numeric_limits<double>::denorm_min());
}

TEST(DoubleConversion, QuantizesSubnormalHalfwayCasesAfterExactDecoding)
{
    using Value = Qu<intBits<0>, fracBits<1073>, isSigned<true>,
                     QuMode<RND::POS_INF>, OfMode<SAT::TCPL>>;

    const Value positive(std::numeric_limits<double>::denorm_min());
    const Value negative(-std::numeric_limits<double>::denorm_min());
    EXPECT_EQ(positive.data.toString(), "1");
    EXPECT_EQ(negative.data.toString(), "0");
}

TEST(DoubleConversion, SupportsFractionWidthsBeyondFormerGuardBuffer)
{
    using Value = Qu<intBits<1>, fracBits<1300>, isSigned<true>,
                     QuMode<TRN::TCPL>, OfMode<SAT::TCPL>>;

    const Value value(1.0);
    const ArbiInt<1302> expected(staticShiftLeft<1300>(ArbiInt<1>(1)));
    EXPECT_EQ(value.data.toString(), expected.toString());
    EXPECT_DOUBLE_EQ(value.toDouble(), 1.0);
}

TEST(DoubleConversion, AppliesScaleBeforeAWideIntegerCanOverflowDouble)
{
    ArbiInt<1408> raw(staticShiftLeft<1300>(ArbiInt<1>(1)));
    EXPECT_DOUBLE_EQ(raw.toDoubleScaled(-1300), 1.0);
}

TEST(DoubleConversion, RoundsAcrossLimbsWithoutLosingStickyBits)
{
    ArbiInt<129> exactTie;
    exactTie.data[1] = (uint64_t{1} << 63) | 1024;
    EXPECT_DOUBLE_EQ(exactTie.toDouble(), std::ldexp(1.0, 127));

    ArbiInt<129> aboveTie = exactTie;
    aboveTie.data[0] = 1;
    EXPECT_DOUBLE_EQ(aboveTie.toDouble(),
                     std::ldexp(1.0, 127) + std::ldexp(1.0, 75));
}

TEST(DoubleConversion, RoundsDirectlyAtTheSubnormalQuantum)
{
    EXPECT_DOUBLE_EQ(ArbiInt<65>(1).toDoubleScaled(-1075), 0.0);
    EXPECT_DOUBLE_EQ(ArbiInt<65>(3).toDoubleScaled(-1075),
                     2 * std::numeric_limits<double>::denorm_min());

    ArbiInt<65> halfwayToNormal((uint64_t{1} << 53) - 1);
    EXPECT_DOUBLE_EQ(halfwayToNormal.toDoubleScaled(-1075),
                     std::numeric_limits<double>::min());

    // Rounding the integer to binary64 first would erase the sticky bit and
    // then round this value a second time in the wrong direction.
    ArbiInt<64> smallStorage;
    smallStorage.data[0] = static_cast<uint64_t>((uint64_t{1} << 62) + 1025);
    const double expected = std::ldexp(
        static_cast<double>((uint64_t{1} << 51) + 1), -1074);
    EXPECT_DOUBLE_EQ(smallStorage.toDoubleScaled(-1085), expected);
}

TEST(RandomState, ConcurrentFillAndShuffleUseIndependentThreadState)
{
    using Scalar = Qu<intBits<8>, fracBits<8>>;
    using Vector = Qu<dim<32>, Scalar>;

    std::array<double, 4> checksums{};
    std::vector<std::thread> workers;
    for (size_t worker = 0; worker < checksums.size(); ++worker)
    {
        workers.emplace_back([worker, &checksums] {
            Vector values;
            for (int iteration = 0; iteration < 100; ++iteration)
            {
                values.fill();
                values.shuffle();
            }

            double sum = 0;
            for (size_t i = 0; i < 32; ++i)
                sum += values[i].toDouble();
            checksums[worker] = sum;
        });
    }

    for (auto &worker : workers)
        worker.join();

    for (double checksum : checksums)
        EXPECT_TRUE(std::isfinite(checksum));
}

TEST(RandomState, WideFillSignExtendsTheLogicalTopLimb)
{
    ArbiInt<70> value;
    bool sawPositive = false;
    bool sawNegative = false;
    constexpr uint64_t logicalMask = (uint64_t{1} << 6) - 1;
    constexpr uint64_t signBit = uint64_t{1} << 5;

    for (int i = 0; i < 1000; ++i)
    {
        value.fill();
        const uint64_t top = value.data[1];
        if ((top & signBit) != 0)
        {
            EXPECT_EQ(top & ~logicalMask, ~logicalMask);
            sawNegative = true;
        }
        else
        {
            EXPECT_EQ(top & ~logicalMask, 0);
            sawPositive = true;
        }
    }

    EXPECT_TRUE(sawPositive);
    EXPECT_TRUE(sawNegative);
    EXPECT_FALSE(ArbiInt<70>{}.isPositive());
}
