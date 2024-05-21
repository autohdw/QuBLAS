#include "QuBLAS.h"
#include <bitset>
#include <iostream>
#include <utility>
#include <chrono>
#include <vector>





int main()
{
    using type1 = Qu<intBits<4>,fracBits<4>>;

    type1 a = -100  ;

    auto res = Qabs(a);

    a.display("a");
    res.display("res");


 

}