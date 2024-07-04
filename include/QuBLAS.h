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

namespace QuBLAS {

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
    inline static constexpr bool value = std::is_same_v<T1<>, T2<>>;
};

template <template <auto...> class T1, auto... Args1, template <auto...> class T2, auto... Args2>
struct isA_s<T1<Args1...>, T2<Args2...>>
{
    inline static constexpr bool value = std::is_same_v<T1<>, T2<>>;
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

    inline static constexpr int minVal = isS ? -((1 << (intBitsInput + fracBitsInput))) : 0;
    inline static constexpr int maxVal = (1 << (intBitsInput + fracBitsInput)) - 1;

    int data;

    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Qu_s(T val)
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
        std::cout << "intBits: " << intB << " fracBits: " << fracB << " isSigned: " << isS << " " << std::endl;
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

    template <int intBitsFrom, int fracBitsFrom, bool isSignedFrom, typename QuModeFrom, typename OfModeFrom>
    inline Qu_s(const Qu_s<intBits<intBitsFrom>, fracBits<fracBitsFrom>, isSigned<isSignedFrom>, QuMode<QuModeFrom>, OfMode<OfModeFrom>> &val)
    {
        data = intConvertDynamic(fracConvertDynamic(val.data, fracBitsFrom, fracB, QuModeFrom::value), intBitsFrom, fracB, isSignedFrom, OfModeFrom::value);
    }

    inline Qu_s(const Qu_s<QuDynamic> &val)
    {
        data = intConvertDynamic(fracConvertDynamic(val.data, val.fracB, fracB, val.QuM), val.intB, fracB, val.isS, val.OfM);
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
        std::cout << "intBits: " << intB << " fracBits: " << fracB << " isSigned: " << isS << " " << std::endl;
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

template <>
struct QuInputHelper<QuDynamic>
{
    using type = Qu_s<QuDynamic>;
};


// ------------------- Complex -------------------
template<typename...realArgs, typename...imagArgs>
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
    Qu_s(T1 a, T2 b) : real(a), imag(b) {}

    // use = a to initialize
    template <typename T>
    Qu_s(T a) : real(a), imag(0)
    {}

    template<typename fromRealType, typename fromImagType>
    Qu_s(const Qu_s<fromRealType, fromImagType> &val)  
    {
        real = val.real;
        imag = val.imag;
    }

    template <typename T>
    Qu_s(const std::complex<T> &val) : real(val.real()), imag(val.imag()) {}

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









} // namespace QuBLAS