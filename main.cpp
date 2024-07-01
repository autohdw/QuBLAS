#include "QuBLAS.h"
#include <bitset>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

using namespace QuBLAS;

int main()
{
    using type1 = Qu<intBits<4>, fracBits<4>, isSigned<false>>;

    type1 a;

    a.fill();

    std::cout<<a.toDouble()<<std::endl;
    std::cout<<a.data<<std::endl;

    a.display();

 


    return 0;
}