
#include "QuBLAS.h"

using namespace QuBLAS;

int main()
{
    using type = Qu<>;
    using complex_t = Qu<type,type>;
    using vec_t = Qu<dim<4>,complex_t>;

    vec_t v1;
    v1[0] = std::complex<double>(1,1);
    v1[1] = std::complex<double>(2,2);
    v1[2] = std::complex<double>(3,3);
    v1[3] = std::complex<double>(4,4);

    type a = 1.5;

    vec_t v2 = a * v1 ;
 

}