#include <gtest/gtest.h>

#include "QuBLAS.h"

using namespace QuBLAS;

namespace {

using Operand = Qu<intBits<5>, fracBits<0>, isSigned<true>,
                   QuMode<TRN::TCPL>, OfMode<SAT::TCPL>>;

template <typename Mode>
double divide(int numerator, int denominator)
{
    const Operand lhs = static_cast<double>(numerator);
    const Operand rhs = static_cast<double>(denominator);

    return Qdiv<intBits<5>, fracBits<0>, isSigned<true>,
                QuMode<Mode>, OfMode<SAT::TCPL>>(lhs, rhs)
        .toDouble();
}

template <typename Mode, int TargetFrac>
double divideTo(int numerator, int denominator)
{
    const Operand lhs = static_cast<double>(numerator);
    const Operand rhs = static_cast<double>(denominator);

    return Qdiv<intBits<5>, fracBits<TargetFrac>, isSigned<true>,
                QuMode<Mode>, OfMode<SAT::TCPL>>(lhs, rhs)
        .toDouble();
}

} // namespace

TEST(SpecDivision, RndPosInfAppliesItsTieRuleToTheRemainder)
{
    EXPECT_DOUBLE_EQ(divide<RND::POS_INF>(3, 2), 2.0);
    EXPECT_DOUBLE_EQ(divide<RND::POS_INF>(-3, 2), -1.0);
}

TEST(SpecDivision, RndNegInfAppliesItsTieRuleToTheRemainder)
{
    EXPECT_DOUBLE_EQ(divide<RND::NEG_INF>(3, 2), 1.0);
    EXPECT_DOUBLE_EQ(divide<RND::NEG_INF>(-3, 2), -2.0);
}

TEST(SpecDivision, RndZeroAppliesItsTieRuleToTheRemainder)
{
    EXPECT_DOUBLE_EQ(divide<RND::ZERO>(3, 2), 1.0);
    EXPECT_DOUBLE_EQ(divide<RND::ZERO>(-3, 2), -1.0);
}

TEST(SpecDivision, RndInfAppliesItsTieRuleToTheRemainder)
{
    EXPECT_DOUBLE_EQ(divide<RND::INF>(3, 2), 2.0);
    EXPECT_DOUBLE_EQ(divide<RND::INF>(-3, 2), -2.0);
}

TEST(SpecDivision, RndConvChoosesAnEvenQuotientAtTies)
{
    EXPECT_DOUBLE_EQ(divide<RND::CONV>(3, 2), 2.0);
    EXPECT_DOUBLE_EQ(divide<RND::CONV>(5, 2), 2.0);
    EXPECT_DOUBLE_EQ(divide<RND::CONV>(-3, 2), -2.0);
    EXPECT_DOUBLE_EQ(divide<RND::CONV>(-5, 2), -2.0);
}

TEST(SpecDivision, RndModesRoundToNearestAwayFromTies)
{
    EXPECT_DOUBLE_EQ(divide<RND::POS_INF>(5, 4), 1.0);
    EXPECT_DOUBLE_EQ(divide<RND::NEG_INF>(7, 4), 2.0);
    EXPECT_DOUBLE_EQ(divide<RND::ZERO>(-5, 4), -1.0);
    EXPECT_DOUBLE_EQ(divide<RND::INF>(-7, 4), -2.0);
    EXPECT_DOUBLE_EQ(divide<RND::CONV>(7, 4), 2.0);
}

TEST(SpecDivision, TrnTcplFloorsNegativeQuotients)
{
    EXPECT_DOUBLE_EQ(divide<TRN::TCPL>(3, 2), 1.0);
    EXPECT_DOUBLE_EQ(divide<TRN::TCPL>(-3, 2), -2.0);
}

TEST(SpecDivision, TrnSmgnTruncatesNegativeQuotientsTowardZero)
{
    EXPECT_DOUBLE_EQ(divide<TRN::SMGN>(3, 2), 1.0);
    EXPECT_DOUBLE_EQ(divide<TRN::SMGN>(-3, 2), -1.0);
}

TEST(SpecDivision, NegativeDivisorsUseTheSignOfTheExactResult)
{
    EXPECT_DOUBLE_EQ(divide<RND::POS_INF>(3, -2), -1.0);
    EXPECT_DOUBLE_EQ(divide<RND::POS_INF>(-3, -2), 2.0);
    EXPECT_DOUBLE_EQ(divide<RND::NEG_INF>(3, -2), -2.0);
    EXPECT_DOUBLE_EQ(divide<RND::NEG_INF>(-3, -2), 1.0);
    EXPECT_DOUBLE_EQ(divide<RND::ZERO>(3, -2), -1.0);
    EXPECT_DOUBLE_EQ(divide<RND::INF>(3, -2), -2.0);
    EXPECT_DOUBLE_EQ(divide<RND::CONV>(3, -2), -2.0);
    EXPECT_DOUBLE_EQ(divide<TRN::TCPL>(3, -2), -2.0);
    EXPECT_DOUBLE_EQ(divide<TRN::SMGN>(3, -2), -1.0);
}

TEST(SpecDivision, ZeroTowardZeroQuotientDoesNotHideANegativeResult)
{
    EXPECT_DOUBLE_EQ(divide<TRN::TCPL>(1, -4), -1.0);
    EXPECT_DOUBLE_EQ(divide<TRN::SMGN>(1, -4), 0.0);
    EXPECT_DOUBLE_EQ(divide<RND::POS_INF>(3, -4), -1.0);
    EXPECT_DOUBLE_EQ(divide<RND::NEG_INF>(-3, 4), -1.0);
}

TEST(SpecDivision, NonzeroTargetFractionIsAppliedBeforeRemainderRounding)
{
    EXPECT_DOUBLE_EQ((divideTo<RND::POS_INF, 2>(2, 3)), 0.75);
    EXPECT_DOUBLE_EQ((divideTo<TRN::TCPL, 2>(2, 3)), 0.5);
    EXPECT_DOUBLE_EQ((divideTo<TRN::TCPL, 2>(-2, 3)), -0.75);
    EXPECT_DOUBLE_EQ((divideTo<TRN::SMGN, 2>(-2, 3)), -0.5);

    EXPECT_DOUBLE_EQ((divideTo<RND::POS_INF, 2>(1, 8)), 0.25);
    EXPECT_DOUBLE_EQ((divideTo<RND::NEG_INF, 2>(1, 8)), 0.0);
    EXPECT_DOUBLE_EQ((divideTo<RND::POS_INF, 2>(1, -8)), 0.0);
    EXPECT_DOUBLE_EQ((divideTo<RND::NEG_INF, 2>(1, -8)), -0.25);
}

TEST(SpecDivision, DifferentSourceFractionsStillFormAnExactRationalValue)
{
    using Lhs = Qu<intBits<5>, fracBits<2>, isSigned<true>,
                   QuMode<TRN::TCPL>, OfMode<SAT::TCPL>>;
    using Rhs = Qu<intBits<5>, fracBits<1>, isSigned<true>,
                   QuMode<TRN::TCPL>, OfMode<SAT::TCPL>>;
    const Lhs lhs = 1.25;
    const Rhs rhs = 2.0;

    EXPECT_DOUBLE_EQ((Qdiv<intBits<5>, fracBits<2>, isSigned<true>,
                           QuMode<RND::POS_INF>, OfMode<SAT::TCPL>>(lhs, rhs)
                          .toDouble()),
                     0.75);
    EXPECT_DOUBLE_EQ((Qdiv<intBits<5>, fracBits<2>, isSigned<true>,
                           QuMode<RND::NEG_INF>, OfMode<SAT::TCPL>>(lhs, rhs)
                          .toDouble()),
                     0.5);
}

TEST(SpecDivision, NegativeTargetFractionScalesTheDenominatorWithoutDiscardingBits)
{
    EXPECT_DOUBLE_EQ((divideTo<RND::POS_INF, -1>(3, 2)), 2.0);
    EXPECT_DOUBLE_EQ((divideTo<TRN::TCPL, -1>(3, 2)), 0.0);
    EXPECT_DOUBLE_EQ((divideTo<TRN::TCPL, -1>(-3, 2)), -2.0);
    EXPECT_DOUBLE_EQ((divideTo<TRN::SMGN, -1>(-3, 2)), 0.0);
    EXPECT_DOUBLE_EQ((divideTo<RND::CONV, -1>(4, 2)), 2.0);
}

TEST(SpecDivision, WideEqualWidthOperandsUseTheSameRemainderRules)
{
    using Wide = Qu<intBits<80>, fracBits<0>, isSigned<true>,
                    QuMode<TRN::TCPL>, OfMode<SAT::TCPL>>;
    Wide lhs;
    Wide positiveRhs;
    Wide negativeRhs;
    lhs.data = ArbiInt<81>(std::string("55340232221128654848"));
    positiveRhs.data = ArbiInt<81>(std::string("36893488147419103232"));
    negativeRhs.data = ArbiInt<81>(std::string("-36893488147419103232"));

    EXPECT_DOUBLE_EQ((Qdiv<intBits<80>, fracBits<0>, QuMode<RND::POS_INF>>(lhs, positiveRhs).toDouble()), 2.0);
    EXPECT_DOUBLE_EQ((Qdiv<intBits<80>, fracBits<0>, QuMode<RND::NEG_INF>>(lhs, positiveRhs).toDouble()), 1.0);
    EXPECT_DOUBLE_EQ((Qdiv<intBits<80>, fracBits<0>, QuMode<TRN::TCPL>>(lhs, negativeRhs).toDouble()), -2.0);
    EXPECT_DOUBLE_EQ((Qdiv<intBits<80>, fracBits<0>, QuMode<TRN::SMGN>>(lhs, negativeRhs).toDouble()), -1.0);
}

TEST(SpecDivision, QuantizationPrecedesOverflowHandling)
{
    const Operand lhs = 3.0;
    const Operand rhs = 2.0;
    const auto result = Qdiv<intBits<1>, fracBits<0>, isSigned<true>,
                             QuMode<RND::POS_INF>, OfMode<SAT::ZERO>>(lhs, rhs);
    EXPECT_DOUBLE_EQ(result.toDouble(), 0.0);
}

TEST(SpecDivision, DivisionByZeroThrows)
{
    const Operand lhs = 1.0;
    const Operand zero = 0.0;
    EXPECT_THROW((Qdiv<intBits<5>, fracBits<0>, QuMode<TRN::TCPL>>(lhs, zero)), std::domain_error);
}
