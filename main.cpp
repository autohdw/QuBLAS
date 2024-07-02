#include "QuBLAS.h"
#include <bitset>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

using namespace QuBLAS;

int main()
{
    using type1 = Qu<intBits<4>, fracBits<8>, isSigned<true>>;
    using type2 = Qu<intBits<3>, fracBits<5>, isSigned<true>>;

    using vec_t_1 = Qu<dim<4>, type1>;
    using vec_t_2 = Qu<dim<4>, type2>;

    vec_t_1 vec1 = {1, 2, 3, 4};
    vec_t_2 vec2 = {5, 6, 7, 8};

    vec1 = vec2;

    vec1 = {1,2,3,4};

 
  
 

 


    return 0;
}