#include <gtest/gtest.h>

#include <string>

#include "QuBLAS.h"

using namespace QuBLAS;

TEST(SpecWrapWidthBoundary, SignedTwosComplementAtExactly128Bits)
{
    using Source = Qu<intBits<129>, fracBits<0>, isSigned<true>,
                      QuMode<TRN::TCPL>, OfMode<SAT::TCPL>>;
    using Target = Qu<intBits<127>, fracBits<0>, isSigned<true>,
                      QuMode<TRN::TCPL>, OfMode<WRP::TCPL>>;

    Source positive;
    positive.data = ArbiInt<130>(
        std::string("170141183460469231731687303715884105728"));
    const Target wrappedPositive = positive;
    EXPECT_EQ(wrappedPositive.data.toString(),
              "-170141183460469231731687303715884105728");

    Source negative;
    negative.data = ArbiInt<130>(
        std::string("-170141183460469231731687303715884105729"));
    const Target wrappedNegative = negative;
    EXPECT_EQ(wrappedNegative.data.toString(),
              "170141183460469231731687303715884105727");
}
