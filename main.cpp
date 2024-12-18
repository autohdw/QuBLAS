#include "QuBLAS.h"
#include <iostream>
#include <string>
using namespace QuBLAS;

int main()
{
    // ------------ vector type ------------
    using vecType = Qu<dim<2, 3>, intBits<5>, fracBits<0>>;
    vecType v1 = {1, 2, 3, 4, 5, 6};

    std::string v_res = BitStream<l2r, l2r>(v1);
    std::cout << v_res << '\n';
    auto z = BitStream<vecType, l2r, r2l<2>>(v_res);
    std::cout << z << "\n\n";

    auto sum = v1 * v1;
    std::cout << sum << '\n';

    // // ------------ complex vector type ------------
    // using type1 = Qu<isSigned<true>, intBits<3>, fracBits<2>, OfMode<SAT::ZERO>>;
    // using c_t = Qcomplex<type1, type1>;
    // using complex_vec_t = Qu<dim<3>, c_t>;

    // c_t complex1 = {1.5, 2};
    // c_t complex2 = {5, 0};
    // c_t complex3 = {3, 4};

    // complex_vec_t complex_vec = {complex1, complex2, complex3};
    // std::string c_res = BitStream<l2r, l2r>(complex_vec);
    // std::cout << c_res << '\n';
    // auto str2bit = BitStream<complex_vec_t, r2l<1>, l2r>(c_res);
    // std::cout << str2bit << '\n';

    return 0;
}