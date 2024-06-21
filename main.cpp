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

    type4 a = 0.5;

    type3 b = 0.5;

    auto less = a<b;
    auto lessEqual = a<=b;
    auto greater = a>b;
    auto greaterEqual = a>=b;
    auto equal = a==b;
    auto notEqual = a!=b;

    // print all the results
    std::cout << "a < b: " << less << std::endl;
    std::cout << "a <= b: " << lessEqual << std::endl;
    std::cout << "a > b: " << greater << std::endl;
    std::cout << "a >= b: " << greaterEqual << std::endl;
    std::cout << "a == b: " << equal << std::endl;
    std::cout << "a != b: " << notEqual << std::endl;
 
 
}