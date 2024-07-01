#include "QuBLAS.h"
#include <bitset>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

using namespace QuBLAS;

int main()
{
    using type1 = Qu<intBits<19>, fracBits<6>>;
    using type2 = Qu<intBits<14>, fracBits<6>>;

    type1 a = 0.5;
    type2 b = 0.5;

    auto c = a + b;

   


    return 0;
}