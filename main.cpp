
#include "QuBLAS.h"
#include <algorithm>
#include <sys/types.h>

using namespace QuBLAS;

int main()
{
    using High_t = Qu<intBits<70>, fracBits<70>, isSigned<true>, QuMode<TRN::SMGN>>;
    using Mid_t = Qu<intBits<30>, fracBits<30>, isSigned<true>, QuMode<TRN::SMGN>>;
    using Low_t = Qu<intBits<10>, fracBits<5>, isSigned<true>, QuMode<TRN::SMGN>>;

    using target_t = Qu<intBits<1>, fracBits<1>, isSigned<true>, QuMode<TRN::SMGN>>;

    Low_t low = 1.5;
    low.display("low");

    target_t target = low;
 

    target.display("target");

}