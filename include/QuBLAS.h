#pragma once

#include <type_traits>
#include <iostream>
#include <concepts>
#include <bitset>

// value extractor
template <typename Tag, typename... Args>
struct tagValueExtractor;

// 当标签未找到时的基础案例
template <template <auto> class Tag, auto Value>
struct tagValueExtractor<Tag<Value>>
{
    static constexpr auto value = Value;
};

// 匹配并提取值
template <template <auto> class Tag, auto Value, auto Value2, typename... Args>
struct tagValueExtractor<Tag<Value>, Tag<Value2>, Args...>
{
    static constexpr auto value = Value2;
};

// 匹配失败，类型不符，继续递归
template <typename Tag, typename Tag2, typename... Args>
struct tagValueExtractor<Tag, Tag2, Args...>
{
    static constexpr auto value = tagValueExtractor<Tag, Args...>::value;
};

// type extractor
template <typename Tag, typename... Args>
struct tagTypeExtractor;

// 当标签未找到时的基础案例
template <template <typename> class Tag, typename Value>
struct tagTypeExtractor<Tag<Value>>
{
    using type = Value;
};

// 匹配并提取值
template <template <typename> class Tag, typename Value, typename Value2, typename... Args>
struct tagTypeExtractor<Tag<Value>, Tag<Value2>, Args...>
{
    using type = Value2;
};

// 匹配失败，类型不符，继续递归
template <typename Tag, typename Tag2, typename... Args>
struct tagTypeExtractor<Tag, Tag2, Args...>
{
    using type = typename tagTypeExtractor<Tag, Args...>::type;
};

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
    template <typename T>
    inline static auto convert(T val)
    {
        using returnType = std::conditional_t<std::is_signed_v<T>, long long int, unsigned long long int>;
        if constexpr (fromFrac <= toFrac)
        {
            return static_cast<returnType>(val) << (fromFrac - toFrac);
        }
        else
        {
            static constexpr unsigned long long int mask = 0 - (1 << (fromFrac - toFrac));
            returnType floor = val & mask;
            returnType ceil = floor + (1 << (fromFrac - toFrac));

            return ((val - floor) < (ceil - val) ? floor : ceil) >> (fromFrac - toFrac);
        }
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<RND::NEG_INF>>
{
    template <typename T>
    inline static auto convert(T val)
    {
        using returnType = std::conditional_t<std::is_signed_v<T>, long long int, unsigned long long int>;
        if constexpr (fromFrac <= toFrac)
        {
            return static_cast<returnType>(val) << (fromFrac - toFrac);
        }
        else
        {

            static constexpr unsigned long long int mask = 0 - (1 << (fromFrac - toFrac));
            returnType floor = val & mask;
            returnType ceil = floor + (1 << (fromFrac - toFrac));

            return ((val - floor) <= (ceil - val) ? floor : ceil) >> (fromFrac - toFrac);
        }
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<RND::ZERO>>
{
    template <typename T>
    inline static auto convert(T val)
    {
        using returnType = std::conditional_t<std::is_signed_v<T>, long long int, unsigned long long int>;
        if constexpr (fromFrac <= toFrac)
        {
            return static_cast<returnType>(val) << (fromFrac - toFrac);
        }
        else
        {
            if constexpr (std::is_signed_v<T>)
            {
                static constexpr unsigned long long int mask = 0 - (1 << (fromFrac - toFrac));
                long long int floor = val & mask;
                long long int ceil = floor + (1 << (fromFrac - toFrac));

                return (floor + ceil) > 0 ? floor >> (fromFrac - toFrac) : ceil >> (fromFrac - toFrac);
            }
            else
            {
                return static_cast<returnType>(val) >> (fromFrac - toFrac);
            }
        }
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<RND::INF>>
{
    template <typename T>
    inline static auto convert(T val)
    {
        using returnType = std::conditional_t<std::is_signed_v<T>, long long int, unsigned long long int>;
        if constexpr (fromFrac <= toFrac)
        {
            return static_cast<returnType>(val) << (fromFrac - toFrac);
        }
        else
        {
            if constexpr (std::is_signed_v<T>)
            {
                static constexpr unsigned long long int mask = 0 - (1 << (fromFrac - toFrac));
                long long int floor = val & mask;
                long long int ceil = floor + (1 << (fromFrac - toFrac));

                return (floor + ceil) < 0 ? floor >> (fromFrac - toFrac) : ceil >> (fromFrac - toFrac);
            }
            else
            {
                return static_cast<returnType>((val + (1 << (fromFrac - toFrac)) - 1)) >> (fromFrac - toFrac);
            }
        }
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<RND::CONV>>
{
    template <typename T>
    inline static auto convert(T val)
    {
        using returnType = std::conditional_t<std::is_signed_v<T>, long long int, unsigned long long int>;
        if constexpr (fromFrac <= toFrac)
        {
            return static_cast<returnType>(val) << (fromFrac - toFrac);
        }
        else
        {
            if constexpr (std::is_signed_v<T>)
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
            else
            {
                static constexpr unsigned long long int mask = 1 << (fromFrac - toFrac);
                unsigned long long int floor = val & mask;
                unsigned long long int ceil = floor + (1 << (fromFrac - toFrac));

                if (floor + ceil == val << 1)
                {
                    if (floor & mask)
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
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<TRN::TCPL>>
{
    template <typename T>
    inline static auto convert(T val)
    {
        using returnType = std::conditional_t<std::is_signed_v<T>, long long int, unsigned long long int>;

        if constexpr (fromFrac > toFrac)
        {
            return static_cast<returnType>(val) >> (fromFrac - toFrac);
        }
        else
        {
            return static_cast<returnType>(val) << (toFrac - fromFrac);
        }
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<TRN::SMGN>>
{
    template <typename T>
    inline static auto convert(T val)
    {
        using returnType = std::conditional_t<std::is_signed_v<T>, long long int, unsigned long long int>;

        if constexpr (fromFrac < toFrac)
        {
            return static_cast<returnType>(val) << (toFrac - fromFrac);
        }
        else
        {
            if (val >= 0)
            {
                return static_cast<returnType>(val) >> (fromFrac - toFrac);
            }
            else
            {
                return -((-static_cast<returnType>(val)) >> (fromFrac - toFrac));
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

template <typename T>
concept fracConvertedT = std::is_same_v<T, long long int> || std::is_same_v<T, unsigned long long int>;

template <int toInt, int toFrac, bool toIsSigned>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<SAT::TCPL>>
{
    template <typename T>
        requires fracConvertedT<T>
    inline static auto convert(T val) -> std::conditional_t<std::is_signed_v<T>, int, unsigned int>
    {
        static constexpr auto maxVal = static_cast<T>((1ULL << (toInt + toFrac)) - 1);
        static constexpr auto minVal = static_cast<T>(toIsSigned ? -maxVal - 1 : 0);

        const auto clampedVal = std::min(std::max(val, minVal), maxVal);

        return static_cast<std::conditional_t<std::is_signed_v<T>, int, unsigned int>>(clampedVal);
    }
};

template <int toInt, int toFrac, bool toIsSigned>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<SAT::ZERO>>
{

    template <typename T>
        requires fracConvertedT<T>
    inline static auto convert(T val)
    {
        static constexpr auto maxVal = static_cast<T>((1ULL << (toInt + toFrac)) - 1);
        static constexpr auto minVal = static_cast<T>(toIsSigned ? -maxVal - 1 : 0);

        if (val > maxVal || val < minVal)
        {
            return 0;
        }
        return static_cast<std::conditional_t<std::is_signed_v<T>, int, unsigned int>>(val);
    }
};

template <int toInt, int toFrac, bool toIsSigned>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<SAT::SMGN>>
{

    template <typename T>
        requires fracConvertedT<T>
    inline static auto convert(T val)
    {
        static constexpr auto maxVal = static_cast<T>((1ULL << (toInt + toFrac)) - 1);
        static constexpr auto minVal = static_cast<T>(toIsSigned ? -maxVal - 1 : 0);

        const auto clampedVal = std::min(std::max(val, minVal + 1), maxVal);

        return static_cast<std::conditional_t<std::is_signed_v<T>, int, unsigned int>>(clampedVal);
    }
};

template <int toInt, int toFrac, bool toIsSigned>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<WRP::TCPL>>
{

    template <typename T>
        requires fracConvertedT<T>
    inline static auto convert(T val) -> std::conditional_t<toIsSigned, int, unsigned int>
    {

        if constexpr (toIsSigned)
        {
            // the last toInt + toFrac bits are the value bits
            static constexpr unsigned long long int mask = (1ULL << (toInt + toFrac)) - 1;

            // judge the sign bit, which is the last toInt + toFrac + 1 bit
            long long int lastBits = val & mask;

            static constexpr unsigned long long int mask2 = 1ULL << (toInt + toFrac);

            if (val & mask2)
            {
                return -((~(lastBits - 1)) & mask);
            }
            else
            {
                return (lastBits & mask);
            }
        }
        else
        {
            constexpr unsigned long long int mask = (1ULL << (toInt + toFrac)) - 1;
            return static_cast<unsigned int>(val & mask);
        }
    }
};

// template <int toInt, int toFrac, bool toIsSigned, auto N>
// struct intConvert<toInt, toFrac, toIsSigned, OfMode<WRP::TCPL_SAT<N>>>
// {

//     template <typename T>
//         requires fracConvertedT<T>
//     inline static auto convert(T val) -> std::conditional_t<toIsSigned, int, unsigned int>
//     {

//         if constexpr (N == 1)
//         {
//             constexpr unsigned long long int mask = (1ULL << (toInt + toFrac)) - 1;
//             if (val>0)
//             {
//                 return static_cast<std::conditional_t<toIsSigned, int, unsigned int>>(val & mask);
//             }
//             else
//             {

//             }

//         }
//         return 0;
//     }
// };

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

template <typename... Args>
class apFixed
{
public:
    using QuM = tagTypeExtractor<QuMode<defaultQuMode>, Args...>::type;
    using OfM = tagTypeExtractor<OfMode<defaultOfMode>, Args...>::type;
    inline static constexpr auto intB = tagValueExtractor<intBits<defaultIntBits>, Args...>::value;
    inline static constexpr auto fracB = tagValueExtractor<fracBits<defaultFracBits>, Args...>::value;
    inline static constexpr auto isS = tagValueExtractor<isSigned<defaultIsSigned>, Args...>::value;

    static_assert(intB + fracB <= (isS ? 31 : 32), "The sum of intBits and fracBits exceeds the total number of bits");

    using dataType = std::conditional_t<isS, int, unsigned int>;
    dataType data;

    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr apFixed(T val)
    {
        data = val * (1 << fracB);
    }

    constexpr apFixed() : data(0) {}
    constexpr apFixed(dataType val, DirectAssignTag) : data(val) {}

    void display(std::string name = "")
    {
        if (name != "")
        {
            std::cout << name << " :";
        }
        std::cout << std::endl;
        std::cout << "Binary: " << std::bitset<intB + fracB>(data) << std::endl;
        std::cout << "Hex: " << std::hex << data << std::dec << std::endl;
        std::cout << "Decimal: " << static_cast<double>(data) / (1 << fracB) << std::endl;
    }

    template <typename... fromArgs>
    inline constexpr apFixed &operator=(const apFixed<fromArgs...> &rhs)
    {
        static constexpr auto fromInt = tagValueExtractor<intBits<defaultIntBits>, fromArgs...>::value;
        static constexpr auto fromFrac = tagValueExtractor<fracBits<defaultFracBits>, fromArgs...>::value;
        static constexpr auto fromIsSigned = tagValueExtractor<isSigned<defaultIsSigned>, fromArgs...>::value;

        if constexpr (fromInt == intB && fromFrac == fracB && fromIsSigned == isS)
        {
            data = rhs.data;
        }
        else
        {
            data = intConvert<intB, fracB, isS, OfMode<OfM>>::convert(fracConvert<fromFrac, fracB, QuMode<QuM>>::convert(rhs.data));
        }
        return *this;
    }

    template <typename... fromArgs>
    inline constexpr bool operator==(const apFixed<fromArgs...> &&rhs) const
    {
        static constexpr auto fromInt = tagValueExtractor<intBits<defaultIntBits>, fromArgs...>::value;
        static constexpr auto fromFrac = tagValueExtractor<fracBits<defaultFracBits>, fromArgs...>::value;
        static constexpr auto fromIsSigned = tagValueExtractor<isSigned<defaultIsSigned>, fromArgs...>::value;

        if constexpr (fromInt == intB && fromFrac == fracB && fromIsSigned == isS)
        {
            return data == rhs.data;
        }
        else
        {
            return false;
        }
    }

    template <typename... fromArgs>
    inline constexpr bool operator!=(const apFixed<fromArgs...> &&rhs) const
    {
        static constexpr auto fromInt = tagValueExtractor<intBits<defaultIntBits>, fromArgs...>::value;
        static constexpr auto fromFrac = tagValueExtractor<fracBits<defaultFracBits>, fromArgs...>::value;
        static constexpr auto fromIsSigned = tagValueExtractor<isSigned<defaultIsSigned>, fromArgs...>::value;

        if constexpr (fromInt == intB && fromFrac == fracB && fromIsSigned == isS)
        {
            return data != rhs.data;
        }
        else
        {
            return true;
        }
    }
};

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto QuMul(const apFixed<fromArgs1...> f1, const apFixed<fromArgs2...> f2)
{
    static constexpr auto fromInt1 = tagValueExtractor<intBits<defaultIntBits>, fromArgs1...>::value;
    static constexpr auto fromInt2 = tagValueExtractor<intBits<defaultIntBits>, fromArgs2...>::value;
    static constexpr auto fromFrac1 = tagValueExtractor<fracBits<defaultFracBits>, fromArgs1...>::value;
    static constexpr auto fromFrac2 = tagValueExtractor<fracBits<defaultFracBits>, fromArgs2...>::value;

    static constexpr auto toInt = tagValueExtractor<intBits<std::max(fromInt1, fromInt2)>, toArgs...>::value;
    static constexpr auto toFrac = tagValueExtractor<fracBits<std::max(fromFrac1, fromFrac2)>, toArgs...>::value;
    static constexpr auto toIsSigned = tagValueExtractor<isSigned<defaultIsSigned>, toArgs...>::value;
    using toQuMode = tagTypeExtractor<QuMode<defaultQuMode>, toArgs...>::type;
    using toOfMode = tagTypeExtractor<OfMode<defaultOfMode>, toArgs...>::type;

    auto fullProduct = static_cast<std::conditional_t<toIsSigned, long long, unsigned long long>>(f1.data) * f2.data;
    auto fracProduct = fracConvert<fromFrac1 + fromFrac2, toFrac, QuMode<toQuMode>>::convert(fullProduct);
    auto intProduct = intConvert<toInt, toFrac, toIsSigned, OfMode<toOfMode>>::convert(fracProduct);

    return apFixed<intBits<toInt>,
                   fracBits<toFrac>,
                   QuMode<toQuMode>,
                   OfMode<toOfMode>,
                   isSigned<toIsSigned>>(intProduct, DirectAssignTag{});
}

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto QuAdd(const apFixed<fromArgs1...> f1, const apFixed<fromArgs2...> f2)
{
    static constexpr auto fromInt1 = tagValueExtractor<intBits<defaultIntBits>, fromArgs1...>::value;
    static constexpr auto fromInt2 = tagValueExtractor<intBits<defaultIntBits>, fromArgs2...>::value;
    static constexpr auto fromFrac1 = tagValueExtractor<fracBits<defaultFracBits>, fromArgs1...>::value;
    static constexpr auto fromFrac2 = tagValueExtractor<fracBits<defaultFracBits>, fromArgs2...>::value;

    static constexpr auto toInt = tagValueExtractor<intBits<std::max(fromInt1, fromInt2)>, toArgs...>::value;
    static constexpr auto toFrac = tagValueExtractor<fracBits<std::max(fromFrac1, fromFrac2)>, toArgs...>::value;
    static constexpr auto toIsSigned = tagValueExtractor<isSigned<defaultIsSigned>, toArgs...>::value;
    using toQuMode = tagTypeExtractor<QuMode<defaultQuMode>, toArgs...>::type;
    using toOfMode = tagTypeExtractor<OfMode<defaultOfMode>, toArgs...>::type;

    static constexpr int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
    static constexpr int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;

    auto fullSum = static_cast<long long int>(f1.data << shiftA) + static_cast<long long int>(f2.data << shiftB);

    auto fracSum = fracConvert<std::max(fromFrac1, fromFrac2), toFrac, QuMode<toQuMode>>::convert(fullSum);

    auto intSum = intConvert<toInt, toFrac, toIsSigned, OfMode<toOfMode>>::convert(fracSum);

    return apFixed<intBits<toInt>,
                   fracBits<toFrac>,
                   QuMode<toQuMode>,
                   OfMode<toOfMode>,
                   isSigned<toIsSigned>>(intSum, DirectAssignTag{});
}

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto QuDiv(const apFixed<fromArgs1...> f1, const apFixed<fromArgs2...> f2)
{
    static constexpr auto fromInt1 = tagValueExtractor<intBits<defaultIntBits>, fromArgs1...>::value;
    static constexpr auto fromInt2 = tagValueExtractor<intBits<defaultIntBits>, fromArgs2...>::value;
    static constexpr auto fromFrac1 = tagValueExtractor<fracBits<defaultFracBits>, fromArgs1...>::value;
    static constexpr auto fromFrac2 = tagValueExtractor<fracBits<defaultFracBits>, fromArgs2...>::value;

    static constexpr auto toInt = tagValueExtractor<intBits<std::max(fromInt1, fromInt2)>, toArgs...>::value;
    static constexpr auto toFrac = tagValueExtractor<fracBits<std::max(fromFrac1, fromFrac2)>, toArgs...>::value;
    static constexpr auto toIsSigned = tagValueExtractor<isSigned<defaultIsSigned>, toArgs...>::value;
    using toQuMode = tagTypeExtractor<QuMode<defaultQuMode>, toArgs...>::type;
    using toOfMode = tagTypeExtractor<OfMode<defaultOfMode>, toArgs...>::type;

    static constexpr int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
    static constexpr int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;

    auto fullQuotient = (static_cast<long long int>(f1.data) << shiftA << toFrac) / (static_cast<long long int>(f2.data) << shiftB);
    auto fracQuotient = fracConvert<fromFrac1, toFrac, QuMode<toQuMode>>::convert(fullQuotient);
    auto intQuotient = intConvert<toInt, toFrac, toIsSigned, OfMode<toOfMode>>::convert(fracQuotient);

    return apFixed<intBits<toInt>,
                   fracBits<toFrac>,
                   QuMode<toQuMode>,
                   OfMode<toOfMode>,
                   isSigned<toIsSigned>>(intQuotient, DirectAssignTag{});
}

 
template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto QuSub(const apFixed<fromArgs1...> f1, const apFixed<fromArgs2...> f2)
{
    static constexpr auto fromInt1 = tagValueExtractor<intBits<defaultIntBits>, fromArgs1...>::value;
    static constexpr auto fromInt2 = tagValueExtractor<intBits<defaultIntBits>, fromArgs2...>::value;
    static constexpr auto fromFrac1 = tagValueExtractor<fracBits<defaultFracBits>, fromArgs1...>::value;
    static constexpr auto fromFrac2 = tagValueExtractor<fracBits<defaultFracBits>, fromArgs2...>::value;

    static constexpr auto toInt = tagValueExtractor<intBits<std::max(fromInt1, fromInt2)>, toArgs...>::value;
    static constexpr auto toFrac = tagValueExtractor<fracBits<std::max(fromFrac1, fromFrac2)>, toArgs...>::value;
    static constexpr auto toIsSigned = tagValueExtractor<isSigned<defaultIsSigned>, toArgs...>::value;
    using toQuMode = tagTypeExtractor<QuMode<defaultQuMode>, toArgs...>::type;
    using toOfMode = tagTypeExtractor<OfMode<defaultOfMode>, toArgs...>::type;

    static constexpr int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
    static constexpr int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;

    auto fullSum = static_cast<long long int>(f1.data << shiftA) - static_cast<long long int>(f2.data << shiftB);

    auto fracSum = fracConvert<std::max(fromFrac1, fromFrac2), toFrac, QuMode<toQuMode>>::convert(fullSum);

    auto intSum = intConvert<toInt, toFrac, toIsSigned, OfMode<toOfMode>>::convert(fracSum);

    return apFixed<intBits<toInt>,
                   fracBits<toFrac>,
                   QuMode<toQuMode>,
                   OfMode<toOfMode>,
                   isSigned<toIsSigned>>(intSum, DirectAssignTag{});
}


































