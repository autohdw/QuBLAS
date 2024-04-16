#include "QuBLAS.h"
#include <bitset>
#include <utility>

int main()
{

    using type1 = Qu<intBits<7>, fracBits<5>>;
    using type2 = Qu<intBits<8>, fracBits<3>>;
    using type3 = Qu<intBits<9>, fracBits<4>>;


    Qu<dim<2,4>, type1> q1 = {0,1,2,3,4,5,6,7};
    Qu<dim<4,3>, type2> q2 = {0,1,2,3,4,5,6,7,8,9,10,11};
    Qu<dim<2,3>, type3> q3;

    using list = TypeList<type1, type2>;

    Qgemul<QgemulAddArgs<list>>(q3, q1, q2);

    q3.display();


    
    return 0;
}