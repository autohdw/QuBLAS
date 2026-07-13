#include <gtest/gtest.h>

#include <array>
#include <limits>
#include <thread>
#include <vector>

#include "QuBLAS.h"

using namespace QuBLAS;

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
