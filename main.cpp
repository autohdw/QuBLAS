#include "QuBLAS.h"
#include <utility>

int main()
{
    using list = dim<2, 2, 3, 4>;

    using type1 = Qu<intBits<5>,fracBits<6>>;
    using type2 = Qu<intBits<6>,fracBits<7>>;
    using type3 = Qu<intBits<8>,fracBits<9>>;

    Qu<dim<2, 3, 4>,type1> a = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};

    auto b = a.get<2, 2, 3>();
    auto c = a[2, 2, 3];
    auto d = a[1];
 
 

    b.display();
    c.display();
    d.display();
}