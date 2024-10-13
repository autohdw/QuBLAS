
#include "QuBLAS.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>

using namespace QuBLAS;

 

using type1 = Qu<intBits<12>, fracBits<10>>;
using type2 = Qu<intBits<0>, fracBits<20>>;

using rx_dmrs_descrambing_add_t = Qu<intBits<12>, fracBits<10>>;

int main()
{
    type1 a;

    a.data.data = 0x29db9;

    a.display();

    type2 b;

    b.data.data = 0xb504f;

    b.display();

    auto res = Qmul<rx_dmrs_descrambing_add_t>(a, b);

    res.display();

 
}
