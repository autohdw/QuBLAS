#include "QuBLAS.h"
#include <bitset>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

using namespace QuBLAS;

int main()
{
    using b_t = Qu<intBits<4>, fracBits<8>, isSigned<true>>;

    b_t b;

    for(auto i = 0; i < 10000; i++)
    {
        b.fill();

        // check if the 13th bit is 1
        unsigned int mask = 1 << 12;

        // check if the 13th bit is 1 but b.data > 0
        if((b.data & mask) && b.data > 0)
        {
            std::cout << "b.data: " << b.data << std::endl;
            b.display();
        }
    }

    std::cout<<"Done!" << std::endl;

  
 

 


    return 0;
}