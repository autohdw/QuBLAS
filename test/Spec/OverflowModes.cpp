#include <gtest/gtest.h>

#include "QuBLAS.h"

using namespace QuBLAS;

namespace {

using WideSigned = Qu<intBits<6>, fracBits<0>, isSigned<true>,
                      QuMode<TRN::TCPL>, OfMode<SAT::TCPL>>;

template <typename Mode, bool Signed, int IntegerBits>
double overflowConvert(double value)
{
    using Target = Qu<intBits<IntegerBits>, fracBits<0>, isSigned<Signed>,
                      QuMode<TRN::TCPL>, OfMode<Mode>>;

    const WideSigned source = value;
    const Target result = source;
    return result.toDouble();
}

template <int N, bool Signed, int IntegerBits>
double wrapSaturatedConvert(double value)
{
    using Target = Qu<intBits<IntegerBits>, fracBits<0>, isSigned<Signed>,
                      QuMode<TRN::TCPL>, OfMode<WRP::TCPL_SAT<N>>>;

    const WideSigned source = value;
    const Target result = source;
    return result.toDouble();
}

} // namespace

TEST(SpecOverflow, SatTcplUsesTwosComplementSignedLimits)
{
    EXPECT_DOUBLE_EQ((overflowConvert<SAT::TCPL, true, 2>(3.0)), 3.0);
    EXPECT_DOUBLE_EQ((overflowConvert<SAT::TCPL, true, 2>(-4.0)), -4.0);
    EXPECT_DOUBLE_EQ((overflowConvert<SAT::TCPL, true, 2>(4.0)), 3.0);
    EXPECT_DOUBLE_EQ((overflowConvert<SAT::TCPL, true, 2>(-5.0)), -4.0);
}

TEST(SpecOverflow, SatZeroClearsSignedOverflowOnly)
{
    EXPECT_DOUBLE_EQ((overflowConvert<SAT::ZERO, true, 2>(3.0)), 3.0);
    EXPECT_DOUBLE_EQ((overflowConvert<SAT::ZERO, true, 2>(-4.0)), -4.0);
    EXPECT_DOUBLE_EQ((overflowConvert<SAT::ZERO, true, 2>(4.0)), 0.0);
    EXPECT_DOUBLE_EQ((overflowConvert<SAT::ZERO, true, 2>(-5.0)), 0.0);
}

TEST(SpecOverflow, SatSmgnUsesSymmetricSignedLimits)
{
    EXPECT_DOUBLE_EQ((overflowConvert<SAT::SMGN, true, 2>(3.0)), 3.0);
    EXPECT_DOUBLE_EQ((overflowConvert<SAT::SMGN, true, 2>(-3.0)), -3.0);
    EXPECT_DOUBLE_EQ((overflowConvert<SAT::SMGN, true, 2>(4.0)), 3.0);
    EXPECT_DOUBLE_EQ((overflowConvert<SAT::SMGN, true, 2>(-4.0)), -3.0);
    EXPECT_DOUBLE_EQ((overflowConvert<SAT::SMGN, true, 2>(-5.0)), -3.0);
}

TEST(SpecOverflow, SaturationModesUseZeroAsTheUnsignedLowerLimit)
{
    EXPECT_DOUBLE_EQ((overflowConvert<SAT::TCPL, false, 3>(8.0)), 7.0);
    EXPECT_DOUBLE_EQ((overflowConvert<SAT::TCPL, false, 3>(-1.0)), 0.0);

    EXPECT_DOUBLE_EQ((overflowConvert<SAT::ZERO, false, 3>(8.0)), 0.0);
    EXPECT_DOUBLE_EQ((overflowConvert<SAT::ZERO, false, 3>(-1.0)), 0.0);

    EXPECT_DOUBLE_EQ((overflowConvert<SAT::SMGN, false, 3>(8.0)), 7.0);
    EXPECT_DOUBLE_EQ((overflowConvert<SAT::SMGN, false, 3>(-1.0)), 0.0);
}

TEST(SpecOverflow, WrpTcplDropsOverflowBits)
{
    EXPECT_DOUBLE_EQ((overflowConvert<WRP::TCPL, true, 3>(8.0)), -8.0);
    EXPECT_DOUBLE_EQ((overflowConvert<WRP::TCPL, true, 3>(9.0)), -7.0);
    EXPECT_DOUBLE_EQ((overflowConvert<WRP::TCPL, true, 3>(-9.0)), 7.0);

    EXPECT_DOUBLE_EQ((overflowConvert<WRP::TCPL, false, 4>(16.0)), 0.0);
    EXPECT_DOUBLE_EQ((overflowConvert<WRP::TCPL, false, 4>(17.0)), 1.0);
    EXPECT_DOUBLE_EQ((overflowConvert<WRP::TCPL, false, 4>(-1.0)), 15.0);
}

TEST(SpecOverflow, DefaultModeIsWrpTcpl)
{
    using DefaultTarget =
        Qu<intBits<3>, fracBits<0>, isSigned<true>, QuMode<TRN::TCPL>>;

    const WideSigned source = 9.0;
    const DefaultTarget result = source;
    EXPECT_DOUBLE_EQ(result.toDouble(), -7.0);
}

TEST(SpecOverflow, WrpTcplSatOnePreservesSignedSignAndWrapsLowerBits)
{
    EXPECT_DOUBLE_EQ((wrapSaturatedConvert<1, true, 3>(9.0)), 1.0);
    EXPECT_DOUBLE_EQ((wrapSaturatedConvert<1, true, 3>(-9.0)), -1.0);

    EXPECT_DOUBLE_EQ((wrapSaturatedConvert<1, true, 3>(1.0)), 1.0);
    EXPECT_DOUBLE_EQ((wrapSaturatedConvert<1, true, 3>(-1.0)), -1.0);
}

TEST(SpecOverflow, WrpTcplSatTwoAlsoSaturatesTheNextSignedMsb)
{
    EXPECT_DOUBLE_EQ((wrapSaturatedConvert<2, true, 3>(9.0)), 5.0);
    EXPECT_DOUBLE_EQ((wrapSaturatedConvert<2, true, 3>(-9.0)), -5.0);

    EXPECT_DOUBLE_EQ((wrapSaturatedConvert<2, true, 3>(1.0)), 1.0);
    EXPECT_DOUBLE_EQ((wrapSaturatedConvert<2, true, 3>(-1.0)), -1.0);
}

TEST(SpecOverflow, WrpTcplSatSetsUnsignedHighBitsOnlyOnOverflow)
{
    EXPECT_DOUBLE_EQ((wrapSaturatedConvert<1, false, 4>(17.0)), 9.0);
    EXPECT_DOUBLE_EQ((wrapSaturatedConvert<2, false, 4>(17.0)), 13.0);

    EXPECT_DOUBLE_EQ((wrapSaturatedConvert<1, false, 4>(2.0)), 2.0);
    EXPECT_DOUBLE_EQ((wrapSaturatedConvert<2, false, 4>(2.0)), 2.0);
}
