#include "QuBLAS.h"

int main()
{

    apFixed<intBits<3>, fracBits<3>, isSigned<true>> a = 1.25;
    a.display("a");

    apFixed<intBits<3>, fracBits<3>, isSigned<true>> b = -1.25;
    b.display("b");

    std::cout << std::endl;

    apFixed<intBits<3>, fracBits<1>, QuMode<RND::POS_INF>, isSigned<true>> POS_INF_res;

    POS_INF_res = a;
    POS_INF_res.display("POS_INF_res = a");

    POS_INF_res = b;
    POS_INF_res.display("POS_INF_res = b");

    std::cout << std::endl;

    apFixed<intBits<3>, fracBits<1>, QuMode<RND::NEG_INF>, isSigned<true>> NEG_INF_res;

    NEG_INF_res = a;
    NEG_INF_res.display("NEG_INF_res = a");

    NEG_INF_res = b;
    NEG_INF_res.display("NEG_INF_res = b");

    std::cout << std::endl;

    apFixed<intBits<3>, fracBits<1>, QuMode<RND::ZERO>, isSigned<true>> ZERO_res;

    ZERO_res = a;
    ZERO_res.display("ZERO_res = a");

    ZERO_res = b;
    ZERO_res.display("ZERO_res = b");

    std::cout << std::endl;

    apFixed<intBits<3>, fracBits<1>, QuMode<RND::INF>, isSigned<true>> INF_res;

    INF_res = a;
    INF_res.display("INF_res = a");

    INF_res = b;
    INF_res.display("INF_res = b");

    std::cout << std::endl;

    apFixed<intBits<3>, fracBits<1>, QuMode<TRN::TCPL>, isSigned<true>> TCPL_res;

    TCPL_res = a;
    TCPL_res.display("TCPL_res = a");

    TCPL_res = b;
    TCPL_res.display("TCPL_res = b");

    std::cout << std::endl;

    apFixed<intBits<3>, fracBits<5>> CONV_a1 = 1.59375;
    CONV_a1.display("CONV_a1");

    apFixed<intBits<3>, fracBits<5>> CONV_a2 = 1.625;
    CONV_a2.display("CONV_a2");

    apFixed<intBits<3>, fracBits<5>> CONV_a3 = 1.375;
    CONV_a3.display("CONV_a3");

    apFixed<intBits<3>, fracBits<5>> CONV_a4 = 1.65625;
    CONV_a4.display("CONV_a4");

    std::cout << std::endl;

    apFixed<intBits<3>, fracBits<2>, QuMode<RND::CONV>, isSigned<true>> CONV_res;

    CONV_res = CONV_a1;
    CONV_res.display("CONV_res = CONV_a1");

    CONV_res = CONV_a2;
    CONV_res.display("CONV_res = CONV_a2");

    CONV_res = CONV_a3;
    CONV_res.display("CONV_res = CONV_a3");

    CONV_res = CONV_a4;
    CONV_res.display("CONV_res = CONV_a4");

    apFixed<intBits<3>, fracBits<1>, QuMode<TRN::SMGN>, isSigned<true>> SMGN_res;

    SMGN_res = a;
    SMGN_res.display("SMGN_res = a");

    SMGN_res = b;
    SMGN_res.display("SMGN_res = b");

    std::cout << std::endl;

    apFixed<intBits<3>, fracBits<0>, QuMode<TRN::TCPL>, OfMode<SAT::TCPL>> SAT_TCPL_SIGNED_res;

    apFixed<intBits<5>, fracBits<1>> SAT_TCPL_a1 = 19.0;

    SAT_TCPL_SIGNED_res = SAT_TCPL_a1;
    SAT_TCPL_SIGNED_res.display("SAT_TCPL_SIGNED_res = SAT_TCPL_a1");

    apFixed<intBits<5>, fracBits<1>> SAT_TCPL_a2 = -19.0;

    SAT_TCPL_SIGNED_res = SAT_TCPL_a2;
    SAT_TCPL_SIGNED_res.display("SAT_TCPL_SIGNED_res = SAT_TCPL_a2");

    std::cout << std::endl;

    apFixed<intBits<4>, fracBits<0>, QuMode<TRN::TCPL>, OfMode<SAT::TCPL>, isSigned<false>> SAT_TCPL_UNSIGNED_res;

    SAT_TCPL_UNSIGNED_res = SAT_TCPL_a1;
    SAT_TCPL_UNSIGNED_res.display("SAT_TCPL_UNSIGNED_res = SAT_TCPL_a1");

    SAT_TCPL_UNSIGNED_res = SAT_TCPL_a2;
    SAT_TCPL_UNSIGNED_res.display("SAT_TCPL_UNSIGNED_res = SAT_TCPL_a2");

    std::cout << std::endl;

    apFixed<intBits<3>, fracBits<1>, OfMode<SAT::ZERO>> SAT_ZERO_SIGNED_res;

    SAT_ZERO_SIGNED_res = SAT_TCPL_a1;
    SAT_ZERO_SIGNED_res.display("SAT_ZERO_SIGNED_res = SAT_TCPL_a1");

    SAT_ZERO_SIGNED_res = SAT_TCPL_a2;
    SAT_ZERO_SIGNED_res.display("SAT_ZERO_SIGNED_res = SAT_TCPL_a2");

    std::cout << std::endl;

    apFixed<intBits<4>, fracBits<0>, OfMode<SAT::ZERO>, isSigned<false>> SAT_ZERO_UNSIGNED_res;

    SAT_ZERO_UNSIGNED_res = SAT_TCPL_a1;
    SAT_ZERO_UNSIGNED_res.display("SAT_ZERO_UNSIGNED_res = SAT_TCPL_a1");

    SAT_ZERO_UNSIGNED_res = SAT_TCPL_a2;
    SAT_ZERO_UNSIGNED_res.display("SAT_ZERO_UNSIGNED_res = SAT_TCPL_a2");

    std::cout << std::endl;

    apFixed<intBits<3>, fracBits<0>, OfMode<SAT::SMGN>> SAT_SMGN_SIGNED_res;

    SAT_SMGN_SIGNED_res = SAT_TCPL_a1;
    SAT_SMGN_SIGNED_res.display("SAT_SMGN_SIGNED_res = SAT_TCPL_a1");

    SAT_SMGN_SIGNED_res = SAT_TCPL_a2;
    SAT_SMGN_SIGNED_res.display("SAT_SMGN_SIGNED_res = SAT_TCPL_a2");

    std::cout << std::endl;

    apFixed<intBits<3>, fracBits<0>, OfMode<WRP::TCPL>> WRP_TCPL_SIGNED_res;

    apFixed<intBits<5>, fracBits<0>> WRP_TCPL_a1 = 31.0;

    WRP_TCPL_SIGNED_res = WRP_TCPL_a1;
    WRP_TCPL_SIGNED_res.display("WRP_TCPL_SIGNED_res = WRP_TCPL_a1");

    apFixed<intBits<5>, fracBits<0>> WRP_TCPL_a2 = -19.0;

    WRP_TCPL_SIGNED_res = WRP_TCPL_a2;
    WRP_TCPL_SIGNED_res.display("WRP_TCPL_SIGNED_res = WRP_TCPL_a2");

    std::cout << std::endl;

    apFixed<intBits<4>, fracBits<0>, OfMode<WRP::TCPL>, isSigned<false>> WRP_TCPL_UNSIGNED_res;

    apFixed<intBits<5>, fracBits<0>> WRP_TCPL_a3 = 19.0;

    WRP_TCPL_UNSIGNED_res = WRP_TCPL_a3;
    WRP_TCPL_UNSIGNED_res.display("WRP_TCPL_UNSIGNED_res = WRP_TCPL_a3");

    WRP_TCPL_UNSIGNED_res = WRP_TCPL_a2;
    WRP_TCPL_UNSIGNED_res.display("WRP_TCPL_UNSIGNED_res = WRP_TCPL_a2");

    std::cout << std::endl;

    // apFixed<intBits<4>, fracBits<0>, OfMode<WRP::TCPL_SAT<3>>> WRP_TCPL_SAT_res;

    // WRP_TCPL_SAT_res = WRP_TCPL_a1;
    // WRP_TCPL_SAT_res.display("WRP_TCPL_SAT_res = WRP_TCPL_a1");

    std::cout << "----------------------------------" << std::endl;
    std::cout << "乘法测试" << std::endl;

    apFixed<intBits<3>, fracBits<3>, isSigned<true>> MUL_a1 = 1.25;

    apFixed<intBits<3>, fracBits<3>, isSigned<true>> MUL_a2 = -1.25;

    apFixed<intBits<3>, fracBits<1>, isSigned<true>> MUL_res;

    MUL_res = Qmul<fracBits<12>>(MUL_a1, MUL_a2);

    MUL_res.display("MUL_res = MUL_a1 * MUL_a2");

    std::cout << std::endl;

    std::cout << "----------------------------------" << std::endl;
    std::cout << "加法测试" << std::endl;

    apFixed<intBits<3>, fracBits<3>, isSigned<true>> ADD_a1 = 5.125;

    apFixed<intBits<3>, fracBits<3>, isSigned<true>> ADD_a2 = -3.25;

    apFixed<intBits<3>, fracBits<1>, isSigned<true>> ADD_res;

    ADD_res = Qadd(ADD_a1, ADD_a2);

    ADD_res.display("ADD_res = ADD_a1 + ADD_a2");

    std::cout << std::endl;

    std::cout << "----------------------------------" << std::endl;

    std::cout << "除法测试" << std::endl;

    apFixed<intBits<5>, fracBits<5>, isSigned<true>> DIV_a1 = 1.5;

    apFixed<intBits<4>, fracBits<4>, isSigned<true>> DIV_a2 = -1.25;

    apFixed<intBits<6>, fracBits<1>, isSigned<true>> DIV_res;

    DIV_res = Qdiv(DIV_a1, DIV_a2);

    DIV_res.display("DIV_res = DIV_a1 / DIV_a2");

    std::cout << std::endl;

    std::cout << "----------------------------------" << std::endl;

    std::cout << "减法测试" << std::endl;

    apFixed<intBits<4>, fracBits<4>, isSigned<true>> SUB_a1 = 5.125;

    apFixed<intBits<4>, fracBits<3>, isSigned<true>> SUB_a2 = -3.25;

    apFixed<intBits<4>, fracBits<2>, isSigned<true>> SUB_res;

    SUB_res = Qsub(SUB_a1, SUB_a2);

    SUB_res.display("SUB_res = SUB_a1 - SUB_a2");

    std::cout << std::endl;

    std::cout << "----------------------------------" << std::endl;

    std::cout << "向量测试" << std::endl;

    apFixedVec<apFixed<intBits<3>, fracBits<3>, isSigned<true>>, 4> VEC_a1 = {1.25, 2.25, 3.25, 4.25};

    VEC_a1.display("VEC_a1");

    std::cout << std::endl;

    std::cout << "----------------------------------" << std::endl;

    std::cout << "矩阵测试" << std::endl;

    using MAT_a1_t = apFixed<intBits<5>, fracBits<3>, isSigned<true>>;

    using MAT_a2_t = apFixed<intBits<5>, fracBits<4>, isSigned<true>>;

    using MAT_res_t = apFixed<intBits<9>, fracBits<2>, isSigned<true>>;

    apFixedMat<MAT_a1_t, 3, 5> MAT_a1 = {1.125, 2.125, 3.125, 4.125, 5.125,
                                         6.125, 7.125, 8.125, 9.125, 10.125,
                                         11.125, 12.125, 13.125, 14.125, 15.125};

    apFixedMat<MAT_a2_t, 5, 4> MAT_a2 = {1.25, 2.25, 3.25, 4.25,
                                         5.25, 6.25, 7.25, 8.25,
                                         9.25, 10.25, 11.25, 12.25,
                                         13.25, 14.25, 15.25, 16.25,
                                         17.25, 18.25, 19.25, 20.25};

    apFixedMat<MAT_res_t, 3, 4> MAT_res;

    using interFixedt = QgemulAddArgs<isSigned<true>, OfMode<WRP::TCPL_SAT<3>>>;

    Qgemul<interFixedt>(MAT_res, MAT_a1, MAT_a2);

    MAT_res.display("MAT_res = MAT_a1 * MAT_a2");



//     std::cout << "----------------------------------" << std::endl;

//     std::cout << "负数位宽测试" << std::endl;

//     using NEG_a1_t = apFixed<intBits<8>, fracBits<-2>, isSigned<true>>;

//     NEG_a1_t NEG_a1 = 100;

//     NEG_a1.display("NEG_a1");
}