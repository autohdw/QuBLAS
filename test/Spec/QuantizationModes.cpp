#include <gtest/gtest.h>

#include "QuBLAS.h"

using namespace QuBLAS;

namespace {

using Fine = Qu<intBits<4>, fracBits<3>, isSigned<true>,
                QuMode<TRN::TCPL>, OfMode<SAT::TCPL>>;

template <typename Mode>
double quantize(double value)
{
    using Coarse = Qu<intBits<4>, fracBits<1>, isSigned<true>,
                      QuMode<Mode>, OfMode<SAT::TCPL>>;

    const Fine source = value;
    const Coarse result = source;
    return result.toDouble();
}

} // namespace

TEST(SpecQuantization, RndPosInfTiesChooseTheGreaterValue)
{
    EXPECT_DOUBLE_EQ(quantize<RND::POS_INF>(1.25), 1.5);
    EXPECT_DOUBLE_EQ(quantize<RND::POS_INF>(-1.25), -1.0);
}

TEST(SpecQuantization, RndNegInfTiesChooseTheSmallerValue)
{
    EXPECT_DOUBLE_EQ(quantize<RND::NEG_INF>(1.25), 1.0);
    EXPECT_DOUBLE_EQ(quantize<RND::NEG_INF>(-1.25), -1.5);
}

TEST(SpecQuantization, RndZeroTiesChooseTheSmallerMagnitude)
{
    EXPECT_DOUBLE_EQ(quantize<RND::ZERO>(1.25), 1.0);
    EXPECT_DOUBLE_EQ(quantize<RND::ZERO>(-1.25), -1.0);
}

TEST(SpecQuantization, RndInfTiesChooseTheGreaterMagnitude)
{
    EXPECT_DOUBLE_EQ(quantize<RND::INF>(1.25), 1.5);
    EXPECT_DOUBLE_EQ(quantize<RND::INF>(-1.25), -1.5);
}

TEST(SpecQuantization, RndConvTiesChooseAnEvenResultLsb)
{
    EXPECT_DOUBLE_EQ(quantize<RND::CONV>(1.25), 1.0);
    EXPECT_DOUBLE_EQ(quantize<RND::CONV>(1.75), 2.0);
    EXPECT_DOUBLE_EQ(quantize<RND::CONV>(-1.25), -1.0);
    EXPECT_DOUBLE_EQ(quantize<RND::CONV>(-1.75), -2.0);
}

TEST(SpecQuantization, RndModesUseNearestAwayFromTies)
{
    EXPECT_DOUBLE_EQ(quantize<RND::POS_INF>(1.125), 1.0);
    EXPECT_DOUBLE_EQ(quantize<RND::NEG_INF>(1.375), 1.5);
    EXPECT_DOUBLE_EQ(quantize<RND::ZERO>(-1.125), -1.0);
    EXPECT_DOUBLE_EQ(quantize<RND::INF>(-1.375), -1.5);
    EXPECT_DOUBLE_EQ(quantize<RND::CONV>(1.375), 1.5);
}

TEST(SpecQuantization, TrnTcplIsTwosComplementFloor)
{
    EXPECT_DOUBLE_EQ(quantize<TRN::TCPL>(1.375), 1.0);
    EXPECT_DOUBLE_EQ(quantize<TRN::TCPL>(-1.375), -1.5);
}

TEST(SpecQuantization, TrnSmgnTruncatesMagnitudeTowardZero)
{
    EXPECT_DOUBLE_EQ(quantize<TRN::SMGN>(1.375), 1.0);
    EXPECT_DOUBLE_EQ(quantize<TRN::SMGN>(-1.375), -1.0);
}

TEST(SpecQuantization, DefaultModeIsTrnTcpl)
{
    using DefaultCoarse =
        Qu<intBits<4>, fracBits<1>, isSigned<true>, OfMode<SAT::TCPL>>;

    const Fine source = -1.375;
    const DefaultCoarse result = source;
    EXPECT_DOUBLE_EQ(result.toDouble(), -1.5);
}
