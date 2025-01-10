#include "QuBLAS.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>

using namespace QuBLAS;


int main()
{

    // using type1 = Qu< intBits<80>, fracBits<47>,OfMode<SAT::SMGN> >;

    // type1 a = 1.0;


    constexpr auto max = ArbiInt<129>::maximum();

    max.display();


    
}