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
    Qu<dim<3, 2>, type1> q1 = {1, 2, 3, 4, 5, 6};

    std::cout << q1 << std::endl;

    Qu<dim<2>, type1> q2 = {1, 2};

    std::cout << q2 << std::endl;

    Qu<dim<3>, type1> q3 ;


    Qgemv(q3, q1, q2);

    std::cout << q3 << std::endl;
}
