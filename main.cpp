#include "QuBLAS.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>

using namespace QuBLAS;

int main()
{

    ArbiInt<129> tt = 123;

    tt.display();

    std::printf("%lf\n",tt.toDouble());

    using type1 = Qu<expBits<23>, valBits<600>>;
    using type2 = Qu<intBits<66>, fracBits<66>>;

    type2 b = -34125.1414125259;

    b.display();

    type1 a;

    a = b;

    a.display();
 
    return 0; 
}


 