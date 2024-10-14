
#include <gtest/gtest.h>
#include "QuBLAS.h"

using namespace QuBLAS;

using High_t = Qu<intBits<70>, fracBits<70>, isSigned<true>, QuMode<RND::POS_INF>>;
using Mid_t = Qu<intBits<30>, fracBits<30>, isSigned<true>, QuMode<RND::POS_INF>>;
using Low_t = Qu<intBits<10>, fracBits<10>, isSigned<true>, QuMode<RND::POS_INF>>;

using target_t = Qu<intBits<1>, fracBits<1>, isSigned<true>, QuMode<RND::POS_INF>>;

TEST(POSINF, HighToTargetPositive)
{
    High_t high = 1.25;
    target_t target = high;
    double targetDouble = target.toDouble();

    EXPECT_DOUBLE_EQ(targetDouble, 1.5);
}

TEST(POSINF, HighToTargetNegative)
{
    High_t high = -1.25;
    target_t target = high;
    double targetDouble = target.toDouble();

    EXPECT_DOUBLE_EQ(targetDouble, -1.0);
}

TEST(POSINF, MidToTargetPositive)
{
    Mid_t mid = 1.25;
    target_t target = mid;
    double targetDouble = target.toDouble();

    EXPECT_DOUBLE_EQ(targetDouble, 1.5);
}

TEST(POSINF, MidToTargetNegative)
{
    Mid_t mid = -1.25;
    target_t target = mid;
    double targetDouble = target.toDouble();

    EXPECT_DOUBLE_EQ(targetDouble, -1.0);
}

TEST(POSINF, LowToTargetPositive)
{
    Low_t low = 1.25;
    target_t target = low;
    double targetDouble = target.toDouble();

    EXPECT_DOUBLE_EQ(targetDouble, 1.5);
}

TEST(POSINF, LowToTargetNegative)
{
    Low_t low = -1.25;
    target_t target = low;
    double targetDouble = target.toDouble();

    EXPECT_DOUBLE_EQ(targetDouble, -1.0);
}

 