#include "QuBLAS.h"



int main()
{
        Qvec<5> a = {1, 2, 3, 4, 5};
        Qmat<3, 5> b = {1, 2, 3, 4, 5,
                        6, 7, 8, 9, 10,
                        11, 12, 13, 14, 15};

        Qvec<3> c;

        Qgemv(c , b, a);
        c.display();
}