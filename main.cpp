#include "QuBLAS.h"
#include <bitset>
#include <iostream>
#include <utility>
#include <chrono>
#include <vector>





int main()
{
    using type1 = Qu<intBits<4>,fracBits<4>>;
    using type2 = Qu<intBits<2>,fracBits<5>>;

    using vec_t_1 = Qu<dim<3>,type1>;
    using vec_t_2 = Qu<dim<3>,type2>;

    vec_t_1 vec1 = {1,2,3};
    vec_t_2 vec2 = {1,2,3};

    vec1 = vec2;


 

}