
#include "QuBLAS.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>

using namespace QuBLAS;

 

int main()
{
    using input_t = Qu<intBits<10>, fracBits<10>>;

    using vec_t = Qu<dim<3>, input_t>;

    vec_t a = {1, 2, 3};
    vec_t b = {4, 5, 6};

    auto c = a + b;

     
}

 