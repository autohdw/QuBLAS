#include "QuBLAS.h"
#include <bitset>
#include <iostream>
#include <utility>

int main()
{


    using type1 = Qu<intBits<4>, fracBits<9>>;
    using type2 = Qu<intBits<5>, fracBits<10>>;
 

 

    using list = TypeList<type1, type2, type1, type2>;

    using gram_t = GramType<3, type1, type2>;

    gram_t m1 = {1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9};

    // m1.display();

    using vec_t = Qu<dim<3>, type1>;

    vec_t x = {1.1,1.2,1.3};

    vec_t y ;

    Qgemv(y, m1, x);

    y.display();




 

 

 





}