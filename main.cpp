
#include "QuBLAS.h"

using namespace QuBLAS;

int main()
{
    using type = Qu<>;
    using complex_t = Qu<type,type>;
    

    complex_t a = {1.123, 2.351};

    type b = 2.131131;


    using innerT  = Qu<intBits<2>,fracBits<2>>;
    using innerT2  = Qu<intBits<3>,fracBits<3>>;
    using innerT3  = Qu<intBits<4>,fracBits<4>>;
    using innerT4  = Qu<intBits<5>,fracBits<5>>;
    using innerT5  = Qu<intBits<6>,fracBits<6>>;
    using innerT6  = Qu<intBits<7>,fracBits<7>>;

    auto res1 = Qmul<
    BasicComplexMul<
    acT<innerT>,
    bdT<innerT2>,
    adT<innerT3>,
    bcT<innerT4>,
    acbdT<innerT5>,
    adbcT<innerT6>
    >>(a,a);

    res1.display();


    // auto res2 = Qadd<realT<innerT>,imagT<innerT2>>(a,a);

    // res2.display();

 

    
 

}