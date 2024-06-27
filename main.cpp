#include "QuBLAS.h"
#include <bitset>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

using namespace QuBLAS;

int main()
{
    using type1 = Qu<intBits<5>, fracBits<6>>;

    using mat_t = Qu<dim<3,3>, type1>;

    mat_t a = {
        1, 2, 3,
        4, 5, 6,
        7, 8, 9
    };

    std::cout << a << std::endl;


    return 0;
}