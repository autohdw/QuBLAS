
#include "QuBLAS.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>

using namespace QuBLAS;

 

int main()
{
    // using High_t = Qu<intBits<70>, fracBits<70>, isSigned<true>, QuMode<RND::POS_INF>>;
    // using Mid_t = Qu<intBits<30>, fracBits<30>, isSigned<true>, QuMode<RND::POS_INF>>;
    using Low_t = Qu<intBits<10>, fracBits<10>, isSigned<true>, QuMode<RND::POS_INF>>;

    using target_t = Qu<intBits<1>, fracBits<1>, isSigned<true>, QuMode<RND::POS_INF>>;

    Low_t from = 1.2;
    from.display("HighToTargetNegative");
 
    target_t target = from;

    target.display("HighToTargetPositive");

    std::cout << std::bitset<32>(from.data.data) << std::endl;


    return 0;
}