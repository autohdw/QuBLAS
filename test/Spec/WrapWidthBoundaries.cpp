#include <gtest/gtest.h>

#include <string>

#include "QuBLAS.h"

using namespace QuBLAS;

namespace {

template <int Width>
using WideSource = Qu<intBits<Width + 1>, fracBits<0>, isSigned<true>,
                      QuMode<TRN::TCPL>, OfMode<SAT::TCPL>>;

template <int Width>
using WrapTarget = Qu<intBits<Width - 1>, fracBits<0>, isSigned<true>,
                      QuMode<TRN::TCPL>, OfMode<WRP::TCPL>>;

template <int Width>
std::string wrapAtWidth(const char *decimal)
{
    WideSource<Width> source;
    source.data = ArbiInt<Width + 2>(std::string(decimal));

    const WrapTarget<Width> result = source;
    return result.data.toString();
}

template <int Width>
void expectWrap(const char *maximum,
                const char *minimum,
                const char *positiveOverflow,
                const char *negativeOverflow)
{
    SCOPED_TRACE(::testing::Message() << "total signed width = " << Width);
    EXPECT_EQ(wrapAtWidth<Width>(positiveOverflow), minimum);
    EXPECT_EQ(wrapAtWidth<Width>(negativeOverflow), maximum);
}

} // namespace

TEST(SpecWrapWidthBoundary, SignedTwosComplementAroundLimbEdges)
{
    expectWrap<63>(
        "4611686018427387903",
        "-4611686018427387904",
        "4611686018427387904",
        "-4611686018427387905");

    expectWrap<64>(
        "9223372036854775807",
        "-9223372036854775808",
        "9223372036854775808",
        "-9223372036854775809");

    expectWrap<65>(
        "18446744073709551615",
        "-18446744073709551616",
        "18446744073709551616",
        "-18446744073709551617");

    expectWrap<127>(
        "85070591730234615865843651857942052863",
        "-85070591730234615865843651857942052864",
        "85070591730234615865843651857942052864",
        "-85070591730234615865843651857942052865");

    expectWrap<129>(
        "340282366920938463463374607431768211455",
        "-340282366920938463463374607431768211456",
        "340282366920938463463374607431768211456",
        "-340282366920938463463374607431768211457");
}
