# QuBLAS

`QuBLAS` is pronounced as  [tɕʰy.blɑ:s]

This library provides simulation capabilities for fixed-point arithmetic operations in C++, tailored for behavioral modeling and accuracy testing of algorithms in a hardware context.

QuBLAS is designed to mimic the behavior of fixed-point arithmetic as closely as possible to what one would expect when running an algorithm on actual hardware such as ASICs or FPGAs. The library supports various quantization modes and overflow handling schemes, allowing users to simulate and explore different numerical and structural scenarios for their designs.


## Installation

Copy `include/QuBLAS.h` to use.

## Usage

```cpp
#include "QuBLAS.h"

#include <format>
#include <iostream>

using namespace QuBLAS;

int main()
{
    // standard usage
    using old_q = Qu<OfMode<SAT::TCPL>, fracBits<4>, isSigned<true>,
                     intBits<6>, QuMode<RND::CONV>>;

    // same number, fewer characters
    using q = Q<6_i, 4_f, signed_, rnd::conv, sat::tcpl>;
    using wide = Q<10_i, 4_f, signed_, rnd::conv, sat::tcpl>;
    using strange = Q<6_i, -3_f, unsigned_, trn::smgn, wrp::tcpl>;

    old_q old = 1.25;
    strange perfectly_normal = 16; // negative frac bits. hardware happens.

    // textual literals supported
    constexpr q bits = "1101.101"_bq | to<q>;
    constexpr q pi = "3.1415"_dq | to<q>;

    auto a = Qadd<q>(bits, pi);
    auto b = Qmul<wide>(a, q{2});
    auto full = Qmul<FullPrec>(bits, pi);
    auto c = Qabs(Qdiv<q>(Qsub<wide>(b, q{1}), q{2}));

    // tensors
    using matrix = Qu<dim<3, 4>, q>;
    matrix m{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    auto one = m[1, 2];
    auto row = m[1, all];
    auto block = m[slice<0, 2>, slice<1, 4>];
    auto smaller = block[all, slice<0, 2>];
    row[0] = q{42}; // views write through. convenient or alarming.

    // lazy evaluation
    auto lazy = Qabs((m + q{1}) * q{-2});
    auto lazy_column = (m + q{1})[all, 2];
    auto frozen = lazy.eval();

    // tree reduction for ASICs
    using layers = TypeList<q, wide>;
    auto total = Qreduce<layers>(frozen);
    auto another_total = Qreduce<wide>(bits, pi, one, q{1}, q{2});

    // python style einsum
    using left_t = Qu<dim<2, 3>, q>;
    using right_t = Qu<dim<3, 2>, q>;
    left_t left{1, 4, 2, 5, 3, 6};
    right_t right{7, 9, 11, 8, 10, 12};

    auto product = einsum<"ij,jk->ik">(left, right).eval();
    auto inferred = einsum<"ij,jk">(left, right);
    auto trace = einsum<"ii->">(Qu<dim<2, 2>, q>{1, 3, 2, 4}).eval();

    // index notation
    using namespace QuBLAS::indices;
    auto same_product =
        (ein[_i, _k] <<= ein[left, _i, _j] * ein[right, _j, _k]).eval();

    // complex
    using cq = Qcomplex<q, q>;
    using same_cq = Qu<q, q>;
    cq z{q{1}, q{2}};
    same_cq also_z{q{3}, q{4}};
    auto zz = Qmul(z, z);

    // nonlinear things live in ANUS
    constexpr q p0{1};
    constexpr q p1{2};
    auto line = ANUS::Qpoly<p0, p1>(pi);
    using low = ANUS::Segment<0.0, p0, p1>;
    using high = ANUS::Segment<100.0, p1, p0>;
    auto approximately_something = ANUS::Qapprox<low, high>(pi);

    // std::format
    auto text = std::format("{:.4f} {:b} {:X} {:q}", pi, pi, pi, pi);
    std::cout << text << '\n' << product << '\n';

    auto host_number = pi.toDouble();
    auto bit_string = pi.toString();
    auto raw = pi.data; // legal. Not stable.

    // more to come ...
}
```


## Guarantees

The `Qu`, `Q`, `Qadd`, `Qmul`, `Qsub`, `Qdiv`, and `Qreduce` spellings are the parts that try not to move.

`ArbiInt<N>` and scalar `Qu_s::data` are public. Use them if you want. Nothing about them is stable.
