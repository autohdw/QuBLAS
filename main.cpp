
#include "QuBLAS.h"

using namespace QuBLAS;

int main()
{

    using type = Qu<intBits<-12>, fracBits<42>>;

    using complex_t = Qu<type, type>;

    complex_t a = {0.000118430797345516, -5.00646053666303e-05};
    complex_t b = {0.000117963441140594, 5.11566487885574e-05};

    a.display();
    b.display();

    double a_real = 0.000118430797345516;
    double a_imag = -5.00646053666303e-05;
    double b_real = 0.000117963441140594;
    double b_imag = 5.11566487885574e-05;

    auto ac = Qmul<type>(a.real, b.real);
    auto bd = Qmul<type>(a.imag, b.imag);
    auto ad = Qmul<type>(a.real, b.imag);
    auto bc = Qmul<type>(a.imag, b.real);

    auto acbd = Qsub<type>(ac, bd);
    auto adbc = Qadd<type>(ad, bc);

    ac.display("ac");
    double ac_true = a_real * b_real;
    std::cout << "True ac: " << ac_true << std::endl;

    bd.display("bd");
    double bd_true = a_imag * b_imag;
    std::cout << "True bd: " << bd_true << std::endl;

    ad.display("ad");
    double ad_true = a_real * b_imag;
    std::cout << "True ad: " << ad_true << std::endl;

    bc.display("bc");
    double bc_true = a_imag * b_real;
    std::cout << "True bc: " << bc_true << std::endl;

    acbd.display("acbd");
    double acbd_true = ac_true - bd_true;
    std::cout << "True acbd: " << acbd_true << std::endl;

    adbc.display("adbc");
    double adbc_true = ad_true + bc_true;
    std::cout << "True adbc: " << adbc_true << std::endl;
}