
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

    constexpr type a =  2;
    constexpr type b =  3;
    constexpr type c =  4;

    type x = 10;

    auto res = Poly<a,b,c>(x);

    std::cout << res << std::endl;


 
}