
#include "QuBLAS.h"

using namespace QuBLAS;

int main()
{
    Qu<dim<2,2>, Qu<>> mat = {1, 2, 3, 4};
    
    Qu<Qu<>,Qu<>> a = {1,2};

    Qu<dim<2,2>, Qu<Qu<>,Qu<>>>  res = Qadd(mat, a);

    std::cout << res << std::endl;
 

}