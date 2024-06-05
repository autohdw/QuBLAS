#include "QuBLAS.h"
#include <bitset>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

int main()
{

    // 10 types

    using type1 = Qu<intBits<7>, fracBits<3>>;
    using type2 = Qu<intBits<8>, fracBits<2>>;
    using type3 = Qu<intBits<3>, fracBits<4>>;
    using type4 = Qu<intBits<6>, fracBits<5>>;

    using c_t_1 = Qcomplex<type1, type2>;
    using c_t_2 = Qu<type3, type4>; // identical to Qcomplex<type3, type4>

    c_t_1 a = {1, 2};
    c_t_2 b = {3, 4};

 
    type3 c = 3;
    type4 d = 4;

    using vec_t_1 = Qu<dim<3>, type1>;
    using vec_t_2 = Qu<dim<3>, c_t_1>;

    vec_t_1 v1 = {1, 2, 3};
    vec_t_2 v2 = {a, a, a};

 

 
 


 
 

 

 

 

    
}