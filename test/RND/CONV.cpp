
#include "QuBLAS.h"
#include <gtest/gtest.h>

using namespace QuBLAS;

TEST(CONV, case1)
{
    using from_t = Qu<intBits<3>, fracBits<5>>;

    using target_t = Qu<intBits<3>, fracBits<2>, QuMode<RND::CONV>>;

    from_t from = 1.59375;

    target_t target = from;

    EXPECT_DOUBLE_EQ(target.toDouble(), 1.5);
}

TEST(CONV, case2)
{
    using from_t = Qu<intBits<3>, fracBits<5>>;

    using target_t = Qu<intBits<3>, fracBits<2>, QuMode<RND::CONV>>;

    from_t from = 1.625;

    target_t target = from;

    EXPECT_DOUBLE_EQ(target.toDouble(), 1.5);
}

TEST(CONV, case3)
{
    using from_t = Qu<intBits<3>, fracBits<5>>;

    using target_t = Qu<intBits<3>, fracBits<2>, QuMode<RND::CONV>>;

    from_t from = 1.375;

    target_t target = from;

    EXPECT_DOUBLE_EQ(target.toDouble(), 1.5);
}

TEST(CONV, case4)
{
    using from_t = Qu<intBits<3>, fracBits<5>>;

    using target_t = Qu<intBits<3>, fracBits<2>, QuMode<RND::CONV>>;

    from_t from = 1.65625;

    target_t target = from;

    EXPECT_DOUBLE_EQ(target.toDouble(), 1.75);
}