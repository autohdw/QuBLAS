#include "QuBLAS.h"
#include <utility>

int main()
{
    using type1 = Qu<intBits<3>, fracBits<7>>;
    using type2 = Qu<intBits<4>, fracBits<5>>;
    using type3 = Qu<intBits<5>, fracBits<3>>;

    using dim1 = dim<4>;

    Qu<dim1, type1> q1 = {1, 2, 3, 4};
    

    auto res1 = Qreduce<type3>(q1);

    return 0;

}