#include "QuBLAS.h"
#include <bitset>
#include <iostream>
#include <utility>

int main()
{
    using type = Qu<intBits<9>, fracBits<8>>;

    using matType = Qu<dim<3, 3>, type>;

    matType A = {
        4, 12, -16,
        12, 37, -43,
        -16, -43, 98};
    //  A.display();
    Qpotrf(A);

    A.display();

    Qu<dim<3>, type> B = {
        -20, -43, 192};

    Qpotrs(A, B);

    B.display();
}