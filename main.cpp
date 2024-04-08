#include "QuBLAS.h"

int main()
{
    //    ================ 1. apFixed的创建 =================
    // 最基础的变量创建，采用默认参数，整数位宽=12，小数位宽=12，带符号位，defaultQuMode = TRN::TCPL , defaultOfMode = SAT::TCPL
    apFixed a = 1.0;

    // 完整的创建, 有五个支持的选项
    apFixed<intBits<8>,
            fracBits<8>,
            isSigned<true>,
            QuMode<RND::ZERO>,
            OfMode<SAT::TCPL>>
        b = 1.0;

    // 你可以随意地传入选项，按照任意顺序，传入任意个数
    apFixed<QuMode<RND::ZERO>, isSigned<true>, intBits<9>> c = 1.0;

    // 就比如只传一个，所有其他选项都将是默认值
    apFixed<fracBits<8>> d = 1.0;

    // apFixed的初始化，直接赋值，随便你传进去int float double都行
    apFixed<fracBits<8>> e = (int)1;

    // ！！！！！！ 注意！！！！！！
    // 优雅地使用方法，先用using声明一个类型，然后直接使用
    using type1 = apFixed<intBits<8>, fracBits<8>, isSigned<true>, QuMode<RND::ZERO>, OfMode<SAT::TCPL>>;
    using type2 = apFixed<intBits<9>>;

    // 这样就不用每次都写一大堆了
    type1 f = 1.0;
    type1 g = 1.0;

    // 打印16进制、二进制、十进制到屏幕
    f.display();

    // 你也可以直接用output将其转换为double
    double h = f.output();

    //    ================ 2. apFixed的基础运算 =================

    // apFixed的基础运算包括加减乘除大于小于等于等等
    // 你可以直接用+ - * / > < == != >= <=等运算符，这个时候会自动推导输出数据的量化类型，规则为
    // 1.小数、整数位宽取输入两数的最大值，
    // 2.除非两个数都为无符号，否则输出为有符号
    // 3.量化和溢出模式，如果输入两个数的模式一样，那么输出的模式就是这个模式，否则输出的模式为默认模式
    // 尤其需要注意，判断大于小于等于不等的意思是判断两个数的实际值，两个量化模式不同的数可能实际值相等，但是量化值不等
    auto abcd = (a + b) * c / d;
    bool agb = a > b;
    bool aeb = a != b;

    // += -= *= /=等运算符暂不支持，需要的话喊我
    // a += b; // error

    // 你可以指定输出的类型，这个时候需要手动调用Qadd Qsub Qmul Qdiv等函数

    // 这是手动调用但没有指定输出类型的例子，这时候等价于直接+
    auto ab = Qadd(a, b);

    // 这是手动调用并指定输出类型的例子，这就是为什么需要using声明类型的原因，不然这里要写一大坨
    auto ab2 = Qadd<type1>(a, b);

    // 当然你还是可以手动输入一大坨，这里同样支持任意顺序，任意个数，缺省的参数会用默认值
    auto ab3 = Qadd<intBits<8>, fracBits<8>, isSigned<true>, QuMode<RND::ZERO>, OfMode<SAT::TCPL>>(a, b);

    // 如果你很闲的话也可以手动包裹一层apFixed，这样也是可以的
    auto ab4 = Qadd<apFixed<intBits<8>, fracBits<8>, isSigned<true>, QuMode<RND::ZERO>, OfMode<SAT::TCPL>>>(a, b);

    // 你也可以直接指定输出类型，这个会先按照type1的类型进行运算和量化，然后再转换为type2的类型，再进行一次量化
    type2 hhh = Qadd<type1>(a, b);

    // ！！！！！！ 注意！！！！！！
    // 虽然输入形式很自由，但是不要整烂活

    // 可以通过，第二个参数会被忽略，大概
    auto ab5 = Qadd<type1, type2>(a, b);

    // 可以通过，自己去研究会是什么结果
    auto ab6 = Qadd<intBits<8>, type1, fracBits<8>, isSigned<true>, QuMode<RND::ZERO>, type2>(a, b);

    //    ================ 3. 向量和矩阵 =================
    // 目前只支持一维向量和二维矩阵，想用更高维度的话去看test分支

    // 一维向量的创建，注意！必须传进去一个完整的apFixed类型，不能只传进去一个零碎的intBits fracBits什么的
    Qvec<8, type1> vec1 = {1, 2, 3, 4, 5, 6, 7, 8};
    Qvec<4> vec2 = {1, 2, 3, 4};

    // 二维矩阵的创建，同样需要传进去一个完整的apFixed类型
    Qmat<4, 4, type2> mat1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

    // 矩阵的索引，用方括号
    auto vec1_1 = vec1[1];
    auto mat1_1 = mat1[1][1];

    // 矩阵的基础运算，仅支持向量的求和，这是一个树形加法器

    // 懒人版本
    auto vec1_sum = Qreduce(vec1);

    // 每一层都用同一个类型
    auto vec1_sum2 = Qreduce<type1>(vec1);

    // 每一层都用同一个类型，一大坨版
    auto vec1_sum3 = Qreduce<intBits<8>, fracBits<8>, isSigned<true>, QuMode<RND::ZERO>, OfMode<SAT::TCPL>>(vec1);

    // 每一层都用不同类型，手动输入每一层的类型
    auto vec1_sum4 = Qreduce<type1, type2, type2>(vec1);

    // 每一层都用不同类型，优雅版
    using list = TypeList<type1, type2, type2>;
    auto vec1_sum5 = Qreduce<list>(vec1);

    //    ================ 4. BLAS =================

    // 有几个基础的BLAS函数，包括矩阵乘法、矩阵向量乘法、LU分解、LU求解

    // 向量加减乘除单个数

    // Qvea, Qves, Qvem, Qved分别是向量加减乘除单个数
    auto vec1_add = Qvea(vec1, a);
    auto vec1_sub = Qves(a, vec1);

    // 也可以直接用运算符
    auto vec1_mul = vec1 * a;
    auto vec1_div = a / vec1;

    // 也可以指定输出类型，优雅或者一大坨
    auto vec1_mul2 = Qvem<type1>(vec1, a);
    auto vec1_div2 = Qved<intBits<8>, fracBits<8>, isSigned<true>, QuMode<RND::ZERO>, OfMode<SAT::TCPL>>(a, vec1);

    // 矩阵乘向量
    // ------------- Qgemv -------------
    // 用于计算 y = beta * y + alpha * op(A) * x.
    // A是一个矩阵，x是一个向量，y是一个向量
    // alpha beta是两个标量
    // op(A) 指的是要不要转置

    // ！！！！！！不能直接用运算符，必须手动调用函数 ！！！！！！

    // 版本一，alpha 和 beta 要在运行时指定
    Qmat<4, 4, type2> A = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    Qvec<4, type2> x = {1, 2, 3, 4};
    Qvec<4, type2> y = {1, 2, 3, 4};

    apFixed alpha = 1.0;
    apFixed beta = 0.0;

    // 你需要输入五个参数
    Qgemv(y, beta, alpha, A, x);

    // 支持两个中间变量的量化，通过标签指定，同时可以指定要不要转置
    // 同样可以任意顺序，任意个数
    Qgemv<QgemvAddArgs<type1>,
          QgemvMulArgs<type2>,
          QgemvTransposedA<true>>(y, beta, alpha, A, x);

    // 版本二，alpha 和 beta 在编译时指定
    // 注意这时候alpha beta需要用constexpr修饰
    constexpr apFixed alpha2 = 1.0;
    constexpr type2 beta2 = 0.0;
    Qgemv<QgemvAlpha<alpha2>,
          QgemvBeta<beta2>>(y, A, x);

    // ------------- Qgemul -------------

    Qmat<4, 4, type2> B = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    Qmat<4, 4, type2> C;

    // 用于计算 C = op(A) * op(B)
    // A B C 都是矩阵

    // 版本一
    Qgemul(C, A, B);

    // 支持指定A B是否转置，以及中间变量加和乘的量化
    Qgemul<QgemulTransposedA<true>,
           QgemulTransposedB<true>,
           QgemulAddArgs<type1>,
           QgemulMulArgs<type2>>(C, A, B);

    // 版本二，专门用来计算C = A^T * A 或者 C = A * A^T

    Qgemul<QgemulTransposedA<true>,
           QgemulAddArgs<type1>,
           QgemulMulArgs<type2>>(C, A, B);
}