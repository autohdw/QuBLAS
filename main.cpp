#include "QuBLAS.h"
#include <bitset>
#include <iostream>
#include <utility>

int main()
{

    using type1 = Qu<intBits<8>, fracBits<10>>;
    using type2 = Qu<intBits<5>, fracBits<10>>;

    using mat_t = Qu<dim<3, 3>, type1>;
    using vec_t = Qu<dim<3>, type1>;

    mat_t mat1 = {
        4, 12, -16,
        12, 37, -43,
        -16, -43, 98};

    // // mat1.display();
    Qpotrf(mat1);



    vec_t vec1 = {-20, -43, 192};

    Qpotrs(mat1, vec1);

    mat1.display();
    vec1.display();

 ;
}