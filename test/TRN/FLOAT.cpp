#include <gtest/gtest.h>
#include "QuBLAS.h"

using namespace QuBLAS;

using High_t = Qu<expBits<60>, valBits<80>>;
using Mid_t = Qu<expBits<30>, valBits<30>>;
using Low_t = Qu<expBits<10>, valBits<10>>;

TEST(INF, HighToTargetPositive_1)
{
    High_t high = -94866246.32024637;                  // 创建一个 High_t 类型的变量 high，并初始化为 -94866246.32024637
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -94866246.32024637); // 断言 targetDouble 等于 -94866246.32024637
}
TEST(INF, HighToTargetPositive_2)
{
    High_t high = 36748003.11674479;                  // 创建一个 High_t 类型的变量 high，并初始化为 36748003.11674479
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 36748003.11674479); // 断言 targetDouble 等于 36748003.11674479
}
TEST(INF, HighToTargetPositive_3)
{
    High_t high = 4855262.712202445;                  // 创建一个 High_t 类型的变量 high，并初始化为 4855262.712202445
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 4855262.712202445); // 断言 targetDouble 等于 4855262.712202445
}
TEST(INF, HighToTargetPositive_4)
{
    High_t high = 98397175.24363077;                  // 创建一个 High_t 类型的变量 high，并初始化为 98397175.24363077
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 98397175.24363077); // 断言 targetDouble 等于 98397175.24363077
}
TEST(INF, HighToTargetPositive_5)
{
    High_t high = 42141808.00755495;                  // 创建一个 High_t 类型的变量 high，并初始化为 42141808.00755495
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 42141808.00755495); // 断言 targetDouble 等于 42141808.00755495
}
TEST(INF, HighToTargetPositive_6)
{
    High_t high = -32280000.058989137;                  // 创建一个 High_t 类型的变量 high，并初始化为 -32280000.058989137
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -32280000.058989137); // 断言 targetDouble 等于 -32280000.058989137
}
TEST(INF, HighToTargetPositive_7)
{
    High_t high = -28717013.33536379;                  // 创建一个 High_t 类型的变量 high，并初始化为 -28717013.33536379
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -28717013.33536379); // 断言 targetDouble 等于 -28717013.33536379
}
TEST(INF, HighToTargetPositive_8)
{
    High_t high = -62764380.78776432;                  // 创建一个 High_t 类型的变量 high，并初始化为 -62764380.78776432
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -62764380.78776432); // 断言 targetDouble 等于 -62764380.78776432
}
TEST(INF, HighToTargetPositive_9)
{
    High_t high = 26354316.208990023;                  // 创建一个 High_t 类型的变量 high，并初始化为 26354316.208990023
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 26354316.208990023); // 断言 targetDouble 等于 26354316.208990023
}
TEST(INF, HighToTargetPositive_10)
{
    High_t high = -67249455.48448214;                  // 创建一个 High_t 类型的变量 high，并初始化为 -67249455.48448214
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -67249455.48448214); // 断言 targetDouble 等于 -67249455.48448214
}
TEST(INF, HighToTargetPositive_11)
{
    High_t high = -90110505.24011022;                  // 创建一个 High_t 类型的变量 high，并初始化为 -90110505.24011022
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -90110505.24011022); // 断言 targetDouble 等于 -90110505.24011022
}
TEST(INF, HighToTargetPositive_12)
{
    High_t high = -49492865.82746337;                  // 创建一个 High_t 类型的变量 high，并初始化为 -49492865.82746337
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -49492865.82746337); // 断言 targetDouble 等于 -49492865.82746337
}
TEST(INF, HighToTargetPositive_13)
{
    High_t high = 99523003.40710697;                  // 创建一个 High_t 类型的变量 high，并初始化为 99523003.40710697
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 99523003.40710697); // 断言 targetDouble 等于 99523003.40710697
}
TEST(INF, HighToTargetPositive_14)
{
    High_t high = 77677222.69994074;                  // 创建一个 High_t 类型的变量 high，并初始化为 77677222.69994074
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 77677222.69994074); // 断言 targetDouble 等于 77677222.69994074
}
TEST(INF, HighToTargetPositive_15)
{
    High_t high = 62279537.559351504;                  // 创建一个 High_t 类型的变量 high，并初始化为 62279537.559351504
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 62279537.559351504); // 断言 targetDouble 等于 62279537.559351504
}
TEST(INF, HighToTargetPositive_16)
{
    High_t high = 35658440.16669461;                  // 创建一个 High_t 类型的变量 high，并初始化为 35658440.16669461
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 35658440.16669461); // 断言 targetDouble 等于 35658440.16669461
}
TEST(INF, HighToTargetPositive_17)
{
    High_t high = 81057569.61066377;                  // 创建一个 High_t 类型的变量 high，并初始化为 81057569.61066377
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 81057569.61066377); // 断言 targetDouble 等于 81057569.61066377
}
TEST(INF, HighToTargetPositive_18)
{
    High_t high = -98048171.6262847;                  // 创建一个 High_t 类型的变量 high，并初始化为 -98048171.6262847
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -98048171.6262847); // 断言 targetDouble 等于 -98048171.6262847
}
TEST(INF, HighToTargetPositive_19)
{
    High_t high = -67870633.06406948;                  // 创建一个 High_t 类型的变量 high，并初始化为 -67870633.06406948
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -67870633.06406948); // 断言 targetDouble 等于 -67870633.06406948
}
TEST(INF, HighToTargetPositive_20)
{
    High_t high = -95936823.49138704;                  // 创建一个 High_t 类型的变量 high，并初始化为 -95936823.49138704
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -95936823.49138704); // 断言 targetDouble 等于 -95936823.49138704
}
TEST(INF, HighToTargetPositive_21)
{
    High_t high = -54422484.84745389;                  // 创建一个 High_t 类型的变量 high，并初始化为 -54422484.84745389
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -54422484.84745389); // 断言 targetDouble 等于 -54422484.84745389
}
TEST(INF, HighToTargetPositive_22)
{
    High_t high = 16291779.498474866;                  // 创建一个 High_t 类型的变量 high，并初始化为 16291779.498474866
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 16291779.498474866); // 断言 targetDouble 等于 16291779.498474866
}
TEST(INF, HighToTargetPositive_23)
{
    High_t high = -78049856.44317979;                  // 创建一个 High_t 类型的变量 high，并初始化为 -78049856.44317979
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -78049856.44317979); // 断言 targetDouble 等于 -78049856.44317979
}
TEST(INF, HighToTargetPositive_24)
{
    High_t high = -63898857.406210266;                  // 创建一个 High_t 类型的变量 high，并初始化为 -63898857.406210266
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -63898857.406210266); // 断言 targetDouble 等于 -63898857.406210266
}
TEST(INF, HighToTargetPositive_25)
{
    High_t high = 33313174.83479303;                  // 创建一个 High_t 类型的变量 high，并初始化为 33313174.83479303
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 33313174.83479303); // 断言 targetDouble 等于 33313174.83479303
}
TEST(INF, HighToTargetPositive_26)
{
    High_t high = 61520708.05121103;                  // 创建一个 High_t 类型的变量 high，并初始化为 61520708.05121103
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 61520708.05121103); // 断言 targetDouble 等于 61520708.05121103
}
TEST(INF, HighToTargetPositive_27)
{
    High_t high = 77144535.3121436;                  // 创建一个 High_t 类型的变量 high，并初始化为 77144535.3121436
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 77144535.3121436); // 断言 targetDouble 等于 77144535.3121436
}
TEST(INF, HighToTargetPositive_28)
{
    High_t high = -13494131.74693343;                  // 创建一个 High_t 类型的变量 high，并初始化为 -13494131.74693343
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -13494131.74693343); // 断言 targetDouble 等于 -13494131.74693343
}
TEST(INF, HighToTargetPositive_29)
{
    High_t high = 45246851.15937582;                  // 创建一个 High_t 类型的变量 high，并初始化为 45246851.15937582
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 45246851.15937582); // 断言 targetDouble 等于 45246851.15937582
}
TEST(INF, HighToTargetPositive_30)
{
    High_t high = 24037525.72001274;                  // 创建一个 High_t 类型的变量 high，并初始化为 24037525.72001274
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 24037525.72001274); // 断言 targetDouble 等于 24037525.72001274
}
TEST(INF, HighToTargetPositive_31)
{
    High_t high = 43055858.67303231;                  // 创建一个 High_t 类型的变量 high，并初始化为 43055858.67303231
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 43055858.67303231); // 断言 targetDouble 等于 43055858.67303231
}
TEST(INF, HighToTargetPositive_32)
{
    High_t high = 41153242.43710372;                  // 创建一个 High_t 类型的变量 high，并初始化为 41153242.43710372
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 41153242.43710372); // 断言 targetDouble 等于 41153242.43710372
}
TEST(INF, HighToTargetPositive_33)
{
    High_t high = -49896396.525497064;                  // 创建一个 High_t 类型的变量 high，并初始化为 -49896396.525497064
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -49896396.525497064); // 断言 targetDouble 等于 -49896396.525497064
}
TEST(INF, HighToTargetPositive_34)
{
    High_t high = -26129390.64647852;                  // 创建一个 High_t 类型的变量 high，并初始化为 -26129390.64647852
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -26129390.64647852); // 断言 targetDouble 等于 -26129390.64647852
}
TEST(INF, HighToTargetPositive_35)
{
    High_t high = 12264765.639374226;                  // 创建一个 High_t 类型的变量 high，并初始化为 12264765.639374226
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 12264765.639374226); // 断言 targetDouble 等于 12264765.639374226
}
TEST(INF, HighToTargetPositive_36)
{
    High_t high = 45922620.18654063;                  // 创建一个 High_t 类型的变量 high，并初始化为 45922620.18654063
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 45922620.18654063); // 断言 targetDouble 等于 45922620.18654063
}
TEST(INF, HighToTargetPositive_37)
{
    High_t high = 79295940.59861985;                  // 创建一个 High_t 类型的变量 high，并初始化为 79295940.59861985
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 79295940.59861985); // 断言 targetDouble 等于 79295940.59861985
}
TEST(INF, HighToTargetPositive_38)
{
    High_t high = 30692062.000798985;                  // 创建一个 High_t 类型的变量 high，并初始化为 30692062.000798985
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 30692062.000798985); // 断言 targetDouble 等于 30692062.000798985
}
TEST(INF, HighToTargetPositive_39)
{
    High_t high = -11526820.845137715;                  // 创建一个 High_t 类型的变量 high，并初始化为 -11526820.845137715
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -11526820.845137715); // 断言 targetDouble 等于 -11526820.845137715
}
TEST(INF, HighToTargetPositive_40)
{
    High_t high = -41971218.12598443;                  // 创建一个 High_t 类型的变量 high，并初始化为 -41971218.12598443
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -41971218.12598443); // 断言 targetDouble 等于 -41971218.12598443
}
TEST(INF, HighToTargetPositive_41)
{
    High_t high = -59246460.05771414;                  // 创建一个 High_t 类型的变量 high，并初始化为 -59246460.05771414
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -59246460.05771414); // 断言 targetDouble 等于 -59246460.05771414
}
TEST(INF, HighToTargetPositive_42)
{
    High_t high = 97663210.57332602;                  // 创建一个 High_t 类型的变量 high，并初始化为 97663210.57332602
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 97663210.57332602); // 断言 targetDouble 等于 97663210.57332602
}
TEST(INF, HighToTargetPositive_43)
{
    High_t high = 95277131.00906098;                  // 创建一个 High_t 类型的变量 high，并初始化为 95277131.00906098
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 95277131.00906098); // 断言 targetDouble 等于 95277131.00906098
}
TEST(INF, HighToTargetPositive_44)
{
    High_t high = 93899311.66581401;                  // 创建一个 High_t 类型的变量 high，并初始化为 93899311.66581401
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 93899311.66581401); // 断言 targetDouble 等于 93899311.66581401
}
TEST(INF, HighToTargetPositive_45)
{
    High_t high = 10296211.466208845;                  // 创建一个 High_t 类型的变量 high，并初始化为 10296211.466208845
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 10296211.466208845); // 断言 targetDouble 等于 10296211.466208845
}
TEST(INF, HighToTargetPositive_46)
{
    High_t high = -830047.7536824048;                  // 创建一个 High_t 类型的变量 high，并初始化为 -830047.7536824048
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -830047.7536824048); // 断言 targetDouble 等于 -830047.7536824048
}
TEST(INF, HighToTargetPositive_47)
{
    High_t high = -4834001.665842429;                  // 创建一个 High_t 类型的变量 high，并初始化为 -4834001.665842429
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -4834001.665842429); // 断言 targetDouble 等于 -4834001.665842429
}
TEST(INF, HighToTargetPositive_48)
{
    High_t high = -37718577.60022373;                  // 创建一个 High_t 类型的变量 high，并初始化为 -37718577.60022373
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -37718577.60022373); // 断言 targetDouble 等于 -37718577.60022373
}
TEST(INF, HighToTargetPositive_49)
{
    High_t high = -8140491.507247761;                  // 创建一个 High_t 类型的变量 high，并初始化为 -8140491.507247761
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -8140491.507247761); // 断言 targetDouble 等于 -8140491.507247761
}
TEST(INF, HighToTargetPositive_50)
{
    High_t high = -14918841.662177876;                  // 创建一个 High_t 类型的变量 high，并初始化为 -14918841.662177876
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -14918841.662177876); // 断言 targetDouble 等于 -14918841.662177876
}
TEST(INF, HighToTargetPositive_51)
{
    High_t high = -86259838.72683498;                  // 创建一个 High_t 类型的变量 high，并初始化为 -86259838.72683498
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -86259838.72683498); // 断言 targetDouble 等于 -86259838.72683498
}
TEST(INF, HighToTargetPositive_52)
{
    High_t high = 32839713.42227283;                  // 创建一个 High_t 类型的变量 high，并初始化为 32839713.42227283
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 32839713.42227283); // 断言 targetDouble 等于 32839713.42227283
}
TEST(INF, HighToTargetPositive_53)
{
    High_t high = 2600029.0271228254;                  // 创建一个 High_t 类型的变量 high，并初始化为 2600029.0271228254
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 2600029.0271228254); // 断言 targetDouble 等于 2600029.0271228254
}
TEST(INF, HighToTargetPositive_54)
{
    High_t high = -9425284.320371881;                  // 创建一个 High_t 类型的变量 high，并初始化为 -9425284.320371881
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -9425284.320371881); // 断言 targetDouble 等于 -9425284.320371881
}
TEST(INF, HighToTargetPositive_55)
{
    High_t high = -73407621.53869784;                  // 创建一个 High_t 类型的变量 high，并初始化为 -73407621.53869784
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -73407621.53869784); // 断言 targetDouble 等于 -73407621.53869784
}
TEST(INF, HighToTargetPositive_56)
{
    High_t high = 42603522.09692681;                  // 创建一个 High_t 类型的变量 high，并初始化为 42603522.09692681
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 42603522.09692681); // 断言 targetDouble 等于 42603522.09692681
}
TEST(INF, HighToTargetPositive_57)
{
    High_t high = 58680821.254697114;                  // 创建一个 High_t 类型的变量 high，并初始化为 58680821.254697114
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 58680821.254697114); // 断言 targetDouble 等于 58680821.254697114
}
TEST(INF, HighToTargetPositive_58)
{
    High_t high = -75725624.35915786;                  // 创建一个 High_t 类型的变量 high，并初始化为 -75725624.35915786
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -75725624.35915786); // 断言 targetDouble 等于 -75725624.35915786
}
TEST(INF, HighToTargetPositive_59)
{
    High_t high = -96839291.56429729;                  // 创建一个 High_t 类型的变量 high，并初始化为 -96839291.56429729
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -96839291.56429729); // 断言 targetDouble 等于 -96839291.56429729
}
TEST(INF, HighToTargetPositive_60)
{
    High_t high = -86789702.26242787;                  // 创建一个 High_t 类型的变量 high，并初始化为 -86789702.26242787
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -86789702.26242787); // 断言 targetDouble 等于 -86789702.26242787
}
TEST(INF, HighToTargetPositive_61)
{
    High_t high = -41024270.85764777;                  // 创建一个 High_t 类型的变量 high，并初始化为 -41024270.85764777
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -41024270.85764777); // 断言 targetDouble 等于 -41024270.85764777
}
TEST(INF, HighToTargetPositive_62)
{
    High_t high = 97087005.38453233;                  // 创建一个 High_t 类型的变量 high，并初始化为 97087005.38453233
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 97087005.38453233); // 断言 targetDouble 等于 97087005.38453233
}
TEST(INF, HighToTargetPositive_63)
{
    High_t high = 5613130.054016933;                  // 创建一个 High_t 类型的变量 high，并初始化为 5613130.054016933
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 5613130.054016933); // 断言 targetDouble 等于 5613130.054016933
}
TEST(INF, HighToTargetPositive_64)
{
    High_t high = -55613181.17795775;                  // 创建一个 High_t 类型的变量 high，并初始化为 -55613181.17795775
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -55613181.17795775); // 断言 targetDouble 等于 -55613181.17795775
}
TEST(INF, HighToTargetPositive_65)
{
    High_t high = 71758526.72039801;                  // 创建一个 High_t 类型的变量 high，并初始化为 71758526.72039801
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 71758526.72039801); // 断言 targetDouble 等于 71758526.72039801
}
TEST(INF, HighToTargetPositive_66)
{
    High_t high = -46211199.09712974;                  // 创建一个 High_t 类型的变量 high，并初始化为 -46211199.09712974
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -46211199.09712974); // 断言 targetDouble 等于 -46211199.09712974
}
TEST(INF, HighToTargetPositive_67)
{
    High_t high = -94747513.02413678;                  // 创建一个 High_t 类型的变量 high，并初始化为 -94747513.02413678
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -94747513.02413678); // 断言 targetDouble 等于 -94747513.02413678
}
TEST(INF, HighToTargetPositive_68)
{
    High_t high = 36289092.74852753;                  // 创建一个 High_t 类型的变量 high，并初始化为 36289092.74852753
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 36289092.74852753); // 断言 targetDouble 等于 36289092.74852753
}
TEST(INF, HighToTargetPositive_69)
{
    High_t high = -85937854.89963429;                  // 创建一个 High_t 类型的变量 high，并初始化为 -85937854.89963429
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -85937854.89963429); // 断言 targetDouble 等于 -85937854.89963429
}
TEST(INF, HighToTargetPositive_70)
{
    High_t high = 56702859.40443331;                  // 创建一个 High_t 类型的变量 high，并初始化为 56702859.40443331
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 56702859.40443331); // 断言 targetDouble 等于 56702859.40443331
}
TEST(INF, HighToTargetPositive_71)
{
    High_t high = -34614908.19440902;                  // 创建一个 High_t 类型的变量 high，并初始化为 -34614908.19440902
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -34614908.19440902); // 断言 targetDouble 等于 -34614908.19440902
}
TEST(INF, HighToTargetPositive_72)
{
    High_t high = -45978127.495666035;                  // 创建一个 High_t 类型的变量 high，并初始化为 -45978127.495666035
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -45978127.495666035); // 断言 targetDouble 等于 -45978127.495666035
}
TEST(INF, HighToTargetPositive_73)
{
    High_t high = 24242654.136920676;                  // 创建一个 High_t 类型的变量 high，并初始化为 24242654.136920676
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 24242654.136920676); // 断言 targetDouble 等于 24242654.136920676
}
TEST(INF, HighToTargetPositive_74)
{
    High_t high = -79991928.05051088;                  // 创建一个 High_t 类型的变量 high，并初始化为 -79991928.05051088
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -79991928.05051088); // 断言 targetDouble 等于 -79991928.05051088
}
TEST(INF, HighToTargetPositive_75)
{
    High_t high = 70828471.60866395;                  // 创建一个 High_t 类型的变量 high，并初始化为 70828471.60866395
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 70828471.60866395); // 断言 targetDouble 等于 70828471.60866395
}
TEST(INF, HighToTargetPositive_76)
{
    High_t high = 98757999.66141286;                  // 创建一个 High_t 类型的变量 high，并初始化为 98757999.66141286
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 98757999.66141286); // 断言 targetDouble 等于 98757999.66141286
}
TEST(INF, HighToTargetPositive_77)
{
    High_t high = 76867895.09027359;                  // 创建一个 High_t 类型的变量 high，并初始化为 76867895.09027359
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 76867895.09027359); // 断言 targetDouble 等于 76867895.09027359
}
TEST(INF, HighToTargetPositive_78)
{
    High_t high = -70957347.46116725;                  // 创建一个 High_t 类型的变量 high，并初始化为 -70957347.46116725
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -70957347.46116725); // 断言 targetDouble 等于 -70957347.46116725
}
TEST(INF, HighToTargetPositive_79)
{
    High_t high = -74098194.55431937;                  // 创建一个 High_t 类型的变量 high，并初始化为 -74098194.55431937
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -74098194.55431937); // 断言 targetDouble 等于 -74098194.55431937
}
TEST(INF, HighToTargetPositive_80)
{
    High_t high = 12975126.275076583;                  // 创建一个 High_t 类型的变量 high，并初始化为 12975126.275076583
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 12975126.275076583); // 断言 targetDouble 等于 12975126.275076583
}
TEST(INF, HighToTargetPositive_81)
{
    High_t high = 24241907.447952464;                  // 创建一个 High_t 类型的变量 high，并初始化为 24241907.447952464
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 24241907.447952464); // 断言 targetDouble 等于 24241907.447952464
}
TEST(INF, HighToTargetPositive_82)
{
    High_t high = -54467409.574893735;                  // 创建一个 High_t 类型的变量 high，并初始化为 -54467409.574893735
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -54467409.574893735); // 断言 targetDouble 等于 -54467409.574893735
}
TEST(INF, HighToTargetPositive_83)
{
    High_t high = -10247200.354971945;                  // 创建一个 High_t 类型的变量 high，并初始化为 -10247200.354971945
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -10247200.354971945); // 断言 targetDouble 等于 -10247200.354971945
}
TEST(INF, HighToTargetPositive_84)
{
    High_t high = -40900150.62264112;                  // 创建一个 High_t 类型的变量 high，并初始化为 -40900150.62264112
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -40900150.62264112); // 断言 targetDouble 等于 -40900150.62264112
}
TEST(INF, HighToTargetPositive_85)
{
    High_t high = -89875562.68126166;                  // 创建一个 High_t 类型的变量 high，并初始化为 -89875562.68126166
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -89875562.68126166); // 断言 targetDouble 等于 -89875562.68126166
}
TEST(INF, HighToTargetPositive_86)
{
    High_t high = 21148749.439708874;                  // 创建一个 High_t 类型的变量 high，并初始化为 21148749.439708874
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 21148749.439708874); // 断言 targetDouble 等于 21148749.439708874
}
TEST(INF, HighToTargetPositive_87)
{
    High_t high = -30044261.5590325;                  // 创建一个 High_t 类型的变量 high，并初始化为 -30044261.5590325
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -30044261.5590325); // 断言 targetDouble 等于 -30044261.5590325
}
TEST(INF, HighToTargetPositive_88)
{
    High_t high = -24318850.647489548;                  // 创建一个 High_t 类型的变量 high，并初始化为 -24318850.647489548
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -24318850.647489548); // 断言 targetDouble 等于 -24318850.647489548
}
TEST(INF, HighToTargetPositive_89)
{
    High_t high = -90357874.92931502;                  // 创建一个 High_t 类型的变量 high，并初始化为 -90357874.92931502
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -90357874.92931502); // 断言 targetDouble 等于 -90357874.92931502
}
TEST(INF, HighToTargetPositive_90)
{
    High_t high = -77639301.57323632;                  // 创建一个 High_t 类型的变量 high，并初始化为 -77639301.57323632
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -77639301.57323632); // 断言 targetDouble 等于 -77639301.57323632
}
TEST(INF, HighToTargetPositive_91)
{
    High_t high = -29050792.84581977;                  // 创建一个 High_t 类型的变量 high，并初始化为 -29050792.84581977
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -29050792.84581977); // 断言 targetDouble 等于 -29050792.84581977
}
TEST(INF, HighToTargetPositive_92)
{
    High_t high = -377779.12788932025;                  // 创建一个 High_t 类型的变量 high，并初始化为 -377779.12788932025
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -377779.12788932025); // 断言 targetDouble 等于 -377779.12788932025
}
TEST(INF, HighToTargetPositive_93)
{
    High_t high = -84629985.8316515;                  // 创建一个 High_t 类型的变量 high，并初始化为 -84629985.8316515
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -84629985.8316515); // 断言 targetDouble 等于 -84629985.8316515
}
TEST(INF, HighToTargetPositive_94)
{
    High_t high = -17067309.9145713;                  // 创建一个 High_t 类型的变量 high，并初始化为 -17067309.9145713
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -17067309.9145713); // 断言 targetDouble 等于 -17067309.9145713
}
TEST(INF, HighToTargetPositive_95)
{
    High_t high = 8515593.764994025;                  // 创建一个 High_t 类型的变量 high，并初始化为 8515593.764994025
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 8515593.764994025); // 断言 targetDouble 等于 8515593.764994025
}
TEST(INF, HighToTargetPositive_96)
{
    High_t high = 10722003.332925946;                  // 创建一个 High_t 类型的变量 high，并初始化为 10722003.332925946
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 10722003.332925946); // 断言 targetDouble 等于 10722003.332925946
}
TEST(INF, HighToTargetPositive_97)
{
    High_t high = 25813268.12550871;                  // 创建一个 High_t 类型的变量 high，并初始化为 25813268.12550871
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 25813268.12550871); // 断言 targetDouble 等于 25813268.12550871
}
TEST(INF, HighToTargetPositive_98)
{
    High_t high = -18715628.048400387;                  // 创建一个 High_t 类型的变量 high，并初始化为 -18715628.048400387
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -18715628.048400387); // 断言 targetDouble 等于 -18715628.048400387
}
TEST(INF, HighToTargetPositive_99)
{
    High_t high = 57433777.86774409;                  // 创建一个 High_t 类型的变量 high，并初始化为 57433777.86774409
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 57433777.86774409); // 断言 targetDouble 等于 57433777.86774409
}
TEST(INF, HighToTargetPositive_100)
{
    High_t high = 20171938.81589943;                  // 创建一个 High_t 类型的变量 high，并初始化为 20171938.81589943
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 20171938.81589943); // 断言 targetDouble 等于 20171938.81589943
}
TEST(INF, HighToTargetPositive_101)
{
    High_t high = -36645045.53519321;                  // 创建一个 High_t 类型的变量 high，并初始化为 -36645045.53519321
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -36645045.53519321); // 断言 targetDouble 等于 -36645045.53519321
}
TEST(INF, HighToTargetPositive_102)
{
    High_t high = 86381778.37857369;                  // 创建一个 High_t 类型的变量 high，并初始化为 86381778.37857369
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 86381778.37857369); // 断言 targetDouble 等于 86381778.37857369
}
TEST(INF, HighToTargetPositive_103)
{
    High_t high = -45041737.73462132;                  // 创建一个 High_t 类型的变量 high，并初始化为 -45041737.73462132
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -45041737.73462132); // 断言 targetDouble 等于 -45041737.73462132
}
TEST(INF, HighToTargetPositive_104)
{
    High_t high = -81843746.14024618;                  // 创建一个 High_t 类型的变量 high，并初始化为 -81843746.14024618
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -81843746.14024618); // 断言 targetDouble 等于 -81843746.14024618
}
TEST(INF, HighToTargetPositive_105)
{
    High_t high = 1749118.70406273;                  // 创建一个 High_t 类型的变量 high，并初始化为 1749118.70406273
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 1749118.70406273); // 断言 targetDouble 等于 1749118.70406273
}
TEST(INF, HighToTargetPositive_106)
{
    High_t high = 78065960.64340678;                  // 创建一个 High_t 类型的变量 high，并初始化为 78065960.64340678
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 78065960.64340678); // 断言 targetDouble 等于 78065960.64340678
}
TEST(INF, HighToTargetPositive_107)
{
    High_t high = -63026404.91392075;                  // 创建一个 High_t 类型的变量 high，并初始化为 -63026404.91392075
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -63026404.91392075); // 断言 targetDouble 等于 -63026404.91392075
}
TEST(INF, HighToTargetPositive_108)
{
    High_t high = -83719633.82250106;                  // 创建一个 High_t 类型的变量 high，并初始化为 -83719633.82250106
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -83719633.82250106); // 断言 targetDouble 等于 -83719633.82250106
}
TEST(INF, HighToTargetPositive_109)
{
    High_t high = 83074328.98432288;                  // 创建一个 High_t 类型的变量 high，并初始化为 83074328.98432288
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 83074328.98432288); // 断言 targetDouble 等于 83074328.98432288
}
TEST(INF, HighToTargetPositive_110)
{
    High_t high = -86504039.1357874;                  // 创建一个 High_t 类型的变量 high，并初始化为 -86504039.1357874
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -86504039.1357874); // 断言 targetDouble 等于 -86504039.1357874
}
TEST(INF, HighToTargetPositive_111)
{
    High_t high = 695401.2751281708;                  // 创建一个 High_t 类型的变量 high，并初始化为 695401.2751281708
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 695401.2751281708); // 断言 targetDouble 等于 695401.2751281708
}
TEST(INF, HighToTargetPositive_112)
{
    High_t high = -75668364.18874735;                  // 创建一个 High_t 类型的变量 high，并初始化为 -75668364.18874735
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -75668364.18874735); // 断言 targetDouble 等于 -75668364.18874735
}
TEST(INF, HighToTargetPositive_113)
{
    High_t high = -46132566.56987927;                  // 创建一个 High_t 类型的变量 high，并初始化为 -46132566.56987927
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -46132566.56987927); // 断言 targetDouble 等于 -46132566.56987927
}
TEST(INF, HighToTargetPositive_114)
{
    High_t high = 80877743.97865742;                  // 创建一个 High_t 类型的变量 high，并初始化为 80877743.97865742
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 80877743.97865742); // 断言 targetDouble 等于 80877743.97865742
}
TEST(INF, HighToTargetPositive_115)
{
    High_t high = -81393995.3703161;                  // 创建一个 High_t 类型的变量 high，并初始化为 -81393995.3703161
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -81393995.3703161); // 断言 targetDouble 等于 -81393995.3703161
}
TEST(INF, HighToTargetPositive_116)
{
    High_t high = 5843514.8494300395;                  // 创建一个 High_t 类型的变量 high，并初始化为 5843514.8494300395
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 5843514.8494300395); // 断言 targetDouble 等于 5843514.8494300395
}
TEST(INF, HighToTargetPositive_117)
{
    High_t high = -95104.50045882165;                  // 创建一个 High_t 类型的变量 high，并初始化为 -95104.50045882165
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -95104.50045882165); // 断言 targetDouble 等于 -95104.50045882165
}
TEST(INF, HighToTargetPositive_118)
{
    High_t high = -47599450.0748075;                  // 创建一个 High_t 类型的变量 high，并初始化为 -47599450.0748075
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -47599450.0748075); // 断言 targetDouble 等于 -47599450.0748075
}
TEST(INF, HighToTargetPositive_119)
{
    High_t high = -82464499.70955218;                  // 创建一个 High_t 类型的变量 high，并初始化为 -82464499.70955218
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -82464499.70955218); // 断言 targetDouble 等于 -82464499.70955218
}
TEST(INF, HighToTargetPositive_120)
{
    High_t high = 93265771.3834045;                  // 创建一个 High_t 类型的变量 high，并初始化为 93265771.3834045
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 93265771.3834045); // 断言 targetDouble 等于 93265771.3834045
}
TEST(INF, HighToTargetPositive_121)
{
    High_t high = 36951274.802369475;                  // 创建一个 High_t 类型的变量 high，并初始化为 36951274.802369475
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 36951274.802369475); // 断言 targetDouble 等于 36951274.802369475
}
TEST(INF, HighToTargetPositive_122)
{
    High_t high = -95428152.39507048;                  // 创建一个 High_t 类型的变量 high，并初始化为 -95428152.39507048
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -95428152.39507048); // 断言 targetDouble 等于 -95428152.39507048
}
TEST(INF, HighToTargetPositive_123)
{
    High_t high = -10451356.943960026;                  // 创建一个 High_t 类型的变量 high，并初始化为 -10451356.943960026
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -10451356.943960026); // 断言 targetDouble 等于 -10451356.943960026
}
TEST(INF, HighToTargetPositive_124)
{
    High_t high = -85114425.63589449;                  // 创建一个 High_t 类型的变量 high，并初始化为 -85114425.63589449
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -85114425.63589449); // 断言 targetDouble 等于 -85114425.63589449
}
TEST(INF, HighToTargetPositive_125)
{
    High_t high = 97271480.25262168;                  // 创建一个 High_t 类型的变量 high，并初始化为 97271480.25262168
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 97271480.25262168); // 断言 targetDouble 等于 97271480.25262168
}
TEST(INF, HighToTargetPositive_126)
{
    High_t high = 13387102.103441343;                  // 创建一个 High_t 类型的变量 high，并初始化为 13387102.103441343
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 13387102.103441343); // 断言 targetDouble 等于 13387102.103441343
}
TEST(INF, HighToTargetPositive_127)
{
    High_t high = 55476312.72265795;                  // 创建一个 High_t 类型的变量 high，并初始化为 55476312.72265795
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 55476312.72265795); // 断言 targetDouble 等于 55476312.72265795
}
TEST(INF, HighToTargetPositive_128)
{
    High_t high = 76468196.09803697;                  // 创建一个 High_t 类型的变量 high，并初始化为 76468196.09803697
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 76468196.09803697); // 断言 targetDouble 等于 76468196.09803697
}
TEST(INF, HighToTargetPositive_129)
{
    High_t high = 85181382.20910206;                  // 创建一个 High_t 类型的变量 high，并初始化为 85181382.20910206
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 85181382.20910206); // 断言 targetDouble 等于 85181382.20910206
}
TEST(INF, HighToTargetPositive_130)
{
    High_t high = 32853050.52417393;                  // 创建一个 High_t 类型的变量 high，并初始化为 32853050.52417393
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 32853050.52417393); // 断言 targetDouble 等于 32853050.52417393
}
TEST(INF, HighToTargetPositive_131)
{
    High_t high = 53024220.104934335;                  // 创建一个 High_t 类型的变量 high，并初始化为 53024220.104934335
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 53024220.104934335); // 断言 targetDouble 等于 53024220.104934335
}
TEST(INF, HighToTargetPositive_132)
{
    High_t high = -89837164.2088508;                  // 创建一个 High_t 类型的变量 high，并初始化为 -89837164.2088508
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -89837164.2088508); // 断言 targetDouble 等于 -89837164.2088508
}
TEST(INF, HighToTargetPositive_133)
{
    High_t high = -31062328.765726328;                  // 创建一个 High_t 类型的变量 high，并初始化为 -31062328.765726328
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -31062328.765726328); // 断言 targetDouble 等于 -31062328.765726328
}
TEST(INF, HighToTargetPositive_134)
{
    High_t high = -73244867.15291041;                  // 创建一个 High_t 类型的变量 high，并初始化为 -73244867.15291041
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -73244867.15291041); // 断言 targetDouble 等于 -73244867.15291041
}
TEST(INF, HighToTargetPositive_135)
{
    High_t high = 8292482.461374491;                  // 创建一个 High_t 类型的变量 high，并初始化为 8292482.461374491
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 8292482.461374491); // 断言 targetDouble 等于 8292482.461374491
}
TEST(INF, HighToTargetPositive_136)
{
    High_t high = 49290938.14528823;                  // 创建一个 High_t 类型的变量 high，并初始化为 49290938.14528823
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 49290938.14528823); // 断言 targetDouble 等于 49290938.14528823
}
TEST(INF, HighToTargetPositive_137)
{
    High_t high = -90200134.27877757;                  // 创建一个 High_t 类型的变量 high，并初始化为 -90200134.27877757
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -90200134.27877757); // 断言 targetDouble 等于 -90200134.27877757
}
TEST(INF, HighToTargetPositive_138)
{
    High_t high = -95039192.34423117;                  // 创建一个 High_t 类型的变量 high，并初始化为 -95039192.34423117
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -95039192.34423117); // 断言 targetDouble 等于 -95039192.34423117
}
TEST(INF, HighToTargetPositive_139)
{
    High_t high = 92496078.24775836;                  // 创建一个 High_t 类型的变量 high，并初始化为 92496078.24775836
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 92496078.24775836); // 断言 targetDouble 等于 92496078.24775836
}
TEST(INF, HighToTargetPositive_140)
{
    High_t high = 92677490.40655684;                  // 创建一个 High_t 类型的变量 high，并初始化为 92677490.40655684
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 92677490.40655684); // 断言 targetDouble 等于 92677490.40655684
}
TEST(INF, HighToTargetPositive_141)
{
    High_t high = -41695143.46665486;                  // 创建一个 High_t 类型的变量 high，并初始化为 -41695143.46665486
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -41695143.46665486); // 断言 targetDouble 等于 -41695143.46665486
}
TEST(INF, HighToTargetPositive_142)
{
    High_t high = 31831782.604491442;                  // 创建一个 High_t 类型的变量 high，并初始化为 31831782.604491442
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 31831782.604491442); // 断言 targetDouble 等于 31831782.604491442
}
TEST(INF, HighToTargetPositive_143)
{
    High_t high = -6581252.880815908;                  // 创建一个 High_t 类型的变量 high，并初始化为 -6581252.880815908
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -6581252.880815908); // 断言 targetDouble 等于 -6581252.880815908
}
TEST(INF, HighToTargetPositive_144)
{
    High_t high = 22508116.693599716;                  // 创建一个 High_t 类型的变量 high，并初始化为 22508116.693599716
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 22508116.693599716); // 断言 targetDouble 等于 22508116.693599716
}
TEST(INF, HighToTargetPositive_145)
{
    High_t high = 32489407.970650166;                  // 创建一个 High_t 类型的变量 high，并初始化为 32489407.970650166
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 32489407.970650166); // 断言 targetDouble 等于 32489407.970650166
}
TEST(INF, HighToTargetPositive_146)
{
    High_t high = -82720346.2762448;                  // 创建一个 High_t 类型的变量 high，并初始化为 -82720346.2762448
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -82720346.2762448); // 断言 targetDouble 等于 -82720346.2762448
}
TEST(INF, HighToTargetPositive_147)
{
    High_t high = -61135860.580906585;                  // 创建一个 High_t 类型的变量 high，并初始化为 -61135860.580906585
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -61135860.580906585); // 断言 targetDouble 等于 -61135860.580906585
}
TEST(INF, HighToTargetPositive_148)
{
    High_t high = -63418586.56095795;                  // 创建一个 High_t 类型的变量 high，并初始化为 -63418586.56095795
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -63418586.56095795); // 断言 targetDouble 等于 -63418586.56095795
}
TEST(INF, HighToTargetPositive_149)
{
    High_t high = -18489342.258493453;                  // 创建一个 High_t 类型的变量 high，并初始化为 -18489342.258493453
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -18489342.258493453); // 断言 targetDouble 等于 -18489342.258493453
}
TEST(INF, HighToTargetPositive_150)
{
    High_t high = -50703067.12553094;                  // 创建一个 High_t 类型的变量 high，并初始化为 -50703067.12553094
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -50703067.12553094); // 断言 targetDouble 等于 -50703067.12553094
}
TEST(INF, HighToTargetPositive_151)
{
    High_t high = -82707953.81340712;                  // 创建一个 High_t 类型的变量 high，并初始化为 -82707953.81340712
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -82707953.81340712); // 断言 targetDouble 等于 -82707953.81340712
}
TEST(INF, HighToTargetPositive_152)
{
    High_t high = 91370978.7291424;                  // 创建一个 High_t 类型的变量 high，并初始化为 91370978.7291424
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 91370978.7291424); // 断言 targetDouble 等于 91370978.7291424
}
TEST(INF, HighToTargetPositive_153)
{
    High_t high = 79598851.8867797;                  // 创建一个 High_t 类型的变量 high，并初始化为 79598851.8867797
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 79598851.8867797); // 断言 targetDouble 等于 79598851.8867797
}
TEST(INF, HighToTargetPositive_154)
{
    High_t high = -13637235.076496124;                  // 创建一个 High_t 类型的变量 high，并初始化为 -13637235.076496124
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -13637235.076496124); // 断言 targetDouble 等于 -13637235.076496124
}
TEST(INF, HighToTargetPositive_155)
{
    High_t high = 47209092.35646182;                  // 创建一个 High_t 类型的变量 high，并初始化为 47209092.35646182
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 47209092.35646182); // 断言 targetDouble 等于 47209092.35646182
}
TEST(INF, HighToTargetPositive_156)
{
    High_t high = -17510840.36501929;                  // 创建一个 High_t 类型的变量 high，并初始化为 -17510840.36501929
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -17510840.36501929); // 断言 targetDouble 等于 -17510840.36501929
}
TEST(INF, HighToTargetPositive_157)
{
    High_t high = 73132063.62423837;                  // 创建一个 High_t 类型的变量 high，并初始化为 73132063.62423837
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 73132063.62423837); // 断言 targetDouble 等于 73132063.62423837
}
TEST(INF, HighToTargetPositive_158)
{
    High_t high = 97698792.21244714;                  // 创建一个 High_t 类型的变量 high，并初始化为 97698792.21244714
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 97698792.21244714); // 断言 targetDouble 等于 97698792.21244714
}
TEST(INF, HighToTargetPositive_159)
{
    High_t high = 10022734.38047339;                  // 创建一个 High_t 类型的变量 high，并初始化为 10022734.38047339
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 10022734.38047339); // 断言 targetDouble 等于 10022734.38047339
}
TEST(INF, HighToTargetPositive_160)
{
    High_t high = 81731766.40357625;                  // 创建一个 High_t 类型的变量 high，并初始化为 81731766.40357625
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 81731766.40357625); // 断言 targetDouble 等于 81731766.40357625
}
TEST(INF, HighToTargetPositive_161)
{
    High_t high = 6484497.518013343;                  // 创建一个 High_t 类型的变量 high，并初始化为 6484497.518013343
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 6484497.518013343); // 断言 targetDouble 等于 6484497.518013343
}
TEST(INF, HighToTargetPositive_162)
{
    High_t high = -2562510.4990460128;                  // 创建一个 High_t 类型的变量 high，并初始化为 -2562510.4990460128
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -2562510.4990460128); // 断言 targetDouble 等于 -2562510.4990460128
}
TEST(INF, HighToTargetPositive_163)
{
    High_t high = 42212429.28420755;                  // 创建一个 High_t 类型的变量 high，并初始化为 42212429.28420755
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 42212429.28420755); // 断言 targetDouble 等于 42212429.28420755
}
TEST(INF, HighToTargetPositive_164)
{
    High_t high = -78112707.25422743;                  // 创建一个 High_t 类型的变量 high，并初始化为 -78112707.25422743
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -78112707.25422743); // 断言 targetDouble 等于 -78112707.25422743
}
TEST(INF, HighToTargetPositive_165)
{
    High_t high = 38478300.84318343;                  // 创建一个 High_t 类型的变量 high，并初始化为 38478300.84318343
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 38478300.84318343); // 断言 targetDouble 等于 38478300.84318343
}
TEST(INF, HighToTargetPositive_166)
{
    High_t high = -44183846.77335485;                  // 创建一个 High_t 类型的变量 high，并初始化为 -44183846.77335485
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -44183846.77335485); // 断言 targetDouble 等于 -44183846.77335485
}
TEST(INF, HighToTargetPositive_167)
{
    High_t high = 88219906.83841667;                  // 创建一个 High_t 类型的变量 high，并初始化为 88219906.83841667
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 88219906.83841667); // 断言 targetDouble 等于 88219906.83841667
}
TEST(INF, HighToTargetPositive_168)
{
    High_t high = -92540432.5170528;                  // 创建一个 High_t 类型的变量 high，并初始化为 -92540432.5170528
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -92540432.5170528); // 断言 targetDouble 等于 -92540432.5170528
}
TEST(INF, HighToTargetPositive_169)
{
    High_t high = -86067183.13619608;                  // 创建一个 High_t 类型的变量 high，并初始化为 -86067183.13619608
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -86067183.13619608); // 断言 targetDouble 等于 -86067183.13619608
}
TEST(INF, HighToTargetPositive_170)
{
    High_t high = 76066426.4507196;                  // 创建一个 High_t 类型的变量 high，并初始化为 76066426.4507196
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 76066426.4507196); // 断言 targetDouble 等于 76066426.4507196
}
TEST(INF, HighToTargetPositive_171)
{
    High_t high = 4796719.8333225995;                  // 创建一个 High_t 类型的变量 high，并初始化为 4796719.8333225995
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 4796719.8333225995); // 断言 targetDouble 等于 4796719.8333225995
}
TEST(INF, HighToTargetPositive_172)
{
    High_t high = 13384070.865405023;                  // 创建一个 High_t 类型的变量 high，并初始化为 13384070.865405023
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 13384070.865405023); // 断言 targetDouble 等于 13384070.865405023
}
TEST(INF, HighToTargetPositive_173)
{
    High_t high = 22068253.78978765;                  // 创建一个 High_t 类型的变量 high，并初始化为 22068253.78978765
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 22068253.78978765); // 断言 targetDouble 等于 22068253.78978765
}
TEST(INF, HighToTargetPositive_174)
{
    High_t high = 61200965.79312411;                  // 创建一个 High_t 类型的变量 high，并初始化为 61200965.79312411
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 61200965.79312411); // 断言 targetDouble 等于 61200965.79312411
}
TEST(INF, HighToTargetPositive_175)
{
    High_t high = 72166176.64499578;                  // 创建一个 High_t 类型的变量 high，并初始化为 72166176.64499578
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 72166176.64499578); // 断言 targetDouble 等于 72166176.64499578
}
TEST(INF, HighToTargetPositive_176)
{
    High_t high = -87539432.37716067;                  // 创建一个 High_t 类型的变量 high，并初始化为 -87539432.37716067
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -87539432.37716067); // 断言 targetDouble 等于 -87539432.37716067
}
TEST(INF, HighToTargetPositive_177)
{
    High_t high = 51908647.89635521;                  // 创建一个 High_t 类型的变量 high，并初始化为 51908647.89635521
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 51908647.89635521); // 断言 targetDouble 等于 51908647.89635521
}
TEST(INF, HighToTargetPositive_178)
{
    High_t high = 893479.1706137508;                  // 创建一个 High_t 类型的变量 high，并初始化为 893479.1706137508
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 893479.1706137508); // 断言 targetDouble 等于 893479.1706137508
}
TEST(INF, HighToTargetPositive_179)
{
    High_t high = -34465800.47057759;                  // 创建一个 High_t 类型的变量 high，并初始化为 -34465800.47057759
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -34465800.47057759); // 断言 targetDouble 等于 -34465800.47057759
}
TEST(INF, HighToTargetPositive_180)
{
    High_t high = 23565424.86633812;                  // 创建一个 High_t 类型的变量 high，并初始化为 23565424.86633812
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 23565424.86633812); // 断言 targetDouble 等于 23565424.86633812
}
TEST(INF, HighToTargetPositive_181)
{
    High_t high = -44063855.81655023;                  // 创建一个 High_t 类型的变量 high，并初始化为 -44063855.81655023
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -44063855.81655023); // 断言 targetDouble 等于 -44063855.81655023
}
TEST(INF, HighToTargetPositive_182)
{
    High_t high = 73113412.72922954;                  // 创建一个 High_t 类型的变量 high，并初始化为 73113412.72922954
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 73113412.72922954); // 断言 targetDouble 等于 73113412.72922954
}
TEST(INF, HighToTargetPositive_183)
{
    High_t high = -6818094.825411186;                  // 创建一个 High_t 类型的变量 high，并初始化为 -6818094.825411186
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -6818094.825411186); // 断言 targetDouble 等于 -6818094.825411186
}
TEST(INF, HighToTargetPositive_184)
{
    High_t high = -81716287.11840096;                  // 创建一个 High_t 类型的变量 high，并初始化为 -81716287.11840096
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -81716287.11840096); // 断言 targetDouble 等于 -81716287.11840096
}
TEST(INF, HighToTargetPositive_185)
{
    High_t high = -91052.21108926833;                  // 创建一个 High_t 类型的变量 high，并初始化为 -91052.21108926833
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -91052.21108926833); // 断言 targetDouble 等于 -91052.21108926833
}
TEST(INF, HighToTargetPositive_186)
{
    High_t high = -17017317.52478169;                  // 创建一个 High_t 类型的变量 high，并初始化为 -17017317.52478169
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -17017317.52478169); // 断言 targetDouble 等于 -17017317.52478169
}
TEST(INF, HighToTargetPositive_187)
{
    High_t high = 19706929.391249985;                  // 创建一个 High_t 类型的变量 high，并初始化为 19706929.391249985
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 19706929.391249985); // 断言 targetDouble 等于 19706929.391249985
}
TEST(INF, HighToTargetPositive_188)
{
    High_t high = -66867530.01408277;                  // 创建一个 High_t 类型的变量 high，并初始化为 -66867530.01408277
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -66867530.01408277); // 断言 targetDouble 等于 -66867530.01408277
}
TEST(INF, HighToTargetPositive_189)
{
    High_t high = -18732171.561116457;                  // 创建一个 High_t 类型的变量 high，并初始化为 -18732171.561116457
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -18732171.561116457); // 断言 targetDouble 等于 -18732171.561116457
}
TEST(INF, HighToTargetPositive_190)
{
    High_t high = -31202659.285812408;                  // 创建一个 High_t 类型的变量 high，并初始化为 -31202659.285812408
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -31202659.285812408); // 断言 targetDouble 等于 -31202659.285812408
}
TEST(INF, HighToTargetPositive_191)
{
    High_t high = -30684774.12996395;                  // 创建一个 High_t 类型的变量 high，并初始化为 -30684774.12996395
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -30684774.12996395); // 断言 targetDouble 等于 -30684774.12996395
}
TEST(INF, HighToTargetPositive_192)
{
    High_t high = 59207144.86326969;                  // 创建一个 High_t 类型的变量 high，并初始化为 59207144.86326969
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 59207144.86326969); // 断言 targetDouble 等于 59207144.86326969
}
TEST(INF, HighToTargetPositive_193)
{
    High_t high = 72820057.34686923;                  // 创建一个 High_t 类型的变量 high，并初始化为 72820057.34686923
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 72820057.34686923); // 断言 targetDouble 等于 72820057.34686923
}
TEST(INF, HighToTargetPositive_194)
{
    High_t high = 13346881.965636998;                  // 创建一个 High_t 类型的变量 high，并初始化为 13346881.965636998
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 13346881.965636998); // 断言 targetDouble 等于 13346881.965636998
}
TEST(INF, HighToTargetPositive_195)
{
    High_t high = 97257551.54108992;                  // 创建一个 High_t 类型的变量 high，并初始化为 97257551.54108992
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 97257551.54108992); // 断言 targetDouble 等于 97257551.54108992
}
TEST(INF, HighToTargetPositive_196)
{
    High_t high = -17296645.210670188;                  // 创建一个 High_t 类型的变量 high，并初始化为 -17296645.210670188
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -17296645.210670188); // 断言 targetDouble 等于 -17296645.210670188
}
TEST(INF, HighToTargetPositive_197)
{
    High_t high = -42195875.56069291;                  // 创建一个 High_t 类型的变量 high，并初始化为 -42195875.56069291
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -42195875.56069291); // 断言 targetDouble 等于 -42195875.56069291
}
TEST(INF, HighToTargetPositive_198)
{
    High_t high = 99759750.37599108;                  // 创建一个 High_t 类型的变量 high，并初始化为 99759750.37599108
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, 99759750.37599108); // 断言 targetDouble 等于 99759750.37599108
}
TEST(INF, HighToTargetPositive_199)
{
    High_t high = -84579588.64343223;                  // 创建一个 High_t 类型的变量 high，并初始化为 -84579588.64343223
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -84579588.64343223); // 断言 targetDouble 等于 -84579588.64343223
}
TEST(INF, HighToTargetPositive_200)
{
    High_t high = -71372090.6501115;                  // 创建一个 High_t 类型的变量 high，并初始化为 -71372090.6501115
    double targetDouble = high.toDouble();      // 调用 target 的 toDouble() 方法，将其转换为 double 类型

    EXPECT_DOUBLE_EQ(targetDouble, -71372090.6501115); // 断言 targetDouble 等于 -71372090.6501115
}
