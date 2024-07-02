#include "QuBLAS.h"
#include <bitset>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

using namespace QuBLAS;

 

 

int main()
{
    using type1 = Qu<>;
    Qu<dim< 3,3>, type1> q1 = {1,2 ,3,4,5,6,7,8,9};

    q1.toMatlab("q1");
 
 
}


