# QuBLAS

`QuBLAS` is pronounced as  [tɕʰy.blɑ:s]

This library provides simulation capabilities for fixed-point arithmetic operations in C++, tailored for behavioral modeling and accuracy testing of algorithms in a hardware context.

QuBLAS is designed to mimic the behavior of fixed-point arithmetic as closely as possible to what one would expect when running an algorithm on actual hardware such as ASICs or FPGAs. The library supports various quantization modes and overflow handling schemes, allowing users to simulate and explore different numerical and structural scenarios for their designs.


## Installation

- QuBLAS is header-only and contains only one header file `QuBLAS.h`.

## Usage

- Set the C++ standard to C++23 or higher in your project.

```cpp

#include "QuBLAS.h"

using namespace QuBLAS;

int main()
{

       // Define a 17-bit fixed-point number with 8 integer bits, 8 fractional bits and a sign bit.
    Qu<intBits<8>, fracBits<8>, isSigned<true>, QuMode<TRN::TCPL>, OfMode<SAT::ZERO>> a = 1.0;

    // Tags can be in any order and are all optional.
    using type1 = Qu<isSigned<true>, intBits<6>, fracBits<3>, OfMode<SAT::ZERO>>;
    type1 q1 = 1.0;

    // Negative width is also supported
    using type2 = Qu<intBits<6>, fracBits<-3>>;
    type2 q2 = 16;

    // Use dim to create an any-dimensional tensor.
    // dim should be the first template parameter.
    using vecType = Qu<dim<4>, intBits<4>>;
    vecType v1 = {1.0, 2.0, 3.0, 4.0};

    using matType = Qu<dim<4, 4>, type1>;
    matType m1 = {1.0, 2.0, 3.0, 4.0,
                  5.0, 6.0, 7.0, 8.0,
                  9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0};

    using highDimType = Qu<dim<4, 1, 2>, type1>;
    highDimType h1 = {1.0, 2.0, 3.0, 4.0,
                      5.0, 6.0, 7.0, 8.0};

    // index a tensor with [] operator
    auto elem = m1[1, 2];

    // Tree-based reduction operations
    auto red1 = Qreduce<type2>(v1);

    // Per-layer quantization
    using list = TypeList<type1, type2>;
    auto red2 = Qreduce<list>(m1);

    // manully provide the input numbers, can be any type and any number of arguments
    auto red3 = Qreduce<type1>(q1, q2, q1, q2);

    // use ANUS:: to get access to the LUTs, there are 3 predifined LUTs

    // LUT for 1/sqrt(x)
    auto lut1 = ANUS::Qtable<ANUS::rsqrtFunc>(q1);

    // LUT for 1/x
    auto lut2 = ANUS::Qtable<ANUS::reciprocalFunc>(q1);

    // LUT for sqrt(x)
    auto lut3 = ANUS::Qtable<ANUS::sqrtFunc>(q1);

    // the method to define your own LUT
    // inline static constexpr auto myLUT = [](double x) { return std::exp(x); };

    // BLAS operations under development

    matType m3;

    Qgemul<QgemulAddArgs<list>,    // Tree-based reduction for dot product
           QgemulMulArgs<type1>,   // Specify quantization mode for multiplication
           QgemulTransposedA<true> // Tags in any order and are all optional as well
           >(m3, m1, m1);

    // create complex type
    using c_t_1 = Qcomplex<type1, type2>;
    using c_t_2 = Qu<type1, type2>; // identical to Qcomplex<type1, type2>

    c_t_1 complex1 = {1, 2};
    c_t_2 complex2 = {3, 4};

    using complex_vec_t = Qu<dim<3>, c_t_1>;

    complex_vec_t complex_vec = {a, a, a};

    // complex mul
    auto complex_vec_mul = Qmul<TFComplexMul< // calling the method for complex multiplication requireing 3 multipliers and 5 adders
        abT<type2>,
        cdT<type1>,
        baT<type2>,
        // abcT<type4>, // all tags are optional
        // cdbT<type1>,
        badT<type2>,
        ABT<type2>,
        BCT<type2>>>(complex_vec, complex_vec);

    // BitStream

    using vec_t_bits = Qu<dim<6>, type1>;

    vec_t_bits vec_bits = {1.0, 2.0, 3.0, 4.0};

    // vector to std::string
    auto res = BitStream<r2l<3>, r2l<2>>(vec_bits);

    std::cout << res << std::endl;

    // std::string to vector, need to provide the target type
    auto z = BitStream<vec_t_bits, r2l<3>, r2l<2>>(res);

    z.display();

    // more to come ...

    return 0;
}
```

## Development Status

The library is under active development and the API is subject to change.
