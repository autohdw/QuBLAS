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

    // Matrix with 2 rows and 3 columns and universal type
    Qu<dim<2,3>, type1> q1 = {1, 2, 3, 4, 5, 6};

    // 懒人写法同样可用
    Qu<dim<2,3>, intBits<5>, fracBits<6>> q3 = {1, 2, 3, 4, 5, 6};

    // static access
    q1.get<1,2>().display();

    // dynamic access
    q1[1,1].display();

    // Matrix with 3 rows and 2 columns and element-wise type
    Qu<dim<3,2>, list> q2 = {1, 2, 3, 4, 5, 6};

    // static access
    q2.get<1,2>().display();

    // dynamic access not possible
    // q2[1,1].display(); 
    
}