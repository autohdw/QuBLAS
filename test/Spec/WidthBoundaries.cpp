#include <gtest/gtest.h>

#include <string>

#include "QuBLAS.h"

using namespace QuBLAS;

namespace {

template <int Width>
using WideSource = Qu<intBits<Width + 1>, fracBits<0>, isSigned<true>,
                      QuMode<TRN::TCPL>, OfMode<SAT::TCPL>>;

template <int Width>
using BoundaryTarget = Qu<intBits<Width - 1>, fracBits<0>, isSigned<true>,
                          QuMode<TRN::TCPL>, OfMode<SAT::TCPL>>;

template <int Width>
WideSource<Width> sourceFrom(const char *decimal)
{
    WideSource<Width> source;
    source.data = ArbiInt<Width + 2>(std::string(decimal));
    return source;
}

template <int Width>
std::string convertAtWidth(const char *decimal)
{
    const BoundaryTarget<Width> result = sourceFrom<Width>(decimal);
    return result.data.toString();
}

template <int Width>
void expectBoundaryBehavior(const char *maximum,
                            const char *minimum,
                            const char *positiveOverflow,
                            const char *negativeOverflow)
{
    SCOPED_TRACE(::testing::Message() << "total signed width = " << Width);

    EXPECT_EQ((convertAtWidth<Width>(maximum)), maximum);
    EXPECT_EQ((convertAtWidth<Width>(minimum)), minimum);
    EXPECT_EQ((convertAtWidth<Width>(positiveOverflow)), maximum);
    EXPECT_EQ((convertAtWidth<Width>(negativeOverflow)), minimum);
}

} // namespace

TEST(SpecWidthBoundary, SignedTwosComplementAt63Bits)
{
    expectBoundaryBehavior<63>(
        "4611686018427387903",
        "-4611686018427387904",
        "4611686018427387904",
        "-4611686018427387905");
}

TEST(SpecWidthBoundary, SignedTwosComplementAt64Bits)
{
    expectBoundaryBehavior<64>(
        "9223372036854775807",
        "-9223372036854775808",
        "9223372036854775808",
        "-9223372036854775809");
}

TEST(SpecWidthBoundary, SignedTwosComplementAt65Bits)
{
    expectBoundaryBehavior<65>(
        "18446744073709551615",
        "-18446744073709551616",
        "18446744073709551616",
        "-18446744073709551617");
}

TEST(SpecWidthBoundary, SignedTwosComplementAt127Bits)
{
    expectBoundaryBehavior<127>(
        "85070591730234615865843651857942052863",
        "-85070591730234615865843651857942052864",
        "85070591730234615865843651857942052864",
        "-85070591730234615865843651857942052865");
}

TEST(SpecWidthBoundary, SignedTwosComplementAt128Bits)
{
    expectBoundaryBehavior<128>(
        "170141183460469231731687303715884105727",
        "-170141183460469231731687303715884105728",
        "170141183460469231731687303715884105728",
        "-170141183460469231731687303715884105729");
}

TEST(SpecWidthBoundary, SignedTwosComplementAt129Bits)
{
    expectBoundaryBehavior<129>(
        "340282366920938463463374607431768211455",
        "-340282366920938463463374607431768211456",
        "340282366920938463463374607431768211456",
        "-340282366920938463463374607431768211457");
}
