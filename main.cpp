#include "QuBLAS.h"

#include <format>
#include <iostream>

using namespace QuBLAS;
using namespace QuBLAS::indices;

int main()
{
    using q = Q<4_i, 8_f, signed_, rnd::conv, sat::tcpl>;

    constexpr auto pi = "3.1415"_dq | to<q>;
    constexpr auto bits = "1101.101"_bq | to<q>;

    std::cout << std::format("pi={:.6f}, bits={:b}, raw=0x{:X}\n",
                             pi, bits, bits);

    using left_t = Qu<dim<2, 3>, q>;
    using right_t = Qu<dim<3, 2>, q>;

    left_t left{1, 4, 2, 5, 3, 6};
    right_t right{7, 9, 11, 8, 10, 12};

    auto middle = left[all, slice<1, 3>];
    auto playful = Qabs((middle + q{1}) * q{-2}).eval();
    auto product =
        (ein[_i, _k] <<= ein[left, _i, _j] * ein[right, _j, _k]).eval();

    std::cout << "slice AST:\n" << playful << "\n\n";
    std::cout << "einsum:\n" << product << '\n';
}
