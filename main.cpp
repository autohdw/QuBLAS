
#include "QuBLAS.h"
#include <algorithm>
#include <sys/types.h>

using namespace QuBLAS;

 

int main()
{
    using High_t = Qu<intBits<70>, fracBits<70>, isSigned<true>, QuMode<TRN::SMGN>>;
    using Mid_t = Qu<intBits<30>, fracBits<30>, isSigned<true>, QuMode<TRN::SMGN>>;
    using Low_t = Qu<intBits<10>, fracBits<10>, isSigned<true>, QuMode<TRN::SMGN>>;

    using target_t = Qu<intBits<2>, fracBits<3>, isSigned<true>, QuMode<TRN::SMGN>>;

    Low_t from = -1.0625;
    from.display("HighToTargetNegative");
 
    target_t target = from;

    target.display("HighToTargetPositive");

 

    return 0;
}