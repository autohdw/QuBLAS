#include "QuBLAS.h"
#include <utility>

int main()
{

    Qu_s a = 5;

    a.display();

    Qu_s<isSigned<false>> b;

    b=a;

    b.display();

}