#include "QuBLAS.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>

using namespace QuBLAS;

int main()
{

    ArbiInt<129> tt = 123;


    using type1 = Qu<expBits<10>, valBits<100>>;
    using type2 = Qu<expBits<20>, valBits<100>>;

    using type3 = ArbiInt<128>;

    type1 a = 34534.436;
    type2 b = 0;

    auto sum = a * b;

    a.display();
    b.display();

    sum.display();  
    return 0; 
}


 