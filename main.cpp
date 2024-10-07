
#include "QuBLAS.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>

using namespace QuBLAS;

int main()
{
    using type1 = Qu<intBits<3>, fracBits<20>>;

    type1 a = 2.12431;

    a.display();

    using type2 = Qu<intBits<3>, fracBits<30>>;
    type2 b = -3.523531;

    b.display();

    auto c = Qsub<intBits<10>, fracBits<100>>(a, b);

    c.display();
 
    return 0;

 

 
}


 