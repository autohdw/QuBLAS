
#include "QuBLAS.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>

using namespace QuBLAS;

using namespace ANUS;


 






int main()
{
    using type = Qu<intBits<0>, fracBits<15>, OfMode<SAT::SMGN>>;

    type a =  -0.75;

    a.display("a");


 
}