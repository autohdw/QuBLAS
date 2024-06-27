#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <complex>
#include <cstddef>
#include <functional>
#include <iostream>
#include <numeric>
#include <random>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <cstring>

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
    struct POS_INF{};
    struct NEG_INF{};
    struct ZERO{};
    struct INF{};
    struct CONV{};
};

struct TRN
{
    struct TCPL{};
    struct SMGN{};
};
// clang-format on

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
    struct TCPL{};
    struct ZERO{};
    struct SMGN{};
    // clang-format on
};

struct WRP
{
    // clang-format off
    struct TCPL{};
    template<auto N>
    struct TCPL_SAT{};
    // clang-format on
};

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

// the base specialization that should not be used
template <typename... Args>
class Qu_s
{
    static_assert(sizeof...(Args) >= 0, "You shall not pass");
};

// the basic Qu type for a single fixed-point number
template <int intBitsInput, int fracBitsInput, bool isSignedInput, typename QuModeInput, typename OfModeInput>
    requires within<QuModeInput, RND::POS_INF, RND::NEG_INF, RND::ZERO, RND::INF, RND::CONV, TRN::TCPL, TRN::SMGN> && within<OfModeInput, SAT::TCPL, SAT::ZERO, SAT::SMGN, WRP::TCPL>
class Qu_s<intBits<intBitsInput>, fracBits<fracBitsInput>, isSigned<isSignedInput>, QuMode<QuModeInput>, OfMode<OfModeInput>>
{
public:
    static_assert(0 <= (intBitsInput + fracBitsInput) <= 31, " Illegal bit width");

    inline static constexpr int intB = intBitsInput;
    inline static constexpr int fracB = fracBitsInput;
    inline static constexpr bool isS = isSignedInput;
    using QuM = QuModeInput;
    using OfM = OfModeInput;

    inline static constexpr int minVal = isS ? -((1 << (intBitsInput + fracBitsInput))) : 0;
    inline static constexpr int maxVal = (1 << (intBitsInput + fracBitsInput)) - 1;

    int data;

    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr Qu_s(T val)
    {
        long long int longVal = shifter<fracB>::template input<T>(val);

        longVal = fracConvert<fracBitsInput, fracB, QuMode<QuM>>::convert(longVal);
        data = intConvert<intBitsInput, fracBitsInput, isSignedInput, OfMode<OfM>>::convert(longVal);
    }

    inline constexpr Qu_s() : data(0) {}
    inline constexpr Qu_s(auto val, DirectAssignTag) : data(val) {}

    template <int intBitsFrom, int fracBitsFrom, bool isSignedFrom, typename QuModeFrom, typename OfModeFrom>
    inline constexpr Qu_s(const Qu_s<intBits<intBitsFrom>, fracBits<fracBitsFrom>, isSigned<isSignedFrom>, QuMode<QuModeFrom>, OfMode<OfModeFrom>> &val)
    {
        if constexpr (intBitsFrom == intBitsInput && fracBitsFrom == fracBitsInput && isSignedFrom == isSignedInput)
        {
            data = val.data;
        }
        else
        {
            data = intConvert<intB, fracB, isS, OfMode<OfM>>::convert(fracConvert<fracBitsFrom, fracBitsInput, QuMode<QuM>>::convert(val.data));
        }
    }

    template <int intBitsFrom, int fracBitsFrom, bool isSignedFrom, typename QuModeFrom, typename OfModeFrom>
    inline constexpr Qu_s &operator=(const Qu_s<intBits<intBitsFrom>, fracBits<fracBitsFrom>, isSigned<isSignedFrom>, QuMode<QuModeFrom>, OfMode<OfModeFrom>> &val)
    {
        if constexpr (intBitsFrom == intBitsInput && fracBitsFrom == fracBitsInput && isSignedFrom == isSignedInput)
        {
            data = val.data;
        }
        else
        {
            data = intConvert<intB, fracB, isS, OfMode<OfM>>::convert(fracConvert<fracBitsFrom, fracBitsInput, QuMode<QuM>>::convert(val.data));
        }
        return *this;
    }

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

        static constexpr auto mask = ~((1u << 31u) - 1u - ((1u << (intBitsInput + fracBitsInput)) - 1u));
        this->data = fillVal > 0 ? fillVal & mask : fillVal | ~mask;
        return *this;
    }

    inline auto fill(std::normal_distribution<double> dis)
    {
        double fillVal = dis(gen);
        long long int longVal = shifter<fracB>::template input<double>(fillVal);

        longVal = fracConvert<fracBitsInput, fracB, QuMode<QuM>>::convert(longVal);
        data = intConvert<intBitsInput, fracBitsInput, isSignedInput, OfMode<OfM>>::convert(longVal);
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

// ------------------- Complex -------------------

template <int realIntBitsInput, int realFracBitsInput, bool realIsSignedInput, typename realQuModeInput, typename realOfModeInput, int imagIntBitsInput, int imagFracBitsInput, bool imagIsSignedInput, typename imagQuModeInput, typename imagOfModeInput>
class Qu_s<Qu_s<intBits<realIntBitsInput>, fracBits<realFracBitsInput>, isSigned<realIsSignedInput>, QuMode<realQuModeInput>, OfMode<realOfModeInput>>, Qu_s<intBits<imagIntBitsInput>, fracBits<imagFracBitsInput>, isSigned<imagIsSignedInput>, QuMode<imagQuModeInput>, OfMode<imagOfModeInput>>>
{
public:
    using realType = Qu_s<intBits<realIntBitsInput>, fracBits<realFracBitsInput>, isSigned<realIsSignedInput>, QuMode<realQuModeInput>, OfMode<realOfModeInput>>;
    using imagType = Qu_s<intBits<imagIntBitsInput>, fracBits<imagFracBitsInput>, isSigned<imagIsSignedInput>, QuMode<imagQuModeInput>, OfMode<imagOfModeInput>>;
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

    // use = Qu_s<realType, imagType> to initialize
    template <typename... realArgs, typename... imagArgs>
    Qu_s(const Qu_s<Qu_s<realArgs...>, Qu_s<imagArgs...>> val) : real(val.real), imag(val.imag) {}

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

// ------------------- Vector and Matrix -------------------

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
    requires(isA<Arg, TypeList<>> || isA<Arg, Qu_s<>>)
class Qu_s<dim<dims...>, Arg>
{
public:
    static inline constexpr bool isElementQu = isA<Arg, TypeList<>>;

    using arrayType = std::conditional_t<isElementQu, typename toTuple<Arg>::type, std::array<Arg, dim<dims...>::elemSize>>;

    arrayType data;

    using innerType = Arg;

    inline static constexpr size_t size = dim<dims...>::elemSize;

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
        if constexpr (!isElementQu)
        {
            for (size_t i = 0; i < dim<dims...>::elemSize; i++)
            {
                data[i] = val[i];
            }
        }
        else
        {
            [this, &val]<size_t... index>(std::index_sequence<index...>) {
                ((std::get<index>(data) = val[index]), ...);
            }(std::make_index_sequence<dim<dims...>::elemSize>());
        }
    }

    // 拷贝构造函数
    constexpr Qu_s(const Qu_s<dim<dims...>, Arg> &val) : data(val.data) {}

    // 移动构造函数，来自同样模版参数的另一个Qu_s
    constexpr Qu_s(Qu_s<dim<dims...>, Arg> &&val) noexcept : data(std::move(val.data)) {}

    // 拷贝赋值运算符
    template <typename SquareBracketIndexableType>
        requires isSquareBracketIndexable<SquareBracketIndexableType>
    constexpr Qu_s &operator=(const SquareBracketIndexableType &val)
    {
        if constexpr (!isElementQu)
        {
            for (size_t i = 0; i < dim<dims...>::elemSize; i++)
            {
                data[i] = val[i];
            }
        }
        else
        {
            [this, &val]<size_t... index>(std::index_sequence<index...>) {
                ((std::get<index>(data) = val[index]), ...);
            }(std::make_index_sequence<dim<dims...>::elemSize>());
        }
        return *this;
    }

    // 移动赋值运算符
    constexpr Qu_s &operator=(Qu_s<dim<dims...>, Arg> &&val)
    {
        data = std::move(val.data);
        return *this;
    }

    inline void clear()
    {
        std::memset(data.data(), 0, dim<dims...>::elemSize * sizeof(Arg));
    }

    inline auto fill(auto... dis)
    {
        if constexpr (!isElementQu)
        {
            for (size_t i = 0; i < dim<dims...>::elemSize; i++)
            {
                data[i].fill(dis...);
            }
        }
        else
        {
            [this, &dis...]<size_t... index>(std::index_sequence<index...>) {
                ((std::get<index>(data).fill(dis...)), ...);
            }(std::make_index_sequence<dim<dims...>::elemSize>());
        }
        return *this;
    }

    inline auto shuffle()
    {
        if constexpr (!isElementQu)
        {
            std::shuffle(data.begin(), data.end(), gen);
        }
        else
        {
            throw std::runtime_error("Not implemented");
        }
        return *this;
    }

    template <size_t... index>
    inline constexpr auto &get()
    {
        if constexpr (isElementQu)
        {
            return std::get<dim<dims...>::template absoluteIndex_s<index...>::value>(data);
        }
        else
        {
            return data[dim<dims...>::template absoluteIndex_s<index...>::value];
        }
    }

    template <size_t... index>
    inline constexpr const auto &get() const
    {
        if constexpr (isElementQu)
        {
            return std::get<dim<dims...>::template absoluteIndex_s<index...>::value>(data);
        }
        else
        {
            return data[dim<dims...>::template absoluteIndex_s<index...>::value];
        }
    }

    template <typename... Ints>
        requires(sizeof...(Ints) == dim<dims...>::dimSize && (std::is_integral_v<Ints> && ...) && sizeof...(Ints) > 1)
    inline constexpr auto &operator[](Ints... indices)
    {
        if constexpr (isElementQu)
        {
            static_assert(!isElementQu, "Element-wise quantization does not support dynamic indexing");
            return std::get<0>(data);
        }
        else
        {
            size_t index = calculateIndex(0, indices...);
            return data[index];
        }
    }

    template <typename... Ints>
        requires(sizeof...(Ints) == dim<dims...>::dimSize && (std::is_integral_v<Ints> && ...) && sizeof...(Ints) > 1)
    inline constexpr const auto &operator[](Ints... indices) const
    {
        if constexpr (isElementQu)
        {
            static_assert(!isElementQu, "Element-wise quantization does not support dynamic indexing");
            return std::get<0>(data);
        }
        else
        {
            size_t index = calculateIndex(0, indices...);
            return data[index];
        }
    }

    inline constexpr auto &operator[](size_t index)
    {
        if constexpr (isElementQu)
        {
            static_assert(!isElementQu, "Element-wise quantization does not support dynamic indexing");
            return std::get<0>(data);
        }
        else
        {
            return data[index];
        }
    }

    inline constexpr const auto &operator[](size_t index) const
    {
        if constexpr (isElementQu)
        {
            static_assert(!isElementQu, "Element-wise quantization does not support dynamic indexing");
            return std::get<0>(data);
        }
        else
        {
            return data[index];
        }
    }

    inline std::array<double, dim<dims...>::elemSize> toDouble() const
    {
        std::array<double, dim<dims...>::elemSize> outputArray;
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            outputArray[i] = data[i].toDouble();
        }
        return outputArray;
    }

    template <size_t... index>
    inline void displayHelper(std::index_sequence<index...>) const
    {
        (std::get<index>(data).display(), ...);
    }

    void display(std::string name = "") const
    {
        if (name != "")
        {
            std::cout << name << " :";
        }
        std::cout << std::endl;

        if (!isElementQu)
        {
            for (size_t i = 0; i < dim<dims...>::elemSize; i++)
            {
                data[i].display();
            }
        }
        else
        {
            displayHelper(std::make_index_sequence<dim<dims...>::elemSize>());
        }
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

template <typename T>
struct isScalar_s;

template <int intBitsInput, int fracBitsInput, bool isSignedInput, typename QuModeInput, typename OfModeInput>
struct isScalar_s<Qu_s<intBits<intBitsInput>, fracBits<fracBitsInput>, isSigned<isSignedInput>, QuMode<QuModeInput>, OfMode<OfModeInput>>>
{
    static inline constexpr bool value = true;
};

template <typename... realArgs, typename... imagArgs>
struct isScalar_s<Qu_s<Qu_s<realArgs...>, Qu_s<imagArgs...>>>
{
    static inline constexpr bool value = true;
};

template <size_t... dims, typename Arg>
struct isScalar_s<Qu_s<dim<dims...>, Arg>>
{
    static inline constexpr bool value = false;
};

template <typename T>
inline constexpr bool isScalar = isScalar_s<T>::value;

// isQu
template <typename... Args>
struct isQu_s
{
    inline static constexpr bool value = false;
};

template <typename... Args>
struct isQu_s<Qu_s<Args...>>
{
    inline static constexpr bool value = true;
};

template <typename... Args>
inline constexpr bool isQu = isQu_s<Args...>::value;

// special case for gram matrix
// 面包会有的，牛奶也会有的
template <typename... Args>
struct Gram;

template <typename diagType, typename offDiagType>
    requires(isA<diagType, Qu_s<>> && isA<offDiagType, Qu_s<>>)
struct Gram<diagType, offDiagType>
{};

template <size_t row, size_t col, typename diagType, typename offDiagType>
class Qu_s<dim<row, col>, Gram<diagType, offDiagType>>
{
public:
    static inline constexpr bool isElementQu = true;

    std::array<offDiagType, row * col> offDiagData;
    std::array<diagType, row> diagData;

    constexpr Qu_s() {}

    template <size_t i, size_t j>
    inline constexpr auto &get()
    {
        if constexpr (i == j)
        {
            return diagData[i];
        }
        else
        {
            return offDiagData[i * col + j];
        }
    }

    template <size_t i, size_t j>
    inline constexpr const auto &get() const
    {
        if constexpr (i == j)
        {
            return diagData[i];
        }
        else
        {
            return offDiagData[i * col + j];
        }
    }

    inline std::array<double, row * col> toDouble() const
    {
        std::array<double, row * col> outputArray;

        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                if (i != j)
                {
                    outputArray[i * col + j] = offDiagData[i * col + j].toDouble();
                }
                else
                {
                    outputArray[i * col + j] = diagData[i].toDouble();
                }
            }
        }
        return outputArray;
    }

    void display(std::string name = "") const
    {
        if (name != "")
        {
            std::cout << name << " :";
        }
        std::cout << std::endl;

        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                if (i != j)
                {
                    offDiagData[i * col + j].display();
                }
                else
                {
                    diagData[i].display();
                }
            }
        }
    }
};

template <size_t row, size_t col, typename diagType, typename offDiagType>
struct QuInputHelper<dim<row, col>, Gram<diagType, offDiagType>>
{
    using type = Qu_s<dim<row, col>, Gram<diagType, offDiagType>>;
};

// ------------------- Basic tensor operations -------------------

// BitStream converter
struct l2r
{};

template <size_t... in>
    requires(sizeof...(in) <= 1)
struct r2l;

template <size_t in>
struct r2l<in>
{
    static inline constexpr size_t index = in;
};

template <>
struct r2l<> : r2l<1>
{};

// handle string to string
template <typename... Args>
struct SingleString_s;

template <>
struct SingleString_s<l2r>
{
    inline static constexpr auto convert(std::string_view str)
    {
        return std::string(str);
    }

    // from function, currently indentical to convert
    inline static constexpr auto from(std::string_view str)
    {
        return convert(str);
    }

    // to function, currently indentical to convert
    inline static constexpr auto to(std::string_view str)
    {
        return convert(str);
    }
};

template <size_t... in>
struct SingleString_s<r2l<in...>>
{
    inline static constexpr auto index = r2l<in...>::index;

    inline static constexpr auto convert(std::string_view str)
    {
        if (str.size() % index != 0)
        {
            throw std::runtime_error("Invalid string length: Must be a multiple of " + std::to_string(index));
        }

        std::string res;
        res.reserve(str.size());

        // Reverse chunks of size Index directly
        for (size_t i = str.size(); i >= index; i -= index)
        {
            res.append(str.data() + i - index, index);
        }

        return res;
    }

    // from function, currently indentical to convert
    inline static constexpr auto from(std::string_view str)
    {
        return convert(str);
    }

    // to function, currently indentical to convert
    inline static constexpr auto to(std::string_view str)
    {
        return convert(str);
    }
};

template <typename... Args>
struct TensorString_s;

template <typename elemProcessT>
struct TensorString_s<l2r, elemProcessT>
{
    // convert to std::array<std::string, size> with element string stored in l2r
    // the input string is expected to be a single string containing all elements, each element has length of elemLength
    template <typename QuTensorT>
    inline static constexpr auto fromString(std::string_view str)
    {
        using QuT = typename QuTensorT::innerType;
        static constexpr auto elemLen = QuT::intB + QuT::fracB + QuT::isS;
        static constexpr auto size = QuTensorT::size;
        if (str.size() % elemLen != 0)
        {
            throw std::runtime_error("Invalid string length: Must be a multiple of " + std::to_string(elemLen));
        }

        std::array<std::string, size> res;
        for (size_t i = 0; i < res.size(); i++)
        {
            res[i] = SingleString_s<elemProcessT>::convert(str.substr(i * elemLen, elemLen));
        }

        return res;
    }

    template <size_t arrSize>
    inline static constexpr auto toString(std::array<std::string, arrSize> arr)
    {
        std::string res;
        res.reserve(arr.size() * arr[0].size());

        for (size_t i = 0; i < arr.size(); i++)
        {
            res.append(SingleString_s<elemProcessT>::to(arr[i]));
        }

        return res;
    }

    // from QuBLAS type to std::array<std::string, size>
    template <size_t... dims, typename QuT>
    inline static constexpr auto fromQu(const Qu_s<dim<dims...>, QuT> &tensor)
    {
        std::array<std::string, Qu_s<dim<dims...>, QuT>::size> res;

        for (size_t i = 0; i < Qu_s<dim<dims...>, QuT>::size; i++)
        {
            res[i] = SingleString_s<elemProcessT>::to(tensor[i].toString());
        }
        return res;
    }

    // from std::array<std::string, size> to QuBLAS type
    template <typename QuTensorT>
    inline static constexpr auto toQu(const std::array<std::string, QuTensorT::size> &arr)
    {
        QuTensorT res;

        for (size_t i = 0; i < QuTensorT::size; i++)
        {
            auto str = SingleString_s<elemProcessT>::from(arr[i]);
            // convert  binary stored in str to integer
            int decimal = std::stoi(str, 0, 2);
            res[i].fill(decimal);
        }
        return res;
    }
};

template <typename elemProcessT, size_t index>
struct TensorString_s<r2l<index>, elemProcessT>
{
    template <typename QuTensorT>
    inline static constexpr auto fromString(std::string_view str)
    {
        using QuT = typename QuTensorT::innerType;
        static constexpr auto elemLen = QuT::intB + QuT::fracB + QuT::isS;
        static constexpr auto size = QuTensorT::size;
        if (str.size() % elemLen != 0)
        {
            throw std::runtime_error("Invalid string length: Must be a multiple of " + std::to_string(elemLen));
        }

        std::array<std::string, size> res;

        // Reverse chunks of size Index directly
        size_t in = 0;
        for (size_t i = size; i > 0; i = i - index)
        {
            for (size_t j = 0; j < index; j++)
            {
                res[in] = SingleString_s<elemProcessT>::convert(str.substr((i + j - index) * elemLen, elemLen));
                in++;
            }
        }

        return res;
    }

    template <size_t arrSize>
    inline static constexpr auto toString(std::array<std::string, arrSize> arr)
    {
        std::string res;
        res.reserve(arr.size() * arr[0].size());

        // reverse the order of elements, with every Index elements as a chunk
        for (size_t i = arr.size(); i > 0; i = i - index)
        {
            for (size_t j = 0; j < index; j++)
            {
                res.append(SingleString_s<elemProcessT>::to(arr[i + j - index]));
            }
        }
        return res;
    }
};

// scalar
template <typename... Args>
struct BitStream_s;

template <typename... QuArgs, typename processT>
struct BitStream_s<Qu_s<QuArgs...>, processT>
{
    inline static auto convert(std::string_view str)
    {
        auto toStr = processT::from(str);
        int decimal = std::stoi(toStr.data(), 0, 2);
        Qu_s<QuArgs...> res;
        res.fill(decimal);
        return res;
    }
};

template <typename processT>
struct BitStream_s<processT>
{
    inline static auto convert(auto Qu)
    {
        return SingleString_s<processT>::to(Qu.toString());
    }
};

// tensor
template <typename QuT, size_t... dims, typename tensorProcessT, typename elemProcessT>
struct BitStream_s<Qu_s<dim<dims...>, QuT>, tensorProcessT, elemProcessT>
{
    inline static auto convert(std::string_view str)
    {
        // use TensorString_s
        auto arr = TensorString_s<tensorProcessT, elemProcessT>::template fromString<Qu_s<dim<dims...>, QuT>>(str);
        return TensorString_s<l2r, l2r>::template toQu<Qu_s<dim<dims...>, QuT>>(arr);
    }
};

template <typename tensorProcessT, typename elemProcessT>
struct BitStream_s<tensorProcessT, elemProcessT>
{
    template <typename... QuArgs>
    inline static auto convert(Qu_s<QuArgs...> Qu)
    {
        auto arr = TensorString_s<l2r, l2r>::template fromQu(Qu);
        return TensorString_s<tensorProcessT, elemProcessT>::template toString(arr);
    }
};

template <typename... Args>
inline auto BitStream(auto input)
{
    return BitStream_s<Args...>::convert(input);
}

// ------------------- element wise operations -------------------

// contain all the trash that is not supposed to be used
namespace elementWise {
template <size_t index, bool horOrVer>
struct vecExtractor
{

    template <typename... fromArgs, typename... toArgs, size_t col, size_t row>
    static inline void extract(const Qu_s<dim<row, col>, Qu_s<fromArgs...>> &input, Qu_s<dim<horOrVer ? col : row>, Qu_s<toArgs...>> &output)
    {
        extract_impl(input, output, std::make_index_sequence < horOrVer ? col : row > ());
    }

    template <typename... fromArgs, typename... toArgs, size_t... I, size_t col, size_t row>
    static inline void extract_impl(const Qu_s<dim<row, col>, Qu_s<fromArgs...>> &input, Qu_s<dim<horOrVer ? col : row>, Qu_s<toArgs...>> &output, std::index_sequence<I...>)
    {
        if constexpr (horOrVer)
        {
            ((output.template get<I>() = input.template get<index, I>()), ...);
        }
        else
        {
            ((output.template get<I>() = input.template get<I, index>()), ...);
        }
    }
};

template <size_t index, bool horOrVer, typename... fromArgs, typename... toArgs, size_t col, size_t row>
inline void vecExtract(const Qu_s<dim<row, col>, Qu_s<fromArgs...>> &input, Qu_s<dim<horOrVer ? col : row>, Qu_s<toArgs...>> &output)
{
    vecExtractor<index, horOrVer>::extract(input, output);
}

} // namespace elementWise

// ------------------- Basic Operations -------------------

struct FullPrec;

template <typename... Args>
struct MulMerger;

template <typename... toArgs, int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2>
struct MulMerger<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, toArgs...>
{
    static inline constexpr bool fullPrecision = (isA<FullPrec, toArgs> || ...);

    using fromQuMode = std::conditional_t<std::is_same_v<fromQuMode1, fromQuMode2>, fromQuMode1, defaultQuMode>;
    using fromOfMode = std::conditional_t<std::is_same_v<fromOfMode1, fromOfMode2>, fromOfMode1, defaultOfMode>;

    static inline constexpr auto toInt = tagExtractor<intBits<fullPrecision ? fromInt1 + fromInt2 : std::max(fromInt1, fromInt2)>, toArgs...>::value;
    static inline constexpr auto toFrac = tagExtractor<fracBits<fullPrecision ? fromFrac1 + fromFrac2 : std::max(fromFrac1, fromFrac2)>, toArgs...>::value;
    static inline constexpr auto toIsSigned = tagExtractor<isSigned<fromIsSigned1 || fromIsSigned2>, toArgs...>::value;
    using toQuMode = tagExtractor<QuMode<fromQuMode>, toArgs...>::type;
    using toOfMode = tagExtractor<OfMode<fromOfMode>, toArgs...>::type;

    using resType = Qu_s<intBits<toInt>, fracBits<toFrac>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>>;
};

// ugly, maybe optimize later
template <typename... Args>
struct MulMergerWraper;

template <typename QuT1, typename QuT2, template <typename...> typename wraper, typename... Args>
struct MulMergerWraper<QuT1, QuT2, wraper<Args...>>
{
    using type = MulMerger<QuT1, QuT2, Args...>;
};

template <typename QuT1, typename QuT2, template <typename...> typename wraper, typename... Args>
struct MulMergerWraper<QuT1, QuT2, wraper<Qu_s<Args...>>>
{
    using type = MulMerger<QuT1, QuT2, Args...>;
};

template <typename... Args>
struct AddMerger;
template <typename... toArgs, int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2>
struct AddMerger<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, toArgs...>
{
    static inline constexpr bool fullPrecision = (isA<FullPrec, toArgs> || ...);

    using fromQuMode = std::conditional_t<std::is_same_v<fromQuMode1, fromQuMode2>, fromQuMode1, defaultQuMode>;
    using fromOfMode = std::conditional_t<std::is_same_v<fromOfMode1, fromOfMode2>, fromOfMode1, defaultOfMode>;

    static inline constexpr auto toInt = tagExtractor<intBits<fullPrecision ? std::max(fromInt1, fromInt2) + 1 : std::max(fromInt1, fromInt2)>, toArgs...>::value;
    static inline constexpr auto toFrac = tagExtractor<fracBits<std::max(fromFrac1, fromFrac2)>, toArgs...>::value;
    static inline constexpr auto toIsSigned = tagExtractor<isSigned<fromIsSigned1 || fromIsSigned2>, toArgs...>::value;
    using toQuMode = tagExtractor<QuMode<fromQuMode>, toArgs...>::type;
    using toOfMode = tagExtractor<OfMode<fromOfMode>, toArgs...>::type;

    using resType = Qu_s<intBits<toInt>, fracBits<toFrac>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>>;
};

template <typename... Args>
struct AddMergerWraper;

template <typename QuT1, typename QuT2, template <typename...> typename wraper, typename... Args>
struct AddMergerWraper<QuT1, QuT2, wraper<Args...>>
{
    using type = AddMerger<QuT1, QuT2, Args...>;
};

template <typename QuT1, typename QuT2, template <typename...> typename wraper, typename... Args>
struct AddMergerWraper<QuT1, QuT2, wraper<Qu_s<Args...>>>
{
    using type = AddMerger<QuT1, QuT2, Args...>;
};

template <typename... Args>
struct Qmul_s;

template <typename... toArgs, int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2>
    requires(!isA<typename TypeList<toArgs...>::head, Qu_s<>>)
struct Qmul_s<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, toArgs...>
{

    using merger = MulMerger<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, toArgs...>;

    inline static constexpr auto mul(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> f2)
    {
        // print the requesting Quantization parameters for debugging
        // std::cout << "mul: " << merger::toInt << " " << merger::toFrac << " " << std::endl;

        auto fullProduct = static_cast<long long int>(f1.data) * static_cast<long long int>(f2.data);
        auto fracProduct = fracConvert<fromFrac1 + fromFrac2, merger::toFrac, QuMode<typename merger::toQuMode>>::convert(fullProduct);
        auto intProduct = intConvert<merger::toInt, merger::toFrac, merger::toIsSigned, OfMode<typename merger::toOfMode>>::convert(fracProduct);

        return Qu_s<intBits<merger::toInt>, fracBits<merger::toFrac>, isSigned<merger::toIsSigned>, QuMode<typename merger::toQuMode>, OfMode<typename merger::toOfMode>>(intProduct, DirectAssignTag());
    }
};

template <typename... fromArgs1, typename... fromArgs2, typename... toArgs>
struct Qmul_s<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, Qu_s<toArgs...>> : Qmul_s<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, toArgs...>
{
};

template <typename... Args>
struct Qadd_s;

template <typename... toArgs, int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2>
    requires(!isA<typename TypeList<toArgs...>::head, Qu_s<>>)
struct Qadd_s<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, toArgs...>
{
    using merger = AddMerger<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, toArgs...>;

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

template <typename... fromArgs1, typename... fromArgs2, typename... toArgs>
struct Qadd_s<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, Qu_s<toArgs...>> : Qadd_s<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, toArgs...>
{
};

template <typename... Args>
struct Qsub_s;

template <typename... toArgs, int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2>
    requires(!isA<typename TypeList<toArgs...>::head, Qu_s<>>)
struct Qsub_s<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, toArgs...>
{
    using merger = AddMerger<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, toArgs...>;

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

template <typename... fromArgs1, typename... fromArgs2, typename... toArgs>
struct Qsub_s<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, Qu_s<toArgs...>> : Qsub_s<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, toArgs...>
{
};

template <typename... Args>
struct Qdiv_s;

template <typename... toArgs, int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2>
    requires(!isA<typename TypeList<toArgs...>::head, Qu_s<>>)
struct Qdiv_s<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, toArgs...>
{
    using merger = AddMerger<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, toArgs...>;

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

template <typename... fromArgs1, typename... fromArgs2, typename... toArgs>
struct Qdiv_s<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, Qu_s<toArgs...>> : Qdiv_s<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, toArgs...>
{
};

template <typename... Args>
struct Qabs_s;

// currently toArgs is not used
template <typename... toArgs, int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode>
struct Qabs_s<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, toArgs...>
{
    inline static constexpr auto abs(const Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>> f1)
    {
        int absVal = std::abs(f1.data);
        return Qu_s<intBits<fromInt + 1>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>(absVal, DirectAssignTag());
    }
};

template <typename... Args>
struct Qneg_s;

// currently toArgs is not used
template <typename... toArgs, int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode>
struct Qneg_s<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, toArgs...>
{
    inline static constexpr auto neg(const Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>> f1)
    {
        return Qu_s<intBits<fromInt + 1>, fracBits<fromFrac>, isSigned<true>, QuMode<fromQuMode>, OfMode<fromOfMode>>(-f1.data, DirectAssignTag());
    }
};

template <typename... Args>
struct Qcmp_s;

template <int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2>
struct Qcmp_s<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>>
{
    static inline constexpr int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
    static inline constexpr int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;

    inline static constexpr auto cmp(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> f2)
    {
        return (f1.data << shiftA) <=> (f2.data << shiftB);
    }
};

template <typename... Args>
struct Qeq_s;

template <int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2>
struct Qeq_s<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>>
{
    static inline constexpr int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
    static inline constexpr int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;

    inline static constexpr bool eq(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> f2)
    {
        return (f1.data << shiftA) == (f2.data << shiftB);
    }
};

template <typename... Args>
struct Qneq_s;

template <int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2>
struct Qneq_s<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>>
{
    static inline constexpr int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
    static inline constexpr int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;

    inline static constexpr bool neq(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> f2)
    {
        return (f1.data << shiftA) != (f2.data << shiftB);
    }
};

template <typename... toArgs, typename QuT1, typename QuT2>
    requires(isScalar<QuT1> && isScalar<QuT2>)
inline constexpr auto Qmul(const QuT1 f1, const QuT2 f2)
{
    return Qmul_s<QuT1, QuT2, toArgs...>::mul(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2>
    requires(isScalar<QuT1> && isScalar<QuT2>)
inline constexpr auto Qadd(const QuT1 f1, const QuT2 f2)
{
    return Qadd_s<QuT1, QuT2, toArgs...>::add(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2>
    requires(isScalar<QuT1> && isScalar<QuT2>)
inline constexpr auto Qsub(const QuT1 f1, const QuT2 f2)
{
    return Qsub_s<QuT1, QuT2, toArgs...>::sub(f1, f2);
}

template <typename... toArgs, typename QuT>
    requires(isScalar<QuT>)
inline constexpr auto Qneg(const QuT f)
{
    return Qneg_s<QuT, toArgs...>::neg(f);
}

template <typename... toArgs, typename QuT1, typename QuT2>
    requires(isScalar<QuT1> && isScalar<QuT2>)
inline constexpr auto Qdiv(const QuT1 f1, const QuT2 f2)
{
    return Qdiv_s<QuT1, QuT2, toArgs...>::div(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2>
    requires(isScalar<QuT1> && isScalar<QuT2>)
inline constexpr auto Qcmp(const QuT1 f1, const QuT2 f2)
{
    return Qcmp_s<QuT1, QuT2>::cmp(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2>
    requires(isScalar<QuT1> && isScalar<QuT2>)
inline constexpr auto Qeq(const QuT1 f1, const QuT2 f2)
{
    return Qeq_s<QuT1, QuT2>::eq(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2>
    requires(isScalar<QuT1> && isScalar<QuT2>)
inline constexpr auto Qneq(const QuT1 f1, const QuT2 f2)
{
    return Qneq_s<QuT1, QuT2>::neq(f1, f2);
}

// ------------------- operator overloading -------------------
template <typename QuT1, typename QuT2>
inline constexpr auto operator*(const QuT1 f1, const QuT2 f2)
{
    return Qmul(f1, f2);
}

template <typename QuT1, typename QuT2>
inline constexpr auto operator+(const QuT1 f1, const QuT2 f2)
{
    return Qadd(f1, f2);
}

template <typename QuT1, typename QuT2>
inline constexpr auto operator-(const QuT1 f1, const QuT2 f2)
{
    return Qsub(f1, f2);
}

template <typename QuT>
inline constexpr auto operator-(const QuT f)
{
    return Qneg(f);
}

template <typename QuT1, typename QuT2>
inline constexpr auto operator/(const QuT1 f1, const QuT2 f2)
{
    return Qdiv(f1, f2);
}

template <typename QuT1, typename QuT2>
inline constexpr auto operator==(const QuT1 f1, const QuT2 f2)
{
    return Qeq(f1, f2);
}

template <typename QuT1, typename QuT2>
inline constexpr auto operator!=(const QuT1 f1, const QuT2 f2)
{
    return Qneq(f1, f2);
}

template <typename QuT1, typename QuT2>
inline constexpr auto operator<=>(const QuT1 f1, const QuT2 f2)
{
    return Qcmp(f1, f2);
}

// ------------------- Complex Operations -------------------

// Basic complex multiplication, realized as (a+bi)(c+di) = (ac-bd) + (ad+bc)i
template <typename... Args>
struct BasicComplexMul;

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

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct MulMerger<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, BasicComplexMul<toArgs...>>
{
    using mulACType = tagExtractor<acT<>, toArgs...>::type;
    using mulBDType = tagExtractor<bdT<>, toArgs...>::type;
    using mulADType = tagExtractor<adT<>, toArgs...>::type;
    using mulBCType = tagExtractor<bcT<>, toArgs...>::type;
    using subACBDType = tagExtractor<acbdT<>, toArgs...>::type;
    using addADBCType = tagExtractor<adbcT<>, toArgs...>::type;

    using ACMerger = MulMergerWraper<Qu_s<realArgs1...>, Qu_s<realArgs2...>, mulACType>::type;
    using BDMerger = MulMergerWraper<Qu_s<imagArgs1...>, Qu_s<imagArgs2...>, mulBDType>::type;
    using ADMerger = MulMergerWraper<Qu_s<realArgs1...>, Qu_s<imagArgs2...>, mulADType>::type;
    using BCMerger = MulMergerWraper<Qu_s<imagArgs1...>, Qu_s<realArgs2...>, mulBCType>::type;

    using RealMerger = AddMergerWraper<typename ACMerger::resType, typename BDMerger::resType, subACBDType>::type;
    using ImagMerger = AddMergerWraper<typename ADMerger::resType, typename BCMerger::resType, addADBCType>::type;

    using ACType = typename ACMerger::resType;
    using BDType = typename BDMerger::resType;
    using ADType = typename ADMerger::resType;
    using BCType = typename BCMerger::resType;

    using resRealType = typename RealMerger::resType;
    using resImagType = typename ImagMerger::resType;

    using resType = Qu_s<resRealType, resImagType>;
};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2>
struct MulMerger<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>> : MulMerger<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, BasicComplexMul<>>
{};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct Qmul_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, BasicComplexMul<toArgs...>>
{
    using merger = MulMerger<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, BasicComplexMul<toArgs...>>;

    inline static constexpr auto mul(const Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>> f1, const Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>> f2)
    {
        auto realPart = Qsub<typename merger::resRealType>(Qmul<typename merger::ACType>(f1.real, f2.real), Qmul<typename merger::BDType>(f1.imag, f2.imag));
        auto imagPart = Qadd<typename merger::resImagType>(Qmul<typename merger::ADType>(f1.real, f2.imag), Qmul<typename merger::BCType>(f1.imag, f2.real));

        return Qu_s<typename merger::resRealType, typename merger::resImagType>(realPart, imagPart);
    }
};

// default complex multiplication using BasicComplexMul
template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2>
struct Qmul_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>> : Qmul_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, BasicComplexMul<>>
{};

// Demanding all FullPrec
template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2>
struct Qmul_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, BasicComplexMul<FullPrec>> : Qmul_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, BasicComplexMul<acT<FullPrec>, bdT<FullPrec>, adT<FullPrec>, bcT<FullPrec>, acbdT<FullPrec>, adbcT<FullPrec>>>
{};

// Complex multiplication realized via 3 multiplications and 5 additions
// x = a + bi, y = c + di
// A = (a + b)c, B = (c + d)b, C = (b − a)d
// xy = (A − B) + (B − C)i
template <typename... Args>
struct TFComplexMul;

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

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct MulMerger<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TFComplexMul<toArgs...>>
{
    using addabType = tagExtractor<abT<>, toArgs...>::type;
    using addcdType = tagExtractor<cdT<>, toArgs...>::type;
    using subbaType = tagExtractor<baT<>, toArgs...>::type;
    using mulabcType = tagExtractor<abcT<>, toArgs...>::type;
    using mulcdbType = tagExtractor<cdbT<>, toArgs...>::type;
    using mulbadType = tagExtractor<badT<>, toArgs...>::type;
    using subABType = tagExtractor<ABT<>, toArgs...>::type;
    using subBCType = tagExtractor<BCT<>, toArgs...>::type;

    using abMerger = AddMergerWraper<Qu_s<realArgs1...>, Qu_s<imagArgs1...>, addabType>::type;
    using cdMerger = AddMergerWraper<Qu_s<realArgs2...>, Qu_s<imagArgs2...>, addcdType>::type;
    using baMerger = AddMergerWraper<Qu_s<imagArgs1...>, Qu_s<realArgs1...>, subbaType>::type;

    using abType = typename abMerger::resType;
    using cdType = typename cdMerger::resType;
    using baType = typename baMerger::resType;

    using abdMerger = MulMergerWraper<abType, Qu_s<imagArgs2...>, mulabcType>::type;
    using cdbMerger = MulMergerWraper<cdType, Qu_s<imagArgs1...>, mulcdbType>::type;
    using badMerger = MulMergerWraper<baType, Qu_s<imagArgs2...>, mulbadType>::type;

    using AType = typename abdMerger::resType;
    using BType = typename cdbMerger::resType;
    using CType = typename badMerger::resType;

    using ABMerger = AddMergerWraper<AType, BType, subABType>::type;
    using BCMerger = AddMergerWraper<BType, CType, subBCType>::type;

    using RealMerger = AddMergerWraper<typename ABMerger::resType, typename BCMerger::resType, subABType>::type;
    using ImagMerger = AddMergerWraper<typename BCMerger::resType, typename ABMerger::resType, subBCType>::type;

    using resRealType = typename RealMerger::resType;
    using resImagType = typename ImagMerger::resType;

    using resType = Qu_s<resRealType, resImagType>;
};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct Qmul_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TFComplexMul<toArgs...>>
{
    using merger = MulMerger<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TFComplexMul<toArgs...>>;

    inline static constexpr auto mul(const Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>> f1, const Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>> f2)
    {
        auto ab = Qadd<typename merger::abType>(f1.real, f1.imag);
        auto cd = Qadd<typename merger::cdType>(f2.real, f2.imag);
        auto ba = Qsub<typename merger::baType>(f1.imag, f1.real);

        auto A = Qmul<typename merger::AType>(ab, f2.real);
        auto B = Qmul<typename merger::BType>(cd, f1.imag);
        auto C = Qmul<typename merger::CType>(ba, f2.imag);

        auto realPart = Qsub<typename merger::resRealType>(A, B);
        auto imagPart = Qsub<typename merger::resImagType>(B, C);

        return Qu_s<typename merger::resRealType, typename merger::resImagType>(realPart, imagPart);
    }
};

// Demanding all FullPrec
template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2>
struct Qmul_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TFComplexMul<FullPrec>> : Qmul_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TFComplexMul<abT<FullPrec>, cdT<FullPrec>, baT<FullPrec>, abcT<FullPrec>, cdbT<FullPrec>, badT<FullPrec>, ABT<FullPrec>, BCT<FullPrec>>>
{};

template <typename... Args>
struct realT;

template <typename... Args>
struct imagT;

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct AddMerger<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, toArgs...>
{
    using realType = tagExtractor<realT<>, toArgs...>::type;
    using imagType = tagExtractor<imagT<>, toArgs...>::type;

    using realMerger = AddMergerWraper<Qu_s<realArgs1...>, Qu_s<realArgs2...>, realType>::type;
    using imagMerger = AddMergerWraper<Qu_s<imagArgs1...>, Qu_s<imagArgs2...>, imagType>::type;

    using resRealType = typename realMerger::resType;
    using resImagType = typename imagMerger::resType;

    using resType = Qu_s<resRealType, resImagType>;
};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct Qadd_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, toArgs...>
{
    using merger = AddMerger<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, toArgs...>;

    inline static constexpr auto add(const Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>> f1, const Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>> f2)
    {
        auto realPart = Qadd<typename merger::resRealType>(f1.real, f2.real);
        auto imagPart = Qadd<typename merger::resImagType>(f1.imag, f2.imag);

        return Qu_s<typename merger::resRealType, typename merger::resImagType>(realPart, imagPart);
    }
};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2>
struct Qadd_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, FullPrec> : Qadd_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, acT<FullPrec>, bdT<FullPrec>>
{};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct Qsub_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, toArgs...>
{
    using merger = AddMerger<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, toArgs...>;

    inline static constexpr auto sub(const Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>> f1, const Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>> f2)
    {
        auto realPart = Qsub<typename merger::resRealType>(f1.real, f2.real);
        auto imagPart = Qsub<typename merger::resImagType>(f1.imag, f2.imag);

        return Qu_s<typename merger::resRealType, typename merger::resImagType>(realPart, imagPart);
    }
};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2>
struct Qsub_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, FullPrec> : Qsub_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, acT<FullPrec>, bdT<FullPrec>>
{};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct Qdiv_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, toArgs...>
{
    inline static constexpr auto div(const Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>> f1, const Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>> f2)
    {
        static_assert(false, "Complex division is not allowed");
    }
};

// ------------------- Real-Complex Operations -------------------

template <int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode, typename... fromRealArgs, typename... fromImagArgs, typename... toArgs>
struct Qmul_s<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, toArgs...>
{
    using fromType = Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>;
    using inputRealType = tagExtractor<realT<>, toArgs...>::type;
    using inputImagType = tagExtractor<imagT<>, toArgs...>::type;

    using realMerger = MulMergerWraper<fromType, Qu_s<fromRealArgs...>, inputRealType>::type;
    using imagMerger = MulMergerWraper<fromType, Qu_s<fromImagArgs...>, inputImagType>::type;

    using resRealType = typename realMerger::resType;
    using resImagType = typename imagMerger::resType;

    inline static constexpr auto mul(const fromType f1, const Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>> f2)
    {
        auto realPart = Qmul<resRealType>(f1, f2.real);
        auto imagPart = Qmul<resImagType>(f1, f2.imag);

        return Qu_s<resRealType, resImagType>(realPart, imagPart);
    }
};

template <int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode, typename... fromRealArgs, typename... fromImagArgs>
struct Qmul_s<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, FullPrec> : Qmul_s<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, realT<FullPrec>, imagT<FullPrec>>
{};

template <int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode, typename... fromRealArgs, typename... fromImagArgs, typename... toArgs>
struct Qmul_s<Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, toArgs...>
{
    inline static constexpr auto mul(const Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>> f1, const Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>> f2)
    {
        return Qmul_s<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, toArgs...>::mul(f2, f1);
    }
};

template <int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode, typename... fromRealArgs, typename... fromImagArgs, typename... toArgs>
struct Qadd_s<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, toArgs...>
{
    using fromType = Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>;
    using inputRealType = tagExtractor<realT<>, toArgs...>::type;
    using inputImagType = tagExtractor<imagT<>, toArgs...>::type;

    using realMerger = AddMergerWraper<fromType, Qu_s<fromRealArgs...>, inputRealType>::type;
    using imagMerger = AddMergerWraper<fromType, Qu_s<fromImagArgs...>, inputImagType>::type;

    using resRealType = typename realMerger::resType;
    using resImagType = typename imagMerger::resType;

    inline static constexpr auto add(const fromType f1, const Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>> f2)
    {
        auto realPart = Qadd<resRealType>(f1, f2.real);
        auto imagPart = Qadd<resImagType>(f1, f2.imag);

        return Qu_s<resRealType, resImagType>(realPart, imagPart);
    }
};

template <int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode, typename... fromRealArgs, typename... fromImagArgs>
struct Qadd_s<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, FullPrec> : Qadd_s<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, realT<FullPrec>, imagT<FullPrec>>
{};

template <int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode, typename... fromRealArgs, typename... fromImagArgs, typename... toArgs>
struct Qadd_s<Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, toArgs...>
{
    inline static constexpr auto add(const Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>> f1, const Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>> f2)
    {
        return Qadd_s<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, toArgs...>::add(f2, f1);
    }
};

template <int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode, typename... fromRealArgs, typename... fromImagArgs, typename... toArgs>
struct Qsub_s<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, toArgs...>
{
    using fromType = Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>;
    using inputRealType = tagExtractor<realT<>, toArgs...>::type;
    using inputImagType = tagExtractor<imagT<>, toArgs...>::type;

    using realMerger = AddMergerWraper<fromType, Qu_s<fromRealArgs...>, inputRealType>::type;
    using imagMerger = AddMergerWraper<fromType, Qu_s<fromImagArgs...>, inputImagType>::type;

    using resRealType = typename realMerger::resType;
    using resImagType = typename imagMerger::resType;

    inline static constexpr auto sub(const fromType f1, const Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>> f2)
    {
        auto realPart = Qsub<resRealType>(f1, f2.real);
        auto imagPart = Qsub<resImagType>(f1, f2.imag);

        return Qu_s<resRealType, resImagType>(realPart, imagPart);
    }
};

template <int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode, typename... fromRealArgs, typename... fromImagArgs>
struct Qsub_s<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, FullPrec> : Qsub_s<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, realT<FullPrec>, imagT<FullPrec>>
{};

template <int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode, typename... fromRealArgs, typename... fromImagArgs, typename... toArgs>
struct Qsub_s<Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, toArgs...>
{
    using fromType = Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>;
    using inputRealType = tagExtractor<realT<>, toArgs...>::type;
    using inputImagType = tagExtractor<imagT<>, toArgs...>::type;

    using realMerger = AddMergerWraper<fromType, Qu_s<fromRealArgs...>, inputRealType>::type;
    using imagMerger = AddMergerWraper<fromType, Qu_s<fromImagArgs...>, inputImagType>::type;

    using resRealType = typename realMerger::resType;
    using resImagType = typename imagMerger::resType;

    inline static constexpr auto sub(const Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>> f1, const fromType f2)
    {
        auto realPart = Qsub<resRealType>(f1.real, f2);
        auto imagPart = Qsub<resImagType>(f1.imag, f2);

        return Qu_s<resRealType, resImagType>(realPart, imagPart);
    }
};

template <int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode, typename... fromRealArgs, typename... fromImagArgs>
struct Qsub_s<Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, FullPrec> : Qsub_s<Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, realT<FullPrec>, imagT<FullPrec>>
{};

template <int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode, typename... fromRealArgs, typename... fromImagArgs, typename... toArgs>
struct Qdiv_s<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, toArgs...>
{
    inline static constexpr auto div(const auto f1, const Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>> f2)
    {
        static_assert(false, "Complex division is not allowed");
    }
};

template <int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode, typename... fromRealArgs, typename... fromImagArgs, typename... toArgs>
struct Qdiv_s<Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, toArgs...>
{
    using fromType = Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>;
    using inputRealType = tagExtractor<realT<>, toArgs...>::type;
    using inputImagType = tagExtractor<imagT<>, toArgs...>::type;

    using realMerger = AddMergerWraper<fromType, Qu_s<fromRealArgs...>, inputRealType>::type;
    using imagMerger = AddMergerWraper<fromType, Qu_s<fromImagArgs...>, inputImagType>::type;

    using resRealType = typename realMerger::resType;
    using resImagType = typename imagMerger::resType;

    inline static constexpr auto div(const Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>> f1, const fromType f2)
    {
        auto realPart = Qdiv<resRealType>(f1.real, f2);
        auto imagPart = Qdiv<resImagType>(f1.imag, f2);

        return Qu_s<resRealType, resImagType>(realPart, imagPart);
    }
};

template <int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode, typename... fromRealArgs, typename... fromImagArgs>
struct Qdiv_s<Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, FullPrec> : Qdiv_s<Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, realT<FullPrec>, imagT<FullPrec>>
{};

// ------------------- Basic tensor operations -------------------

// mul

template <int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode, typename... fromRealArgs, typename... fromImagArgs, typename... toArgs>
struct MulMerger<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, toArgs...>
{
    using scalarT = Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>;

    using realType = tagExtractor<realT<>, toArgs...>::type;
    using imagType = tagExtractor<imagT<>, toArgs...>::type;

    using realMerger = MulMergerWraper<scalarT, Qu_s<fromRealArgs...>, realType>::type;
    using imagMerger = MulMergerWraper<scalarT, Qu_s<fromImagArgs...>, imagType>::type;

    using resRealType = typename realMerger::resType;
    using resImagType = typename imagMerger::resType;

    using resType = Qu_s<resRealType, resImagType>;
};

template <int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode, typename... fromRealArgs, typename... fromImagArgs, typename... toArgs>
struct MulMerger<Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, toArgs...> : MulMerger<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, toArgs...>
{};

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
inline constexpr auto Qmul(const Qu_s<dim<dims...>, QuT1> &f1, const Qu_s<dim<dims...>, QuT2> &f2)
{
    return Qmul_s<Qu<dim<dims...>, QuT1>, Qu<dim<dims...>, QuT2>, toArgs...>::mul(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
    requires(!Qu_s<dim<dims...>, QuT1>::isElementQu && !Qu_s<dim<dims...>, QuT2>::isElementQu && !isQu<toArgs...>)
struct Qmul_s<Qu_s<dim<dims...>, QuT1>, Qu_s<dim<dims...>, QuT2>, toArgs...>
{
    using merger = MulMerger<QuT1, QuT2, toArgs...>;

    inline static constexpr auto mul(const Qu_s<dim<dims...>, QuT1> &f1, const Qu_s<dim<dims...>, QuT2> &f2)
    {
        Qu<dim<dims...>, typename merger::resType> res;
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            res[i] = Qmul<toArgs...>(f1[i], f2[i]);
        }

        return res;
    }
};

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
    requires isScalar<QuT1>
inline constexpr auto Qmul(const QuT1 f1, const Qu_s<dim<dims...>, QuT2> &f2)
{
    return Qmul_s<QuT1, Qu<dim<dims...>, QuT2>, toArgs...>::mul(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
    requires isScalar<QuT2>
inline constexpr auto Qmul(const Qu_s<dim<dims...>, QuT1> &f1, const QuT2 f2)
{
    return Qmul_s<QuT2, Qu<dim<dims...>, QuT1>, toArgs...>::mul(f2, f1);
}

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
    requires(!Qu_s<dim<dims...>, QuT2>::isElementQu && isScalar<QuT1> && !isQu<toArgs...>)
struct Qmul_s<QuT1, Qu_s<dim<dims...>, QuT2>, toArgs...>
{
    using merger = MulMerger<QuT1, QuT2, toArgs...>;

    inline static constexpr auto mul(const QuT1 f1, const Qu_s<dim<dims...>, QuT2> &f2)
    {
        Qu<dim<dims...>, typename merger::resType> res;
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            res[i] = Qmul<toArgs...>(f1, f2[i]);
        }

        return res;
    }
};

// add

template <int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode, typename... fromRealArgs, typename... fromImagArgs, typename... toArgs>
struct AddMerger<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, toArgs...>
{
    using scalarT = Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>;

    using realType = tagExtractor<realT<>, toArgs...>::type;
    using imagType = tagExtractor<imagT<>, toArgs...>::type;

    using realMerger = AddMergerWraper<scalarT, Qu_s<fromRealArgs...>, realType>::type;
    using imagMerger = AddMergerWraper<scalarT, Qu_s<fromImagArgs...>, imagType>::type;

    using resRealType = typename realMerger::resType;
    using resImagType = typename imagMerger::resType;

    using resType = Qu_s<resRealType, resImagType>;
};

template <int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode, typename... fromRealArgs, typename... fromImagArgs, typename... toArgs>
struct AddMerger<Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, toArgs...> : AddMerger<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, Qu_s<Qu_s<fromRealArgs...>, Qu_s<fromImagArgs...>>, toArgs...>
{};

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
inline constexpr auto Qadd(const Qu_s<dim<dims...>, QuT1> &f1, const Qu_s<dim<dims...>, QuT2> &f2)
{
    return Qadd_s<Qu<dim<dims...>, QuT1>, Qu<dim<dims...>, QuT2>, toArgs...>::add(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
    requires(!Qu_s<dim<dims...>, QuT1>::isElementQu && !Qu_s<dim<dims...>, QuT2>::isElementQu && !isQu<toArgs...>)
struct Qadd_s<Qu_s<dim<dims...>, QuT1>, Qu_s<dim<dims...>, QuT2>, toArgs...>
{
    using merger = AddMerger<QuT1, QuT2, toArgs...>;

    inline static constexpr auto add(const Qu_s<dim<dims...>, QuT1> &f1, const Qu_s<dim<dims...>, QuT2> &f2)
    {
        Qu<dim<dims...>, typename merger::resType> res;
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            res[i] = Qadd<toArgs...>(f1[i], f2[i]);
        }

        return res;
    }
};

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
    requires isScalar<QuT1>
inline constexpr auto Qadd(const QuT1 f1, const Qu_s<dim<dims...>, QuT2> &f2)
{
    return Qadd_s<QuT1, Qu<dim<dims...>, QuT2>, toArgs...>::add(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
    requires isScalar<QuT2>
inline constexpr auto Qadd(const Qu_s<dim<dims...>, QuT1> &f1, const QuT2 f2)
{
    return Qadd_s<QuT2, Qu<dim<dims...>, QuT1>, toArgs...>::add(f2, f1);
}

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
    requires(!Qu_s<dim<dims...>, QuT2>::isElementQu && !isQu<toArgs...>)
struct Qadd_s<QuT1, Qu_s<dim<dims...>, QuT2>, toArgs...>
{
    using merger = AddMerger<QuT1, QuT2, toArgs...>;

    inline static constexpr auto add(const QuT1 f1, const Qu_s<dim<dims...>, QuT2> &f2)
    {
        Qu<dim<dims...>, typename merger::resType> res;
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            res[i] = Qadd<toArgs...>(f1, f2[i]);
        }

        return res;
    }
};

// sub

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
inline constexpr auto Qsub(const Qu_s<dim<dims...>, QuT1> &f1, const Qu_s<dim<dims...>, QuT2> &f2)
{
    return Qsub_s<Qu<dim<dims...>, QuT1>, Qu<dim<dims...>, QuT2>, toArgs...>::sub(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
    requires(!Qu_s<dim<dims...>, QuT1>::isElementQu && !Qu_s<dim<dims...>, QuT2>::isElementQu && !isQu<toArgs...>)
struct Qsub_s<Qu_s<dim<dims...>, QuT1>, Qu_s<dim<dims...>, QuT2>, toArgs...>
{
    using merger = AddMerger<QuT1, QuT2, toArgs...>;

    inline static constexpr auto sub(const Qu_s<dim<dims...>, QuT1> &f1, const Qu_s<dim<dims...>, QuT2> &f2)
    {
        Qu<dim<dims...>, typename merger::resType> res;
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            res[i] = Qsub<toArgs...>(f1[i], f2[i]);
        }

        return res;
    }
};

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
    requires isScalar<QuT1>
inline constexpr auto Qsub(const QuT1 f1, const Qu_s<dim<dims...>, QuT2> &f2)
{
    return Qsub_s<QuT1, Qu<dim<dims...>, QuT2>, toArgs...>::sub(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
    requires isScalar<QuT2>
inline constexpr auto Qsub(const Qu_s<dim<dims...>, QuT1> &f1, const QuT2 f2)
{
    return Qsub_s<Qu_s<dim<dims...>, QuT1>, QuT2, toArgs...>::sub(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
    requires(!Qu_s<dim<dims...>, QuT2>::isElementQu)
struct Qsub_s<QuT1, Qu_s<dim<dims...>, QuT2>, toArgs...>
{
    using merger = AddMerger<QuT1, QuT2, toArgs...>;

    inline static constexpr auto sub(const QuT1 f1, const Qu_s<dim<dims...>, QuT2> &f2)
    {
        Qu<dim<dims...>, typename merger::resType> res;
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            res[i] = Qsub<toArgs...>(f1, f2[i]);
        }

        return res;
    }
};

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
    requires(!Qu_s<dim<dims...>, QuT2>::isElementQu && !isQu<toArgs...>)
struct Qsub_s<Qu_s<dim<dims...>, QuT1>, QuT2, toArgs...>
{
    using merger = AddMerger<QuT1, QuT2, toArgs...>;

    inline static constexpr auto sub(const Qu_s<dim<dims...>, QuT1> &f1, const QuT2 f2)
    {
        Qu<dim<dims...>, typename merger::resType> res;
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            res[i] = Qsub<toArgs...>(f1[i], f2);
        }

        return res;
    }
};

// div

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
inline constexpr auto Qdiv(const Qu_s<dim<dims...>, QuT1> &f1, const Qu_s<dim<dims...>, QuT2> &f2)
{
    return Qdiv_s<Qu<dim<dims...>, QuT1>, Qu<dim<dims...>, QuT2>, toArgs...>::div(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
    requires(!Qu_s<dim<dims...>, QuT1>::isElementQu && !Qu_s<dim<dims...>, QuT2>::isElementQu && !isQu<toArgs...>)
struct Qdiv_s<Qu_s<dim<dims...>, QuT1>, Qu_s<dim<dims...>, QuT2>, toArgs...>
{
    using merger = AddMerger<QuT1, QuT2, toArgs...>;

    inline static constexpr auto div(const Qu_s<dim<dims...>, QuT1> &f1, const Qu_s<dim<dims...>, QuT2> &f2)
    {
        Qu<dim<dims...>, typename merger::resType> res;
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            res[i] = Qdiv<toArgs...>(f1[i], f2[i]);
        }

        return res;
    }
};

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
    requires isScalar<QuT1>
inline constexpr auto Qdiv(const QuT1 f1, const Qu_s<dim<dims...>, QuT2> &f2)
{
    return Qdiv_s<QuT1, Qu<dim<dims...>, QuT2>, toArgs...>::div(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
    requires isScalar<QuT2>
inline constexpr auto Qdiv(const Qu_s<dim<dims...>, QuT1> &f1, const QuT2 f2)
{
    return Qdiv_s<Qu_s<dim<dims...>, QuT1>, QuT2, toArgs...>::div(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
    requires(!Qu_s<dim<dims...>, QuT2>::isElementQu && !isQu<toArgs...>)
struct Qdiv_s<QuT1, Qu_s<dim<dims...>, QuT2>, toArgs...>
{
    using merger = AddMerger<QuT1, QuT2, toArgs...>;

    inline static constexpr auto div(const QuT1 f1, const Qu_s<dim<dims...>, QuT2> &f2)
    {
        Qu<dim<dims...>, typename merger::resType> res;
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            res[i] = Qdiv<toArgs...>(f1, f2[i]);
        }

        return res;
    }
};

template <typename... toArgs, typename QuT1, typename QuT2, size_t... dims>
    requires(!Qu_s<dim<dims...>, QuT2>::isElementQu && !isQu<toArgs...>)
struct Qdiv_s<Qu_s<dim<dims...>, QuT1>, QuT2, toArgs...>
{
    using merger = AddMerger<QuT1, QuT2, toArgs...>;

    inline static constexpr auto div(const Qu_s<dim<dims...>, QuT1> &f1, const QuT2 f2)
    {
        Qu<dim<dims...>, typename merger::resType> res;
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            res[i] = Qdiv<toArgs...>(f1[i], f2);
        }

        return res;
    }
};

// ------------------- Advanced Nonlinear Universal Subprograms -------------------
// the operations like lookup table, linear/polynomial fitting, etc. used to implement the non-linear operation in asic
// note that the operations are not standard BLAS operations, use ANUS:: to get access to them

namespace ANUS {

// polynomial fitting
template <auto... an>
struct PolyImpl;

template <typename anT, anT an>
struct PolyImpl<an>
{
    static inline constexpr auto execute(const auto prev, const auto x)
    {
        return Qadd<anT>(Qmul<anT>(prev, x), an);
    }
};

template <typename a1T, a1T a1, typename... anT, anT... an>
struct PolyImpl<a1, an...>
{
    static inline constexpr auto execute(const auto prev, const auto x)
    {
        return PolyImpl<an...>::execute(Qadd<a1T>(Qmul<a1T>(prev, x), a1), x);
    }
};

template <auto a0, auto... an>
    requires(sizeof...(an) > 0)
struct Poly
{
    static inline constexpr auto execute(const auto x)
    {
        return PolyImpl<an...>::execute(a0, x);
    }
};

// Approx

template <auto... points>
    requires(std::is_arithmetic_v<decltype(points)> && ...)
struct segments;

template <typename... polynomials>
struct polys;

template <typename... Args>
struct Approx;

template <auto firstPoint, auto... points, typename firstPoly, typename... polynomials>
struct Approx<segments<firstPoint, points...>, polys<firstPoly, polynomials...>>
{
    template <typename T>
    static inline constexpr T execute(const T x)
    {
        if (x.toDouble() < (firstPoint - T::minVal) / (T::maxVal - T::minVal))
        {
            return T(firstPoly::execute(x));
        }
        else
        {
            return T(Approx<segments<points...>, polys<polynomials...>>::execute(x));
        }
    }
};

template <typename polynominal>
struct Approx<segments<>, polys<polynominal>>
{
    static inline constexpr auto execute(const auto x)
    {
        return polynominal::execute(x);
    }
};

// lookup tables

// some pre-defined functions, stored as std::function

// sprt
inline static constexpr auto sqrtFunc = [](double x) { return std::sqrt(x); };

// reciprocal
inline static constexpr auto reciprocalFunc = [](double x) { return 1.0 / x; };

// reciprocal square root
inline static constexpr auto rsqrtFunc = [](double x) { return 1.0 / std::sqrt(x); };

// exponential
inline static constexpr auto expFunc = [](double x) { return std::exp(x); };

// note that essentially the lookup table is implemented via runtime calculation. This is theoretically identical to implementing a real pre-calculated lookup table in asic.
template <double (*func)(double), int intB, int fracB, bool isS, typename QuM, typename OfM>
inline constexpr auto Qtable(const Qu_s<intBits<intB>, fracBits<fracB>, isSigned<isS>, QuMode<QuM>, OfMode<OfM>> x)
{
    using interiorType = Qu_s<intBits<intB>, fracBits<fracB>, isSigned<isS>, QuMode<RND::ZERO>, OfMode<OfM>>;

    interiorType val = func(x.toDouble());

    return Qu_s<intBits<intB>, fracBits<fracB>, isSigned<isS>, QuMode<QuM>, OfMode<OfM>>(val.data, DirectAssignTag());
}

} // namespace ANUS

// ===================== BLAS =====================
// ------------------- Reducer -------------------
// it's not a standard BLAS operation, but tree-based reduction is a common operation in asic design

template <typename... Args>
struct Reducer
{
    template <bool condition, size_t layer>
    struct ReducerTypeSelector;

    // 递归展开的情况，满足条件
    template <size_t layer>
    struct ReducerTypeSelector<true, layer>
    {
        using type = TypeAt<layer >= sizeof...(Args) ? sizeof...(Args) - 1 : layer, TypeList<Args...>>;
    };

    // 基础情况，不满足计算条件的部分
    template <size_t layer>
    struct ReducerTypeSelector<false, layer>
    {
        using type = std::nullptr_t;
    };

    // version for arbitrary input, please avoid using this version for efficiency consideration
    template <size_t layer, typename... Ts, size_t... I>
    static inline auto reduce_impl(std::index_sequence<I...>,
                                   const Ts... quants)
    {
        // (quants.display("layer " + std::to_string(layer)), ...);
        if constexpr (sizeof...(quants) == 1)
        {
            return packIndex<0>(quants...);
        }
        else
        {
            using type = typename ReducerTypeSelector<sizeof...(Args) != 0, layer>::type;
            if constexpr (sizeof...(quants) % 2 == 0)
            {
                return reduce_impl<layer + 1>(
                    std::make_index_sequence<sizeof...(I) / 2>{},
                    Qadd<type>(packIndex<I * 2>(quants...), packIndex<I * 2 + 1>(quants...))...);
            }
            else
            {
                auto res = reduce_impl<layer + 1>(
                    std::make_index_sequence<sizeof...(I) / 2>{},
                    Qadd<type>(packIndex<I * 2>(quants...), packIndex<I * 2 + 1>(quants...))...);

                return Qadd<type>(res, packIndex<sizeof...(quants) - 1>(quants...));
            }
        }
    }

    template <typename... Ts>
    static auto reduce(const Ts... quants)
    {
        return reduce_impl<0>(std::make_index_sequence<sizeof...(Ts) / 2>{}, quants...);
    }

    // version for a vec
    template <size_t layer, size_t len, typename... fromArgs>
    static auto reduce_impl(const Qu_s<dim<len>, fromArgs...> &quants)
    {
        using type = typename ReducerTypeSelector<sizeof...(Args) != 0, layer>::type;
        // quants.display("layer " + std::to_string(layer));

        static Qu_s<dim<(len + 1) / 2>, typename std::conditional_t<std::is_same_v<type, std::nullptr_t>, Qu<fromArgs...>, type>> res;
        if constexpr (len == 1)
        {
            return quants.template get<0>();
        }
        else
        {
            [&res = res, &quants = quants]<size_t... I>(std::index_sequence<I...>) {
                ((res.template get<I>() = Qadd<type>(quants.template get<I * 2>(), quants.template get<I * 2 + 1>())), ...);
            }(std::make_index_sequence<len / 2>());

            if constexpr (len % 2 != 0)
            {
                res.template get<(len + 1) / 2 - 1>() = quants.template get<len - 1>();
            }

            return reduce_impl<layer + 1>(res);
        }
    }

    template <size_t len, typename... fromArgs>
    static auto reduce(const Qu_s<dim<len>, fromArgs...> &quants)
    {
        return reduce_impl<0>(quants);
    }

    template <size_t... dims, typename... fromArgs>
    static auto reduce(const Qu_s<dim<dims...>, fromArgs...> &quants)
    {
        static Qu_s<dim<dim<dims...>::elemSize>, fromArgs...> vec;
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            vec[i] = quants[i];
        }
        return reduce(vec);
    }
};

template <typename... Args>
struct ReducerInputHelper : public Reducer<Args...>
{
};

template <typename... Args>
struct ReducerInputHelper<TypeList<Args...>> : public Reducer<Args...>
{
};

template <typename... Args, typename... Ts>
inline auto constexpr Qreduce(const Ts... quants)
{
    return ReducerInputHelper<Args...>::reduce(quants...);
}

// ----------- Qgemul -----------
// C = op(A) * op(B)

template <bool Value>
struct QgemulTransposedA;

template <bool Value>
struct QgemulTransposedB;

// the arguments for the tree-based reduction
template <typename... Args>
struct QgemulAddArgs;

// the arguments for the dot product
template <typename... Args>
struct QgemulMulArgs;

template <typename... Args>
struct Qgemul_s;

template <bool isTransposedA, bool isTransposedB, typename... addArgs, typename... mulArgs, size_t colA, size_t rowA, size_t colB, size_t rowB, size_t colC, size_t rowC, typename... ArgsC, typename... ArgsA, typename... ArgsB>
    requires(Qu_s<dim<rowA, colA>, ArgsA...>::isElementQu) || (Qu_s<dim<rowB, colB>, ArgsB...>::isElementQu) || (Qu_s<dim<rowC, colC>, ArgsC...>::isElementQu)
struct Qgemul_s<QgemulTransposedA<isTransposedA>, QgemulTransposedB<isTransposedB>, QgemulAddArgs<addArgs...>, QgemulMulArgs<mulArgs...>, Qu_s<dim<rowC, colC>, ArgsC...>, Qu_s<dim<rowA, colA>, ArgsA...>, Qu_s<dim<rowB, colB>, ArgsB...>>
{
    static_assert(
        (!isTransposedA && !isTransposedB && (colA == rowB && rowA == rowC && colB == colC)) ||
            (!isTransposedA && isTransposedB && (colA == colB && rowA == rowC && rowB == colC)) ||
            (isTransposedA && !isTransposedB && (rowA == rowB && colA == rowC && colB == colC)) ||
            (isTransposedA && isTransposedB && (rowA == colB && colA == rowC && rowB == colC)),
        "Size mismatch when calling Qgemul");

    static inline void execute(Qu_s<dim<rowC, colC>, ArgsC...> &C, const Qu_s<dim<rowA, colA>, ArgsA...> &A, const Qu_s<dim<rowB, colB>, ArgsB...> &B)
    {
        return execute_outer(C, A, B, std::make_index_sequence < isTransposedA ? colA : rowA > ());
    }

    template <size_t... I>
    static inline void execute_outer(Qu_s<dim<rowC, colC>, ArgsC...> &C, const Qu_s<dim<rowA, colA>, ArgsA...> &A, const Qu_s<dim<rowB, colB>, ArgsB...> &B, std::index_sequence<I...>)
    {
        ((execute_inner<I>(C, A, B, std::make_index_sequence < isTransposedB ? rowB : colB > ()), ...));
    }

    template <size_t I, size_t... J>
    static inline void execute_inner(Qu_s<dim<rowC, colC>, ArgsC...> &C, const Qu_s<dim<rowA, colA>, ArgsA...> &A, const Qu_s<dim<rowB, colB>, ArgsB...> &B, std::index_sequence<J...>)
    {
        ((execute_ele<I, J>(C, A, B, std::make_index_sequence < isTransposedA ? rowA : colA > ()), ...));
    }

    template <size_t I, size_t J, size_t... K>
    static inline void execute_ele(Qu_s<dim<rowC, colC>, ArgsC...> &C, const Qu_s<dim<rowA, colA>, ArgsA...> &A, const Qu_s<dim<rowB, colB>, ArgsB...> &B, std::index_sequence<K...>)
    {
        if constexpr (!isTransposedA && !isTransposedB)
        {
            C.template get<I, J>() = Qreduce<addArgs...>(Qmul<mulArgs...>(A.template get<I, K>(), B.template get<K, J>())...);
        }
        else if constexpr (!isTransposedA && isTransposedB)
        {
            C.template get<I, J>() = Qreduce<addArgs...>(Qmul<mulArgs...>(A.template get<I, K>(), B.template get<J, K>())...);
        }
        else if constexpr (isTransposedA && !isTransposedB)
        {
            C.template get<I, J>() = Qreduce<addArgs...>(Qmul<mulArgs...>(A.template get<K, I>(), B.template get<K, J>())...);
        }
        else
        {
            C.template get<I, J>() = Qreduce<addArgs...>(Qmul<mulArgs...>(A.template get<K, I>(), B.template get<J, K>())...);
        }
    }
};

template <bool isTransposedA, bool isTransposedB, typename... addArgs, typename... mulArgs, size_t colA, size_t rowA, size_t colB, size_t rowB, size_t colC, size_t rowC, typename... ArgsC, typename... ArgsA, typename... ArgsB>
    requires(!Qu_s<dim<rowA, colA>, ArgsA...>::isElementQu) && (!Qu_s<dim<rowB, colB>, ArgsB...>::isElementQu) && (!Qu_s<dim<rowC, colC>, ArgsC...>::isElementQu)
struct Qgemul_s<QgemulTransposedA<isTransposedA>, QgemulTransposedB<isTransposedB>, QgemulAddArgs<addArgs...>, QgemulMulArgs<mulArgs...>, Qu_s<dim<rowC, colC>, ArgsC...>, Qu_s<dim<rowA, colA>, ArgsA...>, Qu_s<dim<rowB, colB>, ArgsB...>>
{
    static_assert(
        (!isTransposedA && !isTransposedB && (colA == rowB && rowA == rowC && colB == colC)) ||
            (!isTransposedA && isTransposedB && (colA == colB && rowA == rowC && rowB == colC)) ||
            (isTransposedA && !isTransposedB && (rowA == rowB && colA == rowC && colB == colC)) ||
            (isTransposedA && isTransposedB && (rowA == colB && colA == rowC && rowB == colC)),
        "Size mismatch when calling Qgemul");

    // the intermediate vector for the dot product
    using mulMerger = MulMerger<Qu<ArgsA...>, Qu<ArgsB...>, mulArgs...>;
    static inline Qu_s<dim<isTransposedA ? rowA : colA>, typename mulMerger::resType> vecC;

    static inline void execute(Qu_s<dim<rowC, colC>, ArgsC...> &C, const Qu_s<dim<rowA, colA>, ArgsA...> &A, const Qu_s<dim<rowB, colB>, ArgsB...> &B)
    {
        for (size_t i = 0; i < (isTransposedA ? colA : rowA); i++)
        {
            for (size_t j = 0; j < (isTransposedB ? rowB : colB); j++)
            {
                for (size_t k = 0; k < (isTransposedA ? rowA : colA); k++)
                {
                    // vecC[k] = Qmul<mulArgs...>(A[i, k], B[k, j]);

                    size_t rA = isTransposedA ? k : i;
                    size_t cA = isTransposedA ? i : k;
                    size_t rB = isTransposedB ? j : k;
                    size_t cB = isTransposedB ? k : j;

                    vecC[k] = Qmul<mulArgs...>(A[rA, cA], B[rB, cB]);
                }
                C[i, j] = Qreduce<addArgs...>(vecC);
            }
        }
    }
};

template <typename... interiorArgs, size_t rowC, size_t colC, size_t rowA, size_t colA, size_t rowB, size_t colB, typename... ArgsC, typename... ArgsA, typename... ArgsB>
inline static void Qgemul(Qu_s<dim<rowC, colC>, ArgsC...> &C, const Qu_s<dim<rowA, colA>, ArgsA...> &A, const Qu_s<dim<rowB, colB>, ArgsB...> &B)
{
    static constexpr bool isTransposedA = tagExtractor<QgemulTransposedA<false>, interiorArgs...>::value;
    static constexpr bool isTransposedB = tagExtractor<QgemulTransposedB<false>, interiorArgs...>::value;
    using addArgs = tagExtractor<QgemulAddArgs<>, interiorArgs...>::type;
    using mulArgs = tagExtractor<QgemulMulArgs<>, interiorArgs...>::type;

    Qgemul_s<QgemulTransposedA<isTransposedA>, QgemulTransposedB<isTransposedB>, addArgs, mulArgs, Qu_s<dim<rowC, colC>, ArgsC...>, Qu_s<dim<rowA, colA>, ArgsA...>, Qu_s<dim<rowB, colB>, ArgsB...>>::execute(C, A, B);
}

// ----------- Qgramul -----------
// C = op(A^T) * op(A)
// It's a special case of Qgemul, where the matrix B is the same as A.
// The diagonal elements of C will be treated with special quantization rules.
// It is not a standard BLAS routine.

template <bool Value>
struct QgramulTransposed;

template <typename... Args>
struct QgramulDiagAddArgs;

template <typename... Args>
struct QgramulDiagMulArgs;

template <typename... Args>
struct QgramulOffDiagAddArgs;

template <typename... Args>
struct QgramulOffDiagMulArgs;

template <typename... Args>
struct Qgramul_s;

template <bool isTransposed, typename... diagAddArgs, typename... diagMulArgs, typename... offDiagAddArgs, typename... offDiagMulArgs, size_t rowA, size_t colA, size_t rowC, size_t colC, typename... ArgsC, typename... ArgsA>
    requires(Qu_s<dim<rowA, colA>, ArgsA...>::isElementQu) && (Qu_s<dim<rowC, colC>, ArgsC...>::isElementQu)
struct Qgramul_s<QgramulTransposed<isTransposed>, QgramulDiagAddArgs<diagAddArgs...>, QgramulDiagMulArgs<diagMulArgs...>, QgramulOffDiagAddArgs<offDiagAddArgs...>, QgramulOffDiagMulArgs<offDiagMulArgs...>, Qu_s<dim<rowC, colC>, ArgsC...>, Qu_s<dim<rowA, colA>, ArgsA...>>
{
    static_assert(rowC == colC, "The output matrix of Qgramul must be square");

    static_assert(
        (!isTransposed && (rowC == colA)) ||
            (isTransposed && (rowC == rowA)),
        "Size mismatch when calling Qgramul");

    static inline void execute(Qu_s<dim<rowC, colC>, ArgsC...> &C, const Qu_s<dim<rowA, colA>, ArgsA...> &A)
    {
        return execute_outer(C, A, std::make_index_sequence<rowC>());
    }

    template <size_t... I>
    static inline void execute_outer(Qu_s<dim<rowC, colC>, ArgsC...> &C, const Qu_s<dim<rowA, colA>, ArgsA...> &A, std::index_sequence<I...>)
    {
        ((execute_inner<I>(C, A, std::make_index_sequence<rowC>()), ...));
    }

    template <size_t I, size_t... J>
    static inline void execute_inner(Qu_s<dim<rowC, colC>, ArgsC...> &C, const Qu_s<dim<rowA, colA>, ArgsA...> &A, std::index_sequence<J...>)
    {
        ((execute_ele<I, J>(C, A, std::make_index_sequence < isTransposed ? colA : rowA > ()), ...));
    }

    template <size_t I, size_t J, size_t... K>
    static inline void execute_ele(Qu_s<dim<rowC, colC>, ArgsC...> &C, const Qu_s<dim<rowA, colA>, ArgsA...> &A, std::index_sequence<K...>)
    {
        if constexpr (!isTransposed)
        {
            if constexpr (I == J)
            {
                C.template get<I, J>() = Qreduce<diagAddArgs...>(Qmul<diagMulArgs...>(A.template get<K, I>(), A.template get<K, J>())...);
            }
            else
            {
                C.template get<I, J>() = Qreduce<offDiagAddArgs...>(Qmul<offDiagMulArgs...>(A.template get<K, I>(), A.template get<K, J>())...);
            }
        }
        else
        {
            if constexpr (I == J)
            {
                C.template get<I, J>() = Qreduce<diagAddArgs...>(Qmul<diagMulArgs...>(A.template get<I, K>(), A.template get<J, K>())...);
            }
            else
            {
                C.template get<I, J>() = Qreduce<offDiagAddArgs...>(Qmul<offDiagMulArgs...>(A.template get<I, K>(), A.template get<J, K>())...);
            }
        }
    }
};

template <bool isTransposed, typename... diagAddArgs, typename... diagMulArgs, typename... offDiagAddArgs, typename... offDiagMulArgs, size_t rowA, size_t colA, size_t rowC, size_t colC, typename... ArgsC, typename... ArgsA>
// requires (!Qu_s<dim<rowA, colA>, ArgsA...>::isElementQu) && (Qu_s<dim<rowC, colC>, ArgsC...>::isElementQu)
struct Qgramul_s<QgramulTransposed<isTransposed>, QgramulDiagAddArgs<diagAddArgs...>, QgramulDiagMulArgs<diagMulArgs...>, QgramulOffDiagAddArgs<offDiagAddArgs...>, QgramulOffDiagMulArgs<offDiagMulArgs...>, Qu_s<dim<rowC, colC>, ArgsC...>, Qu_s<dim<rowA, colA>, ArgsA...>>
{
    // the intermediate vector loaded from A for dot product
    static inline Qu_s<dim<isTransposed ? colA : rowA>, Qu<ArgsA...>> vecA;

    // the intermediate vector loaded from B for dot product
    static inline Qu_s<dim<isTransposed ? colA : rowA>, Qu<ArgsA...>> vecB;

    static inline Qu_s<dim<isTransposed ? colA : rowA>, std::conditional_t<sizeof...(diagMulArgs) == 0, Qu<ArgsA...>, Qu<diagMulArgs...>>> diagMulRes;
    static inline Qu_s<dim<isTransposed ? colA : rowA>, std::conditional_t<sizeof...(offDiagMulArgs) == 0, Qu<ArgsA...>, Qu<offDiagMulArgs...>>> offDiagMulRes;

    static_assert(rowC == colC, "The output matrix of Qgramul must be square");

    static_assert(
        (!isTransposed && (rowC == colA)) ||
            (isTransposed && (rowC == rowA)),
        "Size mismatch when calling Qgramul");

    static inline void execute(Qu_s<dim<rowC, colC>, ArgsC...> &C, const Qu_s<dim<rowA, colA>, ArgsA...> &A)
    {
        return execute_outer(C, A, std::make_index_sequence<rowC>());
    }

    template <size_t... I>
    static inline void execute_outer(Qu_s<dim<rowC, colC>, ArgsC...> &C, const Qu_s<dim<rowA, colA>, ArgsA...> &A, std::index_sequence<I...>)
    {
        ((execute_inner<I>(C, A, std::make_index_sequence<rowC>()), ...));
    }

    template <size_t I, size_t... J>
    static inline void execute_inner(Qu_s<dim<rowC, colC>, ArgsC...> &C, const Qu_s<dim<rowA, colA>, ArgsA...> &A, std::index_sequence<J...>)
    {
        ((execute_ele<I, J>(C, A, std::make_index_sequence < isTransposed ? colA : rowA > ()), ...));
    }

    template <size_t I, size_t J, size_t... K>
    static inline void execute_ele(Qu_s<dim<rowC, colC>, ArgsC...> &C, const Qu_s<dim<rowA, colA>, ArgsA...> &A, std::index_sequence<K...>)
    {
        elementWise::vecExtract<I, isTransposed>(A, vecA);
        elementWise::vecExtract<J, isTransposed>(A, vecB);

        if constexpr (I == J)
        {
            Qmul<diagMulArgs...>(diagMulRes, vecA, vecB);
            C.template get<I, J>() = Qreduce<diagAddArgs...>(diagMulRes);
        }
        else
        {
            Qmul<offDiagMulArgs...>(offDiagMulRes, vecA, vecB);
            C.template get<I, J>() = Qreduce<offDiagAddArgs...>(offDiagMulRes);
        }
    }
};

template <typename... interiorArgs, size_t rowC, size_t colC, size_t rowA, size_t colA, typename... ArgsC, typename... ArgsA>
inline static void Qgramul(Qu_s<dim<rowC, colC>, ArgsC...> &C, const Qu_s<dim<rowA, colA>, ArgsA...> &A)
{
    static constexpr bool isTransposed = tagExtractor<QgramulTransposed<false>, interiorArgs...>::value;
    using diagAddArgs = tagExtractor<QgramulDiagAddArgs<>, interiorArgs...>::type;
    using diagMulArgs = tagExtractor<QgramulDiagMulArgs<>, interiorArgs...>::type;
    using offDiagAddArgs = tagExtractor<QgramulOffDiagAddArgs<>, interiorArgs...>::type;
    using offDiagMulArgs = tagExtractor<QgramulOffDiagMulArgs<>, interiorArgs...>::type;

    Qgramul_s<QgramulTransposed<isTransposed>, diagAddArgs, diagMulArgs, offDiagAddArgs, offDiagMulArgs, Qu_s<dim<rowC, colC>, ArgsC...>, Qu_s<dim<rowA, colA>, ArgsA...>>::execute(C, A);
};

// ------------------- Qgemv -------------------
// y = beta * y + alpha * op(A) * x

template <bool isTransposedA>
struct QgemvTransposedA;

template <typename... Args>
struct QgemvAddArgs;

template <typename... Args>
struct QgemvMulArgs;

template <Qu_s alpha>
struct QgemvAlpha;

template <Qu_s beta>
struct QgemvBeta;

template <typename... Args>
struct Qgemv_s;

template <size_t sizeY, size_t rowA, size_t colA, size_t sizeX, typename... ArgsY, typename... ArgsA, typename... ArgsX, typename... addArgs, typename... mulArgs, bool isTransposedA, Qu_s alpha, Qu_s beta>
    requires(Qu_s<dim<sizeY>, ArgsY...>::isElementQu || Qu_s<dim<rowA, colA>, ArgsA...>::isElementQu || Qu_s<dim<sizeX>, ArgsX...>::isElementQu)
struct Qgemv_s<QgemvTransposedA<isTransposedA>, QgemvAddArgs<addArgs...>, QgemvMulArgs<mulArgs...>, Qu_s<dim<sizeY>, ArgsY...>, Qu_s<dim<rowA, colA>, ArgsA...>, Qu_s<dim<sizeX>, ArgsX...>, QgemvAlpha<alpha>, QgemvBeta<beta>>
{
    static_assert(
        (!isTransposedA && (colA == sizeX && rowA == sizeY)) ||
            (isTransposedA && (rowA == sizeX && colA == sizeY)),
        "Size mismatch when calling Qgemv");

    static inline void execute(Qu_s<dim<sizeY>, ArgsY...> &y, const Qu_s<dim<rowA, colA>, ArgsA...> &A, const Qu_s<dim<sizeX>, ArgsX...> &x)
    {
        return execute_outer(y, A, x, std::make_index_sequence<sizeY>());
    }

    template <size_t... I>
    static inline void execute_outer(Qu_s<dim<sizeY>, ArgsY...> &y, const Qu_s<dim<rowA, colA>, ArgsA...> &A, const Qu_s<dim<sizeX>, ArgsX...> &x, std::index_sequence<I...>)
    {
        ((execute_inner<I>(y, A, x, std::make_index_sequence<sizeX>()), ...));
    }

    template <size_t I, size_t... J>
    static inline void execute_inner(Qu_s<dim<sizeY>, ArgsY...> &y, const Qu_s<dim<rowA, colA>, ArgsA...> &A, const Qu_s<dim<sizeX>, ArgsX...> &x, std::index_sequence<J...>)
    {
        auto addRes = Qreduce<addArgs...>(Qmul<mulArgs...>(A.template get < isTransposedA ? J : I, isTransposedA ? I : J > (), x.template get<J>())...);

        if constexpr (beta.data == 0)
        {
            if constexpr (alpha == Qu<ArgsY...>(1))
            {
                y.template get<I>() = addRes;
            }
            else
            {
                y.template get<I>() = Qmul<ArgsY...>(alpha, addRes);
            }
        }
        else
        {
            if constexpr (alpha == Qu<ArgsY...>(1))
            {
                y.template get<I>() = Qadd<ArgsY...>(Qmul<ArgsY...>(beta, y.template get<I>()), addRes);
            }
            else
            {
                y.template get<I>() = Qadd<ArgsY...>(Qmul<ArgsY...>(beta, y.template get<I>()), Qmul<ArgsY...>(alpha, addRes));
            }
        }
    }
};

template <size_t sizeY, size_t rowA, size_t colA, size_t sizeX, typename... ArgsY, typename... ArgsA, typename... ArgsX, typename... addArgs, typename... mulArgs, bool isTransposedA, Qu_s alpha, Qu_s beta>
    requires(!Qu_s<dim<sizeY>, ArgsY...>::isElementQu && !Qu_s<dim<rowA, colA>, ArgsA...>::isElementQu && !Qu_s<dim<sizeX>, ArgsX...>::isElementQu)
struct Qgemv_s<QgemvTransposedA<isTransposedA>, QgemvAddArgs<addArgs...>, QgemvMulArgs<mulArgs...>, Qu_s<dim<sizeY>, ArgsY...>, Qu_s<dim<rowA, colA>, ArgsA...>, Qu_s<dim<sizeX>, ArgsX...>, QgemvAlpha<alpha>, QgemvBeta<beta>>
{
    static_assert(
        (!isTransposedA && (colA == sizeX && rowA == sizeY)) ||
            (isTransposedA && (rowA == sizeX && colA == sizeY)),
        "Size mismatch when calling Qgemv");

    using mulMerger = MulMerger<Qu<ArgsA...>, Qu<ArgsX...>, mulArgs...>;
    static inline Qu_s<dim<isTransposedA ? rowA : colA>, typename mulMerger::resType> vecA;

    static inline void execute(Qu_s<dim<sizeY>, ArgsY...> &y, const Qu_s<dim<rowA, colA>, ArgsA...> &A, const Qu_s<dim<sizeX>, ArgsX...> &x)
    {
        for (size_t i = 0; i < sizeY; i++)
        {
            for (size_t j = 0; j < sizeX; j++)
            {
                vecA[j] = Qmul<mulArgs...>(A[isTransposedA ? j : i, isTransposedA ? i : j], x[j]);
            }
            auto addRes = Qreduce<addArgs...>(vecA);

            if constexpr (beta.data == 0)
            {
                if constexpr (alpha == Qu<ArgsY...>(1))
                {
                    y[i] = addRes;
                }
                else
                {
                    y[i] = Qmul<ArgsY...>(alpha, addRes);
                }
            }
            else
            {
                if constexpr (alpha == Qu<ArgsY...>(1))
                {
                    y[i] = Qadd<ArgsY...>(Qmul<ArgsY...>(beta, y[i]), addRes);
                }
                else
                {
                    y[i] = Qadd<ArgsY...>(Qmul<ArgsY...>(beta, y[i]), Qmul<ArgsY...>(alpha, addRes));
                }
            }
        }
    }
};

template <typename... interiorArgs, size_t sizeY, size_t rowA, size_t colA, size_t sizeX, typename... ArgsY, typename... ArgsA, typename... ArgsX>
inline static void Qgemv(Qu_s<dim<sizeY>, ArgsY...> &y, const Qu_s<dim<rowA, colA>, ArgsA...> &A, const Qu_s<dim<sizeX>, ArgsX...> &x)
{
    static constexpr bool isTransposedA = tagExtractor<QgemvTransposedA<false>, interiorArgs...>::value;
    using addArgs = tagExtractor<QgemvAddArgs<>, interiorArgs...>::type;
    using mulArgs = tagExtractor<QgemvMulArgs<>, interiorArgs...>::type;

    static constexpr Qu<ArgsY...> defaultAlpha = 1;
    static constexpr Qu<ArgsY...> defaultBeta = 0;

    static constexpr auto alpha = tagExtractor<QgemvAlpha<defaultAlpha>, interiorArgs...>::value;
    static constexpr auto beta = tagExtractor<QgemvBeta<defaultBeta>, interiorArgs...>::value;

    Qgemv_s<QgemvTransposedA<isTransposedA>, addArgs, mulArgs, Qu_s<dim<sizeY>, ArgsY...>, Qu_s<dim<rowA, colA>, ArgsA...>, Qu_s<dim<sizeX>, ArgsX...>, QgemvAlpha<alpha>, QgemvBeta<beta>>::execute(y, A, x);
}

// normal version for reference
// int potrf(double* A, int n) {
//     for (int j = 0; j < n; ++j) {
//         for (int k = 0; k < j; ++k) {
//             for (int i = j; i < n; ++i) {
//                 A[i * n + j] -= A[i * n + k] * A[j * n + k];
//             }
//         }
//         if (A[n * j + j] <= 0) {
//             return -1; // 不是正定矩阵
//         }
//         double temp = 1.0/sqrt(A[n * j + j]);
//         for (int i = j; i < n; ++i) {
//             A[i * n + j] *= temp;
//         }
//     }
//     return 0;
// }

// ------------------- Qpotrf -------------------
// the diagonal elements of the input matrix will be treated with special quantization rules.
// IMPORTANT: the diagonal elements of the output matrix will be stored as the reciprocal form

template <typename... Args>
struct Qpotrf_s;

template <typename... Args, size_t row, size_t col>
struct Qpotrf_s<Qu_s<dim<row, col>, Args...>>
{
    static_assert(row == col, "The input matrix of Qpotrf must be square");

    static inline void execute(Qu_s<dim<row, col>, Args...> &A)
    {
        return loop(A, std::make_index_sequence<col>());
    }

    template <size_t... J>
    static inline void loop(Qu_s<dim<row, col>, Args...> &A, std::index_sequence<J...>)
    {
        ((loop_inner<J>(A), ...));
    }

    template <size_t J>
    static inline void loop_inner(Qu_s<dim<row, col>, Args...> &A)
    {
        loop_sec1_outer<J>(A, std::make_index_sequence<J>());
        if (A.template get<J, J>().data <= 0)
        {
            return;
        }
        loop_sec2<J>(A, std::make_index_sequence<row - J>());
    }

    template <size_t J, size_t... K>
    static inline void loop_sec1_outer(Qu_s<dim<row, col>, Args...> &A, std::index_sequence<K...>)
    {
        ((loop_sec1_inner<J, K>(A, std::make_index_sequence<row - J>()), ...));
    }

    template <size_t J, size_t K, size_t... I>
    static inline void loop_sec1_inner(Qu_s<dim<row, col>, Args...> &A, std::index_sequence<I...>)
    {
        ((A.template get<I + J, J>() = A.template get<I + J, J>() - A.template get<I + J, K>() * A.template get<J, K>()), ...);
    }

    template <size_t J, size_t... I>
    static inline void loop_sec2(Qu_s<dim<row, col>, Args...> &A, std::index_sequence<I...>)
    {
        auto temp = ANUS::Qtable<ANUS::rsqrtFunc>(A.template get<J, J>());
        ((A.template get<I + J, J>() = A.template get<I + J, J>() * temp), ...);
        A.template get<J, J>() = temp;
    }
};

template <typename... interiorArgs, size_t row, size_t col, typename... Args>
inline static void Qpotrf(Qu_s<dim<row, col>, Args...> &A)
{
    Qpotrf_s<Qu_s<dim<row, col>, Args...>>::execute(A);
}

// normal version for reference
// void potrs(double* L, double* b, int n) {
//     // 前向替代
//     for (int i = 0; i < n; ++i) {
//         for (int j = 0; j < i; ++j) {
//             b[i] -= L[i * n + j] * b[j];
//         }
//         b[i] *= L[i * n + i];
//     }

//     // 后向替代
//     for (int i = n - 1; i >= 0; --i) {
//         for (int j = i + 1; j < n; ++j) {
//             b[i] -= L[j * n + i] * b[j];
//         }
//         b[i] *= L[i * n + i];
//     }
// }

// ------------------- Qpotrs -------------------
// IMPORTANT: the diagonal elements of the input matrix must be stored as the reciprocal form

template <typename... Args>
struct Qpotrs_s;

template <typename... LArgs, typename... bArgs, size_t row, size_t col, size_t bRow>
struct Qpotrs_s<Qu_s<dim<row, col>, LArgs...>, Qu_s<dim<bRow>, bArgs...>>
{
    static_assert(row == col, "The input matrix of Qpotrs must be square");

    static inline void execute(const Qu_s<dim<row, col>, LArgs...> &L, Qu_s<dim<bRow>, bArgs...> &b)
    {
        return execute_loop(L, b, std::make_index_sequence<row>());
    }

    template <size_t... I>
    static inline void execute_loop(const Qu_s<dim<row, col>, LArgs...> &L, Qu_s<dim<bRow>, bArgs...> &b, std::index_sequence<I...>)
    {
        ((execute_forward<I>(L, b, std::make_index_sequence<I>()), ...));
        ((execute_backward<row - 1 - I>(L, b, std::make_index_sequence<I>()), ...));
    }

    template <size_t I, size_t... J>
    static inline void execute_forward(const Qu_s<dim<row, col>, LArgs...> &L, Qu_s<dim<bRow>, bArgs...> &b, std::index_sequence<J...>)
    {
        ((b.template get<I>() = b.template get<I>() - L.template get<I, J>() * b.template get<J>()), ...);
        b.template get<I>() = b.template get<I>() * L.template get<I, I>();
    }

    template <size_t I, size_t... J>
    static inline void execute_backward(const Qu_s<dim<row, col>, LArgs...> &L, Qu_s<dim<bRow>, bArgs...> &b, std::index_sequence<J...>)
    {
        ((b.template get<I>() = b.template get<I>() - L.template get<J + I + 1, I>() * b.template get<J + I + 1>()), ...);
        b.template get<I>() = b.template get<I>() * L.template get<I, I>();
    }
};

template <typename... interiorArgs, size_t row, size_t col, size_t bRow, typename... LArgs, typename... bArgs>
inline static void Qpotrs(const Qu_s<dim<row, col>, LArgs...> &L, Qu_s<dim<bRow>, bArgs...> &b)
{
    Qpotrs_s<Qu_s<dim<row, col>, LArgs...>, Qu_s<dim<bRow>, bArgs...>>::execute(L, b);
}

// ------------------- Qsytrf -------------------
// LDL^T factorization
// not identical to the standard LAPACK routine, L and D will be stored separately

// matlab code for reference

// L = eye(n); % 初始化L为单位矩阵
// D = zeros(n, 1); % 初始化D为零向量

// for j = 1:n
//     % 计算D(j)
//     LD_vector = zeros(1, j-1);
//     for k = 1:(j-1)
//         LD_vector(k) = L[j, k]^2 * D(k);
//     end
//     sum_LD = vector_sum(LD_vector);
//     D(j) = A[j, j] - sum_LD;

//     % 计算L(i, j) 对于 i > j
//     for i = (j+1):n
//         LD_vector = zeros(1, j-1);
//         for k = 1:(j-1)
//             LD_vector(k) = L(i, k) * L[j, k] * D(k);
//         end
//         sum_LD = vector_sum(LD_vector);
//         L(i, j) = (A(i, j) - sum_LD) / D(j);
//     end
// end

template <typename... Args>
struct QsytrfLDArgs;

template <typename... Args>
struct QsytrfSumLDArgs;

template <typename... Args>
struct Qsytrf_s;

template <typename... AArgs, typename... LArgs, typename... DArgs, typename... LDArgs, typename... sumLDArgs, size_t row, size_t col>
struct Qsytrf_s<QsytrfLDArgs<LDArgs...>, QsytrfSumLDArgs<sumLDArgs...>, Qu_s<dim<row, col>, AArgs...>, Qu_s<dim<row, col>, LArgs...>, Qu_s<dim<row>, DArgs...>>
{
    static_assert(row == col, "The input matrix of Qsytrf must be square");

    inline static auto LD_vector = Qu<dim<row - 1>, LDArgs...>();

    inline static auto sum_LD = Qu<sumLDArgs...>();

    inline static void execute(Qu_s<dim<row, col>, LArgs...> &L, Qu_s<dim<row>, DArgs...> &D, Qu_s<dim<row, col>, AArgs...> &A)
    {
        // set L to identity matrix
        L.clear();
        for (size_t i = 0; i < row; ++i)
        {
            L[i, i] = 1;
        }

        for (size_t j = 0; j < row; ++j)
        {
            // clear LD_vector
            LD_vector.clear();

            // 计算D[j]
            for (size_t k = 0; k < j; ++k)
            {
                LD_vector[k] = L[j, k] * L[j, k] * D[k];
            }

            sum_LD = 0;
            for (size_t k = 0; k < j; ++k)
            {
                sum_LD = sum_LD + LD_vector[k];
            }
            D[j] = A[j, j] - sum_LD;

            // 计算L[i, j] 对于 i > j
            for (size_t i = j + 1; i < row; ++i)
            {
                // clear LD_vector
                LD_vector.clear();

                for (size_t k = 0; k < j; ++k)
                {
                    LD_vector[k] = L[i, k] * L[j, k] * D[k];
                }
                sum_LD = 0;
                for (size_t k = 0; k < j; ++k)
                {
                    sum_LD = sum_LD + LD_vector[k];
                }

                L[i, j] = (A[i, j] - sum_LD) / D[j];
            }
        }
    }
};

template <typename... interiorArgs, size_t row, size_t col, typename... AArgs, typename... LArgs, typename... DArgs>
inline static void Qsytrf(Qu_s<dim<row, col>, LArgs...> &L, Qu_s<dim<row>, DArgs...> &D, Qu_s<dim<row, col>, AArgs...> &A)
{
    using LDArgs = tagExtractor<QsytrfLDArgs<LArgs...>, interiorArgs...>::type;
    using sumLDArgs = tagExtractor<QsytrfSumLDArgs<LArgs...>, interiorArgs...>::type;

    Qsytrf_s<LDArgs, sumLDArgs, Qu_s<dim<row, col>, AArgs...>, Qu_s<dim<row, col>, LArgs...>, Qu_s<dim<row>, DArgs...>>::execute(L, D, A);
}

// ------------------- Qtrtri -------------------
// inverse of a triangular matrix
// not identical to the standard LAPACK routine, need a extra matrix to store the result

// matlab code for reference
// % for lower triangular matrix
// function Ainv = inverseLowerTriangularMatrix(A)
//     % 计算下三角矩阵的逆矩阵
//     n = size(A, 1);
//     Ainv = zeros(n, n);
//     for i = 1:n
//         Ainv(i, i) = 1 / A(i, i);
//         for j = (i+1):n
//             sum_Ainv = 0;
//             for k = i:(j-1)
//                 sum_Ainv = sum_Ainv + A(j, k) * Ainv(k, i);
//             end
//             Ainv(j, i) = -sum_Ainv / A(j, j);
//         end
//     end
// end

// % for upper triangular matrix
// function Ainv = inverseUpperTriangularMatrix(A)
//     % 计算上三角矩阵的逆矩阵
//     n = size(A, 1);
//     Ainv = zeros(n, n);
//     for i = n:-1:1
//         Ainv(i, i) = 1 / A(i, i);
//         for j = (i-1):-1:1
//             sum_Ainv = 0;
//             for k = (j+1):i
//                 sum_Ainv = sum_Ainv + A(j, k) * Ainv(k, i);
//             end
//             Ainv(j, i) = -sum_Ainv / A(j, j);
//         end
//     end
// end

template <bool isLower>
struct QtrtriLower;

// too lazy to add more configurations, currently only the sum args
template <typename... Args>
struct QtrtriSumAinvArgs;

template <typename... Args>
struct Qtrtri_s;

template <bool isLow, typename... sumAinvArgs, size_t row, size_t col, typename... AArgs, typename... AinvArgs>
struct Qtrtri_s<QtrtriLower<isLow>, QtrtriSumAinvArgs<sumAinvArgs...>, Qu_s<dim<row, col>, AArgs...>, Qu_s<dim<row, col>, AinvArgs...>>
{
    static_assert(row == col, "The input matrix of Qtrtri must be square");

    inline static auto sum_Ainv = Qu<sumAinvArgs...>();

    inline static void execute(Qu_s<dim<row, col>, AinvArgs...> &Ainv, Qu_s<dim<row, col>, AArgs...> &A)
    {
        if constexpr (isLow)
        {
            Ainv.clear();

            for (size_t i = 0; i < row; ++i)
            {
                Ainv[i, i] = ANUS::Qtable<ANUS::reciprocalFunc>(A[i, i]);
                for (size_t j = i + 1; j < row; ++j)
                {
                    sum_Ainv = 0;
                    for (size_t k = i; k < j; ++k)
                    {
                        sum_Ainv = sum_Ainv + A[j, k] * Ainv[k, i];
                    }
                    Ainv[j, i] = -sum_Ainv / A[j, j];
                }
            }
        }
        else
        {
            Ainv.clear();

            for (size_t i = row - 1; i < row; --i)
            {
                Ainv[i, i] = 1 / A[i, i];
                for (size_t j = i - 1; j < row; --j)
                {
                    sum_Ainv = 0;
                    for (size_t k = j + 1; k < i; ++k)
                    {
                        sum_Ainv = sum_Ainv + A[j, k] * Ainv[k, i];
                    }
                    Ainv[j, i] = -sum_Ainv / A[j, j];
                }
            }
        }
    }
};

template <typename... interiorArgs, size_t row, size_t col, typename... AArgs, typename... AinvArgs>
inline static void Qtrtri(Qu_s<dim<row, col>, AinvArgs...> &Ainv, Qu_s<dim<row, col>, AArgs...> &A)
{
    static constexpr bool isLower = tagExtractor<QtrtriLower<true>, interiorArgs...>::value;
    using sumAinvArgs = tagExtractor<QtrtriSumAinvArgs<AinvArgs...>, interiorArgs...>::type;

    Qtrtri_s<QtrtriLower<isLower>, sumAinvArgs, Qu_s<dim<row, col>, AArgs...>, Qu_s<dim<row, col>, AinvArgs...>>::execute(Ainv, A);
};

}; // namespace QuBLAS