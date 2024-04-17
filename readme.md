# QuBLAS

This library provides simulation capabilities for fixed-point arithmetic operations in C++, tailored for behavioral modeling and accuracy testing of algorithms in a hardware context.

QuBLAS is designed to mimic the behavior of fixed-point arithmetic as closely as possible to what one would expect when running an algorithm on actual hardware such as ASICs or FPGAs. The library supports various quantization modes and overflow handling schemes, allowing users to simulate and explore different numerical and structural scenarios for their designs.


## Installation

- QuBLAS is header-only and contains only one header file `QuBLAS.h`.

## Usage

- Set the C++ standard to C++23 or higher in your project.

```cpp
#include "QuBLAS.h"

int main() {
    
    // Define a 17-bit fixed-point number with 8 integer bits, 8 fractional bits and a sign bit. 
    Qu<intBits<8>,fracBits<8>,isSigned<true>,QuMode<TRN::TCPL>,OfMode<SAT::ZERO>> a = 1.0;

    // Tags can be in any order and are all optional.
    using type1 = Qu<isSigned<true>,OfMode<SAT::ZERO>>;
    type1 q1 = 1.0;

    // Negative width is also supported
    using type2 = Qu<intBits<6>,fracBits<-3>>;
    type2 q2 = 16;

    // Use dim to create an any-dimensional tensor.
    using vecType = Qu<dim<4>,intBits<4>>;
    vecType v1 = {1.0, 2.0, 3.0, 4.0};

    using matType = Qu<dim<4,4>, type1>;
    matType m1 = {1.0, 2.0, 3.0, 4.0,
                  5.0, 6.0, 7.0, 8.0,
                  9.0, 10.0, 11.0, 12.0,
                  13.0, 14.0, 15.0, 16.0};

    using highDimType = Qu<dim<4,1,2>, type1>;
    highDimType h1 = {1.0, 2.0, 3.0, 4.0,
                      5.0, 6.0, 7.0, 8.0};

    // Support element-wise operations with compile-time broadcasting
    auto add = m1 + v1; // add dim = <4,4>
    
    // Quantization modes specification
    auto mul = Qmul<type2>(m1, h2) // mul dim = <4,4,2>

    // Incomplete type deduction and inplace operations
    matType m2;
    Qadd<intBits<2>>(m2,v1,m2);

    // Tree-based reduction operations
    auto red1 = Qreduce<type2>(vec1);

    // Per-layer quantization
    using list = TypeList<type1, type2>;
    auto red2 = Qreduce<list>(m1);

    // BLAS operations under development
    auto mm = Qgemul<
                QgemulAddArgs<list>,    // Tree-based reduction for dot product
                QgemulMulArgs<type1>,   // Specify quantization mode for multiplication
                QgemulIsTransposedA<false>, // Tags in any order and are all optional as well
    >(m1, m1);

    // more to come...

    return 0;
}
```

## Development Status

The library is under active development and the API is subject to change.
