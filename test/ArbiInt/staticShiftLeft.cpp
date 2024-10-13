
#include "QuBLAS.h"
#include <gtest/gtest.h>

using namespace QuBLAS;


// a comparision function that check if the last "shift" bits of a string are all 0 and then "val" bits are same as the last "val" bits of another string

template <size_t shift, size_t val>
bool check(const std::string &shifted, const std::string &raw)
{
    for (size_t i = 0; i < shift; i++)
    {
        if (shifted[shifted.size() - 1 - i] != '0')
        {
            return false;
        }
    }

    for (size_t i = 0; i < val; i++)
    {
        if (shifted[shifted.size() - 1 - (i + shift)] != raw[raw.size() - 1 - i])
        {
            return false;
        }
    }

    return true;
}




TEST(staticShiftLeft, 4_4)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_8)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_12)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_16)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_20)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_24)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_28)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_32)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_36)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_40)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_44)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_48)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_52)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_56)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_60)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_64)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_68)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_72)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_76)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_80)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_84)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_88)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_92)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_96)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_100)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_104)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_108)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_112)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_116)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_120)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_124)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_128)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_132)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_136)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_140)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_144)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_148)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_152)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_156)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_160)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_164)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_168)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_172)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_176)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_180)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_184)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_188)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_192)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_196)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 4_200)
{
    ArbiInt<4> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 4>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_4)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_8)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_12)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_16)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_20)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_24)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_28)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_32)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_36)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_40)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_44)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_48)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_52)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_56)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_60)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_64)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_68)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_72)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_76)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_80)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_84)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_88)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_92)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_96)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_100)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_104)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_108)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_112)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_116)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_120)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_124)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_128)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_132)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_136)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_140)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_144)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_148)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_152)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_156)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_160)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_164)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_168)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_172)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_176)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_180)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_184)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_188)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_192)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_196)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 8_200)
{
    ArbiInt<8> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 8>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_4)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_8)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_12)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_16)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_20)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_24)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_28)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_32)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_36)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_40)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_44)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_48)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_52)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_56)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_60)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_64)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_68)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_72)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_76)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_80)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_84)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_88)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_92)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_96)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_100)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_104)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_108)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_112)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_116)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_120)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_124)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_128)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_132)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_136)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_140)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_144)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_148)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_152)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_156)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_160)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_164)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_168)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_172)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_176)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_180)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_184)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_188)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_192)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_196)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 12_200)
{
    ArbiInt<12> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 12>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_4)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_8)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_12)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_16)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_20)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_24)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_28)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_32)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_36)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_40)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_44)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_48)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_52)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_56)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_60)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_64)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_68)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_72)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_76)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_80)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_84)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_88)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_92)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_96)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_100)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_104)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_108)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_112)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_116)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_120)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_124)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_128)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_132)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_136)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_140)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_144)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_148)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_152)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_156)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_160)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_164)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_168)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_172)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_176)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_180)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_184)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_188)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_192)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_196)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 16_200)
{
    ArbiInt<16> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 16>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_4)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_8)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_12)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_16)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_20)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_24)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_28)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_32)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_36)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_40)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_44)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_48)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_52)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_56)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_60)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_64)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_68)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_72)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_76)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_80)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_84)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_88)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_92)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_96)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_100)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_104)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_108)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_112)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_116)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_120)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_124)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_128)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_132)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_136)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_140)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_144)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_148)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_152)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_156)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_160)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_164)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_168)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_172)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_176)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_180)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_184)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_188)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_192)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_196)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 20_200)
{
    ArbiInt<20> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 20>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_4)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_8)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_12)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_16)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_20)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_24)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_28)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_32)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_36)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_40)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_44)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_48)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_52)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_56)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_60)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_64)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_68)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_72)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_76)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_80)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_84)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_88)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_92)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_96)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_100)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_104)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_108)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_112)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_116)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_120)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_124)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_128)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_132)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_136)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_140)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_144)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_148)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_152)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_156)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_160)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_164)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_168)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_172)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_176)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_180)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_184)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_188)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_192)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_196)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 24_200)
{
    ArbiInt<24> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 24>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_4)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_8)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_12)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_16)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_20)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_24)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_28)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_32)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_36)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_40)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_44)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_48)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_52)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_56)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_60)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_64)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_68)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_72)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_76)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_80)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_84)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_88)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_92)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_96)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_100)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_104)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_108)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_112)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_116)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_120)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_124)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_128)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_132)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_136)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_140)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_144)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_148)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_152)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_156)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_160)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_164)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_168)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_172)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_176)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_180)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_184)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_188)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_192)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_196)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 28_200)
{
    ArbiInt<28> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 28>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_4)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_8)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_12)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_16)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_20)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_24)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_28)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_32)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_36)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_40)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_44)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_48)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_52)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_56)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_60)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_64)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_68)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_72)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_76)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_80)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_84)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_88)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_92)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_96)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_100)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_104)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_108)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_112)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_116)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_120)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_124)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_128)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_132)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_136)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_140)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_144)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_148)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_152)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_156)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_160)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_164)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_168)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_172)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_176)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_180)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_184)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_188)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_192)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_196)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 32_200)
{
    ArbiInt<32> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 32>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_4)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_8)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_12)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_16)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_20)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_24)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_28)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_32)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_36)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_40)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_44)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_48)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_52)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_56)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_60)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_64)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_68)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_72)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_76)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_80)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_84)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_88)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_92)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_96)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_100)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_104)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_108)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_112)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_116)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_120)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_124)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_128)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_132)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_136)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_140)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_144)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_148)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_152)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_156)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_160)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_164)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_168)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_172)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_176)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_180)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_184)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_188)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_192)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_196)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 36_200)
{
    ArbiInt<36> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 36>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_4)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_8)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_12)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_16)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_20)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_24)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_28)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_32)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_36)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_40)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_44)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_48)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_52)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_56)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_60)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_64)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_68)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_72)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_76)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_80)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_84)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_88)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_92)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_96)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_100)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_104)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_108)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_112)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_116)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_120)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_124)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_128)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_132)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_136)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_140)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_144)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_148)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_152)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_156)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_160)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_164)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_168)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_172)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_176)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_180)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_184)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_188)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_192)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_196)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 40_200)
{
    ArbiInt<40> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 40>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_4)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_8)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_12)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_16)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_20)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_24)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_28)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_32)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_36)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_40)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_44)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_48)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_52)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_56)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_60)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_64)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_68)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_72)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_76)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_80)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_84)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_88)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_92)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_96)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_100)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_104)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_108)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_112)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_116)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_120)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_124)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_128)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_132)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_136)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_140)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_144)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_148)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_152)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_156)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_160)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_164)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_168)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_172)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_176)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_180)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_184)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_188)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_192)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_196)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 44_200)
{
    ArbiInt<44> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 44>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_4)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_8)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_12)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_16)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_20)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_24)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_28)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_32)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_36)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_40)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_44)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_48)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_52)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_56)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_60)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_64)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_68)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_72)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_76)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_80)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_84)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_88)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_92)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_96)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_100)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_104)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_108)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_112)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_116)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_120)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_124)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_128)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_132)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_136)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_140)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_144)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_148)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_152)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_156)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_160)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_164)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_168)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_172)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_176)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_180)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_184)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_188)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_192)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_196)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 48_200)
{
    ArbiInt<48> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 48>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_4)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_8)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_12)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_16)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_20)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_24)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_28)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_32)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_36)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_40)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_44)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_48)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_52)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_56)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_60)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_64)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_68)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_72)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_76)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_80)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_84)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_88)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_92)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_96)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_100)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_104)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_108)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_112)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_116)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_120)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_124)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_128)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_132)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_136)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_140)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_144)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_148)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_152)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_156)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_160)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_164)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_168)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_172)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_176)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_180)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_184)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_188)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_192)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_196)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 52_200)
{
    ArbiInt<52> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 52>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_4)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_8)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_12)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_16)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_20)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_24)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_28)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_32)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_36)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_40)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_44)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_48)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_52)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_56)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_60)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_64)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_68)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_72)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_76)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_80)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_84)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_88)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_92)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_96)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_100)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_104)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_108)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_112)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_116)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_120)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_124)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_128)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_132)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_136)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_140)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_144)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_148)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_152)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_156)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_160)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_164)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_168)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_172)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_176)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_180)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_184)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_188)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_192)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_196)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 56_200)
{
    ArbiInt<56> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 56>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_4)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_8)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_12)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_16)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_20)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_24)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_28)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_32)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_36)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_40)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_44)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_48)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_52)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_56)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_60)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_64)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_68)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_72)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_76)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_80)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_84)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_88)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_92)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_96)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_100)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_104)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_108)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_112)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_116)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_120)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_124)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_128)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_132)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_136)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_140)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_144)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_148)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_152)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_156)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_160)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_164)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_168)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_172)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_176)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_180)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_184)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_188)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_192)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_196)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 60_200)
{
    ArbiInt<60> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 60>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_4)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_8)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_12)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_16)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_20)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_24)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_28)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_32)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_36)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_40)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_44)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_48)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_52)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_56)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_60)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_64)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_68)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_72)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_76)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_80)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_84)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_88)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_92)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_96)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_100)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_104)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_108)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_112)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_116)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_120)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_124)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_128)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_132)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_136)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_140)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_144)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_148)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_152)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_156)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_160)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_164)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_168)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_172)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_176)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_180)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_184)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_188)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_192)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_196)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 64_200)
{
    ArbiInt<64> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 64>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_4)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_8)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_12)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_16)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_20)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_24)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_28)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_32)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_36)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_40)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_44)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_48)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_52)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_56)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_60)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_64)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_68)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_72)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_76)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_80)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_84)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_88)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_92)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_96)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_100)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_104)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_108)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_112)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_116)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_120)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_124)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_128)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_132)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_136)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_140)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_144)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_148)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_152)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_156)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_160)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_164)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_168)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_172)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_176)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_180)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_184)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_188)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_192)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_196)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 68_200)
{
    ArbiInt<68> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 68>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_4)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_8)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_12)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_16)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_20)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_24)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_28)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_32)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_36)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_40)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_44)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_48)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_52)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_56)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_60)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_64)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_68)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_72)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_76)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_80)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_84)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_88)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_92)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_96)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_100)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_104)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_108)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_112)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_116)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_120)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_124)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_128)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_132)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_136)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_140)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_144)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_148)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_152)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_156)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_160)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_164)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_168)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_172)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_176)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_180)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_184)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_188)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_192)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_196)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 72_200)
{
    ArbiInt<72> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 72>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_4)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_8)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_12)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_16)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_20)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_24)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_28)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_32)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_36)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_40)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_44)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_48)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_52)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_56)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_60)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_64)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_68)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_72)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_76)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_80)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_84)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_88)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_92)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_96)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_100)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_104)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_108)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_112)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_116)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_120)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_124)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_128)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_132)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_136)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_140)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_144)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_148)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_152)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_156)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_160)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_164)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_168)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_172)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_176)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_180)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_184)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_188)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_192)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_196)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 76_200)
{
    ArbiInt<76> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 76>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_4)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_8)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_12)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_16)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_20)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_24)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_28)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_32)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_36)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_40)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_44)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_48)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_52)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_56)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_60)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_64)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_68)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_72)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_76)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_80)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_84)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_88)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_92)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_96)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_100)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_104)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_108)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_112)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_116)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_120)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_124)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_128)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_132)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_136)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_140)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_144)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_148)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_152)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_156)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_160)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_164)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_168)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_172)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_176)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_180)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_184)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_188)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_192)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_196)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 80_200)
{
    ArbiInt<80> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 80>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_4)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_8)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_12)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_16)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_20)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_24)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_28)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_32)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_36)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_40)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_44)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_48)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_52)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_56)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_60)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_64)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_68)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_72)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_76)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_80)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_84)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_88)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_92)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_96)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_100)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_104)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_108)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_112)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_116)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_120)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_124)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_128)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_132)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_136)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_140)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_144)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_148)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_152)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_156)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_160)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_164)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_168)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_172)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_176)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_180)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_184)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_188)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_192)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_196)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 84_200)
{
    ArbiInt<84> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 84>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_4)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_8)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_12)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_16)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_20)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_24)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_28)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_32)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_36)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_40)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_44)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_48)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_52)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_56)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_60)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_64)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_68)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_72)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_76)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_80)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_84)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_88)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_92)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_96)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_100)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_104)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_108)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_112)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_116)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_120)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_124)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_128)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_132)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_136)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_140)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_144)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_148)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_152)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_156)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_160)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_164)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_168)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_172)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_176)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_180)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_184)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_188)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_192)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_196)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 88_200)
{
    ArbiInt<88> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 88>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_4)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_8)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_12)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_16)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_20)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_24)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_28)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_32)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_36)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_40)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_44)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_48)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_52)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_56)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_60)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_64)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_68)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_72)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_76)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_80)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_84)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_88)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_92)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_96)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_100)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_104)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_108)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_112)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_116)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_120)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_124)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_128)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_132)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_136)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_140)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_144)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_148)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_152)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_156)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_160)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_164)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_168)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_172)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_176)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_180)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_184)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_188)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_192)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_196)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 92_200)
{
    ArbiInt<92> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 92>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_4)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_8)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_12)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_16)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_20)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_24)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_28)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_32)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_36)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_40)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_44)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_48)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_52)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_56)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_60)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_64)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_68)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_72)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_76)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_80)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_84)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_88)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_92)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_96)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_100)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_104)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_108)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_112)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_116)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_120)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_124)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_128)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_132)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_136)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_140)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_144)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_148)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_152)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_156)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_160)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_164)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_168)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_172)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_176)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_180)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_184)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_188)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_192)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_196)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 96_200)
{
    ArbiInt<96> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 96>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_4)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_8)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_12)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_16)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_20)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_24)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_28)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_32)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_36)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_40)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_44)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_48)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_52)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_56)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_60)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_64)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_68)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_72)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_76)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_80)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_84)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_88)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_92)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_96)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_100)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_104)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_108)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_112)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_116)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_120)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_124)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_128)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_132)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_136)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_140)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_144)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_148)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_152)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_156)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_160)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_164)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_168)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_172)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_176)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_180)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_184)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_188)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_192)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_196)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 100_200)
{
    ArbiInt<100> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 100>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_4)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_8)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_12)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_16)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_20)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_24)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_28)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_32)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_36)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_40)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_44)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_48)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_52)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_56)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_60)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_64)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_68)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_72)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_76)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_80)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_84)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_88)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_92)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_96)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_100)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_104)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_108)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_112)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_116)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_120)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_124)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_128)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_132)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_136)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_140)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_144)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_148)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_152)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_156)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_160)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_164)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_168)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_172)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_176)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_180)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_184)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_188)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_192)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_196)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 104_200)
{
    ArbiInt<104> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 104>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_4)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_8)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_12)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_16)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_20)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_24)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_28)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_32)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_36)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_40)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_44)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_48)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_52)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_56)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_60)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_64)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_68)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_72)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_76)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_80)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_84)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_88)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_92)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_96)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_100)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_104)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_108)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_112)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_116)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_120)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_124)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_128)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_132)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_136)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_140)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_144)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_148)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_152)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_156)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_160)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_164)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_168)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_172)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_176)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_180)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_184)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_188)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_192)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_196)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 108_200)
{
    ArbiInt<108> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 108>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_4)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_8)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_12)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_16)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_20)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_24)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_28)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_32)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_36)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_40)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_44)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_48)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_52)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_56)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_60)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_64)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_68)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_72)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_76)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_80)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_84)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_88)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_92)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_96)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_100)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_104)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_108)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_112)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_116)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_120)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_124)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_128)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_132)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_136)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_140)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_144)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_148)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_152)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_156)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_160)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_164)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_168)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_172)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_176)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_180)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_184)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_188)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_192)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_196)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 112_200)
{
    ArbiInt<112> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 112>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_4)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_8)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_12)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_16)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_20)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_24)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_28)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_32)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_36)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_40)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_44)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_48)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_52)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_56)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_60)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_64)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_68)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_72)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_76)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_80)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_84)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_88)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_92)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_96)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_100)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_104)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_108)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_112)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_116)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_120)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_124)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_128)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_132)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_136)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_140)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_144)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_148)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_152)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_156)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_160)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_164)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_168)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_172)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_176)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_180)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_184)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_188)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_192)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_196)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 116_200)
{
    ArbiInt<116> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 116>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_4)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_8)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_12)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_16)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_20)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_24)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_28)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_32)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_36)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_40)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_44)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_48)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_52)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_56)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_60)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_64)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_68)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_72)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_76)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_80)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_84)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_88)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_92)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_96)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_100)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_104)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_108)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_112)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_116)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_120)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_124)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_128)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_132)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_136)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_140)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_144)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_148)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_152)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_156)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_160)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_164)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_168)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_172)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_176)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_180)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_184)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_188)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_192)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_196)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 120_200)
{
    ArbiInt<120> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 120>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_4)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_8)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_12)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_16)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_20)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_24)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_28)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_32)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_36)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_40)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_44)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_48)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_52)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_56)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_60)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_64)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_68)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_72)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_76)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_80)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_84)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_88)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_92)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_96)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_100)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_104)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_108)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_112)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_116)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_120)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_124)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_128)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_132)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_136)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_140)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_144)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_148)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_152)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_156)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_160)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_164)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_168)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_172)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_176)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_180)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_184)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_188)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_192)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_196)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 124_200)
{
    ArbiInt<124> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 124>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_4)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_8)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_12)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_16)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_20)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_24)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_28)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_32)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_36)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_40)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_44)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_48)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_52)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_56)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_60)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_64)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_68)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_72)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_76)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_80)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_84)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_88)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_92)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_96)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_100)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_104)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_108)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_112)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_116)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_120)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_124)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_128)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_132)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_136)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_140)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_144)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_148)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_152)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_156)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_160)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_164)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_168)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_172)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_176)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_180)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_184)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_188)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_192)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_196)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 128_200)
{
    ArbiInt<128> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 128>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_4)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_8)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_12)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_16)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_20)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_24)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_28)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_32)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_36)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_40)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_44)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_48)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_52)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_56)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_60)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_64)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_68)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_72)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_76)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_80)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_84)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_88)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_92)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_96)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_100)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_104)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_108)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_112)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_116)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_120)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_124)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_128)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_132)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_136)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_140)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_144)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_148)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_152)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_156)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_160)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_164)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_168)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_172)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_176)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_180)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_184)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_188)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_192)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_196)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 132_200)
{
    ArbiInt<132> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 132>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_4)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_8)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_12)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_16)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_20)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_24)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_28)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_32)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_36)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_40)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_44)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_48)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_52)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_56)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_60)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_64)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_68)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_72)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_76)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_80)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_84)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_88)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_92)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_96)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_100)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_104)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_108)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_112)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_116)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_120)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_124)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_128)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_132)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_136)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_140)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_144)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_148)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_152)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_156)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_160)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_164)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_168)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_172)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_176)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_180)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_184)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_188)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_192)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_196)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 136_200)
{
    ArbiInt<136> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 136>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_4)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_8)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_12)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_16)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_20)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_24)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_28)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_32)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_36)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_40)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_44)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_48)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_52)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_56)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_60)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_64)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_68)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_72)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_76)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_80)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_84)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_88)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_92)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_96)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_100)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_104)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_108)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_112)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_116)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_120)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_124)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_128)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_132)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_136)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_140)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_144)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_148)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_152)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_156)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_160)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_164)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_168)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_172)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_176)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_180)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_184)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_188)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_192)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_196)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 140_200)
{
    ArbiInt<140> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 140>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_4)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_8)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_12)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_16)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_20)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_24)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_28)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_32)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_36)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_40)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_44)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_48)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_52)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_56)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_60)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_64)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_68)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_72)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_76)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_80)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_84)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_88)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_92)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_96)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_100)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_104)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_108)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_112)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_116)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_120)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_124)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_128)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_132)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_136)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_140)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_144)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_148)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_152)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_156)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_160)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_164)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_168)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_172)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_176)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_180)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_184)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_188)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_192)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_196)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 144_200)
{
    ArbiInt<144> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 144>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_4)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_8)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_12)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_16)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_20)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_24)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_28)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_32)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_36)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_40)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_44)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_48)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_52)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_56)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_60)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_64)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_68)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_72)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_76)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_80)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_84)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_88)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_92)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_96)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_100)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_104)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_108)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_112)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_116)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_120)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_124)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_128)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_132)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_136)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_140)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_144)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_148)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_152)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_156)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_160)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_164)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_168)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_172)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_176)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_180)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_184)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_188)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_192)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_196)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 148_200)
{
    ArbiInt<148> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 148>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_4)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_8)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_12)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_16)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_20)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_24)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_28)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_32)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_36)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_40)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_44)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_48)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_52)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_56)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_60)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_64)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_68)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_72)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_76)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_80)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_84)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_88)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_92)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_96)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_100)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_104)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_108)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_112)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_116)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_120)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_124)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_128)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_132)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_136)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_140)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_144)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_148)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_152)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_156)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_160)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_164)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_168)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_172)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_176)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_180)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_184)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_188)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_192)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_196)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 152_200)
{
    ArbiInt<152> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 152>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_4)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_8)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_12)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_16)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_20)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_24)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_28)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_32)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_36)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_40)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_44)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_48)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_52)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_56)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_60)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_64)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_68)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_72)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_76)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_80)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_84)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_88)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_92)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_96)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_100)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_104)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_108)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_112)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_116)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_120)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_124)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_128)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_132)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_136)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_140)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_144)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_148)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_152)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_156)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_160)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_164)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_168)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_172)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_176)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_180)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_184)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_188)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_192)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_196)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 156_200)
{
    ArbiInt<156> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 156>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_4)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_8)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_12)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_16)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_20)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_24)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_28)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_32)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_36)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_40)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_44)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_48)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_52)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_56)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_60)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_64)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_68)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_72)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_76)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_80)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_84)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_88)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_92)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_96)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_100)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_104)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_108)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_112)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_116)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_120)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_124)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_128)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_132)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_136)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_140)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_144)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_148)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_152)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_156)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_160)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_164)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_168)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_172)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_176)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_180)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_184)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_188)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_192)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_196)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 160_200)
{
    ArbiInt<160> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 160>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_4)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_8)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_12)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_16)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_20)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_24)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_28)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_32)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_36)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_40)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_44)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_48)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_52)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_56)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_60)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_64)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_68)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_72)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_76)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_80)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_84)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_88)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_92)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_96)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_100)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_104)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_108)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_112)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_116)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_120)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_124)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_128)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_132)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_136)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_140)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_144)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_148)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_152)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_156)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_160)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_164)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_168)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_172)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_176)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_180)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_184)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_188)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_192)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_196)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 164_200)
{
    ArbiInt<164> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 164>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_4)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_8)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_12)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_16)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_20)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_24)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_28)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_32)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_36)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_40)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_44)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_48)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_52)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_56)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_60)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_64)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_68)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_72)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_76)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_80)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_84)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_88)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_92)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_96)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_100)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_104)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_108)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_112)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_116)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_120)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_124)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_128)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_132)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_136)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_140)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_144)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_148)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_152)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_156)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_160)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_164)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_168)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_172)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_176)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_180)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_184)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_188)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_192)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_196)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 168_200)
{
    ArbiInt<168> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 168>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_4)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_8)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_12)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_16)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_20)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_24)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_28)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_32)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_36)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_40)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_44)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_48)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_52)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_56)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_60)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_64)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_68)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_72)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_76)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_80)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_84)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_88)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_92)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_96)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_100)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_104)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_108)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_112)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_116)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_120)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_124)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_128)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_132)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_136)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_140)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_144)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_148)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_152)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_156)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_160)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_164)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_168)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_172)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_176)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_180)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_184)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_188)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_192)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_196)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 172_200)
{
    ArbiInt<172> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 172>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_4)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_8)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_12)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_16)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_20)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_24)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_28)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_32)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_36)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_40)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_44)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_48)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_52)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_56)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_60)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_64)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_68)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_72)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_76)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_80)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_84)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_88)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_92)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_96)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_100)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_104)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_108)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_112)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_116)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_120)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_124)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_128)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_132)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_136)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_140)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_144)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_148)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_152)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_156)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_160)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_164)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_168)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_172)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_176)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_180)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_184)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_188)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_192)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_196)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 176_200)
{
    ArbiInt<176> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 176>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_4)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_8)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_12)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_16)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_20)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_24)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_28)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_32)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_36)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_40)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_44)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_48)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_52)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_56)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_60)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_64)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_68)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_72)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_76)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_80)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_84)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_88)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_92)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_96)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_100)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_104)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_108)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_112)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_116)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_120)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_124)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_128)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_132)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_136)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_140)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_144)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_148)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_152)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_156)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_160)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_164)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_168)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_172)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_176)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_180)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_184)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_188)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_192)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_196)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 180_200)
{
    ArbiInt<180> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 180>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_4)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_8)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_12)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_16)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_20)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_24)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_28)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_32)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_36)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_40)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_44)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_48)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_52)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_56)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_60)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_64)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_68)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_72)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_76)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_80)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_84)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_88)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_92)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_96)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_100)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_104)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_108)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_112)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_116)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_120)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_124)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_128)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_132)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_136)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_140)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_144)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_148)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_152)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_156)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_160)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_164)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_168)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_172)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_176)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_180)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_184)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_188)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_192)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_196)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 184_200)
{
    ArbiInt<184> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 184>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_4)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_8)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_12)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_16)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_20)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_24)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_28)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_32)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_36)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_40)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_44)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_48)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_52)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_56)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_60)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_64)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_68)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_72)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_76)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_80)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_84)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_88)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_92)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_96)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_100)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_104)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_108)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_112)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_116)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_120)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_124)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_128)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_132)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_136)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_140)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_144)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_148)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_152)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_156)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_160)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_164)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_168)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_172)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_176)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_180)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_184)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_188)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_192)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_196)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 188_200)
{
    ArbiInt<188> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 188>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_4)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_8)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_12)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_16)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_20)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_24)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_28)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_32)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_36)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_40)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_44)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_48)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_52)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_56)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_60)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_64)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_68)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_72)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_76)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_80)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_84)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_88)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_92)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_96)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_100)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_104)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_108)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_112)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_116)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_120)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_124)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_128)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_132)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_136)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_140)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_144)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_148)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_152)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_156)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_160)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_164)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_168)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_172)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_176)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_180)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_184)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_188)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_192)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_196)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 192_200)
{
    ArbiInt<192> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 192>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_4)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_8)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_12)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_16)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_20)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_24)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_28)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_32)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_36)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_40)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_44)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_48)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_52)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_56)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_60)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_64)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_68)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_72)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_76)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_80)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_84)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_88)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_92)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_96)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_100)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_104)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_108)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_112)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_116)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_120)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_124)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_128)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_132)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_136)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_140)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_144)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_148)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_152)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_156)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_160)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_164)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_168)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_172)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_176)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_180)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_184)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_188)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_192)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_196)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 196_200)
{
    ArbiInt<196> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 196>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_4)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<4>(a).toBinary();

    bool result = check<4, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_8)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<8>(a).toBinary();

    bool result = check<8, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_12)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<12>(a).toBinary();

    bool result = check<12, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_16)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<16>(a).toBinary();

    bool result = check<16, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_20)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<20>(a).toBinary();

    bool result = check<20, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_24)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<24>(a).toBinary();

    bool result = check<24, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_28)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<28>(a).toBinary();

    bool result = check<28, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_32)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<32>(a).toBinary();

    bool result = check<32, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_36)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<36>(a).toBinary();

    bool result = check<36, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_40)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<40>(a).toBinary();

    bool result = check<40, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_44)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<44>(a).toBinary();

    bool result = check<44, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_48)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<48>(a).toBinary();

    bool result = check<48, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_52)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<52>(a).toBinary();

    bool result = check<52, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_56)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<56>(a).toBinary();

    bool result = check<56, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_60)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<60>(a).toBinary();

    bool result = check<60, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_64)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<64>(a).toBinary();

    bool result = check<64, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_68)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<68>(a).toBinary();

    bool result = check<68, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_72)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<72>(a).toBinary();

    bool result = check<72, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_76)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<76>(a).toBinary();

    bool result = check<76, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_80)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<80>(a).toBinary();

    bool result = check<80, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_84)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<84>(a).toBinary();

    bool result = check<84, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_88)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<88>(a).toBinary();

    bool result = check<88, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_92)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<92>(a).toBinary();

    bool result = check<92, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_96)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<96>(a).toBinary();

    bool result = check<96, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_100)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<100>(a).toBinary();

    bool result = check<100, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_104)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<104>(a).toBinary();

    bool result = check<104, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_108)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<108>(a).toBinary();

    bool result = check<108, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_112)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<112>(a).toBinary();

    bool result = check<112, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_116)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<116>(a).toBinary();

    bool result = check<116, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_120)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<120>(a).toBinary();

    bool result = check<120, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_124)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<124>(a).toBinary();

    bool result = check<124, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_128)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<128>(a).toBinary();

    bool result = check<128, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_132)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<132>(a).toBinary();

    bool result = check<132, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_136)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<136>(a).toBinary();

    bool result = check<136, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_140)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<140>(a).toBinary();

    bool result = check<140, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_144)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<144>(a).toBinary();

    bool result = check<144, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_148)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<148>(a).toBinary();

    bool result = check<148, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_152)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<152>(a).toBinary();

    bool result = check<152, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_156)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<156>(a).toBinary();

    bool result = check<156, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_160)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<160>(a).toBinary();

    bool result = check<160, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_164)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<164>(a).toBinary();

    bool result = check<164, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_168)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<168>(a).toBinary();

    bool result = check<168, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_172)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<172>(a).toBinary();

    bool result = check<172, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_176)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<176>(a).toBinary();

    bool result = check<176, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_180)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<180>(a).toBinary();

    bool result = check<180, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_184)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<184>(a).toBinary();

    bool result = check<184, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_188)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<188>(a).toBinary();

    bool result = check<188, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_192)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<192>(a).toBinary();

    bool result = check<192, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_196)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<196>(a).toBinary();

    bool result = check<196, 200>(shifted, raw);

    EXPECT_TRUE(result);
}


TEST(staticShiftLeft, 200_200)
{
    ArbiInt<200> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftLeft<200>(a).toBinary();

    bool result = check<200, 200>(shifted, raw);

    EXPECT_TRUE(result);
}

