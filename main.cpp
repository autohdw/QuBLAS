
#include "QuBLAS.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>

using namespace QuBLAS;

using namespace ANUS;


 






int main()
{


    using type1 = Qu<intBits<32>, fracBits<32>>;
    using type2 = Qu<intBits<20>, fracBits<0>>;

    type2 b = 10000;


    type1 a = b;

    a.display();
}