
#include "QuBLAS.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>

using namespace QuBLAS;

int main()
{
    using from_t = Qu<intBits<3>, fracBits<5>>;
 
    using target_t = Qu<intBits<3>, fracBits<2>, QuMode<RND::CONV>>;

    from_t from = 1.59375;
    from.display("HighToTargetNegative");

    target_t target = from;

    target.display("target");
 
    return 0;
}

 