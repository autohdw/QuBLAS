
#include "QuBLAS.h"
#include <gtest/gtest.h>

using namespace QuBLAS;


// a comparision function that check if the last "val - shift" bits of shifted are the same as the last "val - shift" bits of raw, staring from the right shifte bits

template <size_t shift, size_t val>
bool check(const std::string &shifted, const std::string &raw)
{
    for (size_t i = 0; i < val - shift; i++)
    {
        if (shifted[shifted.size() - 1 - i] != raw[raw.size() - 1 - i - shift])
        {
            return false;
        }
    }

    return true;
}



TEST(staticShiftRight, 8_4)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 12_4)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 12_8)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 16_4)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 16_8)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 16_12)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 20_4)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 20_8)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 20_12)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 20_16)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 24_4)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 24_8)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 24_12)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 24_16)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 24_20)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 28_4)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 28_8)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 28_12)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 28_16)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 28_20)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 28_24)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 32_4)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 32_8)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 32_12)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 32_16)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 32_20)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 32_24)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 32_28)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 36_4)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 36_8)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 36_12)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 36_16)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 36_20)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 36_24)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 36_28)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 36_32)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 40_4)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 40_8)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 40_12)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 40_16)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 40_20)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 40_24)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 40_28)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 40_32)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 40_36)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 44_4)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 44_8)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 44_12)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 44_16)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 44_20)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 44_24)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 44_28)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 44_32)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 44_36)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 44_40)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 48_4)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 48_8)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 48_12)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 48_16)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 48_20)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 48_24)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 48_28)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 48_32)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 48_36)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 48_40)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 48_44)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 52_4)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 52_8)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 52_12)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 52_16)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 52_20)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 52_24)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 52_28)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 52_32)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 52_36)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 52_40)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 52_44)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 52_48)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 56_4)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 56_8)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 56_12)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 56_16)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 56_20)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 56_24)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 56_28)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 56_32)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 56_36)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 56_40)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 56_44)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 56_48)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 56_52)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 60_4)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 60_8)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 60_12)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 60_16)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 60_20)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 60_24)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 60_28)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 60_32)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 60_36)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 60_40)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 60_44)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 60_48)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 60_52)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 60_56)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 64_4)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 64_8)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 64_12)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 64_16)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 64_20)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 64_24)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 64_28)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 64_32)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 64_36)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 64_40)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 64_44)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 64_48)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 64_52)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 64_56)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 64_60)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 68_4)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 68_8)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 68_12)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 68_16)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 68_20)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 68_24)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 68_28)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 68_32)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 68_36)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 68_40)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 68_44)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 68_48)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 68_52)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 68_56)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 68_60)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 68_64)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 72_4)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 72_8)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 72_12)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 72_16)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 72_20)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 72_24)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 72_28)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 72_32)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 72_36)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 72_40)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 72_44)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 72_48)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 72_52)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 72_56)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 72_60)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 72_64)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 72_68)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 76_4)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 76_8)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 76_12)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 76_16)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 76_20)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 76_24)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 76_28)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 76_32)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 76_36)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 76_40)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 76_44)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 76_48)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 76_52)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 76_56)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 76_60)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 76_64)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 76_68)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 76_72)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 80_4)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 80_8)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 80_12)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 80_16)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 80_20)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 80_24)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 80_28)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 80_32)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 80_36)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 80_40)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 80_44)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 80_48)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 80_52)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 80_56)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 80_60)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 80_64)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 80_68)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 80_72)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 80_76)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 84_4)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 84_8)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 84_12)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 84_16)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 84_20)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 84_24)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 84_28)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 84_32)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 84_36)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 84_40)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 84_44)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 84_48)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 84_52)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 84_56)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 84_60)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 84_64)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 84_68)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 84_72)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 84_76)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 84_80)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_4)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_8)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_12)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_16)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_20)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_24)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_28)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_32)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_36)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_40)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_44)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_48)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_52)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_56)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_60)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_64)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_68)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_72)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_76)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_80)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 88_84)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_4)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_8)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_12)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_16)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_20)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_24)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_28)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_32)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_36)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_40)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_44)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_48)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_52)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_56)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_60)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_64)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_68)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_72)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_76)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_80)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_84)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 92_88)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_4)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_8)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_12)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_16)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_20)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_24)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_28)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_32)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_36)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_40)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_44)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_48)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_52)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_56)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_60)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_64)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_68)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_72)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_76)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_80)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_84)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_88)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 96_92)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_4)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_8)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_12)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_16)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_20)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_24)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_28)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_32)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_36)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_40)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_44)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_48)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_52)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_56)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_60)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_64)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_68)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_72)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_76)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_80)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_84)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_88)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_92)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 100_96)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_4)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_8)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_12)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_16)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_20)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_24)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_28)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_32)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_36)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_40)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_44)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_48)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_52)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_56)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_60)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_64)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_68)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_72)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_76)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_80)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_84)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_88)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_92)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_96)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 104_100)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_4)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_8)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_12)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_16)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_20)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_24)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_28)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_32)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_36)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_40)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_44)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_48)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_52)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_56)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_60)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_64)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_68)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_72)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_76)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_80)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_84)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_88)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_92)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_96)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_100)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 108_104)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_4)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_8)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_12)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_16)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_20)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_24)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_28)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_32)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_36)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_40)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_44)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_48)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_52)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_56)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_60)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_64)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_68)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_72)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_76)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_80)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_84)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_88)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_92)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_96)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_100)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_104)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 112_108)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_4)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_8)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_12)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_16)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_20)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_24)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_28)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_32)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_36)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_40)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_44)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_48)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_52)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_56)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_60)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_64)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_68)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_72)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_76)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_80)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_84)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_88)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_92)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_96)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_100)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_104)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_108)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 116_112)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_4)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_8)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_12)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_16)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_20)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_24)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_28)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_32)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_36)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_40)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_44)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_48)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_52)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_56)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_60)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_64)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_68)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_72)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_76)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_80)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_84)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_88)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_92)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_96)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_100)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_104)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_108)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_112)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 120_116)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_4)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_8)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_12)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_16)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_20)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_24)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_28)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_32)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_36)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_40)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_44)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_48)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_52)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_56)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_60)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_64)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_68)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_72)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_76)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_80)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_84)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_88)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_92)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_96)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_100)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_104)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_108)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_112)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_116)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 124_120)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<120>(a).toBinary();

    bool result = check<120, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_4)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_8)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_12)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_16)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_20)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_24)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_28)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_32)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_36)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_40)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_44)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_48)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_52)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_56)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_60)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_64)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_68)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_72)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_76)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_80)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_84)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_88)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_92)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_96)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_100)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_104)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_108)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_112)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_116)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_120)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<120>(a).toBinary();

    bool result = check<120, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 128_124)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<124>(a).toBinary();

    bool result = check<124, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_4)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_8)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_12)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_16)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_20)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_24)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_28)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_32)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_36)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_40)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_44)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_48)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_52)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_56)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_60)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_64)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_68)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_72)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_76)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_80)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_84)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_88)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_92)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_96)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_100)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_104)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_108)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_112)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_116)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_120)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<120>(a).toBinary();

    bool result = check<120, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_124)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<124>(a).toBinary();

    bool result = check<124, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 132_128)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<128>(a).toBinary();

    bool result = check<128, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_4)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_8)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_12)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_16)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_20)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_24)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_28)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_32)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_36)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_40)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_44)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_48)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_52)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_56)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_60)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_64)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_68)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_72)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_76)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_80)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_84)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_88)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_92)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_96)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_100)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_104)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_108)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_112)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_116)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_120)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<120>(a).toBinary();

    bool result = check<120, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_124)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<124>(a).toBinary();

    bool result = check<124, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_128)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<128>(a).toBinary();

    bool result = check<128, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 136_132)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<132>(a).toBinary();

    bool result = check<132, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_4)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_8)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_12)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_16)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_20)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_24)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_28)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_32)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_36)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_40)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_44)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_48)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_52)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_56)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_60)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_64)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_68)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_72)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_76)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_80)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_84)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_88)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_92)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_96)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_100)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_104)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_108)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_112)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_116)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_120)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<120>(a).toBinary();

    bool result = check<120, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_124)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<124>(a).toBinary();

    bool result = check<124, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_128)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<128>(a).toBinary();

    bool result = check<128, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_132)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<132>(a).toBinary();

    bool result = check<132, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 140_136)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<136>(a).toBinary();

    bool result = check<136, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_4)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_8)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_12)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_16)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_20)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_24)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_28)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_32)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_36)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_40)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_44)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_48)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_52)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_56)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_60)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_64)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_68)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_72)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_76)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_80)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_84)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_88)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_92)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_96)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_100)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_104)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_108)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_112)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_116)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_120)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<120>(a).toBinary();

    bool result = check<120, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_124)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<124>(a).toBinary();

    bool result = check<124, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_128)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<128>(a).toBinary();

    bool result = check<128, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_132)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<132>(a).toBinary();

    bool result = check<132, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_136)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<136>(a).toBinary();

    bool result = check<136, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 144_140)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<140>(a).toBinary();

    bool result = check<140, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_4)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_8)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_12)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_16)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_20)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_24)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_28)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_32)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_36)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_40)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_44)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_48)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_52)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_56)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_60)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_64)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_68)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_72)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_76)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_80)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_84)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_88)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_92)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_96)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_100)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_104)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_108)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_112)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_116)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_120)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<120>(a).toBinary();

    bool result = check<120, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_124)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<124>(a).toBinary();

    bool result = check<124, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_128)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<128>(a).toBinary();

    bool result = check<128, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_132)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<132>(a).toBinary();

    bool result = check<132, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_136)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<136>(a).toBinary();

    bool result = check<136, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_140)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<140>(a).toBinary();

    bool result = check<140, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 148_144)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<144>(a).toBinary();

    bool result = check<144, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_4)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_8)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_12)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_16)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_20)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_24)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_28)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_32)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_36)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_40)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_44)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_48)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_52)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_56)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_60)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_64)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_68)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_72)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_76)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_80)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_84)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_88)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_92)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_96)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_100)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_104)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_108)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_112)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_116)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_120)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<120>(a).toBinary();

    bool result = check<120, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_124)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<124>(a).toBinary();

    bool result = check<124, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_128)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<128>(a).toBinary();

    bool result = check<128, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_132)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<132>(a).toBinary();

    bool result = check<132, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_136)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<136>(a).toBinary();

    bool result = check<136, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_140)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<140>(a).toBinary();

    bool result = check<140, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_144)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<144>(a).toBinary();

    bool result = check<144, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 152_148)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<148>(a).toBinary();

    bool result = check<148, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_4)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_8)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_12)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_16)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_20)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_24)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_28)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_32)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_36)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_40)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_44)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_48)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_52)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_56)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_60)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_64)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_68)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_72)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_76)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_80)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_84)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_88)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_92)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_96)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_100)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_104)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_108)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_112)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_116)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_120)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<120>(a).toBinary();

    bool result = check<120, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_124)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<124>(a).toBinary();

    bool result = check<124, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_128)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<128>(a).toBinary();

    bool result = check<128, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_132)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<132>(a).toBinary();

    bool result = check<132, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_136)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<136>(a).toBinary();

    bool result = check<136, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_140)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<140>(a).toBinary();

    bool result = check<140, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_144)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<144>(a).toBinary();

    bool result = check<144, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_148)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<148>(a).toBinary();

    bool result = check<148, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 156_152)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<152>(a).toBinary();

    bool result = check<152, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_4)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_8)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_12)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_16)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_20)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_24)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_28)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_32)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_36)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_40)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_44)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_48)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_52)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_56)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_60)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_64)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_68)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_72)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_76)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_80)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_84)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_88)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_92)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_96)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_100)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_104)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_108)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_112)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_116)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_120)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<120>(a).toBinary();

    bool result = check<120, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_124)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<124>(a).toBinary();

    bool result = check<124, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_128)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<128>(a).toBinary();

    bool result = check<128, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_132)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<132>(a).toBinary();

    bool result = check<132, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_136)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<136>(a).toBinary();

    bool result = check<136, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_140)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<140>(a).toBinary();

    bool result = check<140, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_144)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<144>(a).toBinary();

    bool result = check<144, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_148)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<148>(a).toBinary();

    bool result = check<148, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_152)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<152>(a).toBinary();

    bool result = check<152, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 160_156)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<156>(a).toBinary();

    bool result = check<156, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_4)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_8)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_12)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_16)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_20)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_24)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_28)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_32)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_36)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_40)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_44)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_48)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_52)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_56)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_60)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_64)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_68)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_72)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_76)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_80)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_84)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_88)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_92)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_96)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_100)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_104)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_108)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_112)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_116)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_120)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<120>(a).toBinary();

    bool result = check<120, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_124)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<124>(a).toBinary();

    bool result = check<124, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_128)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<128>(a).toBinary();

    bool result = check<128, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_132)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<132>(a).toBinary();

    bool result = check<132, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_136)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<136>(a).toBinary();

    bool result = check<136, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_140)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<140>(a).toBinary();

    bool result = check<140, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_144)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<144>(a).toBinary();

    bool result = check<144, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_148)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<148>(a).toBinary();

    bool result = check<148, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_152)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<152>(a).toBinary();

    bool result = check<152, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_156)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<156>(a).toBinary();

    bool result = check<156, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 164_160)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<160>(a).toBinary();

    bool result = check<160, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_4)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_8)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_12)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_16)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_20)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_24)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_28)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_32)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_36)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_40)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_44)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_48)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_52)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_56)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_60)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_64)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_68)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_72)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_76)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_80)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_84)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_88)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_92)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_96)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_100)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_104)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_108)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_112)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_116)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_120)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<120>(a).toBinary();

    bool result = check<120, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_124)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<124>(a).toBinary();

    bool result = check<124, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_128)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<128>(a).toBinary();

    bool result = check<128, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_132)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<132>(a).toBinary();

    bool result = check<132, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_136)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<136>(a).toBinary();

    bool result = check<136, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_140)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<140>(a).toBinary();

    bool result = check<140, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_144)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<144>(a).toBinary();

    bool result = check<144, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_148)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<148>(a).toBinary();

    bool result = check<148, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_152)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<152>(a).toBinary();

    bool result = check<152, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_156)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<156>(a).toBinary();

    bool result = check<156, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_160)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<160>(a).toBinary();

    bool result = check<160, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 168_164)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<164>(a).toBinary();

    bool result = check<164, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_4)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_8)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_12)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_16)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_20)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_24)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_28)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_32)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_36)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_40)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_44)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_48)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_52)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_56)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_60)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_64)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_68)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_72)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_76)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_80)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_84)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_88)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_92)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_96)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_100)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_104)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_108)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_112)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_116)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_120)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<120>(a).toBinary();

    bool result = check<120, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_124)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<124>(a).toBinary();

    bool result = check<124, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_128)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<128>(a).toBinary();

    bool result = check<128, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_132)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<132>(a).toBinary();

    bool result = check<132, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_136)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<136>(a).toBinary();

    bool result = check<136, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_140)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<140>(a).toBinary();

    bool result = check<140, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_144)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<144>(a).toBinary();

    bool result = check<144, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_148)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<148>(a).toBinary();

    bool result = check<148, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_152)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<152>(a).toBinary();

    bool result = check<152, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_156)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<156>(a).toBinary();

    bool result = check<156, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_160)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<160>(a).toBinary();

    bool result = check<160, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_164)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<164>(a).toBinary();

    bool result = check<164, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 172_168)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<168>(a).toBinary();

    bool result = check<168, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_4)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_8)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_12)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_16)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_20)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_24)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_28)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_32)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_36)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_40)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_44)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_48)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_52)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_56)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_60)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_64)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_68)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_72)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_76)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_80)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_84)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_88)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_92)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_96)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_100)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_104)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_108)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_112)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_116)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_120)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<120>(a).toBinary();

    bool result = check<120, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_124)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<124>(a).toBinary();

    bool result = check<124, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_128)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<128>(a).toBinary();

    bool result = check<128, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_132)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<132>(a).toBinary();

    bool result = check<132, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_136)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<136>(a).toBinary();

    bool result = check<136, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_140)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<140>(a).toBinary();

    bool result = check<140, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_144)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<144>(a).toBinary();

    bool result = check<144, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_148)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<148>(a).toBinary();

    bool result = check<148, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_152)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<152>(a).toBinary();

    bool result = check<152, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_156)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<156>(a).toBinary();

    bool result = check<156, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_160)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<160>(a).toBinary();

    bool result = check<160, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_164)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<164>(a).toBinary();

    bool result = check<164, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_168)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<168>(a).toBinary();

    bool result = check<168, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 176_172)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<172>(a).toBinary();

    bool result = check<172, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_4)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_8)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_12)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_16)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_20)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_24)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_28)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_32)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_36)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_40)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_44)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_48)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_52)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_56)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_60)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_64)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_68)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_72)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_76)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_80)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_84)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_88)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_92)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_96)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_100)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_104)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_108)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_112)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_116)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_120)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<120>(a).toBinary();

    bool result = check<120, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_124)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<124>(a).toBinary();

    bool result = check<124, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_128)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<128>(a).toBinary();

    bool result = check<128, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_132)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<132>(a).toBinary();

    bool result = check<132, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_136)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<136>(a).toBinary();

    bool result = check<136, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_140)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<140>(a).toBinary();

    bool result = check<140, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_144)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<144>(a).toBinary();

    bool result = check<144, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_148)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<148>(a).toBinary();

    bool result = check<148, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_152)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<152>(a).toBinary();

    bool result = check<152, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_156)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<156>(a).toBinary();

    bool result = check<156, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_160)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<160>(a).toBinary();

    bool result = check<160, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_164)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<164>(a).toBinary();

    bool result = check<164, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_168)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<168>(a).toBinary();

    bool result = check<168, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_172)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<172>(a).toBinary();

    bool result = check<172, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 180_176)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<176>(a).toBinary();

    bool result = check<176, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_4)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_8)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_12)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_16)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_20)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_24)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_28)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_32)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_36)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_40)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_44)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_48)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_52)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_56)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_60)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_64)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_68)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_72)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_76)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_80)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_84)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_88)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_92)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_96)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_100)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_104)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_108)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_112)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_116)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_120)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<120>(a).toBinary();

    bool result = check<120, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_124)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<124>(a).toBinary();

    bool result = check<124, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_128)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<128>(a).toBinary();

    bool result = check<128, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_132)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<132>(a).toBinary();

    bool result = check<132, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_136)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<136>(a).toBinary();

    bool result = check<136, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_140)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<140>(a).toBinary();

    bool result = check<140, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_144)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<144>(a).toBinary();

    bool result = check<144, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_148)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<148>(a).toBinary();

    bool result = check<148, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_152)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<152>(a).toBinary();

    bool result = check<152, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_156)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<156>(a).toBinary();

    bool result = check<156, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_160)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<160>(a).toBinary();

    bool result = check<160, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_164)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<164>(a).toBinary();

    bool result = check<164, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_168)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<168>(a).toBinary();

    bool result = check<168, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_172)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<172>(a).toBinary();

    bool result = check<172, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_176)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<176>(a).toBinary();

    bool result = check<176, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 184_180)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<180>(a).toBinary();

    bool result = check<180, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_4)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_8)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_12)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_16)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_20)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_24)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_28)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_32)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_36)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_40)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_44)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_48)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_52)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_56)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_60)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_64)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_68)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_72)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_76)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_80)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_84)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_88)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_92)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_96)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_100)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_104)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_108)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_112)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_116)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_120)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<120>(a).toBinary();

    bool result = check<120, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_124)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<124>(a).toBinary();

    bool result = check<124, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_128)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<128>(a).toBinary();

    bool result = check<128, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_132)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<132>(a).toBinary();

    bool result = check<132, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_136)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<136>(a).toBinary();

    bool result = check<136, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_140)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<140>(a).toBinary();

    bool result = check<140, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_144)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<144>(a).toBinary();

    bool result = check<144, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_148)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<148>(a).toBinary();

    bool result = check<148, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_152)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<152>(a).toBinary();

    bool result = check<152, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_156)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<156>(a).toBinary();

    bool result = check<156, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_160)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<160>(a).toBinary();

    bool result = check<160, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_164)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<164>(a).toBinary();

    bool result = check<164, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_168)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<168>(a).toBinary();

    bool result = check<168, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_172)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<172>(a).toBinary();

    bool result = check<172, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_176)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<176>(a).toBinary();

    bool result = check<176, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_180)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<180>(a).toBinary();

    bool result = check<180, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 188_184)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<184>(a).toBinary();

    bool result = check<184, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_4)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_8)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_12)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_16)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_20)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_24)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_28)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_32)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_36)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_40)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_44)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_48)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_52)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_56)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_60)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_64)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_68)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_72)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_76)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_80)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_84)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_88)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_92)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_96)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_100)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_104)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_108)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_112)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_116)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_120)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<120>(a).toBinary();

    bool result = check<120, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_124)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<124>(a).toBinary();

    bool result = check<124, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_128)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<128>(a).toBinary();

    bool result = check<128, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_132)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<132>(a).toBinary();

    bool result = check<132, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_136)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<136>(a).toBinary();

    bool result = check<136, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_140)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<140>(a).toBinary();

    bool result = check<140, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_144)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<144>(a).toBinary();

    bool result = check<144, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_148)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<148>(a).toBinary();

    bool result = check<148, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_152)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<152>(a).toBinary();

    bool result = check<152, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_156)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<156>(a).toBinary();

    bool result = check<156, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_160)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<160>(a).toBinary();

    bool result = check<160, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_164)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<164>(a).toBinary();

    bool result = check<164, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_168)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<168>(a).toBinary();

    bool result = check<168, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_172)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<172>(a).toBinary();

    bool result = check<172, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_176)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<176>(a).toBinary();

    bool result = check<176, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_180)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<180>(a).toBinary();

    bool result = check<180, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_184)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<184>(a).toBinary();

    bool result = check<184, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 192_188)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<188>(a).toBinary();

    bool result = check<188, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_4)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_8)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_12)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_16)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_20)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_24)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_28)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_32)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_36)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_40)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_44)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_48)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_52)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_56)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_60)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_64)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_68)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_72)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_76)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_80)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_84)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_88)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_92)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_96)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_100)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_104)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_108)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_112)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_116)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_120)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<120>(a).toBinary();

    bool result = check<120, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_124)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<124>(a).toBinary();

    bool result = check<124, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_128)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<128>(a).toBinary();

    bool result = check<128, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_132)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<132>(a).toBinary();

    bool result = check<132, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_136)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<136>(a).toBinary();

    bool result = check<136, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_140)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<140>(a).toBinary();

    bool result = check<140, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_144)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<144>(a).toBinary();

    bool result = check<144, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_148)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<148>(a).toBinary();

    bool result = check<148, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_152)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<152>(a).toBinary();

    bool result = check<152, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_156)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<156>(a).toBinary();

    bool result = check<156, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_160)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<160>(a).toBinary();

    bool result = check<160, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_164)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<164>(a).toBinary();

    bool result = check<164, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_168)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<168>(a).toBinary();

    bool result = check<168, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_172)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<172>(a).toBinary();

    bool result = check<172, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_176)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<176>(a).toBinary();

    bool result = check<176, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_180)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<180>(a).toBinary();

    bool result = check<180, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_184)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<184>(a).toBinary();

    bool result = check<184, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_188)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<188>(a).toBinary();

    bool result = check<188, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 196_192)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<192>(a).toBinary();

    bool result = check<192, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_4)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<4>(a).toBinary();

    bool result = check<4, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_8)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<8>(a).toBinary();

    bool result = check<8, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_12)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<12>(a).toBinary();

    bool result = check<12, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_16)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<16>(a).toBinary();

    bool result = check<16, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_20)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<20>(a).toBinary();

    bool result = check<20, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_24)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<24>(a).toBinary();

    bool result = check<24, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_28)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<28>(a).toBinary();

    bool result = check<28, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_32)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<32>(a).toBinary();

    bool result = check<32, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_36)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<36>(a).toBinary();

    bool result = check<36, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_40)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<40>(a).toBinary();

    bool result = check<40, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_44)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<44>(a).toBinary();

    bool result = check<44, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_48)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<48>(a).toBinary();

    bool result = check<48, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_52)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<52>(a).toBinary();

    bool result = check<52, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_56)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<56>(a).toBinary();

    bool result = check<56, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_60)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<60>(a).toBinary();

    bool result = check<60, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_64)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<64>(a).toBinary();

    bool result = check<64, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_68)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<68>(a).toBinary();

    bool result = check<68, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_72)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<72>(a).toBinary();

    bool result = check<72, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_76)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<76>(a).toBinary();

    bool result = check<76, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_80)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<80>(a).toBinary();

    bool result = check<80, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_84)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<84>(a).toBinary();

    bool result = check<84, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_88)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<88>(a).toBinary();

    bool result = check<88, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_92)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<92>(a).toBinary();

    bool result = check<92, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_96)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<96>(a).toBinary();

    bool result = check<96, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_100)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<100>(a).toBinary();

    bool result = check<100, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_104)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<104>(a).toBinary();

    bool result = check<104, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_108)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<108>(a).toBinary();

    bool result = check<108, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_112)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<112>(a).toBinary();

    bool result = check<112, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_116)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<116>(a).toBinary();

    bool result = check<116, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_120)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<120>(a).toBinary();

    bool result = check<120, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_124)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<124>(a).toBinary();

    bool result = check<124, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_128)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<128>(a).toBinary();

    bool result = check<128, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_132)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<132>(a).toBinary();

    bool result = check<132, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_136)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<136>(a).toBinary();

    bool result = check<136, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_140)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<140>(a).toBinary();

    bool result = check<140, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_144)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<144>(a).toBinary();

    bool result = check<144, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_148)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<148>(a).toBinary();

    bool result = check<148, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_152)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<152>(a).toBinary();

    bool result = check<152, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_156)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<156>(a).toBinary();

    bool result = check<156, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_160)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<160>(a).toBinary();

    bool result = check<160, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_164)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<164>(a).toBinary();

    bool result = check<164, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_168)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<168>(a).toBinary();

    bool result = check<168, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_172)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<172>(a).toBinary();

    bool result = check<172, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_176)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<176>(a).toBinary();

    bool result = check<176, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_180)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<180>(a).toBinary();

    bool result = check<180, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_184)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<184>(a).toBinary();

    bool result = check<184, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_188)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<188>(a).toBinary();

    bool result = check<188, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_192)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<192>(a).toBinary();

    bool result = check<192, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftRight, 200_196)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<196>(a).toBinary();

    bool result = check<196, 200>(shifted, raw);

    EXPECT_TRUE(result);
}

