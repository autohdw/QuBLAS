#include "QuBLAS.h"
#include <bitset>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

int main()
{

    // 10 types

    using type1 = Qu<intBits<3>, fracBits<6>>;
    using type2 = Qu<intBits<8>, fracBits<2>>;
    using type3 = Qu<intBits<7>, fracBits<4>>;
    using type4 = Qu<intBits<6>, fracBits<5>>;

    using c_t_1 = Qcomplex<type1, type2>;
    using c_t_2 = Qu<type3, type4>; // identical to Qcomplex<type3, type4>

    c_t_1 a = {1, 2};
    c_t_2 b = {3, 4};

 
    type3 c = 113.123;
    type4 d = 4;

    using vec_t_1 = Qu<dim<6>, type1>;
    using vec_t_2 = Qu<dim<3>, c_t_1>;

    vec_t_1 v1 = {1, 2, 3, 4, 5, 6};
    vec_t_2 v2 = {a, a, a};

    auto res = BitStream<r2l<3>,r2l<2>>(v1);

    std::cout << res << std::endl;

    v1.display();
    // seperate res into 10 bits  each line
    for (int i = 0; i < res.size(); i++)
    {
        if (i % 10 == 0)
        {
            std::cout << std::endl;
        }
        std::cout << res[i] << " ";

    }

    auto z = BitStream<vec_t_1,r2l<3>,r2l<2>>(res);

    z.display();
 
    return 0;

 
 



 

 

 

    
}