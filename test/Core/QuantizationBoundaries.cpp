#include "QuBLAS.h"
#include <gtest/gtest.h>

using namespace QuBLAS;

namespace {

template <int Discarded>
void expectTieModesAtLimbBoundary()
{
    const auto unit = staticShiftLeft<Discarded>(ArbiInt<2>(1));
    const auto half = quantizationHalf<Discarded>();
    const auto positive_tie = unit + half; // +1.5 in the target scale
    const auto negative_tie = -positive_tie;

    EXPECT_EQ((fracConvert<Discarded, 0, QuMode<RND::POS_INF>>::convert(positive_tie)).toString(), "2");
    EXPECT_EQ((fracConvert<Discarded, 0, QuMode<RND::POS_INF>>::convert(negative_tie)).toString(), "-1");
    EXPECT_EQ((fracConvert<Discarded, 0, QuMode<RND::NEG_INF>>::convert(positive_tie)).toString(), "1");
    EXPECT_EQ((fracConvert<Discarded, 0, QuMode<RND::NEG_INF>>::convert(negative_tie)).toString(), "-2");
    EXPECT_EQ((fracConvert<Discarded, 0, QuMode<RND::ZERO>>::convert(positive_tie)).toString(), "1");
    EXPECT_EQ((fracConvert<Discarded, 0, QuMode<RND::ZERO>>::convert(negative_tie)).toString(), "-1");
    EXPECT_EQ((fracConvert<Discarded, 0, QuMode<RND::INF>>::convert(positive_tie)).toString(), "2");
    EXPECT_EQ((fracConvert<Discarded, 0, QuMode<RND::INF>>::convert(negative_tie)).toString(), "-2");
    EXPECT_EQ((fracConvert<Discarded, 0, QuMode<RND::CONV>>::convert(positive_tie)).toString(), "2");
    EXPECT_EQ((fracConvert<Discarded, 0, QuMode<RND::CONV>>::convert(negative_tie)).toString(), "-2");
    EXPECT_EQ((fracConvert<Discarded, 0, QuMode<TRN::TCPL>>::convert(positive_tie)).toString(), "1");
    EXPECT_EQ((fracConvert<Discarded, 0, QuMode<TRN::TCPL>>::convert(negative_tie)).toString(), "-2");
    EXPECT_EQ((fracConvert<Discarded, 0, QuMode<TRN::SMGN>>::convert(positive_tie)).toString(), "1");
    EXPECT_EQ((fracConvert<Discarded, 0, QuMode<TRN::SMGN>>::convert(negative_tie)).toString(), "-1");
}

} // namespace

TEST(QuantizationBoundaries, TiesAt32DiscardedBits)
{
    expectTieModesAtLimbBoundary<32>();
}

TEST(QuantizationBoundaries, TiesAt64DiscardedBits)
{
    expectTieModesAtLimbBoundary<64>();
}

TEST(QuantizationBoundaries, TiesAt128DiscardedBits)
{
    expectTieModesAtLimbBoundary<128>();
}
