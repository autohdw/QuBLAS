
#include "QuBLAS.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>

using namespace QuBLAS;

using namespace ANUS;

constexpr Qu<intBits<10>, fracBits<20>> reciprocalLUT_coeff_d28f6d541d6d4df19b1e8b412c4c9a33 = 7.71349707;
constexpr Qu<intBits<10>, fracBits<20>> reciprocalLUT_coeff_c1bc85120c994a2aa54b0aa82ed5f7ba = -22.67908011;
constexpr Qu<intBits<10>, fracBits<20>> reciprocalLUT_coeff_9d253e8d7e6b492582c5c2a8e62770bf = 32.74572555;
constexpr Qu<intBits<10>, fracBits<20>> reciprocalLUT_coeff_7766d934313645319262cad459f36d96 = -24.7175808;
constexpr Qu<intBits<10>, fracBits<20>> reciprocalLUT_coeff_1ee2165e5560419ea708ae0a0dbcb1c9 = 9.33773585;
constexpr Qu<intBits<10>, fracBits<20>> reciprocalLUT_coeff_fb5a93989b8943c48ab46e62e9e44aca = -1.39146644;
using reciprocalLUT_seg_9ffae240577b4a769072b6539a1e1eb6 = Segment<2.0,reciprocalLUT_coeff_d28f6d541d6d4df19b1e8b412c4c9a33,reciprocalLUT_coeff_c1bc85120c994a2aa54b0aa82ed5f7ba,reciprocalLUT_coeff_9d253e8d7e6b492582c5c2a8e62770bf,reciprocalLUT_coeff_7766d934313645319262cad459f36d96,reciprocalLUT_coeff_1ee2165e5560419ea708ae0a0dbcb1c9,reciprocalLUT_coeff_fb5a93989b8943c48ab46e62e9e44aca>;
using reciprocalLUT = Qapprox_s<reciprocalLUT_seg_9ffae240577b4a769072b6539a1e1eb6>;

int main()
{
    using input_t = Qu<intBits<10>, fracBits<10>>;

    input_t x = 1.9;

    input_t res ;
    
    res = reciprocalLUT::execute(x);



    res.display();

    Qu<intBits<40>, fracBits<40>> res2 = res;

    res2.display();
}


// int main()
// {
//     using type1 = Qu<intBits<10>, fracBits<20>>;

//     type1 a = - 12.12312;

//     a.display();

//     using type2 = Qu<intBits<40>, fracBits<40>>;

//     type2 b;

//     b = a;

//     b.display();
// }