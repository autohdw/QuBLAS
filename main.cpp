#include "QuBLAS.h"
#include <bitset>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

using namespace QuBLAS;

int main()
{

    using type1 = Qu<intBits<5>, fracBits<4>>;
    using type2 = Qu<intBits<3>, fracBits<6>>;
    using type3 = Qu<intBits<4>, fracBits<5>>;
    using type4 = Qu<QuDynamic>;
 
    using complex_t_1 = Qcomplex<type1, type2>;
    using complex_t_2 = Qcomplex<type3, type4>;

    complex_t_1 a = {1, 2};
    complex_t_2 b = {3, 4};

    complex_t_1 c = {5, 6};

 
    a=b;
    a.display();

    a=c;
    a.display();

  

 
   
}
