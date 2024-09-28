
#include "QuBLAS.h"
#include <algorithm>
#include <sys/types.h>

using namespace QuBLAS;

int main()
{
    using High_t = Qu<intBits<70>, fracBits<70>, isSigned<true>, QuMode<TRN::SMGN>>;
    using Mid_t = Qu<intBits<30>, fracBits<30>, isSigned<true>, QuMode<TRN::SMGN>>;
    using Low_t = Qu<intBits<10>, fracBits<10>, isSigned<true>, QuMode<TRN::SMGN>>;

    using target_t = Qu<intBits<1>, fracBits<1>, isSigned<true>, QuMode<TRN::SMGN>>;

    High_t from = -1.25;
    // from.data.data[1] ++;
    from.display("from");

    target_t target = from;

    target.display("HighToTargetPositive");



    return 0;
}