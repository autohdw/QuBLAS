#include "QuBLAS.h"
#include <utility>

int main()
{

    using type1 = Qu<intBits<5>,fracBits<6>>;
    using type2 = Qu<intBits<6>,fracBits<7>>;
    using type3 = Qu<intBits<8>,fracBits<9>>;
    using type4 = Qu<intBits<9>,fracBits<10>>;
    using type5 = Qu<intBits<10>,fracBits<11>>;
    using type6 = Qu<intBits<11>,fracBits<12>>;

    using list = TypeList<type1, type2, type3, type4, type5, type6>;

    Qu<dim<2,3>, list> q1 = {1, 2, 3, 4, 5, 6};

    q1.get<1,1>().display();
    
}