#include "QuBLAS.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>

using namespace QuBLAS;


int main()
{

    auto a = ArbiInt<108>();

    for (int i =0 ; i < 108; i++)
    {
        a.fill();

        a.display();
    }

    
}