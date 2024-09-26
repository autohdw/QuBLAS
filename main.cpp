
#include "QuBLAS.h"
#include <sys/types.h>

using namespace QuBLAS;

int main()
{
 

    ArbiInt<150> a;

    a.fill();

    a.display();
 
    auto b = staticShiftRight<30>(a);

    b.display();

    return 0;
}