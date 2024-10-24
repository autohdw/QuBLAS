#include "QuBLAS.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>

using namespace QuBLAS;

int main()
{

    ArbiInt<129> tt = 123;


    using type1 = Qu<expBits<10>, valBits<336>>;
    using type2 = Qu<expBits<20>, valBits<200>>;


    type1 a = -40003.032;
    type2 b = 39678.15;
    auto sum = a + b;

    a.display();
    b.display();

    sum.display();  
    return 0; 
}


 