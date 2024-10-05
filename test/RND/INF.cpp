
#include <gtest/gtest.h>
#include "QuBLAS.h"

using namespace QuBLAS;

using High_t = Qu<intBits<70>, fracBits<70>, isSigned<true>, QuMode<RND::INF>>;
using Mid_t = Qu<intBits<30>, fracBits<30>, isSigned<true>, QuMode<RND::INF>>;
using Low_t = Qu<intBits<10>, fracBits<10>, isSigned<true>, QuMode<RND::INF>>;

using target_t = Qu<intBits<1>, fracBits<1>, isSigned<true>, QuMode<RND::INF>>;

TEST(SMGN, HighToTargetPositive)
{
    High_t high = 1.25;
    target_t target = high;
    double targetDouble = target.toDouble();

    EXPECT_DOUBLE_EQ(targetDouble, 1.5);
}

TEST(SMGN, HighToTargetNegative)
{
    High_t high = -1.25;
    target_t target = high;
    double targetDouble = target.toDouble();

    EXPECT_DOUBLE_EQ(targetDouble, -1.5);
}

TEST(SMGN, MidToTargetPositive)
{
    Mid_t mid = 1.25;
    target_t target = mid;
    double targetDouble = target.toDouble();

    EXPECT_DOUBLE_EQ(targetDouble, 1.5);
}

TEST(SMGN, MidToTargetNegative)
{
    Mid_t mid = -1.25;
    target_t target = mid;
    double targetDouble = target.toDouble();

    EXPECT_DOUBLE_EQ(targetDouble, -1.5);
}

TEST(SMGN, LowToTargetPositive)
{
    Low_t low = 1.25;
    target_t target = low;
    double targetDouble = target.toDouble();

    EXPECT_DOUBLE_EQ(targetDouble, 1.5);
}

TEST(SMGN, LowToTargetNegative)
{
    Low_t low = -1.25;
    target_t target = low;
    double targetDouble = target.toDouble();

    EXPECT_DOUBLE_EQ(targetDouble, -1.5);
}

 