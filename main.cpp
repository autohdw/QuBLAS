#include "QuBLAS.h"
#include <bitset>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

using namespace QuBLAS;

int main()
{

    using type1 = Qu<intBits<4>, fracBits<2>>;
    using type2 = Qu<intBits<3>, fracBits<5>>;
    using type3 = Qu<intBits<6>, fracBits<5>>;
    using type4 = Qu<QuDynamic>;

    using vec_t_1 = Qu<dim<4>, type1>;
    using vec_t_2 = Qu<dim<4>, Qcomplex<type1, type2>>;

      vec_t_1 vec1 = {1, 2, 3, 4};
     vec_t_2 vec2 = {1, 2, 3, 4};

    vec2.display();

 
      auto vec3 = Qmul(vec1, vec2);

    vec3.display();
 

    

  

 
   
}
