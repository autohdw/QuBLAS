#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <stdexcept>
#include <string_view>
#include <type_traits>
#include <utility>

inline namespace QuBLAS {

// ------------------- Random -------------------

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<int> UniRand(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()); // 整数的全范围分布
static std::normal_distribution<double> NormRand(0, 1);                                                              // 正态分布

// ------------------- TypeList -------------------

template <typename... Types>
struct TypeList
{
    using head = std::nullptr_t;
    static inline constexpr size_t size = sizeof...(Types);
};

template <typename Head, typename... Tail>
struct TypeList<Head, Tail...>
{
    static inline constexpr size_t size = sizeof...(Tail) + 1;
    using head = Head;
    using tail = TypeList<Tail...>;
};

template <int index, typename List>
struct TypeAt_s;

template <typename Head, typename... Tail>
struct TypeAt_s<0, TypeList<Head, Tail...>>
{
    using Result = Head;
};

template <int index, typename Head, typename... Tail>
struct TypeAt_s<index, TypeList<Head, Tail...>>
{
    static_assert(index < sizeof...(Tail) + 1, "Index out of bounds");
    using Result = typename TypeAt_s<index - 1, TypeList<Tail...>>::Result;
};

template <size_t N, typename List>
using TypeAt = typename TypeAt_s<N, List>::Result;

// to tuple
template <typename List>
struct toTuple
{
    using type = std::nullptr_t;
};

template <typename... Types>
struct toTuple<TypeList<Types...>>
{
    using type = std::tuple<Types...>;
};

// ------------------- isA -------------------

template <typename... Args>
struct isA_s
{
    inline static constexpr bool value = false;
};

template <typename T1, typename T2>
struct isA_s<T1, T2>
{
    inline static constexpr bool value = std::is_same_v<T1, T2>;
};

template <template <typename...> class T1, typename... Args1, template <typename...> class T2, typename... Args2>
struct isA_s<T1<Args1...>, T2<Args2...>>
{
    inline static constexpr bool value = false;
};

template <template <typename...> class T1, typename... Args1, typename... Args2>
struct isA_s<T1<Args1...>, T1<Args2...>>
{
    inline static constexpr bool value = true;
};

template <template <auto...> class T1, auto... Args1, template <auto...> class T2, auto... Args2>
struct isA_s<T1<Args1...>, T2<Args2...>>
{
    inline static constexpr bool value = false;
};

template <template <auto...> class T1, auto... Args1, auto... Args2>
struct isA_s<T1<Args1...>, T1<Args2...>>
{
    inline static constexpr bool value = true;
};

template <typename... Args>
inline constexpr bool isA = isA_s<Args...>::value;

// 能否方括号索引
// ------------------- isSquareBracketIndexable -------------------
template <typename T>
concept isSquareBracketIndexable = requires(T a) {
    a[0];
};

// ------------------- tagExtractor -------------------

template <typename Tag, typename... Args>
struct tagExtractor;

// 值未能匹配，最终返回默认值
template <typename T, template <T> class Tag, T Value>
struct tagExtractor<Tag<Value>>
{
    static constexpr T value = Value;
};

// 值匹配成功
template <typename T, template <T> class Tag, T Value, T Value2, typename... Args>
struct tagExtractor<Tag<Value>, Tag<Value2>, Args...>
{
    static constexpr T value = Value2;
};

// 值匹配成功，复合类型版本,应该只会出现在BLAS函数里传入alpha和beta的部分
template <template <typename...> class valType, typename... valArgs1, typename... valArgs2, valType<valArgs1...> val1, valType<valArgs2...> val2, template <valType> class Tag, typename... Args>
struct tagExtractor<Tag<val1>, Tag<val2>, Args...>
{
    static constexpr auto value = val2;
};

// 类型未能匹配，最终返回默认值
template <template <typename> class Tag, typename T>
struct tagExtractor<Tag<T>>
{
    using type = T;
};

// 类型未能匹配，最终返回默认值，多个参数版本
// 注意多个参数版本非常特殊地会将Tag<>保留
template <template <typename...> class Tag, typename... Args>
struct tagExtractor<Tag<Args...>>
{
    using type = Tag<Args...>;
};

// 类型匹配成功，单个参数版本
template <template <typename> class Tag, typename T, typename T2, typename... Args>
struct tagExtractor<Tag<T>, Tag<T2>, Args...>
{
    using type = T2;
};

// 类型匹配成功，多个参数版本
template <template <typename...> class Tag, typename... Args, typename... Args2, typename... Args3>
struct tagExtractor<Tag<Args...>, Tag<Args2...>, Args3...>
{
    using type = Tag<Args2...>;
};

// 匹配失败，类型不符，继续递归
template <typename Tag, typename Tag2, typename... Args>
struct tagExtractor<Tag, Tag2, Args...> : tagExtractor<Tag, Args...>
{
};

// ------------------- pack indexer -------------------
// which is in C++26, we cannot use it now, so we have to implement it in a ugly way

template <size_t IDX, typename T, typename... Ts>
constexpr auto packIndex(T &&t, Ts &&...ts)
{
    static_assert(IDX <= sizeof...(ts), "Index out of bounds");
    if constexpr (IDX > sizeof...(ts))
    {
        return 0;
    }
    else
    {
        if constexpr (IDX == 0)
        {
            return std::forward<T>(t);
        }
        else
        {
            return packIndex<IDX - 1>(std::forward<Ts>(ts)...);
        }
    }
}

// ------------------- concept -------------------

template <typename T, typename... Types>
concept within = (std::is_same_v<T, Types> || ...);

// ------------------- shifter -------------------

static inline auto shiftLeftDynamic(auto val, int shift)
{
    if (shift >= 0)
    {
        return val << shift;
    }
    else
    {
        return val >> (-shift);
    }
}

static inline auto shiftRightDynamic(auto val, int shift)
{
    if (shift >= 0)
    {
        return val >> shift;
    }
    else
    {
        return val << (-shift);
    }
}

static inline double toDoubleDynamic(auto val, int shift)
{
    if (shift >= 0)
    {
        return static_cast<double>(val) / (1 << shift);
    }
    else
    {
        return static_cast<double>(val) * (1 << (-shift));
    }
}

static inline long long int inputDynamic(auto val, int shift)
{
    if (shift >= 0)
    {
        return static_cast<long long int>(static_cast<double>(val) * (1 << shift));
    }
    else
    {

        if (val < (1 << (-shift)))
        {
            return (static_cast<long long int>((static_cast<double>(val) * (1 << (-shift))) / (1 << (-shift)))) >> (-shift);
        }
        else
        {
            return static_cast<long long int>(static_cast<double>(val) / (1 << (-shift)));
        }
    }
}

template <int shift>
struct shifter
{
    template <typename T>
    inline static constexpr T shiftLeft(T val)
    {
        // shift >=0 : left shift, shift < 0 : right shift
        if constexpr (shift >= 0)
        {
            return val << shift;
        }
        else
        {
            return val >> (-shift);
        }
    }

    template <typename T>
    inline static constexpr T shiftRight(T val)
    {
        // shift >=0 : left shift, shift < 0 : right shift
        if constexpr (shift >= 0)
        {
            return val >> shift;
        }
        else
        {
            return val << (-shift);
        }
    }

    template <typename T>
    inline static double toDouble(T val)
    {
        if constexpr (shift >= 0)
        {
            return static_cast<double>(val) / (1 << shift);
        }
        else
        {
            return static_cast<double>(val) * (1 << (-shift));
        }
    }

    template <typename T>
    inline static constexpr long long int input(T val)
    {
        if constexpr (shift >= 0)
        {
            return static_cast<long long int>(static_cast<double>(val) * (1 << shift));
        }
        else
        {

            if (val < (1 << (-shift)))
            {
                return (static_cast<long long int>((static_cast<double>(val) * (1 << (-shift))) / (1 << (-shift)))) >> (-shift);
            }
            else
            {
                return static_cast<long long int>(static_cast<double>(val) / (1 << (-shift)));
            }
        }
    }
};

// ------------------- Qu -------------------

template <typename T>
struct QuMode;

// clang-format off
struct RND
{
    struct POS_INF{inline static constexpr int value = 0;};
    struct NEG_INF{inline static constexpr int value = 1;};
    struct ZERO{inline static constexpr int value = 2;};
    struct INF{inline static constexpr int value = 3;};
    struct CONV{inline static constexpr int value = 4;};
};

struct TRN
{
    struct TCPL{inline static constexpr int value = 5;};
    struct SMGN{inline static constexpr int value = 6;};
};
// clang-format on

inline static long long int fracConvertDynamic(long long int val, int fromFrac, int toFrac, int QuModeTag)
{
    switch (QuModeTag)
    {
    case 0: // POS_INF
        if (fromFrac <= toFrac)
        {
            return val << (toFrac - fromFrac);
        }
        else
        {
            unsigned long long int mask = 0 - (1 << (fromFrac - toFrac));
            long long int floor = val & mask;
            long long int ceil = floor + (1 << (fromFrac - toFrac));

            return ((val - floor) < (ceil - val) ? floor : ceil) >> (fromFrac - toFrac);
        }
        break;
    case 1: // NEG_INF
        if (fromFrac <= toFrac)
        {
            return val << (toFrac - fromFrac);
        }
        else
        {
            unsigned long long int mask = 0 - (1 << (fromFrac - toFrac));
            long long int floor = val & mask;
            long long int ceil = floor + (1 << (fromFrac - toFrac));

            return ((val - floor) <= (ceil - val) ? floor : ceil) >> (fromFrac - toFrac);
        }
        break;
    case 2: // ZERO
        if (fromFrac <= toFrac)
        {
            return val << (toFrac - fromFrac);
        }
        else
        {
            unsigned long long int mask = 0 - (1 << (fromFrac - toFrac));
            long long int floor = val & mask;
            long long int ceil = floor + (1 << (fromFrac - toFrac));

            return (floor + ceil) > 0 ? floor >> (fromFrac - toFrac) : ceil >> (fromFrac - toFrac);
        }
        break;
    case 3: // INF
        if (fromFrac <= toFrac)
        {
            return val << (toFrac - fromFrac);
        }
        else
        {
            unsigned long long int mask = 0 - (1 << (fromFrac - toFrac));
            long long int floor = val & mask;
            long long int ceil = floor + (1 << (fromFrac - toFrac));

            return (floor + ceil) < 0 ? floor >> (fromFrac - toFrac) : ceil >> (fromFrac - toFrac);
        }
        break;
    case 4: // CONV
        if (fromFrac <= toFrac)
        {
            return val << (toFrac - fromFrac);
        }
        else
        {
            unsigned long long int mask = 0 - (1 << (fromFrac - toFrac));
            long long int floor = val & mask;
            long long int ceil = floor + (1 << (fromFrac - toFrac));

            if (floor + ceil == val << 1)
            {
                unsigned long long int mask2 = 1 << (fromFrac - toFrac);
                if (floor & mask2)
                {
                    return ceil >> (fromFrac - toFrac);
                }
                else
                {
                    return floor >> (fromFrac - toFrac);
                }
            }

            return (val - floor) < (ceil - val) ? floor >> (fromFrac - toFrac) : ceil >> (fromFrac - toFrac);
        }
        break;
    case 5: // TCPL
        return shiftRightDynamic(val, fromFrac - toFrac);
        break;
    case 6: // SMGN
        if (fromFrac < toFrac)
        {
            return val << (toFrac - fromFrac);
        }
        else
        {
            if (val >= 0)
            {
                return val >> (fromFrac - toFrac);
            }
            else
            {
                return -((-val) >> (fromFrac - toFrac));
            }
        }
        break;
    default:
        throw std::runtime_error("Invalid QuMode");
    }
}

template <int fromFrac, int toFrac, typename QuMode>
struct fracConvert;

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<RND::POS_INF>>
{
    inline static constexpr auto convert(long long int val)
    {
        if constexpr (fromFrac <= toFrac)
        {
            return val << (toFrac - fromFrac);
        }
        else
        {
            static constexpr unsigned long long int mask = 0 - (1 << (fromFrac - toFrac));
            long long int floor = val & mask;
            long long int ceil = floor + (1 << (fromFrac - toFrac));

            return ((val - floor) < (ceil - val) ? floor : ceil) >> (fromFrac - toFrac);
        }
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<RND::NEG_INF>>
{
    inline static constexpr auto convert(long long int val)
    {
        if constexpr (fromFrac <= toFrac)
        {
            return val << (toFrac - fromFrac);
        }
        else
        {
            static constexpr unsigned long long int mask = 0 - (1 << (fromFrac - toFrac));
            long long int floor = val & mask;
            long long int ceil = floor + (1 << (fromFrac - toFrac));

            return ((val - floor) <= (ceil - val) ? floor : ceil) >> (fromFrac - toFrac);
        }
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<RND::ZERO>>
{
    inline static constexpr auto convert(long long int val)
    {
        if constexpr (fromFrac <= toFrac)
        {
            return val << (toFrac - fromFrac);
        }
        else
        {
            static constexpr unsigned long long int mask = 0 - (1 << (fromFrac - toFrac));
            long long int floor = val & mask;
            long long int ceil = floor + (1 << (fromFrac - toFrac));

            return (floor + ceil) > 0 ? floor >> (fromFrac - toFrac) : ceil >> (fromFrac - toFrac);
        }
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<RND::INF>>
{
    inline static constexpr auto convert(long long int val)
    {
        if constexpr (fromFrac <= toFrac)
        {
            return val << (toFrac - fromFrac);
        }
        else
        {
            static constexpr unsigned long long int mask = 0 - (1 << (fromFrac - toFrac));
            long long int floor = val & mask;
            long long int ceil = floor + (1 << (fromFrac - toFrac));

            return (floor + ceil) < 0 ? floor >> (fromFrac - toFrac) : ceil >> (fromFrac - toFrac);
        }
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<RND::CONV>>
{
    inline static constexpr auto convert(long long int val)
    {
        if constexpr (fromFrac <= toFrac)
        {
            return val << (toFrac - fromFrac);
        }
        else
        {
            static constexpr unsigned long long int mask = 0 - (1 << (fromFrac - toFrac));
            long long int floor = val & mask;
            long long int ceil = floor + (1 << (fromFrac - toFrac));

            if (floor + ceil == val << 1)
            {
                static constexpr unsigned long long int mask2 = 1 << (fromFrac - toFrac);
                if (floor & mask2)
                {
                    return ceil >> (fromFrac - toFrac);
                }
                else
                {
                    return floor >> (fromFrac - toFrac);
                }
            }

            return (val - floor) < (ceil - val) ? floor >> (fromFrac - toFrac) : ceil >> (fromFrac - toFrac);
        }
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<TRN::TCPL>>
{
    inline static constexpr auto convert(long long int val)
    {
        return shifter<fromFrac - toFrac>::shiftRight(static_cast<long long int>(val));
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<TRN::SMGN>>
{
    inline static constexpr auto convert(long long int val)
    {

        if constexpr (fromFrac < toFrac)
        {
            return val << (toFrac - fromFrac);
        }
        else
        {
            if (val >= 0)
            {
                return val >> (fromFrac - toFrac);
            }
            else
            {
                return -((-val) >> (fromFrac - toFrac));
            }
        }
    }
};

template <typename T>
struct OfMode;

struct SAT
{
    // clang-format off
    struct TCPL{inline static constexpr int value = 0;};
    struct ZERO{inline static constexpr int value = 1;};
    struct SMGN{inline static constexpr int value = 2;};
    // clang-format on
};

struct WRP
{
    // clang-format off
    struct TCPL{inline static constexpr int value = 3;};
    template<auto N>
    struct TCPL_SAT{inline static constexpr auto value = 4;};
    // clang-format on
};

inline static int intConvertDynamic(long long int val, int toInt, int toFrac, bool toIsSigned, int OfModeTag)
{
    switch (OfModeTag)
    {
    case 0: // TCPL
    {
        auto maxVal = static_cast<long long int>((1ULL << (toInt + toFrac)) - 1);
        auto minVal = static_cast<long long int>(toIsSigned ? -maxVal - 1 : 0);
        auto clampedVal = std::min(std::max(val, minVal), maxVal);
        return static_cast<int>(clampedVal);
    }
    break;
    case 1: // ZERO
    {
        auto maxVal2 = static_cast<long long int>((1ULL << (toInt + toFrac)) - 1);
        auto minVal2 = static_cast<long long int>(toIsSigned ? -maxVal2 - 1 : 0);
        if (val > maxVal2 || val < minVal2)
        {
            return 0;
        }
        return static_cast<int>(val);
    }
    break;
    case 2: // SMGN
    {
        auto maxVal3 = static_cast<long long int>((1ULL << (toInt + toFrac)) - 1);
        auto minVal3 = static_cast<long long int>(toIsSigned ? -maxVal3 - 1 : 0);
        auto clampedVal2 = std::min(std::max(val, minVal3 + 1), maxVal3);
        return static_cast<int>(clampedVal2);
    }
    break;
    case 3: // TCPL
    {
        if (toIsSigned)
        {
            unsigned long long int mask = (1ULL << (toInt + toFrac + 1)) - 1;

            auto maskedVal = val & mask;

            if (maskedVal >> (toInt + toFrac))
            {
                unsigned long long int mask2 = ~mask;
                return static_cast<int>(maskedVal | mask2);
            }
            else
            {
                return static_cast<int>(maskedVal);
            }
        }
        else
        {
            unsigned long long int mask = (1ULL << (toInt + toFrac)) - 1;
            return static_cast<int>(val & mask);
        }
    }
    break;
    default:
        throw std::runtime_error("Invalid OfMode");
    }
}

template <int toInt, int toFrac, bool toIsSigned, typename OfMode>
struct intConvert;

template <int toInt, int toFrac, bool toIsSigned>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<SAT::TCPL>>
{
    inline static constexpr int convert(long long int val)
    {
        static constexpr auto maxVal = static_cast<long long int>((1ULL << (toInt + toFrac)) - 1);
        static constexpr auto minVal = static_cast<long long int>(toIsSigned ? -maxVal - 1 : 0);

        auto clampedVal = std::min(std::max(val, minVal), maxVal);

        return static_cast<int>(clampedVal);
    }
};

template <int toInt, int toFrac, bool toIsSigned>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<SAT::ZERO>>
{
    inline static constexpr int convert(long long int val)
    {
        static constexpr auto maxVal = static_cast<long long int>((1ULL << (toInt + toFrac)) - 1);
        static constexpr auto minVal = static_cast<long long int>(toIsSigned ? -maxVal - 1 : 0);

        if (val > maxVal || val < minVal)
        {
            return 0;
        }
        return static_cast<int>(val);
    }
};

template <int toInt, int toFrac, bool toIsSigned>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<SAT::SMGN>>
{
    inline static constexpr int convert(long long int val)
    {
        static constexpr auto maxVal = static_cast<long long int>((1ULL << (toInt + toFrac)) - 1);
        static constexpr auto minVal = static_cast<long long int>(toIsSigned ? -maxVal - 1 : 0);

        auto clampedVal = std::min(std::max(val, minVal + 1), maxVal);

        return static_cast<int>(clampedVal);
    }
};

template <int toInt, int toFrac, bool toIsSigned>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<WRP::TCPL>>
{

    inline static constexpr int convert(long long int val)
    {

        if constexpr (toIsSigned)
        {
            static constexpr unsigned long long int mask = (1ULL << (toInt + toFrac + 1)) - 1;

            auto maskedVal = val & mask;

            if (maskedVal >> (toInt + toFrac))
            {
                static constexpr unsigned long long int mask2 = ~mask;
                return static_cast<int>(maskedVal | mask2);
            }
            else
            {
                return static_cast<int>(maskedVal);
            }
        }
        else
        {
            static constexpr unsigned long long int mask = (1ULL << (toInt + toFrac)) - 1;
            return static_cast<int>(val & mask);
        }
    }
};

template <int toInt, int toFrac, bool toIsSigned, auto N>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<WRP::TCPL_SAT<N>>>
{
    inline static constexpr int convert(long long int val)
    {
        throw std::runtime_error("Very cool, coming soon");
        // if constexpr (N == 1)
        // {
        //     constexpr unsigned long long int mask = (1ULL << (toInt + toFrac)) - 1;
        //     if (val>0)
        //     {
        //         return static_cast<std::conditional_t<toIsSigned, int, unsigned int>>(val & mask);
        //     }
        //     else
        //     {

        //     }

        // }
        // return 0;
        return 0;
    }
};

template <int Value>
struct intBits;

template <int Value>
struct fracBits;

template <bool Value>
struct isSigned;

constexpr int defaultIntBits = 12;
constexpr int defaultFracBits = 12;
constexpr bool defaultIsSigned = true;
using defaultQuMode = TRN::TCPL;
using defaultOfMode = SAT::TCPL;

struct DirectAssignTag
{
};

// Dynamic Qu
struct QuDynamic;

// the base specialization that should not be used
template <typename... Args>
class Qu_s
{
    static_assert(sizeof...(Args) >= 0, "You shall not pass");
};

// the basic Qu type for a single fixed-point number
template <int intBitsInput, int fracBitsInput, bool isSignedInput, typename QuModeInput, typename OfModeInput>
class Qu_s<intBits<intBitsInput>, fracBits<fracBitsInput>, isSigned<isSignedInput>, QuMode<QuModeInput>, OfMode<OfModeInput>>
{
public:
    static_assert(0 <= (intBitsInput + fracBitsInput) && (intBitsInput + fracBitsInput) <= 31, "The total bits of a fixed-point number should be between 0 and 31");

    inline static constexpr int intB = intBitsInput;
    inline static constexpr int fracB = fracBitsInput;
    inline static constexpr bool isS = isSignedInput;
    using QuM_t = QuModeInput;
    using OfM_t = OfModeInput;
    inline static constexpr int QuM = QuModeInput::value;
    inline static constexpr int OfM = OfModeInput::value;

    inline static constexpr int minVal = isS ? -((1 << (intBitsInput + fracBitsInput))) : 0;
    inline static constexpr int maxVal = (1 << (intBitsInput + fracBitsInput)) - 1;

    int data;

    template <typename T>
        requires std::is_arithmetic_v<T>
    inline constexpr Qu_s(T val)
    {
        long long int longVal = shifter<fracB>::template input<T>(val);

        longVal = fracConvert<fracBitsInput, fracB, QuMode<QuM_t>>::convert(longVal);
        data = intConvert<intBitsInput, fracBitsInput, isSignedInput, OfMode<OfM_t>>::convert(longVal);
    }

    inline constexpr Qu_s() : data(0) {}
    inline constexpr Qu_s(auto val, DirectAssignTag) : data(val) {}

    // from another static Qu_s
    template <int intBitsFrom, int fracBitsFrom, bool isSignedFrom, typename QuModeFrom, typename OfModeFrom>
    inline constexpr Qu_s(const Qu_s<intBits<intBitsFrom>, fracBits<fracBitsFrom>, isSigned<isSignedFrom>, QuMode<QuModeFrom>, OfMode<OfModeFrom>> &val)
    {
        if constexpr (intBitsFrom == intBitsInput && fracBitsFrom == fracBitsInput && isSignedFrom == isSignedInput)
        {
            data = val.data;
        }
        else
        {
            data = intConvert<intB, fracB, isS, OfMode<OfM_t>>::convert(fracConvert<fracBitsFrom, fracBitsInput, QuMode<QuM_t>>::convert(val.data));
        }
    }

    // from another dynamic Qu_s
    inline Qu_s(const Qu_s<QuDynamic> val);

    // assign() function, just same as the constructor in this specification

    // static
    template <int intBitsFrom, int fracBitsFrom, bool isSignedFrom, typename QuModeFrom, typename OfModeFrom>
    inline constexpr void assign(const Qu_s<intBits<intBitsFrom>, fracBits<fracBitsFrom>, isSigned<isSignedFrom>, QuMode<QuModeFrom>, OfMode<OfModeFrom>> &val)
    {
        if constexpr (intBitsFrom == intBitsInput && fracBitsFrom == fracBitsInput && isSignedFrom == isSignedInput)
        {
            data = val.data;
        }
        else
        {
            data = intConvert<intB, fracB, isS, OfMode<OfM_t>>::convert(fracConvert<fracBitsFrom, fracBitsInput, QuMode<QuM_t>>::convert(val.data));
        }
    }

    // dynamic
    inline void assign(const Qu_s<QuDynamic> val);

    inline constexpr double toDouble() const
    {
        return shifter<fracB>::toDouble(data);
    }

    inline constexpr auto toString() const
    {
        return std::bitset<intB + fracB + (isS ? 1 : 0)>(data).to_string();
    }

    inline auto fill()
    {
        return fill(UniRand);
    }

    inline auto fill(std::uniform_int_distribution<int> dis)
    {
        int fillVal = dis(gen);

        // mask to get the last intBits + fracBits + isSigned? 1 : 0 bits
        static constexpr auto mask = ~(~(0u) - ((1u << (intBitsInput + fracBitsInput + (isSignedInput ? 1 : 0))) - 1u));

        auto maskedVal = fillVal & mask;

        if constexpr (isSignedInput)
        {
            if (fillVal & (1 << (intBitsInput + fracBitsInput)))
            {
                this->data = (maskedVal | ~mask);
            }
            else
            {
                this->data = maskedVal;
            }
        }
        else
        {
            this->data = maskedVal;
        }

        return *this;
    }

    inline auto fill(std::normal_distribution<double> dis)
    {
        double fillVal = dis(gen);
        long long int longVal = shifter<fracB>::template input<double>(fillVal);

        longVal = fracConvert<fracBitsInput, fracB, QuMode<QuM_t>>::convert(longVal);
        data = intConvert<intBitsInput, fracBitsInput, isSignedInput, OfMode<OfM_t>>::convert(longVal);
        return *this;
    }

    // fill with a specific binary value
    inline auto fill(int fillVal)
    {
        static constexpr auto maskToGetTheHighestBit = 1u << (intBitsInput + fracBitsInput);
        static constexpr auto mask = ~(~(0u) - ((1u << (intBitsInput + fracBitsInput)) - 1u));

        if (fillVal & maskToGetTheHighestBit)
        {
            this->data = (fillVal | ~mask);
        }
        else
        {
            this->data = fillVal & mask;
        }
        return *this;
    }

    void display(std::string name = "") const
    {
        if (name != "")
        {
            std::cout << name << " :" << std::endl;
        }
        std::cout << "intBits: " << intB << " fracBits: " << fracB << " isSigned: " << isS << " " << "Static" << std::endl;
        std::cout << "Binary: " << std::bitset<intB + fracB + (isS ? 1 : 0)>(data) << std::endl;
        std::cout << "Binary 32: " << std::bitset<32>(data) << std::endl;
        std::cout << "Hex: " << std::hex << data << std::dec << std::endl;

        std::cout << "Decimal: " << shifter<fracB>::toDouble(data) << std::endl;
        std::cout << std::endl;
    }

    // overload for std::cout
    friend std::ostream &operator<<(std::ostream &os, const Qu_s &val)
    {
        os << val.toDouble();
        return os;
    }
};

template <typename... Args>
struct QuInputHelper
{
    inline static constexpr auto intB = tagExtractor<intBits<defaultIntBits>, Args...>::value;
    inline static constexpr auto fracB = tagExtractor<fracBits<defaultFracBits>, Args...>::value;
    inline static constexpr auto isS = tagExtractor<isSigned<defaultIsSigned>, Args...>::value;

    using QuM = tagExtractor<QuMode<defaultQuMode>, Args...>::type;
    using OfM = tagExtractor<OfMode<defaultOfMode>, Args...>::type;

    using type = Qu_s<intBits<intB>, fracBits<fracB>, isSigned<isS>, QuMode<QuM>, OfMode<OfM>>;
};

template <typename... Args>
struct QuInputHelper<Qu_s<Args...>> : QuInputHelper<Args...>
{};

template <typename... Args>
using Qu = typename QuInputHelper<Args...>::type;

// specialization for QuDynamic
template <>
class Qu_s<QuDynamic>
{
public:
    int intB = 8;
    int fracB = 8;
    bool isS = true;
    int QuM = defaultQuMode::value;
    int OfM = defaultOfMode::value;

    int data;

    template <typename T>
        requires std::is_arithmetic_v<T>
    Qu_s(T val)
    {
        long long int longVal = inputDynamic(val, fracB);

        longVal = fracConvertDynamic(longVal, fracB, fracB, QuM);
        data = intConvertDynamic(longVal, intB, fracB, isS, OfM);
    }

    inline Qu_s() : data(0) {}
    inline Qu_s(auto val, DirectAssignTag) : data(val) {}

    template <typename... Args>
    inline Qu_s(const Qu_s<Args...> &val) : intB(val.intB), fracB(val.fracB), isS(val.isS), QuM(val.QuM), OfM(val.OfM), data(val.data) {}

    // operator =
    template <typename... Args>
    inline Qu_s &operator=(const Qu_s<Args...> &val)
    {
        data = intConvertDynamic(fracConvertDynamic(val.data, val.fracB, fracB, val.QuM), val.intB, fracB, val.isS, val.OfM);
        return *this;
    }

    //  move
    template <typename... Args>
    inline Qu_s(Qu_s<Args...> &&val) : intB(val.intB), fracB(val.fracB), isS(val.isS), QuM(val.QuM), OfM(val.OfM), data(val.data) {}

    // move =
    template <typename... Args>
    inline Qu_s &operator=(Qu_s<Args...> &&val)
    {
        data = intConvertDynamic(fracConvertDynamic(val.data, val.fracB, fracB, val.QuM), val.intB, fracB, val.isS, val.OfM);
        return *this;
    }

    // assign() function
    inline void assign(const Qu_s<QuDynamic> val)
    {
        intB = val.intB;
        fracB = val.fracB;
        isS = val.isS;
        QuM = val.QuM;
        OfM = val.OfM;
        data = val.data;
    }

    inline double toDouble() const
    {
        return toDoubleDynamic(data, fracB);
    }

    inline auto toString() const
    {
        std::string str = std::bitset<32>(data).to_string();
        // cut the string to the length of intB + fracB + isS? 1 : 0
        return str.substr(32 - (intB + fracB + (isS ? 1 : 0)));
    }

    inline auto fill(std::uniform_int_distribution<int> dis)
    {
        int fillVal = dis(gen);

        // mask to get the last intBits + fracBits + isSigned? 1 : 0 bits
        auto mask = ~(~(0u) - ((1u << (intB + fracB + (isS ? 1 : 0))) - 1u));

        auto maskedVal = fillVal & mask;

        if (isS)
        {
            if (fillVal & (1 << (intB + fracB)))
            {
                this->data = (maskedVal | ~mask);
            }
            else
            {
                this->data = maskedVal;
            }
        }
        else
        {
            this->data = maskedVal;
        }

        return *this;
    }

    inline auto fill()
    {
        return fill(UniRand);
    }

    inline auto fill(std::normal_distribution<double> dis)
    {
        double fillVal = dis(gen);
        long long int longVal = inputDynamic(fillVal, fracB);

        longVal = fracConvertDynamic(longVal, fracB, fracB, QuM);
        data = intConvertDynamic(longVal, intB, fracB, isS, OfM);
        return *this;
    }

    // fill with a specific binary value
    inline auto fill(int fillVal)
    {
        auto maskToGetTheHighestBit = 1u << (intB + fracB);
        auto mask = ~(~(0u) - ((1u << (intB + fracB)) - 1u));

        if (fillVal & maskToGetTheHighestBit)
        {
            this->data = (fillVal | ~mask);
        }
        else
        {
            this->data = fillVal & mask;
        }
        return *this;
    }

    void display(std::string name = "") const
    {
        if (name != "")
        {
            std::cout << name << " :" << std::endl;
        }
        std::cout << "intBits: " << intB << " fracBits: " << fracB << " isSigned: " << isS << " " << "Dynamic" << std::endl;
        std::cout << "Binary: " << this->toString() << std::endl;
        std::cout << "Binary 32: " << std::bitset<32>(data) << std::endl;
        std::cout << "Hex: " << std::hex << data << std::dec << std::endl;

        std::cout << "Decimal: " << toDouble() << std::endl;
        std::cout << std::endl;
    }

    friend std::ostream &operator<<(std::ostream &os, const Qu_s &val)
    {
        os << val.toDouble();
        return os;
    }
};

template <int intBitsInput, int fracBitsInput, bool isSignedInput, typename QuModeInput, typename OfModeInput>
inline Qu_s<intBits<intBitsInput>, fracBits<fracBitsInput>, isSigned<isSignedInput>, QuMode<QuModeInput>, OfMode<OfModeInput>>::Qu_s(const Qu_s<QuDynamic> val)
{
    long long int longVal = val.data;

    longVal = fracConvertDynamic(longVal, val.fracB, fracBitsInput, QuModeInput::value);
    data = intConvertDynamic(longVal, intBitsInput, fracBitsInput, isSignedInput, OfModeInput::value);
}

template <int intBitsInput, int fracBitsInput, bool isSignedInput, typename QuModeInput, typename OfModeInput>
inline void Qu_s<intBits<intBitsInput>, fracBits<fracBitsInput>, isSigned<isSignedInput>, QuMode<QuModeInput>, OfMode<OfModeInput>>::assign(const Qu_s<QuDynamic> val)
{
    long long int longVal = val.data;

    longVal = fracConvertDynamic(longVal, val.fracB, fracBitsInput, QuModeInput::value);
    data = intConvertDynamic(longVal, intBitsInput, fracBitsInput, isSignedInput, OfModeInput::value);
}

template <>
struct QuInputHelper<QuDynamic>
{
    using type = Qu_s<QuDynamic>;
};

// ------------------- Complex -------------------
template <typename... realArgs, typename... imagArgs>
class Qu_s<Qu_s<realArgs...>, Qu_s<imagArgs...>>
{
public:
    using realType = Qu_s<realArgs...>;
    using imagType = Qu_s<imagArgs...>;
    realType real;
    imagType imag;

    // basic constructor
    Qu_s() {}

    // use = {a, b} to initialize
    template <typename T1, typename T2>
    inline constexpr Qu_s(T1 a, T2 b) : real(a), imag(b) {}

    // use = a to initialize
    template <typename T>
    inline constexpr Qu_s(T a) : real(a), imag(0)
    {}

    template <typename fromRealType, typename fromImagType>
    inline constexpr Qu_s(const Qu_s<fromRealType, fromImagType> &val)
    {
        real = val.real;
        imag = val.imag;
    }

    template <typename T>
    inline constexpr Qu_s(const std::complex<T> &val) : real(val.real()), imag(val.imag()) {}

    // assign from another Qu_s<Qu_s<realArgs...>, Qu_s<imagArgs...>>
    template <typename fromRealType, typename fromImagType>
    inline constexpr void assign(const Qu_s<fromRealType, fromImagType> &val)
    {
        real.assign(val.real);
        imag.assign(val.imag);
    }

    void display(std::string name = "") const
    {
        if (name != "")
        {
            std::cout << name << " :";
        }
        std::cout << std::endl;
        std::cout << "Real part: " << std::endl;
        real.display();
        std::cout << "Imaginary part: " << std::endl;
        imag.display();
    }

    inline constexpr std::complex<double> toDouble() const
    {
        return std::complex<double>(real.toDouble(), imag.toDouble());
    }

    inline constexpr auto toString()
    {
        return "(" + real.toString() + ", " + imag.toString() + ")";
    }

    inline auto fill(auto... dis)
        requires(sizeof...(dis) <= 1)
    {
        real.fill(dis...);
        imag.fill(dis...);
        return *this;
    }

    inline auto fill(auto realInput, auto imagInput)
    {
        real.fill(realInput);
        imag.fill(imagInput);
        return *this;
    }

    // overload for std::cout
    friend std::ostream &operator<<(std::ostream &os, const Qu_s &val)
    {
        os << val.toDouble();
        return os;
    }
};

template <typename... realArgs, typename... imagArgs>
struct QuInputHelper<Qu_s<realArgs...>, Qu_s<imagArgs...>>
{
    using realType = Qu_s<realArgs...>;
    using imagType = Qu_s<imagArgs...>;

    using type = Qu_s<realType, imagType>;
};

template <typename realType, typename imagType>
using Qcomplex = typename QuInputHelper<realType, imagType>::type;

// isDynamic
template <typename T>
struct isDynamic_s
{
};

template <>
struct isDynamic_s<QuDynamic>
{
    static inline constexpr bool value = true;
};

template <int intBitsInput, int fracBitsInput, bool isSignedInput, typename QuModeInput, typename OfModeInput>
struct isDynamic_s<Qu_s<intBits<intBitsInput>, fracBits<fracBitsInput>, isSigned<isSignedInput>, QuMode<QuModeInput>, OfMode<OfModeInput>>>
{
    static inline constexpr bool value = false;
};

template <typename... realArgs, typename... imagArgs>
struct isDynamic_s<Qu_s<Qu_s<realArgs...>, Qu_s<imagArgs...>>>
{
    static inline constexpr bool value = isDynamic_s<Qu_s<realArgs...>>::value || isDynamic_s<Qu_s<imagArgs...>>::value;
};

template <typename T>
inline constexpr bool isDynamic = isDynamic_s<T>::value;

// ------------------- Vector and Matrix -------------------

// std::mdspan only available in clang 18, we need to support gcc
template <size_t... dims>
struct dim
{
    static inline constexpr size_t dimSize = sizeof...(dims);
    static inline constexpr size_t elemSize = (dims * ...);

    static inline constexpr std::array<size_t, dimSize> dimArray = {dims...};

    template <size_t index>
        requires(index < dimSize)
    struct dimAt_s
    {
        static inline constexpr size_t value = dimArray[index];
    };

    template <size_t index>
        requires(index < dimSize)
    static inline constexpr size_t dimAt = dimAt_s<index>::value;

    template <size_t index2>
    struct elemSizeForIndexHead
    {
        static inline constexpr size_t value = std::accumulate(dimArray.begin(), dimArray.begin() + index2, 1, std::multiplies<size_t>());
    };

    template <size_t... index>
        requires(sizeof...(index) == dimSize)
    struct absoluteIndex_s
    {
        template <size_t loc, size_t... index2>
        struct compute;

        template <size_t loc, size_t firstIndex, size_t... indexLeft>
        struct compute<loc, firstIndex, indexLeft...>
        {
            static inline constexpr size_t value = firstIndex * elemSizeForIndexHead<loc>::value + compute<loc + 1, indexLeft...>::value;
        };

        template <size_t firstIndex>
        struct compute<dimSize - 1, firstIndex>
        {
            static inline constexpr size_t value = firstIndex * elemSizeForIndexHead<dimSize - 1>::value;
        };

        static inline constexpr size_t value = compute<0, index...>::value;
    };

    template <size_t... index>
        requires(sizeof...(index) == dimSize)
    using absoluteIndex = absoluteIndex_s<index...>::value;
};

template <size_t... dims, typename Arg>
    requires(isA<Arg, Qu_s<>>)
class Qu_s<dim<dims...>, Arg>
{
public:
    std::array<Arg, dim<dims...>::elemSize> data;

    template <typename First, typename... Rest>
    inline static constexpr size_t calculateIndex(size_t accum, First first, Rest... rest)
    {
        if constexpr (sizeof...(Rest) == 0)
        {
            return accum + first * dim<dims...>::template elemSizeForIndexHead<sizeof...(dims) - 1>::value;
        }
        else
        {
            static constexpr size_t nextDimProduct = dim<dims...>::template elemSizeForIndexHead<sizeof...(dims) - sizeof...(Rest) - 1>::value;
            return calculateIndex(accum + first * nextDimProduct, rest...);
        }
    }

    // 构造函数
    constexpr Qu_s() {}
    constexpr Qu_s(auto... values) : data{values...} {}

    template <typename SquareBracketIndexableType>
        requires isSquareBracketIndexable<SquareBracketIndexableType>
    constexpr Qu_s(const SquareBracketIndexableType &val)
    {
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            data[i] = val[i];
        }
    }

    // 拷贝构造函数
    // 来自相同类型的Qu_s, 直接拷贝std::array
    constexpr Qu_s(const Qu_s<dim<dims...>, Arg> &val) : data(val.data) {}

    // 来自不同类型的Qu_s，逐个元素转换
    template <typename fromArg>
    constexpr Qu_s(const Qu_s<dim<dims...>, fromArg> &val)
    {
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            data[i] = val.data[i];
        }
    }

    // 移动构造函数
    // 来自相同类型的Qu_s, 直接移动std::array
    constexpr Qu_s(Qu_s<dim<dims...>, Arg> &&val) : data(std::move(val.data)) {}

    // 来自不同类型的Qu_s，逐个元素转换
    template <typename fromArg>
    constexpr Qu_s(Qu_s<dim<dims...>, fromArg> &&val)
    {
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            data[i] = std::move(val.data[i]);
        }
    }

    // 拷贝赋值运算符
    // 来自相同类型的Qu_s, 直接拷贝std::array
    constexpr Qu_s &operator=(const Qu_s<dim<dims...>, Arg> &val)
    {
        data = val.data;
        return *this;
    }

    // 来自不同类型的Qu_s，逐个元素转换
    template <typename fromArg>
    constexpr Qu_s &operator=(const Qu_s<dim<dims...>, fromArg> &val)
    {
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            data[i] = val.data[i];
        }
        return *this;
    }

    // 移动赋值运算符
    // 来自相同类型的Qu_s, 直接移动std::array
    constexpr Qu_s &operator=(Qu_s<dim<dims...>, Arg> &&val)
    {
        data = std::move(val.data);
        return *this;
    }

    // 来自不同类型的Qu_s，逐个元素转换
    template <typename fromArg>
    constexpr Qu_s &operator=(Qu_s<dim<dims...>, fromArg> &&val)
    {
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            data[i] = std::move(val.data[i]);
        }
        return *this;
    }

    inline void clear()
    {
        memset(data.data(), 0, dim<dims...>::elemSize * sizeof(Arg));
    }

    inline auto fill(auto... dis)
    {
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            data[i].fill(dis...);
        }
        return *this;
    }

    inline auto shuffle()
    {
        std::shuffle(data.begin(), data.end(), gen);
        return *this;
    }

    // get
    template <auto... index>
    inline constexpr auto &get()
    {
        return data[dim<dims...>::template absoluteIndex<index...>];
    }

    template <auto... index>
    inline constexpr const auto &get() const
    {
        return data[dim<dims...>::template absoluteIndex<index...>];
    }

    // operator[]
    inline constexpr auto &operator[](auto... index)
        requires(sizeof...(index) == dim<dims...>::dimSize && sizeof...(index) > 1)
    {
        return data[calculateIndex(0, index...)];
    }

    inline constexpr const auto &operator[](auto... index) const
        requires(sizeof...(index) == dim<dims...>::dimSize && sizeof...(index) > 1)
    {
        return data[calculateIndex(0, index...)];
    }

    inline constexpr auto &operator[](size_t index)
    {
        return data[index];
    }

    inline constexpr const auto &operator[](size_t index) const
    {
        return data[index];
    }

    inline std::array<double, dim<dims...>::elemSize> toDouble() const
    {
        std::array<double, dim<dims...>::elemSize> result;
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            result[i] = data[i].toDouble();
        }
        return result;
    }

    void display(std::string name = "") const
    {
        if (name != "")
        {
            std::cout << name << " :";
        }

        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            data[i].display();
        }
    }

    // overload for std::cout
    // output the double value in matrix form if it is a matrix
    friend std::ostream &operator<<(std::ostream &os, const Qu_s &val)
    {
        // 保存原始格式状态
        std::ios_base::fmtflags original_flags = os.flags();
        std::streamsize original_precision = os.precision();

        // 遍历以找出最大数字，以便设置输出宽度
        int max_width = 0;
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(4) << val.data[i].toDouble();

            max_width = std::max(max_width, static_cast<int>(ss.str().size()));
        }

        // 设置固定小数点表示法和小数点后两位
        os << std::fixed << std::setprecision(4);

        os << "[";
        if constexpr (dim<dims...>::dimSize == 2)
        {
            size_t row = dim<dims...>::template dimAt<0>;
            size_t col = dim<dims...>::template dimAt<1>;

            for (size_t i = 0; i < row; i++)
            {
                if (i != 0)
                {
                    os << ' ';
                }
                for (size_t j = 0; j < col; j++)
                {
                    os << std::setw(max_width) << std::right << val[i, j].toDouble();

                    if (j != col - 1)
                    {
                        os << ", ";
                    }
                }

                if (i != row - 1)
                {
                    os << std::endl;
                }
            }
        }
        else
        {
            for (size_t i = 0; i < dim<dims...>::elemSize; i++)
            {
                os << val[i];
                if (i != dim<dims...>::elemSize - 1)
                {
                    os << ", ";
                }
            }
        }
        os << "]";

        // 恢复原始格式状态
        os.flags(original_flags);
        os.precision(original_precision);

        return os;
    }

    void toMatlab(std::string filename)
    {
        // 如果没有带后缀，自动加上.txt
        if (filename.find('.') == std::string::npos)
        {
            filename += ".txt";
        }

        std::ofstream file(filename);

        // output to file in the matlab format
        file << "[";
        if constexpr (dim<dims...>::dimSize == 2)
        {
            size_t row = dim<dims...>::template dimAt<0>;
            size_t col = dim<dims...>::template dimAt<1>;

            for (size_t i = 0; i < row; i++)
            {
                if (i != 0)
                {
                    file << ' ';
                }
                for (size_t j = 0; j < col; j++)
                {
                    file << this->operator[](i, j).toDouble();

                    if (j != col - 1)
                    {
                        file << ", ";
                    }
                    else
                    {
                        file << ";";
                    }
                }

                if (i != row - 1)
                {
                    file << std::endl;
                }
            }
        }
        else
        {
            for (size_t i = 0; i < dim<dims...>::elemSize; i++)
            {
                file << data[i].toDouble();
                if (i != dim<dims...>::elemSize - 1)
                {
                    file << ", ";
                }
            }
        }
        file << "]";
        file.close();
    }
};

template <typename... Args, size_t... dims>
struct QuInputHelper<dim<dims...>, Args...>
{
    using type = Qu_s<dim<dims...>, Qu<Args...>>;
};

template <typename... Args, size_t... dims>
struct QuInputHelper<dim<dims...>, TypeList<Args...>>
{
    using type = Qu_s<dim<dims...>, TypeList<Args...>>;
};

// ------------------- Basic Operations -------------------
struct FullPrec;

template <typename... Args>
struct MergerArgsWrapper_s
{
    using type = TypeList<Args...>;
};

template <typename... Args>
struct MergerArgsWrapper_s<TypeList<Args...>>
{
    using type = TypeList<>;
};

template <typename... Args>
struct MergerArgsWrapper_s<MergerArgsWrapper_s<Args...>> : MergerArgsWrapper_s<Args...>
{};

template <int intB, int fracB, bool isS, typename QuM, typename OfM>
struct MergerArgsWrapper_s<Qu_s<intBits<intB>, fracBits<fracB>, isSigned<isS>, QuMode<QuM>, OfMode<OfM>>> : MergerArgsWrapper_s<intBits<intB>, fracBits<fracB>, isSigned<isS>, QuMode<QuM>, OfMode<OfM>>
{};

template <typename... Args>
using MergerArgsWrapper = typename MergerArgsWrapper_s<Args...>::type;

template <typename... Args>
struct MulMerger;

template <typename... toArgs, int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2>
struct MulMerger<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, TypeList<toArgs...>>
{
    static inline constexpr bool fullPrecision = (std::is_same_v<FullPrec, toArgs> || ...);
    using fromQuMode = std::conditional_t<std::is_same_v<fromQuMode1, fromQuMode2>, fromQuMode1, defaultQuMode>;
    using fromOfMode = std::conditional_t<std::is_same_v<fromOfMode1, fromOfMode2>, fromOfMode1, defaultOfMode>;

    static inline constexpr auto toInt = tagExtractor<intBits<fullPrecision ? fromInt1 + fromInt2 : std::max(fromInt1, fromInt2)>, toArgs...>::value;
    static inline constexpr auto toFrac = tagExtractor<fracBits<fullPrecision ? fromFrac1 + fromFrac2 : std::max(fromFrac1, fromFrac2)>, toArgs...>::value;
    static inline constexpr auto toIsSigned = tagExtractor<isSigned<fromIsSigned1 || fromIsSigned2>, toArgs...>::value;
    using toQuMode = tagExtractor<QuMode<fromQuMode>, toArgs...>::type;
    using toOfMode = tagExtractor<OfMode<fromOfMode>, toArgs...>::type;

    // process toInt and toFrac when toInt + toFrac > 31
    static inline constexpr auto toIntFinal = toInt + toFrac > 31 ? toInt - (toInt + toFrac - 31 + 1) / 2 : toInt;
    static inline constexpr auto toFracFinal = toFrac + toInt > 31 ? toFrac - (toInt + toFrac - 31 + 1) / 2 : toFrac;

    using resType = Qu_s<intBits<toIntFinal>, fracBits<toFracFinal>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>>;
};

template <typename... Args>
struct AddMerger;
template <typename... toArgs, int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2>
struct AddMerger<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, TypeList<toArgs...>>
{
    static inline constexpr bool fullPrecision = (std::is_same_v<FullPrec, toArgs> || ...);

    using fromQuMode = std::conditional_t<std::is_same_v<fromQuMode1, fromQuMode2>, fromQuMode1, defaultQuMode>;
    using fromOfMode = std::conditional_t<std::is_same_v<fromOfMode1, fromOfMode2>, fromOfMode1, defaultOfMode>;

    static inline constexpr auto toInt = tagExtractor<intBits<fullPrecision ? std::max(fromInt1, fromInt2) + 1 : std::max(fromInt1, fromInt2)>, toArgs...>::value;
    static inline constexpr auto toFrac = tagExtractor<fracBits<std::max(fromFrac1, fromFrac2)>, toArgs...>::value;
    static inline constexpr auto toIsSigned = tagExtractor<isSigned<fromIsSigned1 || fromIsSigned2>, toArgs...>::value;
    using toQuMode = tagExtractor<QuMode<fromQuMode>, toArgs...>::type;
    using toOfMode = tagExtractor<OfMode<fromOfMode>, toArgs...>::type;

    // process toInt and toFrac when toInt + toFrac > 31
    static inline constexpr auto toIntFinal = toInt + toFrac > 31 ? toInt - (toInt + toFrac - 31 + 1) / 2 : toInt;
    static inline constexpr auto toFracFinal = toFrac + toInt > 31 ? toFrac - (toInt + toFrac - 31 + 1) / 2 : toFrac;

    using resType = Qu_s<intBits<toIntFinal>, fracBits<toFracFinal>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>>;
};

template <typename... Args>
struct Qmul_s;

// specialization for both inputs being static Qu_s
template <typename... toArgs, int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2>
struct Qmul_s<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, TypeList<toArgs...>>
{

    using merger = MulMerger<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, TypeList<toArgs...>>;

    inline static constexpr auto mul(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> f2)
    {

        auto fullProduct = static_cast<long long int>(f1.data) * static_cast<long long int>(f2.data);
        auto fracProduct = fracConvert<fromFrac1 + fromFrac2, merger::toFrac, QuMode<typename merger::toQuMode>>::convert(fullProduct);
        auto intProduct = intConvert<merger::toInt, merger::toFrac, merger::toIsSigned, OfMode<typename merger::toOfMode>>::convert(fracProduct);

        return Qu_s<intBits<merger::toInt>, fracBits<merger::toFrac>, isSigned<merger::toIsSigned>, QuMode<typename merger::toQuMode>, OfMode<typename merger::toOfMode>>(intProduct, DirectAssignTag());
    }
};

// specialization for any input being QuDynamic
template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
    requires std::is_same_v<Qu_s<fromArgs1...>, Qu_s<QuDynamic>> || std::is_same_v<Qu_s<fromArgs2...>, Qu_s<QuDynamic>>
struct Qmul_s<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, TypeList<toArgs...>>
{
    inline static constexpr bool hasIntBits = (isA<intBits<0>, toArgs> || ...);
    inline static constexpr bool hasFracBits = (isA<fracBits<0>, toArgs> || ...);
    inline static constexpr bool hasIsSigned = (isA<isSigned<0>, toArgs> || ...);
    inline static constexpr bool hasQuMode = (isA<QuMode<defaultQuMode>, toArgs> || ...);
    inline static constexpr bool hasOfMode = (isA<OfMode<defaultOfMode>, toArgs> || ...);

    inline static constexpr auto toArgInt = tagExtractor<intBits<defaultIntBits>, toArgs...>::value;
    inline static constexpr auto toArgFrac = tagExtractor<fracBits<defaultFracBits>, toArgs...>::value;
    inline static constexpr auto toArgIsSigned = tagExtractor<isSigned<defaultIsSigned>, toArgs...>::value;
    inline static constexpr auto toArgQuMode = tagExtractor<QuMode<defaultQuMode>, toArgs...>::type::value;
    inline static constexpr auto toArgOfMode = tagExtractor<OfMode<defaultOfMode>, toArgs...>::type::value;

    static inline constexpr bool fullPrecision = (isA<FullPrec, toArgs> || ...);
    inline static auto mul(const Qu_s<fromArgs1...> f1, const Qu_s<fromArgs2...> f2)
    {

        int fromInt1 = f1.intB;
        int fromFrac1 = f1.fracB;
        bool fromIsSigned1 = f1.isS;
        int fromQuMode1 = f1.QuM;
        int fromOfMode1 = f1.OfM;

        int fromInt2 = f2.intB;
        int fromFrac2 = f2.fracB;
        bool fromIsSigned2 = f2.isS;
        int fromQuMode2 = f2.QuM;
        int fromOfMode2 = f2.OfM;

        int toInt = hasIntBits ? toArgInt : (fullPrecision ? fromInt1 + fromInt2 : std::max(fromInt1, fromInt2));
        int toFrac = hasFracBits ? toArgFrac : (fullPrecision ? fromFrac1 + fromFrac2 : std::max(fromFrac1, fromFrac2));
        bool toIsSigned = hasIsSigned ? toArgIsSigned : (fromIsSigned1 || fromIsSigned2);
        int toQuMode = hasQuMode ? toArgQuMode : fromQuMode1 == fromQuMode2 ? fromQuMode1
                                                                            : defaultQuMode::value;
        int toOfMode = hasOfMode ? toArgOfMode : fromOfMode1 == fromOfMode2 ? fromOfMode1
                                                                            : defaultOfMode::value;

        // process toInt and toFrac when toInt + toFrac > 31
        auto toIntFinal = toInt + toFrac > 31 ? toInt - (toInt + toFrac - 31 + 1) / 2 : toInt;
        auto toFracFinal = toFrac + toInt > 31 ? toFrac - (toInt + toFrac - 31 + 1) / 2 : toFrac;

        Qu<QuDynamic> res;

        res.intB = toIntFinal;
        res.fracB = toFracFinal;
        res.isS = toIsSigned;
        res.QuM = toQuMode;
        res.OfM = toOfMode;

        auto fullProduct = static_cast<long long int>(f1.data) * static_cast<long long int>(f2.data);
        auto fracProduct = fracConvertDynamic(fullProduct, fromFrac1 + fromFrac2, toFracFinal, toQuMode);
        res.data = intConvertDynamic(fracProduct, toIntFinal, toFracFinal, toIsSigned, toOfMode);

        return res;
    }
};

template <typename... Args>
struct Qadd_s;

// specialization for both inputs being static Qu_s
template <typename... toArgs, int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2>
struct Qadd_s<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, TypeList<toArgs...>>
{
    using merger = AddMerger<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, TypeList<toArgs...>>;

    static inline constexpr int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
    static inline constexpr int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;

    inline static constexpr auto add(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> f2)
    {
        // print the requesting Quantization parameters for debugging
        // std::cout << "add: " << merger::toInt << " " << merger::toFrac << " " << std::endl;

        auto fullSum = static_cast<long long int>(f1.data << shiftA) + static_cast<long long int>(f2.data << shiftB);
        auto fracSum = fracConvert<std::max(fromFrac1, fromFrac2), merger::toFrac, QuMode<typename merger::toQuMode>>::convert(fullSum);
        auto intSum = intConvert<merger::toInt, merger::toFrac, merger::toIsSigned, OfMode<typename merger::toOfMode>>::convert(fracSum);

        return Qu_s<intBits<merger::toInt>, fracBits<merger::toFrac>, isSigned<merger::toIsSigned>, QuMode<typename merger::toQuMode>, OfMode<typename merger::toOfMode>>(intSum, DirectAssignTag());
    }
};

// specialization for any input being QuDynamic
template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
    requires std::is_same_v<Qu_s<fromArgs1...>, Qu_s<QuDynamic>> || std::is_same_v<Qu_s<fromArgs2...>, Qu_s<QuDynamic>>
struct Qadd_s<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, TypeList<toArgs...>>
{
    inline static constexpr bool hasIntBits = (isA<intBits<0>, toArgs> || ...);
    inline static constexpr bool hasFracBits = (isA<fracBits<0>, toArgs> || ...);
    inline static constexpr bool hasIsSigned = (isA<isSigned<0>, toArgs> || ...);
    inline static constexpr bool hasQuMode = (isA<QuMode<defaultQuMode>, toArgs> || ...);
    inline static constexpr bool hasOfMode = (isA<OfMode<defaultOfMode>, toArgs> || ...);

    inline static constexpr auto toArgInt = tagExtractor<intBits<defaultIntBits>, toArgs...>::value;
    inline static constexpr auto toArgFrac = tagExtractor<fracBits<defaultFracBits>, toArgs...>::value;
    inline static constexpr auto toArgIsSigned = tagExtractor<isSigned<defaultIsSigned>, toArgs...>::value;
    inline static constexpr auto toArgQuMode = tagExtractor<QuMode<defaultQuMode>, toArgs...>::type::value;
    inline static constexpr auto toArgOfMode = tagExtractor<OfMode<defaultOfMode>, toArgs...>::type::value;

    static inline constexpr bool fullPrecision = (isA<FullPrec, toArgs> || ...);
    inline static auto add(const Qu_s<fromArgs1...> f1, const Qu_s<fromArgs2...> f2)
    {

        int fromInt1 = f1.intB;
        int fromFrac1 = f1.fracB;
        bool fromIsSigned1 = f1.isS;
        int fromQuMode1 = f1.QuM;
        int fromOfMode1 = f1.OfM;

        int fromInt2 = f2.intB;
        int fromFrac2 = f2.fracB;
        bool fromIsSigned2 = f2.isS;
        int fromQuMode2 = f2.QuM;
        int fromOfMode2 = f2.OfM;

        int toInt = hasIntBits ? toArgInt : (fullPrecision ? std::max(fromInt1, fromInt2) + 1 : std::max(fromInt1, fromInt2));
        int toFrac = hasFracBits ? toArgFrac : std::max(fromFrac1, fromFrac2);
        bool toIsSigned = hasIsSigned ? toArgIsSigned : (fromIsSigned1 || fromIsSigned2);
        int toQuMode = hasQuMode ? toArgQuMode : fromQuMode1 == fromQuMode2 ? fromQuMode1
                                                                            : defaultQuMode::value;
        int toOfMode = hasOfMode ? toArgOfMode : fromOfMode1 == fromOfMode2 ? fromOfMode1
                                                                            : defaultOfMode::value;

        // process toInt and toFrac when toInt + toFrac > 31
        auto toIntFinal = toInt + toFrac > 31 ? toInt - (toInt + toFrac - 31 + 1) / 2 : toInt;
        auto toFracFinal = toFrac + toInt > 31 ? toFrac - (toInt + toFrac - 31 + 1) / 2 : toFrac;

        Qu<QuDynamic> res;

        res.intB = toIntFinal;
        res.fracB = toFracFinal;
        res.isS = toIsSigned;
        res.QuM = toQuMode;
        res.OfM = toOfMode;

        int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
        int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;

        auto fullSum = static_cast<long long int>(f1.data << shiftA) + static_cast<long long int>(f2.data << shiftB);
        auto fracSum = fracConvertDynamic(fullSum, std::max(fromFrac1, fromFrac2), toFracFinal, toQuMode);
        res.data = intConvertDynamic(fracSum, toIntFinal, toFracFinal, toIsSigned, toOfMode);

        return res;
    }
};

template <typename... Args>
struct Qsub_s;

// specialization for both inputs being static Qu_s
template <typename... toArgs, int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2>
    requires(!isA<typename TypeList<toArgs...>::head, Qu_s<>>)
struct Qsub_s<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, TypeList<toArgs...>>
{
    using merger = AddMerger<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, TypeList<toArgs...>>;

    static inline constexpr int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
    static inline constexpr int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;

    inline static constexpr auto sub(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> f2)
    {
        // // print the requesting Quantization parameters for debugging
        // std::cout << "sub: " << merger::toInt << " " << merger::toFrac << " " << std::endl;

        auto fullDiff = static_cast<long long int>(f1.data << shiftA) - static_cast<long long int>(f2.data << shiftB);
        auto fracDiff = fracConvert<std::max(fromFrac1, fromFrac2), merger::toFrac, QuMode<typename merger::toQuMode>>::convert(fullDiff);
        auto intDiff = intConvert<merger::toInt, merger::toFrac, merger::toIsSigned, OfMode<typename merger::toOfMode>>::convert(fracDiff);

        return Qu_s<intBits<merger::toInt>, fracBits<merger::toFrac>, isSigned<merger::toIsSigned>, QuMode<typename merger::toQuMode>, OfMode<typename merger::toOfMode>>(intDiff, DirectAssignTag());
    }
};

// specialization for any input being QuDynamic
template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
    requires std::is_same_v<Qu_s<fromArgs1...>, Qu_s<QuDynamic>> || std::is_same_v<Qu_s<fromArgs2...>, Qu_s<QuDynamic>>
struct Qsub_s<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, TypeList<toArgs...>>
{
    inline static constexpr bool hasIntBits = (isA<intBits<0>, toArgs> || ...);
    inline static constexpr bool hasFracBits = (isA<fracBits<0>, toArgs> || ...);
    inline static constexpr bool hasIsSigned = (isA<isSigned<0>, toArgs> || ...);
    inline static constexpr bool hasQuMode = (isA<QuMode<defaultQuMode>, toArgs> || ...);
    inline static constexpr bool hasOfMode = (isA<OfMode<defaultOfMode>, toArgs> || ...);

    inline static constexpr auto toArgInt = tagExtractor<intBits<defaultIntBits>, toArgs...>::value;
    inline static constexpr auto toArgFrac = tagExtractor<fracBits<defaultFracBits>, toArgs...>::value;
    inline static constexpr auto toArgIsSigned = tagExtractor<isSigned<defaultIsSigned>, toArgs...>::value;
    inline static constexpr auto toArgQuMode = tagExtractor<QuMode<defaultQuMode>, toArgs...>::type::value;
    inline static constexpr auto toArgOfMode = tagExtractor<OfMode<defaultOfMode>, toArgs...>::type::value;

    static inline constexpr bool fullPrecision = (isA<FullPrec, toArgs> || ...);
    inline static auto sub(const Qu_s<fromArgs1...> f1, const Qu_s<fromArgs2...> f2)
    {

        int fromInt1 = f1.intB;
        int fromFrac1 = f1.fracB;
        bool fromIsSigned1 = f1.isS;
        int fromQuMode1 = f1.QuM;
        int fromOfMode1 = f1.OfM;

        int fromInt2 = f2.intB;
        int fromFrac2 = f2.fracB;
        bool fromIsSigned2 = f2.isS;
        int fromQuMode2 = f2.QuM;
        int fromOfMode2 = f2.OfM;

        int toInt = hasIntBits ? toArgInt : (fullPrecision ? std::max(fromInt1, fromInt2) + 1 : std::max(fromInt1, fromInt2));
        int toFrac = hasFracBits ? toArgFrac : std::max(fromFrac1, fromFrac2);
        bool toIsSigned = hasIsSigned ? toArgIsSigned : (fromIsSigned1 || fromIsSigned2);
        int toQuMode = hasQuMode ? toArgQuMode : fromQuMode1 == fromQuMode2 ? fromQuMode1
                                                                            : defaultQuMode::value;
        int toOfMode = hasOfMode ? toArgOfMode : fromOfMode1 == fromOfMode2 ? fromOfMode1
                                                                            : defaultOfMode::value;

        // process toInt and toFrac when toInt + toFrac > 31
        auto toIntFinal = toInt + toFrac > 31 ? toInt - (toInt + toFrac - 31 + 1) / 2 : toInt;
        auto toFracFinal = toFrac + toInt > 31 ? toFrac - (toInt + toFrac - 31 + 1) / 2 : toFrac;

        Qu<QuDynamic> res;

        res.intB = toIntFinal;
        res.fracB = toFracFinal;
        res.isS = toIsSigned;
        res.QuM = toQuMode;
        res.OfM = toOfMode;

        int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
        int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;

        auto fullSum = static_cast<long long int>(f1.data << shiftA) - static_cast<long long int>(f2.data << shiftB);
        auto fracSum = fracConvertDynamic(fullSum, std::max(fromFrac1, fromFrac2), toFracFinal, toQuMode);
        res.data = intConvertDynamic(fracSum, toIntFinal, toFracFinal, toIsSigned, toOfMode);

        return res;
    }
};

template <typename... Args>
struct Qdiv_s;

// specialization for both inputs being static Qu_s
template <typename... toArgs, int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2>
    requires(!isA<typename TypeList<toArgs...>::head, Qu_s<>>)
struct Qdiv_s<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, TypeList<toArgs...>>
{
    using merger = AddMerger<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, TypeList<toArgs...>>;

    static inline constexpr int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
    static inline constexpr int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;

    inline static constexpr auto div(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> f2)
    {
        if (f2.data == 0)
        {
            return Qu_s<intBits<merger::toInt>, fracBits<merger::toFrac>, isSigned<merger::toIsSigned>, QuMode<typename merger::toQuMode>, OfMode<typename merger::toOfMode>>(0, DirectAssignTag());
        }

        auto fullQuotient = (static_cast<long long int>(f1.data) << shiftA << merger::toFrac) / (static_cast<long long int>(f2.data) << shiftB);
        auto intQuotient = intConvert<merger::toInt, merger::toFrac, merger::toIsSigned, OfMode<typename merger::toOfMode>>::convert(fullQuotient);

        return Qu_s<intBits<merger::toInt>, fracBits<merger::toFrac>, isSigned<merger::toIsSigned>, QuMode<typename merger::toQuMode>, OfMode<typename merger::toOfMode>>(intQuotient, DirectAssignTag());
    }
};

// specialization for any input being QuDynamic
template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
    requires std::is_same_v<Qu_s<fromArgs1...>, Qu_s<QuDynamic>> || std::is_same_v<Qu_s<fromArgs2...>, Qu_s<QuDynamic>>
struct Qdiv_s<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, TypeList<toArgs...>>
{
    inline static constexpr bool hasIntBits = (isA<intBits<0>, toArgs> || ...);
    inline static constexpr bool hasFracBits = (isA<fracBits<0>, toArgs> || ...);
    inline static constexpr bool hasIsSigned = (isA<isSigned<0>, toArgs> || ...);
    inline static constexpr bool hasQuMode = (isA<QuMode<defaultQuMode>, toArgs> || ...);
    inline static constexpr bool hasOfMode = (isA<OfMode<defaultOfMode>, toArgs> || ...);

    inline static constexpr auto toArgInt = tagExtractor<intBits<defaultIntBits>, toArgs...>::value;
    inline static constexpr auto toArgFrac = tagExtractor<fracBits<defaultFracBits>, toArgs...>::value;
    inline static constexpr auto toArgIsSigned = tagExtractor<isSigned<defaultIsSigned>, toArgs...>::value;
    inline static constexpr auto toArgQuMode = tagExtractor<QuMode<defaultQuMode>, toArgs...>::type::value;
    inline static constexpr auto toArgOfMode = tagExtractor<OfMode<defaultOfMode>, toArgs...>::type::value;

    static inline constexpr bool fullPrecision = (isA<FullPrec, toArgs> || ...);
    inline static auto div(const Qu_s<fromArgs1...> f1, const Qu_s<fromArgs2...> f2)
    {

        int fromInt1 = f1.intB;
        int fromFrac1 = f1.fracB;
        bool fromIsSigned1 = f1.isS;
        int fromQuMode1 = f1.QuM;
        int fromOfMode1 = f1.OfM;

        int fromInt2 = f2.intB;
        int fromFrac2 = f2.fracB;
        bool fromIsSigned2 = f2.isS;
        int fromQuMode2 = f2.QuM;
        int fromOfMode2 = f2.OfM;

        int toInt = hasIntBits ? toArgInt : (fullPrecision ? std::max(fromInt1, fromInt2) + 1 : std::max(fromInt1, fromInt2));
        int toFrac = hasFracBits ? toArgFrac : std::max(fromFrac1, fromFrac2);
        bool toIsSigned = hasIsSigned ? toArgIsSigned : (fromIsSigned1 || fromIsSigned2);
        int toQuMode = hasQuMode ? toArgQuMode : fromQuMode1 == fromQuMode2 ? fromQuMode1
                                                                            : defaultQuMode::value;
        int toOfMode = hasOfMode ? toArgOfMode : fromOfMode1 == fromOfMode2 ? fromOfMode1
                                                                            : defaultOfMode::value;

        // process toInt and toFrac when toInt + toFrac > 31
        auto toIntFinal = toInt + toFrac > 31 ? toInt - (toInt + toFrac - 31 + 1) / 2 : toInt;
        auto toFracFinal = toFrac + toInt > 31 ? toFrac - (toInt + toFrac - 31 + 1) / 2 : toFrac;

        Qu<QuDynamic> res;

        res.intB = toIntFinal;
        res.fracB = toFracFinal;
        res.isS = toIsSigned;
        res.QuM = toQuMode;
        res.OfM = toOfMode;

        int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
        int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;

        if (f2.data == 0)
        {
            res.data = 0;
            return res;
        }

        auto fullQuotient = (static_cast<long long int>(f1.data) << shiftA << toFracFinal) / (static_cast<long long int>(f2.data) << shiftB);
        auto intQuotient = intConvertDynamic(fullQuotient, toIntFinal, toFracFinal, toIsSigned, toOfMode);

        res.data = intQuotient;

        return res;
    }
};

// ------------------- Complex Operations -------------------
// Basic complex multiplication, realized as (a+bi)(c+di) = (ac-bd) + (ad+bc)i
template <typename... Args>
struct BasicComplexMul;

template <typename... Args>
struct MergerArgsWrapper_s<BasicComplexMul<Args...>>
{
    using type = BasicComplexMul<Args...>;
};

template <typename... Args>
struct acT;

template <typename... Args>
struct bdT;

template <typename... Args>
struct adT;

template <typename... Args>
struct bcT;

template <typename... Args>
struct acbdT;

template <typename... Args>
struct adbcT;

template <typename... Args>
struct MergerArgsWrapper_s<acT<Args...>> : MergerArgsWrapper_s<Args...>
{};

template <typename... Args>
struct MergerArgsWrapper_s<bdT<Args...>> : MergerArgsWrapper_s<Args...>
{};

template <typename... Args>
struct MergerArgsWrapper_s<adT<Args...>> : MergerArgsWrapper_s<Args...>
{};

template <typename... Args>
struct MergerArgsWrapper_s<bcT<Args...>> : MergerArgsWrapper_s<Args...>
{};

template <typename... Args>
struct MergerArgsWrapper_s<acbdT<Args...>> : MergerArgsWrapper_s<Args...>
{};

template <typename... Args>
struct MergerArgsWrapper_s<adbcT<Args...>> : MergerArgsWrapper_s<Args...>
{};

// used for Qmul(c1, c2) without any additional arguments
template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2>
struct Qmul_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TypeList<>> : Qmul_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, BasicComplexMul<>>
{};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct Qmul_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, BasicComplexMul<toArgs...>>
{
    using mulACType = tagExtractor<acT<>, toArgs...>::type;
    using mulBDType = tagExtractor<bdT<>, toArgs...>::type;
    using mulADType = tagExtractor<adT<>, toArgs...>::type;
    using mulBCType = tagExtractor<bcT<>, toArgs...>::type;

    using subACBDType = tagExtractor<acbdT<>, toArgs...>::type;
    using addADBCType = tagExtractor<adbcT<>, toArgs...>::type;

    inline static constexpr auto mul(const Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>> f1, const Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>> f2)
    {
        auto realPart = Qsub<subACBDType>(Qmul<mulACType>(f1.real, f2.real), Qmul<mulBDType>(f1.imag, f2.imag));
        auto imagPart = Qadd<addADBCType>(Qmul<mulADType>(f1.real, f2.imag), Qmul<mulBCType>(f1.imag, f2.real));

        // get the type of the real part and the imaginary part
        Qcomplex<decltype(realPart), decltype(imagPart)> res(realPart, imagPart);
        return res;
    }
};

// Complex multiplication via 3 multiplications and 5 additions
// x = a + bi, y = c + di
// A = (a + b)c, B = (c + d)b, C = (b − a)d
// xy = (A − B) + (B − C)i

template <typename... Args>
struct TFComplexMul;

template <typename... Args>
struct MergerArgsWrapper_s<TFComplexMul<Args...>>
{
    using type = TFComplexMul<Args...>;
};

template <typename... Args>
struct abT;

template <typename... Args>
struct cdT;

template <typename... Args>
struct baT;

template <typename... Args>
struct abcT;

template <typename... Args>
struct cdbT;

template <typename... Args>
struct badT;

template <typename... Args>
struct ABT;

template <typename... Args>
struct BCT;

template <typename... Args>
struct MergerArgsWrapper_s<abT<Args...>> : MergerArgsWrapper_s<Args...>
{};

template <typename... Args>
struct MergerArgsWrapper_s<cdT<Args...>> : MergerArgsWrapper_s<Args...>
{};

template <typename... Args>
struct MergerArgsWrapper_s<baT<Args...>> : MergerArgsWrapper_s<Args...>
{};

template <typename... Args>
struct MergerArgsWrapper_s<abcT<Args...>> : MergerArgsWrapper_s<Args...>
{};

template <typename... Args>
struct MergerArgsWrapper_s<cdbT<Args...>> : MergerArgsWrapper_s<Args...>
{};

template <typename... Args>
struct MergerArgsWrapper_s<badT<Args...>> : MergerArgsWrapper_s<Args...>
{};

template <typename... Args>
struct MergerArgsWrapper_s<ABT<Args...>> : MergerArgsWrapper_s<Args...>
{};

template <typename... Args>
struct MergerArgsWrapper_s<BCT<Args...>> : MergerArgsWrapper_s<Args...>
{};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct Qmul_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TFComplexMul<toArgs...>>
{
    using addabType = tagExtractor<abT<>, toArgs...>::type;
    using addcdType = tagExtractor<cdT<>, toArgs...>::type;
    using subbaType = tagExtractor<baT<>, toArgs...>::type;
    using mulabcType = tagExtractor<abcT<>, toArgs...>::type;
    using mulcdbType = tagExtractor<cdbT<>, toArgs...>::type;
    using mulbadType = tagExtractor<badT<>, toArgs...>::type;
    using subABType = tagExtractor<ABT<>, toArgs...>::type;
    using subBCType = tagExtractor<BCT<>, toArgs...>::type;

    inline static constexpr auto mul(const Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>> f1, const Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>> f2)
    {
        auto A = Qmul<mulabcType>(Qadd<addabType>(f1.real, f1.imag), f2.real);
        auto B = Qmul<mulbadType>(Qadd<addcdType>(f2.real, f2.imag), f1.imag);
        auto C = Qmul<mulcdbType>(Qsub<subbaType>(f1.imag, f1.real), f2.imag);

        auto realPart = Qsub<subABType>(A, B);
        auto imagPart = Qsub<subBCType>(B, C);

        // get the type of the real part and the imaginary part
        Qcomplex<decltype(realPart), decltype(imagPart)> res(realPart, imagPart);
        return res;
    }
};

template <typename... Args>
struct realT;

template <typename... Args>
struct imagT;

template <typename... Args>
struct MergerArgsWrapper_s<realT<Args...>> : MergerArgsWrapper_s<Args...>
{};

template <typename... Args>
struct MergerArgsWrapper_s<imagT<Args...>> : MergerArgsWrapper_s<Args...>
{};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct Qadd_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TypeList<toArgs...>>
{
    using realType = tagExtractor<realT<>, toArgs...>::type;
    using imagType = tagExtractor<imagT<>, toArgs...>::type;

    inline static constexpr auto add(const Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>> f1, const Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>> f2)
    {
        auto realPart = Qadd<realType>(f1.real, f2.real);
        auto imagPart = Qadd<imagType>(f1.imag, f2.imag);

        // get the type of the real part and the imaginary part
        Qcomplex<decltype(realPart), decltype(imagPart)> res(realPart, imagPart);
        return res;
    }
};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct Qsub_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TypeList<toArgs...>>
{
    using realType = tagExtractor<realT<>, toArgs...>::type;
    using imagType = tagExtractor<imagT<>, toArgs...>::type;

    inline static constexpr auto add(const Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>> f1, const Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>> f2)
    {
        auto realPart = Qsub<realType>(f1.real, f2.real);
        auto imagPart = Qsub<imagType>(f1.imag, f2.imag);

        // get the type of the real part and the imaginary part
        Qcomplex<decltype(realPart), decltype(imagPart)> res(realPart, imagPart);
        return res;
    }
};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct Qdiv_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, toArgs...>
{
    inline static constexpr auto div(const Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>> f1, const Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>> f2)
    {
        throw std::runtime_error("Complex division is not supported yet.");
    }
};

// ------------------- Real-Complex Operations -------------------

// Real-Complex multiplication
template <typename... realArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct Qmul_s<Qu_s<realArgs1...>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TypeList<toArgs...>>
{
    using realMulType = tagExtractor<realT<>, toArgs...>::type;
    using imagMulType = tagExtractor<imagT<>, toArgs...>::type;

    inline static constexpr auto mul(const Qu_s<realArgs1...> f1, const Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>> f2)
    {
        auto realPart = Qmul<realMulType>(f1, f2.real);
        auto imagPart = Qmul<imagMulType>(f1, f2.imag);

        // get the type of the real part and the imaginary part
        Qcomplex<decltype(realPart), decltype(imagPart)> res(realPart, imagPart);
        return res;
    }
};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... toArgs>
struct Qmul_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<realArgs2...>, TypeList<toArgs...>>
{
    using realMulType = tagExtractor<realT<>, toArgs...>::type;
    using imagMulType = tagExtractor<imagT<>, toArgs...>::type;

    inline static constexpr auto mul(const Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>> f1, const Qu_s<realArgs2...> f2)
    {
        auto realPart = Qmul<realMulType>(f1.real, f2);
        auto imagPart = Qmul<imagMulType>(f1.imag, f2);

        // get the type of the real part and the imaginary part
        Qcomplex<decltype(realPart), decltype(imagPart)> res(realPart, imagPart);
        return res;
    }
};

// Real-Complex addition
template <typename... realArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct Qadd_s<Qu_s<realArgs1...>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TypeList<toArgs...>>
{

    inline static constexpr auto add(const Qu_s<realArgs1...> f1, const Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>> f2)
    {
        auto realPart = Qadd<toArgs...>(f1, f2.real);
        auto imagPart = f2.imag;

        // get the type of the real part and the imaginary part
        Qcomplex<decltype(realPart), decltype(imagPart)> res(realPart, imagPart);

        return res;
    }
};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... toArgs>
struct Qadd_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<realArgs2...>, TypeList<toArgs...>>
{
    inline static constexpr auto add(const Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>> f1, const Qu_s<realArgs2...> f2)
    {
        auto realPart = Qadd<toArgs...>(f1.real, f2);
        auto imagPart = f1.imag;

        // get the type of the real part and the imaginary part
        Qcomplex<decltype(realPart), decltype(imagPart)> res(realPart, imagPart);

        return res;
    }
};

// Real-Complex subtraction
template <typename... realArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct Qsub_s<Qu_s<realArgs1...>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TypeList<toArgs...>>
{
    inline static constexpr auto sub(const Qu_s<realArgs1...> f1, const Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>> f2)
    {
        auto realPart = Qsub<toArgs...>(f1, f2.real);
        auto imagPart = Qsub<toArgs...>(Qu_s<realArgs1...>(0, DirectAssignTag()), f2.imag);

        // get the type of the real part and the imaginary part
        Qcomplex<decltype(realPart), decltype(imagPart)> res(realPart, imagPart);

        return res;
    }
};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... toArgs>
struct Qsub_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<realArgs2...>, TypeList<toArgs...>>
{
    inline static constexpr auto sub(const Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>> f1, const Qu_s<realArgs2...> f2)
    {
        auto realPart = Qsub<toArgs...>(f1.real, f2);
        auto imagPart = f1.imag;

        // get the type of the real part and the imaginary part
        Qcomplex<decltype(realPart), decltype(imagPart)> res(realPart, imagPart);

        return res;
    }
};

// Real-Complex division
template <typename... realArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct Qdiv_s<Qu_s<realArgs1...>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TypeList<toArgs...>>
{
    inline static constexpr auto div(const Qu_s<realArgs1...> f1, const Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>> f2)
    {
        throw std::runtime_error("Real-Complex division is not supported yet.");
    }
};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... toArgs>
struct Qdiv_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<realArgs2...>, TypeList<toArgs...>>
{
    using realDivType = tagExtractor<realT<>, toArgs...>::type;
    using imagDivType = tagExtractor<imagT<>, toArgs...>::type;

    inline static constexpr auto div(const Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>> f1, const Qu_s<realArgs2...> f2)
    {
        auto realPart = Qdiv<realDivType>(f1.real, f2);
        auto imagPart = Qdiv<imagDivType>(f1.imag, f2);

        // get the type of the real part and the imaginary part
        Qcomplex<decltype(realPart), decltype(imagPart)> res(realPart, imagPart);

        return res;
    }
};

// ------------------- Basic tensor operations -------------------

template <size_t... dims1, size_t... dims2, typename QuT1, typename QuT2, typename... toArgs>
struct Qmul_s<Qu_s<dim<dims1...>, QuT1>, Qu_s<dim<dims2...>, QuT2>, toArgs...>
{
    static_assert(std::is_same_v<dim<dims1...>, dim<dims2...>>, "Tensor dimensions must match for multiplication. Broadcasting is not supported yet.");

    inline static constexpr auto mul(const Qu_s<dim<dims1...>, QuT1> f1, const Qu_s<dim<dims2...>, QuT2> f2)
    {
        auto res = Qmul<toArgs...>(f1[0], f2[0]);
        Qu<dim<dims1...>, decltype(res)> result;
        result[0].assign(res);
        for (size_t i = 1; i < dim<dims1...>::elemSize; i++)
        {
            result[i].assign(Qmul<toArgs...>(f1[i], f2[i]));
        }
        return result;
    }
};

template <size_t... dims1, size_t... dims2, typename QuT1, typename QuT2, typename... toArgs>
struct Qadd_s<Qu_s<dim<dims1...>, QuT1>, Qu_s<dim<dims2...>, QuT2>, toArgs...>
{
    static_assert(std::is_same_v<dim<dims1...>, dim<dims2...>>, "Tensor dimensions must match for addition. Broadcasting is not supported yet.");

    inline static constexpr auto add(const Qu_s<dim<dims1...>, QuT1> f1, const Qu_s<dim<dims2...>, QuT2> f2)
    {
        auto res = Qadd<toArgs...>(f1[0], f2[0]);
        Qu<dim<dims1...>, decltype(res)> result;
        result[0].assign(res);
        for (size_t i = 1; i < dim<dims1...>::elemSize; i++)
        {
            result[i].assign(Qadd<toArgs...>(f1[i], f2[i]));
        }
        return result;
    }
};

template <size_t... dims1, size_t... dims2, typename QuT1, typename QuT2, typename... toArgs>
struct Qsub_s<Qu_s<dim<dims1...>, QuT1>, Qu_s<dim<dims2...>, QuT2>, toArgs...>
{
    static_assert(std::is_same_v<dim<dims1...>, dim<dims2...>>, "Tensor dimensions must match for subtraction. Broadcasting is not supported yet.");

    inline static constexpr auto sub(const Qu_s<dim<dims1...>, QuT1> f1, const Qu_s<dim<dims2...>, QuT2> f2)
    {
        auto res = Qsub<toArgs...>(f1[0], f2[0]);
        Qu<dim<dims1...>, decltype(res)> result;
        result[0].assign(res);
        for (size_t i = 1; i < dim<dims1...>::elemSize; i++)
        {
            result[i].assign(Qsub<toArgs...>(f1[i], f2[i]));
        }
        return result;
    }
};

template <size_t... dims1, size_t... dims2, typename QuT1, typename QuT2, typename... toArgs>
struct Qdiv_s<Qu_s<dim<dims1...>, QuT1>, Qu_s<dim<dims2...>, QuT2>, toArgs...>
{
    static_assert(std::is_same_v<dim<dims1...>, dim<dims2...>>, "Tensor dimensions must match for division. Broadcasting is not supported yet.");

    inline static constexpr auto div(const Qu_s<dim<dims1...>, QuT1> f1, const Qu_s<dim<dims2...>, QuT2> f2)
    {
        auto res = Qdiv<toArgs...>(f1[0], f2[0]);
        Qu<dim<dims1...>, decltype(res)> result;
        result[0].assign(res);
        for (size_t i = 1; i < dim<dims1...>::elemSize; i++)
        {
            result[i].assign(Qdiv<toArgs...>(f1[i], f2[i]));
        }
        return result;
    }
};

template <typename... toArgs, typename QuT1, typename QuT2>
inline constexpr auto Qmul(const QuT1 f1, const QuT2 f2)
{
    return Qmul_s<QuT1, QuT2, MergerArgsWrapper<toArgs...>>::mul(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2>
inline constexpr auto Qadd(const QuT1 f1, const QuT2 f2)
{
    return Qadd_s<QuT1, QuT2, MergerArgsWrapper<toArgs...>>::add(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2>
inline constexpr auto Qsub(const QuT1 f1, const QuT2 f2)
{
    return Qsub_s<QuT1, QuT2, MergerArgsWrapper<toArgs...>>::sub(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2>
inline constexpr auto Qdiv(const QuT1 f1, const QuT2 f2)
{
    return Qdiv_s<QuT1, QuT2, MergerArgsWrapper<toArgs...>>::div(f1, f2);
}

} // namespace QuBLAS