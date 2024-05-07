#include "QuBLAS.h"
#include <bitset>
#include <iostream>
#include <utility>

int main()
{


    using type1 = Qu<intBits<4>, fracBits<9>>;
    using type2 = Qu<intBits<5>, fracBits<10>>;
    using type3 = Qu<intBits<6>, fracBits<6>>;
    using type4 = Qu<intBits<8>, fracBits<7>>;

    using mat_t_1 = Qu<dim<2,3>, type1>;
    using mat_t_2 = Qu<dim<3,4>, type2>;
    using mat_t_3 = Qu<dim<2,4>, type3>;

    using list = TypeList<type1, type2, type1, type2>;

    using gram_t = GramType<2, type1, type2>;

    gram_t m1;

    using mat_t = Qu<dim<3,2>, type1>;

    mat_t m2 = {1.1, 1.2, 1.3, 1.4, 1.5, 1.6};

    Qgemul<QgemulTransposedA<true>>
    (m1, m2, m2);

    m1.display();





}