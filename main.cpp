#include "QuBLAS.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>

using namespace QuBLAS;

int main()
{

    ArbiInt<129> tt = 123;


    using type1 = Qu<expBits<20>, valBits<1000>>;
    using type2 = Qu<expBits<20>, valBits<1000>>;

    using type3 = ArbiInt<128>;

    type1 a = 3.353;
    type2 b = -4.325;

    auto sum = a * b;

    a.display();
    b.display();

    sum.display();
    sum.accurateDisplay();  
    return 0; 
}


 