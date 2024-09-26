
#include "QuBLAS.h"
#include <sys/types.h>

using namespace QuBLAS;

int main()
{
 

    ArbiInt<150> a;

    a = ~a;

    a.display();
 
    auto b = staticShiftRight<100>(a);

    b.display();

    return 0;
}