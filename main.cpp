
#include "QuBLAS.h"
#include <algorithm>
#include <sys/types.h>

using namespace QuBLAS;

int main()
{
    // int a = -123;

    // std::cout<< std::bitset<32>(a) << std::endl;

    // int b = ~((~a) >> 1);

    // std::cout<< std::bitset<32>(b) << std::endl;
    
    ArbiInt<80> a = -123123;

    a.display();

    auto b = - a;

    b.display();
 
}