#include "QuBLAS.h"
#include <bitset>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

using namespace QuBLAS;

int main()
{

    using type1 = Qu<intBits<14>, fracBits<2>>;
    using type2 = Qu<intBits<13>, fracBits<5>>;
    using type3 = Qu<intBits<16>, fracBits<5>>;
    using type4 = Qu<QuDynamic>;

    using mat_t_1 = Qu<dim<3, 4>, type1>;
    using mat_t_2 = Qu<dim<2, 3>, type2>;

    mat_t_1 mat1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    // // 1 4 7 10
    // // 2 5 8 11
    // // 3 6 9 12

    mat_t_2 mat2 = {1, 2, 3, 4, 5, 6};

    // // 1 3 5
    // // 2 4 6

    // mat_t_2 mat3 = Qslice<sr<0, 0, 1>, sr<1, 1, 3>>(mat1) + mat2;
    mat_t_2 mat3 = Qslice(-mat1*mat1, srd(0, 0, 1), srd(1, 1, 3)) + mat2;

    // // 4 7 10
    // // 5 8 11

    // // +

    // // 1 3 5
    // // 2 4 6

    std::cout << mat3 << std::endl;

    

 

    
}
