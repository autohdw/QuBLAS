
#include "QuBLAS.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>

using namespace QuBLAS;

 

int main()
{
    using real_t = Qu<intBits<35>,fracBits<-15>, OfMode<SAT::SMGN>>;
 
    using from_t = Qu<intBits<13>,fracBits<27>, OfMode<SAT::SMGN>>;

    using float_t = Qu<expBits<14>,valBits<256>>;

    using float_t1 = Qu<expBits<3>,valBits<33>, OfMode<SAT::ZERO>>;

    real_t a = 0.5;

    from_t b = 0.5;

    float_t c = 999999999999999999.99;

    float_t1 d = 123;

    c.display();

    d = c;

    d.display();

    return 0;
}

 