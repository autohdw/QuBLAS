#include "QuBLAS.h"
#include <bitset>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

using namespace QuBLAS;

int main()
{
    using type1 = Qu<intBits<12>, fracBits<8>>;
    using type2 = Qu<intBits<12>, fracBits<8>>;
    using type3 = Qu<intBits<12>, fracBits<8>>;
    using type4 = Qu<intBits<7>, fracBits<9>>;

    using A_t = Qu<dim<3, 3>, type1>;
    using L_t = Qu<dim<3, 3>, type2>;
    using D_t = Qu<dim<3>, type3>;

    A_t A = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    L_t L = {1, 0, 0, 2, 1, 0, 3, 4, 1};

    type4 a = 1.0;

    auto res = Qmul<type2>(a, A);


 
 
}