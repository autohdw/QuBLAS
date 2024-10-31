
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

    real_t a = 0.5;

    from_t b = 0.5;

    a = b;

    std::cout << a << std::endl;

}

 