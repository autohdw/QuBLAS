#include "QuBLAS.h"
#include <bitset>
#include <utility>

int main()
{

    using type1 = Qu<intBits<3>, fracBits<5>>;
    using type2 = Qu<intBits<5>, fracBits<3>>;
    using type3 = Qu<intBits<4>, fracBits<4>>;

    type1 a = -0.5;
    type2 b = -0.5;

    a.display();
    b.display();

    auto c = a + b;
    c.display();


    c.fill();
    c.display();

    c.fill();
    c.display();

    // use bits to set the value
    c.fill(0b11110001111);
    c.display();

    return 0;
}