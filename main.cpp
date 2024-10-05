
#include "QuBLAS.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>

using namespace QuBLAS;

int main()
{
    using type = Qu<intBits<3>, fracBits<100>>;

    type a = 2.1231;

    a.display();
 
    return 0;
}

 