
#include "QuBLAS.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>

using namespace QuBLAS;

using namespace ANUS;

constexpr Qu<intBits<40>, fracBits<40>> reciprocalLUT_coff_0 = 5.717728701437725;
constexpr Qu<intBits<40>, fracBits<40>> reciprocalLUT_coff_1 = -11.887489318548910 ;
constexpr Qu<intBits<40>, fracBits<40>> reciprocalLUT_coff_2 = 12.178263947171612 ;
constexpr Qu<intBits<40>, fracBits<40>> reciprocalLUT_coff_3 = -7.032528815312644;
constexpr Qu<intBits<40>, fracBits<40>> reciprocalLUT_coff_4 = 2.459391299065025;
constexpr Qu<intBits<40>, fracBits<40>> reciprocalLUT_coff_5 = -0.539281158217049;
constexpr Qu<intBits<40>, fracBits<40>> reciprocalLUT_coff_6 = 0.074481090279575 ;
constexpr Qu<intBits<40>, fracBits<40>> reciprocalLUT_coff_7 = -0.006284558338393;
constexpr Qu<intBits<40>, fracBits<40>> reciprocalLUT_coff_8 = 0.000295654876854;
constexpr Qu<intBits<40>, fracBits<40>> reciprocalLUT_coff_9 = -0.000005938871649;

using reciprocalLUT_seg_1 = Segment<10.1, reciprocalLUT_coff_0, reciprocalLUT_coff_1, reciprocalLUT_coff_2, reciprocalLUT_coff_3, reciprocalLUT_coff_4, reciprocalLUT_coff_5, reciprocalLUT_coff_6, reciprocalLUT_coff_7, reciprocalLUT_coff_8, reciprocalLUT_coff_9>;

using reciprocalLUT = Qapprox_s<reciprocalLUT_seg_1>;

int main()
{
    using input_t = Qu<intBits<40>, fracBits<40>>;

    input_t x = 6;

    std::cout << reciprocalLUT::execute(x) << std::endl;
}