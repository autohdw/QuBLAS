
#include "QuBLAS.h"
#include <sys/types.h>

using namespace QuBLAS;

int main()
{
 

    double dbl = 512;

    Qu<intBits<8>,fracBits<8>, isSigned<false>> a = dbl;
 
     
    a.display("a");

    return 0;
}