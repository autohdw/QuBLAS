#include "QuBLAS.h"
#include <iostream>
#include <string>
using namespace QuBLAS;

int main()
{
    // ------------ vector type ------------
    using fixed_type = Qu<intBits<5>, fracBits<0>>;
    using vec_type = Qu<dim<2, 3>, fixed_type>;
    using complex_vec_type = Qu<dim<3>, Qcomplex<fixed_type, fixed_type>>;
    vec_type v = {1, 2, 3, 4, 5, 6};

    std::string v_res = BitStream<r2l<1>, l2r>(v);
    std::cout << v_res << '\n';

    auto z = BitStream<complex_vec_type, l2r, l2r>(v_res);
    std::cout << z << "\n";

    // using fixed_t = Qu<intBits<5>, fracBits<0>>;
    // fixed_t v1 = 4;

    // std::string v_res = BitStream<l2r>(v1);
    // std::cout << v_res << '\n';
    // auto z = BitStream<Qu<dim<2>, intBits<5>, fracBits<0>>, l2r, l2r>(v_res);
    // std::cout << z << "\n\n";

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