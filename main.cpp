#include "QuBLAS.h"
#include <bitset>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

using namespace QuBLAS;

int main()
{
    using type1 = Qu<intBits<3>, fracBits<3>>;
    using type2 = Qu<intBits<2>, fracBits<3>>;
    using type3 = Qu<intBits<3>, fracBits<4>>;

    Qu<dim<3>, type1> a = {1, 2, 3};
    Qu<dim<3>, type2> b = {4, 5, 6};

    auto c = Qsub<type3>(a, b);

    c.display();
}
