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

    apFixed<dimList<2, 3, 4>> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};

    auto b = a.get<2, 2, 3>();
    auto c = a[2, 2, 3];

    b.display();
    c.display();
}