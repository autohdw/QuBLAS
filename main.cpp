
#include "QuBLAS.h"
#include <sys/types.h>

using namespace QuBLAS;

int main()
{
 

    double dbl = 12331233123.523123;

    Qu<intBits<100>,fracBits<2>, isSigned<false>> a = dbl;
 
     
    a.display("a");

    return 0;
}