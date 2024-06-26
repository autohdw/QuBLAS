#include "QuBLAS.h"
#include <bitset>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

using namespace QuBLAS;

int main()
{
    using type1 = Qu<intBits<12>, fracBits<8>>;
    using type2 = Qu<intBits<12>, fracBits<8>>;
    using type3 = Qu<intBits<12>, fracBits<8>>;
    using type4 = Qu<intBits<7>, fracBits<9>>;

    using A_t = Qu<dim<3, 3>, type1>;
    using L_t = Qu<dim<3, 3>, type2>;
    using D_t = Qu<dim<3>, type3>;

    A_t A = {69, 27, 67, 27, 38, 72, 67, 72, 142};
    L_t L;
    D_t D;

    Qsytrf<QsytrfSumLDArgs<type4>>(L, D, A);

    L.display("L");
    D.display("D");

    // using Linv_t = Qu<dim<3, 3>, type2>;

    // Linv_t Linv;

    // Qtrtri(Linv, L);

    // Linv.display();
 
}