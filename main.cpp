
#include "QuBLAS.h"

using namespace QuBLAS;

int main()
{

    using type1 = Qu<QuDynamic>;

    type1 a,b;

    a.intB = 5;
    a.fracB = 3;
    b.intB = 3;
    b.fracB = 4;

    a=1;
    b=2;

    auto c = Qreduce(b,a,a,a,a);

    c.display();

 

    return 0;
}