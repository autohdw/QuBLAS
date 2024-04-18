#include "QuBLAS.h"
#include <bitset>
#include <utility>

int main()
{

    using type1 = Qu<intBits<7>, fracBits<5>>;
    using type2 = Qu<intBits<8>, fracBits<3>>;
    using type3 = Qu<intBits<10>, fracBits<4>>;

    Qu<dim<3,4>, type1> A= {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    Qu<dim<4>, type2> x = {1, 2, 3, 4};
    Qu<dim<3>, type3> y = {-1, -2, -3};

    using list = TypeList<type1, type2>;

    constexpr Qu<> alpha = 2;
    constexpr Qu<> beta = 1;

    Qgemv<QgemvAddArgs<list>,QgemvAlpha<alpha>,QgemvBeta<beta> >(y, A, x);

    y.display();

    return 0;
}