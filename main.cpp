#include "QuBLAS.h"

void GETRF(std::vector<std::vector<double>> &A, std::vector<int> &pivot)
{
    int n = A.size();

    pivot.resize(n, 0);

    for (int i = 0; i < n; ++i)
        pivot[i] = i;

    for (int k = 0; k < n; ++k)
    {
        double max = 0.0;
        int i_max = k;

        for (int i = k; i < n; ++i)
        {
            if (std::abs(A[i][k]) > max)
            {
                max = std::abs(A[i][k]);
                i_max = i;
            }
        }

        if (max == 0.0)
        {
            std::cerr << "Matrix is singular!" << std::endl;
            return;
        }

        std::swap(A[k], A[i_max]);
        std::swap(pivot[k], pivot[i_max]);

        for (int i = k + 1; i < n; ++i)
        {
            A[i][k] /= A[k][k];
            for (int j = k + 1; j < n; ++j)
            {
                A[i][j] -= A[i][k] * A[k][j];
            }
        }
    }
}

void GETRS(std::vector<std::vector<double>> &A, std::vector<int> &pivot, std::vector<double> &b)
{
    int n = A.size();
    std::vector<double> b_permuted(n);

    for (int i = 0; i < n; ++i)
    {
        b_permuted[i] = b[pivot[i]];
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            b_permuted[i] -= A[i][j] * b_permuted[j];
        }
    }

    for (int i = n - 1; i >= 0; --i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            b_permuted[i] -= A[i][j] * b_permuted[j];
        }
        b_permuted[i] /= A[i][i];
    }

    for (int i = 0; i < n; ++i)
    {
        b[i] = b_permuted[i];
    }
}

int main()
{

    // apFixed<intBits<3>, fracBits<3>, isSigned<true>> a = 1.25;
    // a.display("a");

    // apFixed<intBits<3>, fracBits<3>, isSigned<true>> b = -1.25;
    // b.display("b");

    // std::cout << std::endl;

    // apFixed<intBits<3>, fracBits<1>, QuMode<RND::POS_INF>, isSigned<true>> POS_INF_res;

    // POS_INF_res = a;
    // POS_INF_res.display("POS_INF_res = a");

    // POS_INF_res = b;
    // POS_INF_res.display("POS_INF_res = b");

    // std::cout << std::endl;

    // apFixed<intBits<3>, fracBits<1>, QuMode<RND::NEG_INF>, isSigned<true>> NEG_INF_res;

    // NEG_INF_res = a;
    // NEG_INF_res.display("NEG_INF_res = a");

    // NEG_INF_res = b;
    // NEG_INF_res.display("NEG_INF_res = b");

    // std::cout << std::endl;

    // apFixed<intBits<3>, fracBits<1>, QuMode<RND::ZERO>, isSigned<true>> ZERO_res;

    // ZERO_res = a;
    // ZERO_res.display("ZERO_res = a");

    // ZERO_res = b;
    // ZERO_res.display("ZERO_res = b");

    // std::cout << std::endl;

    // apFixed<intBits<3>, fracBits<1>, QuMode<RND::INF>, isSigned<true>> INF_res;

    // INF_res = a;
    // INF_res.display("INF_res = a");

    // INF_res = b;
    // INF_res.display("INF_res = b");

    // std::cout << std::endl;

    // apFixed<intBits<3>, fracBits<1>, QuMode<TRN::TCPL>, isSigned<true>> TCPL_res;

    // TCPL_res = a;
    // TCPL_res.display("TCPL_res = a");

    // TCPL_res = b;
    // TCPL_res.display("TCPL_res = b");

    // std::cout << std::endl;

    // apFixed<intBits<3>, fracBits<5>> CONV_a1 = 1.59375;
    // CONV_a1.display("CONV_a1");

    // apFixed<intBits<3>, fracBits<5>> CONV_a2 = 1.625;
    // CONV_a2.display("CONV_a2");

    // apFixed<intBits<3>, fracBits<5>> CONV_a3 = 1.375;
    // CONV_a3.display("CONV_a3");

    // apFixed<intBits<3>, fracBits<5>> CONV_a4 = 1.65625;
    // CONV_a4.display("CONV_a4");

    // std::cout << std::endl;

    // apFixed<intBits<3>, fracBits<2>, QuMode<RND::CONV>, isSigned<true>> CONV_res;

    // CONV_res = CONV_a1;
    // CONV_res.display("CONV_res = CONV_a1");

    // CONV_res = CONV_a2;
    // CONV_res.display("CONV_res = CONV_a2");

    // CONV_res = CONV_a3;
    // CONV_res.display("CONV_res = CONV_a3");

    // CONV_res = CONV_a4;
    // CONV_res.display("CONV_res = CONV_a4");

    // apFixed<intBits<3>, fracBits<1>, QuMode<TRN::SMGN>, isSigned<true>> SMGN_res;

    // SMGN_res = a;
    // SMGN_res.display("SMGN_res = a");

    // SMGN_res = b;
    // SMGN_res.display("SMGN_res = b");

    // std::cout << std::endl;

    // apFixed<intBits<3>, fracBits<0>, QuMode<TRN::TCPL>, OfMode<SAT::TCPL>> SAT_TCPL_SIGNED_res;

    // apFixed<intBits<5>, fracBits<1>> SAT_TCPL_a1 = 19.0;

    // SAT_TCPL_SIGNED_res = SAT_TCPL_a1;
    // SAT_TCPL_SIGNED_res.display("SAT_TCPL_SIGNED_res = SAT_TCPL_a1");

    // apFixed<intBits<5>, fracBits<1>> SAT_TCPL_a2 = -19.0;

    // SAT_TCPL_SIGNED_res = SAT_TCPL_a2;
    // SAT_TCPL_SIGNED_res.display("SAT_TCPL_SIGNED_res = SAT_TCPL_a2");

    // std::cout << std::endl;

    // apFixed<intBits<4>, fracBits<0>, QuMode<TRN::TCPL>, OfMode<SAT::TCPL>, isSigned<false>> SAT_TCPL_UNSIGNED_res;

    // SAT_TCPL_UNSIGNED_res = SAT_TCPL_a1;
    // SAT_TCPL_UNSIGNED_res.display("SAT_TCPL_UNSIGNED_res = SAT_TCPL_a1");

    // SAT_TCPL_UNSIGNED_res = SAT_TCPL_a2;
    // SAT_TCPL_UNSIGNED_res.display("SAT_TCPL_UNSIGNED_res = SAT_TCPL_a2");

    // std::cout << std::endl;

    // apFixed<intBits<3>, fracBits<1>, OfMode<SAT::ZERO>> SAT_ZERO_SIGNED_res;

    // SAT_ZERO_SIGNED_res = SAT_TCPL_a1;
    // SAT_ZERO_SIGNED_res.display("SAT_ZERO_SIGNED_res = SAT_TCPL_a1");

    // SAT_ZERO_SIGNED_res = SAT_TCPL_a2;
    // SAT_ZERO_SIGNED_res.display("SAT_ZERO_SIGNED_res = SAT_TCPL_a2");

    // std::cout << std::endl;

    // apFixed<intBits<4>, fracBits<0>, OfMode<SAT::ZERO>, isSigned<false>> SAT_ZERO_UNSIGNED_res;

    // SAT_ZERO_UNSIGNED_res = SAT_TCPL_a1;
    // SAT_ZERO_UNSIGNED_res.display("SAT_ZERO_UNSIGNED_res = SAT_TCPL_a1");

    // SAT_ZERO_UNSIGNED_res = SAT_TCPL_a2;
    // SAT_ZERO_UNSIGNED_res.display("SAT_ZERO_UNSIGNED_res = SAT_TCPL_a2");

    // std::cout << std::endl;

    // apFixed<intBits<3>, fracBits<0>, OfMode<SAT::SMGN>> SAT_SMGN_SIGNED_res;

    // SAT_SMGN_SIGNED_res = SAT_TCPL_a1;
    // SAT_SMGN_SIGNED_res.display("SAT_SMGN_SIGNED_res = SAT_TCPL_a1");

    // SAT_SMGN_SIGNED_res = SAT_TCPL_a2;
    // SAT_SMGN_SIGNED_res.display("SAT_SMGN_SIGNED_res = SAT_TCPL_a2");

    // std::cout << std::endl;

    // apFixed<intBits<3>, fracBits<0>, OfMode<WRP::TCPL>> WRP_TCPL_SIGNED_res;

    // apFixed<intBits<5>, fracBits<0>> WRP_TCPL_a1 = 31.0;

    // WRP_TCPL_SIGNED_res = WRP_TCPL_a1;
    // WRP_TCPL_SIGNED_res.display("WRP_TCPL_SIGNED_res = WRP_TCPL_a1");

    // apFixed<intBits<5>, fracBits<0>> WRP_TCPL_a2 = -19.0;

    // WRP_TCPL_SIGNED_res = WRP_TCPL_a2;
    // WRP_TCPL_SIGNED_res.display("WRP_TCPL_SIGNED_res = WRP_TCPL_a2");

    // std::cout << std::endl;

    // apFixed<intBits<4>, fracBits<0>, OfMode<WRP::TCPL>, isSigned<false>> WRP_TCPL_UNSIGNED_res;

    // apFixed<intBits<5>, fracBits<0>> WRP_TCPL_a3 = 19.0;

    // WRP_TCPL_UNSIGNED_res = WRP_TCPL_a3;
    // WRP_TCPL_UNSIGNED_res.display("WRP_TCPL_UNSIGNED_res = WRP_TCPL_a3");

    // WRP_TCPL_UNSIGNED_res = WRP_TCPL_a2;
    // WRP_TCPL_UNSIGNED_res.display("WRP_TCPL_UNSIGNED_res = WRP_TCPL_a2");

    // std::cout << std::endl;

    // // apFixed<intBits<4>, fracBits<0>, OfMode<WRP::TCPL_SAT<3>>> WRP_TCPL_SAT_res;

    // // WRP_TCPL_SAT_res = WRP_TCPL_a1;
    // // WRP_TCPL_SAT_res.display("WRP_TCPL_SAT_res = WRP_TCPL_a1");

    // std::cout << "----------------------------------" << std::endl;
    // std::cout << "乘法测试" << std::endl;

    // apFixed<intBits<3>, fracBits<3>, isSigned<true>> MUL_a1 = 1.25;

    // apFixed<intBits<3>, fracBits<3>, isSigned<true>> MUL_a2 = -1.25;

    // apFixed<intBits<3>, fracBits<1>, isSigned<true>> MUL_res;

    // MUL_res = Qmul<fracBits<12>>(MUL_a1, MUL_a2);

    // MUL_res.display("MUL_res = MUL_a1 * MUL_a2");

    // std::cout << std::endl;

    // std::cout << "----------------------------------" << std::endl;
    // std::cout << "加法测试" << std::endl;

    // apFixed<intBits<3>, fracBits<3>, isSigned<true>> ADD_a1 = 5.125;

    // apFixed<intBits<3>, fracBits<3>, isSigned<true>> ADD_a2 = -3.25;

    // apFixed<intBits<3>, fracBits<1>, isSigned<true>> ADD_res;

    // ADD_res = Qadd(ADD_a1, ADD_a2);

    // ADD_res.display("ADD_res = ADD_a1 + ADD_a2");

    // std::cout << std::endl;

    // std::cout << "----------------------------------" << std::endl;

    // std::cout << "除法测试" << std::endl;

    // apFixed<intBits<5>, fracBits<5>, isSigned<true>> DIV_a1 = 1.5;

    // apFixed<intBits<4>, fracBits<4>, isSigned<true>> DIV_a2 = -1.25;

    // apFixed<intBits<6>, fracBits<1>, isSigned<true>> DIV_res;

    // DIV_res = Qdiv(DIV_a1, DIV_a2);

    // DIV_res.display("DIV_res = DIV_a1 / DIV_a2");

    // std::cout << std::endl;

    // std::cout << "----------------------------------" << std::endl;

    // std::cout << "减法测试" << std::endl;

    // apFixed<intBits<4>, fracBits<4>, isSigned<true>> SUB_a1 = 5.125;

    // apFixed<intBits<4>, fracBits<3>, isSigned<true>> SUB_a2 = -3.25;

    // apFixed<intBits<4>, fracBits<2>, isSigned<true>> SUB_res;

    // SUB_res = Qsub(SUB_a1, SUB_a2);

    // SUB_res.display("SUB_res = SUB_a1 - SUB_a2");

    // std::cout << std::endl;

    // std::cout << "----------------------------------" << std::endl;

    // std::cout << "向量测试" << std::endl;

    // apFixedVec<apFixed<intBits<3>, fracBits<3>, isSigned<true>>, 4> VEC_a1 = {1.25, 2.25, 3.25, 4.25};

    // VEC_a1.display("VEC_a1");

    // std::cout << std::endl;

    // std::cout << "----------------------------------" << std::endl;

    // std::cout << "矩阵测试" << std::endl;

    // using MAT_a1_t = apFixed<intBits<5>, fracBits<3>, isSigned<true>>;

    // using MAT_a2_t = apFixed<intBits<5>, fracBits<4>, isSigned<true>>;

    // using MAT_res_t = apFixed<intBits<13>, fracBits<2>, isSigned<true>>;

    // apFixedMat<MAT_a1_t, 3, 5> MAT_a1 = {1.125, 2.125, 3.125, 4.125, 5.125,
    //                                      6.125, 7.125, 8.125, 9.125, 10.125,
    //                                      11.125, 12.125, 13.125, 14.125, 15.125};

    // apFixedMat<MAT_a2_t, 5, 4> MAT_a2 = {1.25, 2.25, 3.25, 4.25,
    //                                      5.25, 6.25, 7.25, 8.25,
    //                                      9.25, 10.25, 11.25, 12.25,
    //                                      13.25, 14.25, 15.25, 16.25,
    //                                      17.25, 18.25, 19.25, 20.25};

    // apFixedMat<MAT_res_t, 3, 4> MAT_res;

    // // version 1 directly pass in the template parameters
    // using addArgs = QgemulAddArgs<OfMode<WRP::TCPL>, intBits<17>, fracBits<13>>;

    // // version 2 pass in a apFixed type
    // using mulType = apFixed<intBits<13>, fracBits<7>>;
    // using mulArgs = QgemulMulArgs<mulType>;

    // // Qgemul<addArgs, mulArgs>(MAT_res, MAT_a1, MAT_a2);

    // // MAT_res.display("MAT_res = MAT_a1 * MAT_a2");

    // apFixedMat<MAT_res_t, 4, 4> MAT_res2;

    // Qgemul<addArgs, mulArgs>(MAT_res2, MAT_a2 );

    // MAT_res2.display("MAT_res2 = MAT_a2^T * MAT_a2");

    std::cout << "----------------------" << std::endl;
    std::cout << "矩阵乘向量测试" << std::endl;
    apFixedMat<apFixed<>, 3, 5> A = {0.1, 0.2, 0.3, 0.4, 0.5,
                                     0.6, 0.7, 0.8, 0.9, 1.0,
                                     1.1, 1.2, 1.3, 1.4, 1.5};

    apFixedVec<apFixed<>, 5> x = {1.1, 2.2, 3.3, 4.4, 5.5};

    // x.display("x before matvec");

    apFixedVec<apFixed<>, 3> y = {1.0, 1.0, 1.0};

    apFixed<> alpha = 1.0;
    apFixed<> beta = 0.0;

    Qgemv(y, A, x);

    y.display("y after matvec");

    // std::cout << "----------------------------------" << std::endl;

    // std::cout << "负数位宽测试" << std::endl;

    // using NEG_a1_t = apFixed<intBits<8>, fracBits<-2>>;

    // NEG_a1_t NEG_a1 = 100;

    // NEG_a1.display("NEG_a1");

    // using NEG_a2_t = apFixed<intBits<-2>, fracBits<8>>;

    // NEG_a2_t NEG_a2 = 0.025;

    // NEG_a2.display("NEG_a2");

    // std::cout << std::endl;

    // std::cout << "----------------------------------" << std::endl;

    // std::cout << "负数小数位量化测试" << std::endl;

    // using NEG_FRAC_res_t = apFixed<intBits<-2>, fracBits<9>>;

    // NEG_FRAC_res_t NEG_FRAC_res;

    // NEG_FRAC_res = NEG_a2;

    // NEG_FRAC_res.display("NEG_FRAC_res = NEG_a2");

    // std::cout << std::endl;

    // std::cout << "----------------------------------" << std::endl;

    // std::cout << "矩阵求逆测试" << std::endl;

    // // normal version
    // std::vector<std::vector<double>> Anormal = {
    //     {1.1, 2.2, 3.3},
    //     {2, 1, 1},
    //     {3.1, 0, 1.1}};
    // std::vector<double> bnormal = {14, 4, 8};

    // std::vector<int> pivot;
    // GETRF(Anormal, pivot);
    // GETRS(Anormal, pivot, bnormal);

    // std::cout << "GETRF result:" << std::endl;
    // for (int i = 0; i < Anormal.size(); i++)
    // {
    //     for (int j = 0; j < Anormal[i].size(); j++)
    //     {
    //         std::cout << Anormal[i][j] << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // std::cout << std::endl;

    // std::cout << "GETRS result:" << std::endl;
    // for (int i = 0; i < bnormal.size(); i++)
    // {
    //     std::cout << bnormal[i] << " ";
    // }

    // std::cout << std::endl;
    // std::cout << std::endl;

    // // QuBLAS version
    // using MAT_INV_a1_t = apFixed<intBits<5>, fracBits<5>, isSigned<true>>;
    // using MAT_INV_b1_t = apFixed<intBits<5>, fracBits<6>, isSigned<true>>;

    // using interiorType1 = apFixed<intBits<11>, fracBits<6>, isSigned<true>, QuMode<RND::INF>>;

    // using interiorType2 = apFixed<intBits<11>, fracBits<7>, isSigned<true>, QuMode<RND::ZERO>>;

    // using interiorType3 = apFixed<intBits<11>, fracBits<4>, isSigned<true>, QuMode<TRN::TCPL>>;

    // std::array<size_t, 3> ipiv;

    // apFixedMat<MAT_INV_a1_t, 3, 3> MAT_INV_a1 = {1.1, 2.2, 3.3,
    //                                              2, 1, 1,
    //                                              3.1, 0, 1.1};

    // apFixedVec<MAT_INV_b1_t, 3> MAT_INV_b1 = {14, 4, 8};

    // Qgetrf<QgetrfMulArgs<intBits<11>, fracBits<6>, isSigned<true>, QuMode<RND::INF>>,
    //        QgetrfDivArgs<interiorType2>,
    //        QgetrfSubArgs<intBits<11>, fracBits<4>, isSigned<true>, QuMode<TRN::TCPL>>>(MAT_INV_a1, ipiv);

    // std::cout << "GETRF result:" << std::endl;
    // MAT_INV_a1.display("MAT_INV_a1");

    // Qgetrs<QgetrfSubArgs<interiorType3>, QgetrfMulArgs<interiorType1>>(MAT_INV_a1, ipiv, MAT_INV_b1);

    // std::cout << "GETRS result:" << std::endl;
    // MAT_INV_b1.display("MAT_INV_b1");

    std::cout << "----------------------------------" << std::endl;
    std::cout << "Qgetrf错误" << std::endl;
    using MAT_a_t = apFixed<intBits<7>, fracBits<10>, isSigned<true>>;

    apFixedMat<MAT_a_t, 32, 32> MAT_a;
    int source[32 * 32] = {40915, -3996, -5784, -2116, 316, 2676, 292, 256, 4580, -3256, 2944, -1144, 4680, -616, -336, -1792, 0, 6780, -896, 540, 940, 4908, 1552, 2424, -7868, -300, 2016, 3868, 5680, 2972, 2312, 6872,
                           -3996, 28755, -804, 1124, -3496, 1940, -4224, 2092, -552, 684, -4, -1332, -5700, -4400, 332, 4784, -6780, 0, 6580, 3360, -528, 172, -4696, 2844, -6104, -1268, -2432, -6192, -9560, 7288, -3092, 2852,
                           -5784, -804, 22035, 164, 776, -3120, 5476, 1292, 2392, 1720, -4760, -1260, -2476, 1508, -5208, -3936, 896, -6580, 0, -6464, 5840, -372, 2232, -3600, 7132, -2428, 4092, -2384, -108, 3984, 1592, -5380,
                           -2116, 1124, 164, 32787, 936, 5816, 2792, 2656, -3940, 5212, -2908, 5364, -5688, -2460, -3940, -6720, -540, -3360, 6464, 0, 2592, 3024, 4160, -3268, 2088, 3028, -1200, 4412, -1972, 1388, -2072, 2472,
                           316, -3496, 776, 936, 27335, -6164, -2792, 3084, -1160, -2572, -2132, 5064, -1728, -1468, -516, -4372, -940, 528, -5840, -2592, 0, -2060, -4356, -10148, -1276, -5184, 1384, 884, -540, 4432, -3008, 2584,
                           2676, 1940, -3120, 5816, -6164, 36051, 2272, 7256, -4920, -776, 5456, 3956, -7452, -436, 6956, -2736, -4908, -172, 372, -3024, 2060, 0, 1872, 11748, -7848, -40, -2264, 1452, 1372, -2820, 3372, -7248,
                           292, -4224, 5476, 2792, -2792, 2272, 28599, -5260, 2056, 3772, 1332, -1072, 4768, -3428, 3176, -1132, -1552, 4696, -2232, -4160, 4356, -1872, 0, -4736, 836, -3024, 1200, -104, -2028, 4028, 4552, -7084,
                           256, 2092, 1292, 2656, 3084, 7256, -5260, 29283, -8000, 1056, 1524, 4744, -3600, -3184, 332, -5912, -2424, -2844, 3600, 3268, 10148, -11748, 4736, 0, -1744, 4040, -4308, 144, -2388, -7424, -3840, -580,
                           4580, -552, 2392, -3940, -1160, -4920, 2056, -8000, 28867, 2844, -1092, 2788, 2900, -5552, -1360, -3468, 7868, 6104, -7132, -2088, 1276, 7848, -836, 1744, 0, 4288, 5556, -2776, 944, 1360, 7564, 1468,
                           -3256, 684, 1720, 5212, -2572, -776, 3772, 1056, 2844, 30019, 2660, -7488, -544, -6396, 4016, 92, 300, 1268, 2428, -3028, 5184, 40, 3024, -4040, -4288, 0, 864, 1792, 372, 7072, 2364, -1224,
                           2944, -4, -4760, -2908, -2132, 5456, 1332, 1524, -1092, 2660, 26443, -1008, 2000, 2008, 4440, 2432, -2016, 2432, -4092, 1200, -1384, 2264, -1200, 4308, -5556, -864, 0, -1028, 2332, 5548, -3424, -3268,
                           -1144, -1332, -1260, 5364, 5064, 3956, -1072, 4744, 2788, -7488, -1008, 36707, 2488, 904, -1676, -1548, -3868, 6192, 2384, -4412, -884, -1452, 104, -144, 2776, -1792, 1028, 0, 5588, -7480, -12, 5556,
                           4680, -5700, -2476, -5688, -1728, -7452, 4768, -3600, 2900, -544, 2000, 2488, 32115, -4580, -1012, 704, -5680, 9560, 108, 1972, 540, -1372, 2028, 2388, -944, -372, -2332, -5588, 0, -2452, 1920, -628,
                           -616, -4400, 1508, -2460, -1468, -436, -3428, -3184, -5552, -6396, 2008, 904, -4580, 38991, -2372, -4456, -2972, -7288, -3984, -1388, -4432, 2820, -4028, 7424, -1360, -7072, -5548, 7480, 2452, 0, 1712, 4324,
                           -336, 332, -5208, -3940, -516, 6956, 3176, 332, -1360, 4016, 4440, -1676, -1012, -2372, 26591, -2744, -2312, 3092, -1592, 2072, 3008, -3372, -4552, 3840, -7564, -2364, 3424, 12, -1920, -1712, 0, -6304,
                           -1792, 4784, -3936, -6720, -4372, -2736, -1132, -5912, -3468, 92, 2432, -1548, 704, -4456, -2744, 34403, -6872, -2852, 5380, -2472, -2584, 7248, 7084, 580, -1468, 1224, 3268, -5556, 628, -4324, 6304, 0,
                           0, -6780, 896, -540, -940, -4908, -1552, -2424, 7868, 300, -2016, -3868, -5680, -2972, -2312, -6872, 40915, -3996, -5784, -2116, 316, 2676, 292, 256, 4580, -3256, 2944, -1144, 4680, -616, -336, -1792,
                           6780, 0, -6580, -3360, 528, -172, 4696, -2844, 6104, 1268, 2432, 6192, 9560, -7288, 3092, -2852, -3996, 28755, -804, 1124, -3496, 1940, -4224, 2092, -552, 684, -4, -1332, -5700, -4400, 332, 4784,
                           -896, 6580, 0, 6464, -5840, 372, -2232, 3600, -7132, 2428, -4092, 2384, 108, -3984, -1592, 5380, -5784, -804, 22035, 164, 776, -3120, 5476, 1292, 2392, 1720, -4760, -1260, -2476, 1508, -5208, -3936,
                           540, 3360, -6464, 0, -2592, -3024, -4160, 3268, -2088, -3028, 1200, -4412, 1972, -1388, 2072, -2472, -2116, 1124, 164, 32787, 936, 5816, 2792, 2656, -3940, 5212, -2908, 5364, -5688, -2460, -3940, -6720,
                           940, -528, 5840, 2592, 0, 2060, 4356, 10148, 1276, 5184, -1384, -884, 540, -4432, 3008, -2584, 316, -3496, 776, 936, 27335, -6164, -2792, 3084, -1160, -2572, -2132, 5064, -1728, -1468, -516, -4372,
                           4908, 172, -372, 3024, -2060, 0, -1872, -11748, 7848, 40, 2264, -1452, -1372, 2820, -3372, 7248, 2676, 1940, -3120, 5816, -6164, 36051, 2272, 7256, -4920, -776, 5456, 3956, -7452, -436, 6956, -2736,
                           1552, -4696, 2232, 4160, -4356, 1872, 0, 4736, -836, 3024, -1200, 104, 2028, -4028, -4552, 7084, 292, -4224, 5476, 2792, -2792, 2272, 28599, -5260, 2056, 3772, 1332, -1072, 4768, -3428, 3176, -1132,
                           2424, 2844, -3600, -3268, -10148, 11748, -4736, 0, 1744, -4040, 4308, -144, 2388, 7424, 3840, 580, 256, 2092, 1292, 2656, 3084, 7256, -5260, 29283, -8000, 1056, 1524, 4744, -3600, -3184, 332, -5912,
                           -7868, -6104, 7132, 2088, -1276, -7848, 836, -1744, 0, -4288, -5556, 2776, -944, -1360, -7564, -1468, 4580, -552, 2392, -3940, -1160, -4920, 2056, -8000, 28867, 2844, -1092, 2788, 2900, -5552, -1360, -3468,
                           -300, -1268, -2428, 3028, -5184, -40, -3024, 4040, 4288, 0, -864, -1792, -372, -7072, -2364, 1224, -3256, 684, 1720, 5212, -2572, -776, 3772, 1056, 2844, 30019, 2660, -7488, -544, -6396, 4016, 92,
                           2016, -2432, 4092, -1200, 1384, -2264, 1200, -4308, 5556, 864, 0, 1028, -2332, -5548, 3424, 3268, 2944, -4, -4760, -2908, -2132, 5456, 1332, 1524, -1092, 2660, 26443, -1008, 2000, 2008, 4440, 2432,
                           3868, -6192, -2384, 4412, 884, 1452, -104, 144, -2776, 1792, -1028, 0, -5588, 7480, 12, -5556, -1144, -1332, -1260, 5364, 5064, 3956, -1072, 4744, 2788, -7488, -1008, 36707, 2488, 904, -1676, -1548,
                           5680, -9560, -108, -1972, -540, 1372, -2028, -2388, 944, 372, 2332, 5588, 0, 2452, -1920, 628, 4680, -5700, -2476, -5688, -1728, -7452, 4768, -3600, 2900, -544, 2000, 2488, 32115, -4580, -1012, 704,
                           2972, 7288, 3984, 1388, 4432, -2820, 4028, -7424, 1360, 7072, 5548, -7480, -2452, 0, -1712, -4324, -616, -4400, 1508, -2460, -1468, -436, -3428, -3184, -5552, -6396, 2008, 904, -4580, 38991, -2372, -4456,
                           2312, -3092, 1592, -2072, -3008, 3372, 4552, -3840, 7564, 2364, -3424, -12, 1920, 1712, 0, 6304, -336, 332, -5208, -3940, -516, 6956, 3176, 332, -1360, 4016, 4440, -1676, -1012, -2372, 26591, -2744,
                           6872, 2852, -5380, 2472, 2584, -7248, -7084, -580, 1468, -1224, -3268, 5556, -628, 4324, -6304, 0, -1792, 4784, -3936, -6720, -4372, -2736, -1132, -5912, -3468, 92, 2432, -1548, 704, -4456, -2744, 34403};

    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            MAT_a[i][j] = apFixed<intBits<7>, fracBits<10>, isSigned<true>>(source[i * 32 + j], DirectAssignTag{});
        }
    }

    // MAT_a.display("MAT_a");
    std::array<size_t, 32> ipiv;

    Qgetrf<QgetrfDivArgs<intBits<4>, fracBits<9>>,
           QgetrfMulArgs<intBits<7>, fracBits<8>>,
           QgetrfSubArgs<intBits<9>, fracBits<4>>>(MAT_a, ipiv);

    MAT_a.display("MAT_a after getrf");
}