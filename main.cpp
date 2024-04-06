#include "QuBLAS.h"
#include <utility>

int main()
{
    using list = dimList<2, 2, 3, 4>;

    std::cout << list::elemSizeForIndexTail<0>::value << std::endl;
    std::cout << list::elemSizeForIndexTail<1>::value << std::endl;
    std::cout << list::elemSizeForIndexTail<2>::value << std::endl;
    std::cout << list::elemSizeForIndexTail<3>::value << std::endl;
    std::cout << list::elemSizeForIndexTail<4>::value << std::endl;

    apFixed<dimList<5, 2>> a = {1, 2,
                                3, 4,
                                5, 6,
                                7, 8,
                                9, 10};

    auto res1 = a.get<2, 1>();

    res1.display();

    auto res2 = a[2, 1];
}