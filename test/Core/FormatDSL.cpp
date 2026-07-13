#include <gtest/gtest.h>

#include <format>

#include "QuBLAS.h"

namespace {

using Value = Qu<intBits<4>, fracBits<4>, isSigned<true>>;

TEST(FormatDSL, UsesStandardNumericFormatting)
{
    const Value value(3.25);
    EXPECT_EQ(std::format("{:.3f}", value), "3.250");
}

TEST(FormatDSL, ExposesBinaryHexAndTypeViews)
{
    const Value value(3.25);
    EXPECT_EQ(std::format("{:b}", value), "000110100");
    EXPECT_EQ(std::format("{:x}", value), "034");
    EXPECT_EQ(std::format("{:X}", value), "034");
    EXPECT_EQ(std::format("{:q}", value),
              "Q<4_i, 4_f, signed_>(3.25)");
}

TEST(FormatDSL, BitViewsComposeWithStandardStringFormatting)
{
    const Value value(3.25);
    EXPECT_EQ(std::format("{:b>12}", value), "   000110100");
    EXPECT_EQ(std::format("{:X^7}", value), "  034  ");
    EXPECT_EQ(std::format("{:q.10}", value), "Q<4_i, 4_f");
}

} // namespace
