
#include "QuBLAS.h"

using namespace QuBLAS;

int main()
{

    using seg1 = sr<0,1,3>;    
    using seg2 = sr<1,2,4>;  
    using type = Qu<>;

    using MatrixT = Qu<dim<4,4>,type>;

    MatrixT A = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};

    std::cout<<A<<std::endl;

    using resT = SliceExpression<MatrixT,seg1,seg2>  ;

 
    resT B = A;
 
    auto res  = B[3];

    std::cout<<res<<std::endl;

 
 
}