#include "QuBLAS.h"
#include <utility>

int main()
{


  //    ================ 1. Qu的创建 =================
    // 最基础的变量创建，采用默认参数，整数位宽=12，小数位宽=12，带符号位，defaultQuMode = TRN::TCPL , defaultOfMode = SAT::TCPL
    Qu a = 1.0;

    // 完整的创建, 有五个支持的选项
    Qu<intBits<8>,
            fracBits<8>,
            isSigned<true>,
            QuMode<RND::ZERO>,
            OfMode<SAT::TCPL>>
        b = 1.0;

    // 你可以随意地传入选项，按照任意顺序，传入任意个数
    Qu<QuMode<RND::ZERO>, isSigned<true>, intBits<9>> c = 1.0;

    // 就比如只传一个，所有其他选项都将是默认值
    Qu<fracBits<8>> d = 1.0;

    // Qu的初始化，直接赋值，随便你传进去int float double都行
    Qu<fracBits<8>> e = (int)1;

    // ！！！！！！ 注意！！！！！！
    // 优雅地使用方法，先用using声明一个类型，然后直接使用
    using type1 = Qu<intBits<8>, fracBits<8>, isSigned<true>, QuMode<RND::ZERO>, OfMode<SAT::TCPL>>;
    using type2 = Qu<intBits<9>>;

    // 这样就不用每次都写一大堆了
    type1 f = 1.0;
    type1 g = 1.0;

    // 打印16进制、二进制、十进制到屏幕
    f.display();

    // 你也可以直接用output将其转换为double
    double h = f.output();

    //    ================ 2. Qu的基础运算 =================

    // Qu的基础运算包括加减乘除大于小于等于等等
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

    // 如果你很闲的话也可以手动包裹一层Qu，这样也是可以的
    auto ab4 = Qadd<Qu<intBits<8>, fracBits<8>, isSigned<true>, QuMode<RND::ZERO>, OfMode<SAT::TCPL>>>(a, b);

    // 你也可以直接指定输出类型，这个会先按照type1的类型进行运算和量化，然后再转换为type2的类型，再进行一次量化
    type2 hhh = Qadd<type1>(a, b);


    // ！！！！！！ 注意！！！！！！
    // 虽然输入形式很自由，但是不要整烂活

    // 可以通过，第二个参数会被忽略，大概
    auto ab5 = Qadd<type1, type2>(a, b);

    // 可以通过，自己去研究会是什么结果
    auto ab6 = Qadd<intBits<8>, type1, fracBits<8>, isSigned<true>, QuMode<RND::ZERO>, type2>(a, b);

    //    ================ 3. 向量和矩阵 =================
    // 所有的向量和矩阵同样也是Qu，区别在于要传一个维度进去
    // 维度用dim<>创建，可以是任意长度，只要你需要
    using vecDim = dim<3>;
    using matDim = dim<3, 3>;
    using cudeDim = dim<3, 3, 3>;
    using fourDim = dim<3, 3, 3, 3>;

    // 在创建Qu时，如果第一个参数是dim<>类型，那么这个Qu就是向量或者矩阵
    // ！！！！一定要是第一个参数！！！！
    Qu<vecDim> vec1 = {1, 2, 3};

    // 你可以额外指定元素量化类型
    // dim之后的参数和创建单个Qu的参数一样，可以是任意个数，任意顺序

    // 一大坨版本
    Qu<vecDim, intBits<8>, fracBits<8>, isSigned<true>, QuMode<RND::ZERO>, OfMode<SAT::TCPL>> vec2 = {1, 2, 3};

    // 优雅版本
    Qu<vecDim, type1> vec3 = {1, 2, 3};

    // 你也可以更优雅点直接指定向量类型
    using vecType1 = Qu<vecDim, type2>;
    vecType1 vec4 = {1, 2, 3};

    // 矩阵同理
    Qu<matDim,type2> mat1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};


    // ---------- 索引 ----------
    // 矩阵的索引有两种模式，静态索引和动态索引

    // 静态索引是指在编译期就可以确定的索引，这种索引的速度会非常快
    // 静态索引使用.get<>()函数

    mat1.get<0, 0>() = 1;

    // 如果你要用变量，请将变量指定为constexpr
    constexpr int indexX = 1;
    constexpr int indexY = 2;
    mat1.get<indexX, indexY>() = 1;

    // 动态索引就是在运行期才能确定的索引，这种索引的速度会慢一些
    // 但是更方便， 而且就是你比较熟悉的那种索引
    // 动态索引使用[]运算符，直接传入任意长度的索引即可
    // ！！！！！！ 注意！！！！！！
    // 如果你想用for循环遍历矩阵，那么请使用动态索引，静态索引不可以用for循环
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
          // !!!!!! 注意，是mat1[i, j]而不是mat1[i][j
            mat1[i, j] = 1;
        }
    }

    // ---------- 元素级量化向量/矩阵 ----------

    // 非常特殊地，你可以创建一个每一位元素的量化类型都不一样的向量或者矩阵
    // 这个时候你需要传入一个元素量化类型的数组，数组的长度就是向量或者矩阵的元素个数

    using typeList =TypeList<type1, type2, type1, type2, type1, type2, type1, type2, type1>;

    Qu<matDim, typeList> mat2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // ！！！！！！ 注意！！！！！！
    // 你需要保证元素量化类型的数组的长度和向量或者矩阵的元素个数一致

    // ！！！！！！ 注意！！！！！！
    // 元素级量化的向量或者矩阵不支持动态索引，只支持静态索引

    auto singleElement = mat2.get<0, 0>();
    singleElement.display();

    mat2.get<0, 0>() = Qadd<type1>(mat2.get<0, 0>(), mat2.get<1, 1>());

    // 错误示范
    // mat2[0, 0] = Qadd<type1>(mat2[0, 0], mat2[1, 1]); // error

}