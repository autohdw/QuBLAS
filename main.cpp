
#include "QuBLAS.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>

using namespace QuBLAS;

using namespace ANUS;


 






int main()
{
    using type = Qu<intBits<8>, fracBits<8>, OfMode<SAT::SMGN>>;

    constexpr Qu<intBits<8>, fracBits<8>> a =  2;
    constexpr Qu<intBits<5>, fracBits<6>> b =  3;
    constexpr Qu<intBits<7>, fracBits<8>> c =  4;
    constexpr Qu<intBits<8>, fracBits<8>> d =  5;

    using seg1 = Segment<10.0, a>;
    using seg2 = Segment<20.0, a,b>;
    using seg3 = Segment<30.0, c>;

    type x = 31;
    auto res = Qapprox<seg1, seg2, seg3>(x);

    std::cout << res << std::endl;
 
}