
#include "QuBLAS.h"

using namespace QuBLAS;

int main()
{

    using type1 = Qu<intBits<3>, fracBits<2>>;
    using type2 = Qu<intBits<4>, fracBits<3>>;
    using type3 = Qu<intBits<5>, fracBits<4>>;
    using type4 = Qu<intBits<6>, fracBits<5>>;
    using type5 = Qu<intBits<7>, fracBits<6>>;
    using type6 = Qu<intBits<8>, fracBits<7>>;
    using type7 = Qu<intBits<9>, fracBits<8>>;
    using type8 = Qu<intBits<10>, fracBits<9>>;

    using complex_t = Qu<type1, type2>;

    complex_t a = {1.123123, 2.123123};

    auto b = Qmul<BasicComplexMul<
        acT<intBits<11>>,
        bdT<type2>,
        adT<type3>,
        // bcT<type4>,
        acbdT<type5>,
        adbcT<type6>>>(a, a);

    auto c = Qmul<BasicComplexMul<
        type5>>(a, a);


    auto d = Qadd<type8,type1>(a, a);

    d.display();
}