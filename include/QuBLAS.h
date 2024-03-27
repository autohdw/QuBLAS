#pragma once

#include <type_traits>
#include <iostream>
#include <concepts>
#include <bitset>
#include <array>
#include <stdexcept>
#include <cmath>
#include <vector>

// ------------------- tagExtractor -------------------

template <typename Tag, typename... Args>
struct tagExtractor;

// 类型未能匹配，最终返回默认值
template <template <typename> class Tag, typename T>
struct tagExtractor<Tag<T>>
{
    using type = T;
};

// 类型未能匹配，最终返回默认值，多个参数版本
template <template <typename...> class Tag, typename... Args>
struct tagExtractor<Tag<Args...>>
{
    using type = std::tuple<Args...>;
};

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
    using type = std::tuple<Args2...>;
};

// 匹配失败，类型不符，继续递归
template <typename Tag, typename Tag2, typename... Args>
struct tagExtractor<Tag, Tag2, Args...> : tagExtractor<Tag, Args...>
{
};

// ------------------- concept -------------------

template<typename T, typename... Types>
concept within = (std::is_same_v<T, Types> || ...);

template<typename T>
concept longlongInt = within<T, long long int, unsigned long long int>;

template<typename T>
concept shortInt = within<T, int, unsigned int>;

template<typename T>
concept allInt = longlongInt<T> || shortInt<T>;

// ------------------- shifter -------------------
template <int shift>
struct shifter
{
    template <typename T>
        requires allInt<T>
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
        requires allInt<T>
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
        requires shortInt<T>
    inline static double output(T val)
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

    template <typename T, typename returnType>
        requires std::is_arithmetic_v<T> && shortInt<returnType>
    inline static returnType input(T val)
    {
        if constexpr (shift >= 0)
        {
            return static_cast<returnType>(static_cast<double>(val) * (1 << shift));
        }
        else
        {
            return static_cast<returnType>(static_cast<double>(val) / (1 << (-shift)));
        }
    }
};

// ------------------- apFixed -------------------

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
            return static_cast<returnType>(val) << (toFrac - fromFrac);
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
            return static_cast<returnType>(val) << (toFrac - fromFrac);
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
            return static_cast<returnType>(val) << (toFrac - fromFrac);
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
            return static_cast<returnType>(val) << (toFrac - fromFrac);
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
            return static_cast<returnType>(val) << (toFrac - fromFrac);
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

        return shifter<fromFrac - toFrac>::shiftRight(static_cast<returnType>(val));
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

template <int toInt, int toFrac, bool toIsSigned>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<SAT::TCPL>>
{
    template <typename T>
        requires longlongInt<T>
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
        requires longlongInt<T>
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
        requires longlongInt<T>
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
        requires longlongInt<T>
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


template <int toInt, int toFrac, bool toIsSigned, auto N>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<WRP::TCPL_SAT<N>>>
{
    template <typename T>
        requires longlongInt<T>
    inline static auto convert(T val) -> std::conditional_t<toIsSigned, int, unsigned int>
    {
        static_assert(false, "Not implemented yet");
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

template <typename... Args>
class apFixed
{
public:
    using QuM = tagExtractor<QuMode<defaultQuMode>, Args...>::type;
    using OfM = tagExtractor<OfMode<defaultOfMode>, Args...>::type;
    inline static constexpr auto intB = tagExtractor<intBits<defaultIntBits>, Args...>::value;
    inline static constexpr auto fracB = tagExtractor<fracBits<defaultFracBits>, Args...>::value;
    inline static constexpr auto isS = tagExtractor<isSigned<defaultIsSigned>, Args...>::value;

    static_assert(intB + fracB <= (isS ? 31 : 32), "The sum of intBits and fracBits exceeds the total number of bits");

    static_assert(intB + fracB > 0, "The sum of intBits and fracBits must be greater than 0");

    using dataType = std::conditional_t<isS, int, unsigned int>;
    dataType data;

    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr apFixed(T val)
    {
        data = shifter<fracB>::template input<T, dataType>(val);
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

        std::cout << "Decimal: " << shifter<fracB>::output(data) << std::endl;
    }

    template <typename... fromArgs>
    inline constexpr apFixed &operator=(const apFixed<fromArgs...> &rhs)
    {
        static constexpr auto fromInt = tagExtractor<intBits<defaultIntBits>, fromArgs...>::value;
        static constexpr auto fromFrac = tagExtractor<fracBits<defaultFracBits>, fromArgs...>::value;
        static constexpr auto fromIsSigned = tagExtractor<isSigned<defaultIsSigned>, fromArgs...>::value;

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
        static constexpr auto fromInt = tagExtractor<intBits<defaultIntBits>, fromArgs...>::value;
        static constexpr auto fromFrac = tagExtractor<fracBits<defaultFracBits>, fromArgs...>::value;
        static constexpr auto fromIsSigned = tagExtractor<isSigned<defaultIsSigned>, fromArgs...>::value;

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
        static constexpr auto fromInt = tagExtractor<intBits<defaultIntBits>, fromArgs...>::value;
        static constexpr auto fromFrac = tagExtractor<fracBits<defaultFracBits>, fromArgs...>::value;
        static constexpr auto fromIsSigned = tagExtractor<isSigned<defaultIsSigned>, fromArgs...>::value;

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

template <typename... toArgs>
struct Qmul_s
{
    template <typename... fromArgs1, typename... fromArgs2>
    inline static constexpr auto apply(const apFixed<fromArgs1...> f1, const apFixed<fromArgs2...> f2)
    {
        static constexpr auto fromInt1 = tagExtractor<intBits<defaultIntBits>, fromArgs1...>::value;
        static constexpr auto fromInt2 = tagExtractor<intBits<defaultIntBits>, fromArgs2...>::value;
        static constexpr auto fromFrac1 = tagExtractor<fracBits<defaultFracBits>, fromArgs1...>::value;
        static constexpr auto fromFrac2 = tagExtractor<fracBits<defaultFracBits>, fromArgs2...>::value;

        static constexpr auto toInt = tagExtractor<intBits<std::max(fromInt1, fromInt2)>, toArgs...>::value;
        static constexpr auto toFrac = tagExtractor<fracBits<std::max(fromFrac1, fromFrac2)>, toArgs...>::value;
        static constexpr auto toIsSigned = tagExtractor<isSigned<defaultIsSigned>, toArgs...>::value;
        using toQuMode = tagExtractor<QuMode<defaultQuMode>, toArgs...>::type;
        using toOfMode = tagExtractor<OfMode<defaultOfMode>, toArgs...>::type;

        auto fullProduct = static_cast<std::conditional_t<toIsSigned, long long, unsigned long long>>(f1.data) * f2.data;
        auto fracProduct = fracConvert<fromFrac1 + fromFrac2, toFrac, QuMode<toQuMode>>::convert(fullProduct);
        auto intProduct = intConvert<toInt, toFrac, toIsSigned, OfMode<toOfMode>>::convert(fracProduct);

        return apFixed<intBits<toInt>,
                       fracBits<toFrac>,
                       QuMode<toQuMode>,
                       OfMode<toOfMode>,
                       isSigned<toIsSigned>>(intProduct, DirectAssignTag{});
    }
};

template <typename... toArgs>
struct Qmul_s<std::tuple<toArgs...>> : Qmul_s<toArgs...>
{
};

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto Qmul(const apFixed<fromArgs1...> f1, const apFixed<fromArgs2...> f2)
{
    return Qmul_s<toArgs...>::apply(f1, f2);
}

template <typename... toArgs>
struct Qadd_s
{
    template <typename... fromArgs1, typename... fromArgs2>
    inline static constexpr auto apply(const apFixed<fromArgs1...> f1, const apFixed<fromArgs2...> f2)
    {
        static constexpr auto fromInt1 = tagExtractor<intBits<defaultIntBits>, fromArgs1...>::value;
        static constexpr auto fromInt2 = tagExtractor<intBits<defaultIntBits>, fromArgs2...>::value;
        static constexpr auto fromFrac1 = tagExtractor<fracBits<defaultFracBits>, fromArgs1...>::value;
        static constexpr auto fromFrac2 = tagExtractor<fracBits<defaultFracBits>, fromArgs2...>::value;

        static constexpr auto toInt = tagExtractor<intBits<std::max(fromInt1, fromInt2)>, toArgs...>::value;
        static constexpr auto toFrac = tagExtractor<fracBits<std::max(fromFrac1, fromFrac2)>, toArgs...>::value;
        static constexpr auto toIsSigned = tagExtractor<isSigned<defaultIsSigned>, toArgs...>::value;
        using toQuMode = tagExtractor<QuMode<defaultQuMode>, toArgs...>::type;
        using toOfMode = tagExtractor<OfMode<defaultOfMode>, toArgs...>::type;

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
};

template <typename... toArgs>
struct Qadd_s<std::tuple<toArgs...>> : Qadd_s<toArgs...>
{
};

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto Qadd(const apFixed<fromArgs1...> f1, const apFixed<fromArgs2...> f2)
{
    return Qadd_s<toArgs...>::apply(f1, f2);
}

template <typename... toArgs>
struct Qdiv_s
{
    template <typename... fromArgs1, typename... fromArgs2>
    inline static constexpr auto apply(const apFixed<fromArgs1...> f1, const apFixed<fromArgs2...> f2)
    {
        static constexpr auto fromInt1 = tagExtractor<intBits<defaultIntBits>, fromArgs1...>::value;
        static constexpr auto fromInt2 = tagExtractor<intBits<defaultIntBits>, fromArgs2...>::value;
        static constexpr auto fromFrac1 = tagExtractor<fracBits<defaultFracBits>, fromArgs1...>::value;
        static constexpr auto fromFrac2 = tagExtractor<fracBits<defaultFracBits>, fromArgs2...>::value;

        static constexpr auto toInt = tagExtractor<intBits<std::max(fromInt1, fromInt2)>, toArgs...>::value;
        static constexpr auto toFrac = tagExtractor<fracBits<std::max(fromFrac1, fromFrac2)>, toArgs...>::value;
        static constexpr auto toIsSigned = tagExtractor<isSigned<defaultIsSigned>, toArgs...>::value;
        using toQuMode = tagExtractor<QuMode<defaultQuMode>, toArgs...>::type;
        using toOfMode = tagExtractor<OfMode<defaultOfMode>, toArgs...>::type;

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
};

template <typename... toArgs>
struct Qdiv_s<std::tuple<toArgs...>> : Qdiv_s<toArgs...>
{
};

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto Qdiv(const apFixed<fromArgs1...> f1, const apFixed<fromArgs2...> f2)
{
    return Qdiv_s<toArgs...>::apply(f1, f2);
}

template <typename... toArgs>
struct Qsub_s
{
    template <typename... fromArgs1, typename... fromArgs2>
    inline static constexpr auto apply(const apFixed<fromArgs1...> f1, const apFixed<fromArgs2...> f2)
    {
        static constexpr auto fromInt1 = tagExtractor<intBits<defaultIntBits>, fromArgs1...>::value;
        static constexpr auto fromInt2 = tagExtractor<intBits<defaultIntBits>, fromArgs2...>::value;
        static constexpr auto fromFrac1 = tagExtractor<fracBits<defaultFracBits>, fromArgs1...>::value;
        static constexpr auto fromFrac2 = tagExtractor<fracBits<defaultFracBits>, fromArgs2...>::value;

        static constexpr auto toInt = tagExtractor<intBits<std::max(fromInt1, fromInt2)>, toArgs...>::value;
        static constexpr auto toFrac = tagExtractor<fracBits<std::max(fromFrac1, fromFrac2)>, toArgs...>::value;
        static constexpr auto toIsSigned = tagExtractor<isSigned<defaultIsSigned>, toArgs...>::value;
        using toQuMode = tagExtractor<QuMode<defaultQuMode>, toArgs...>::type;
        using toOfMode = tagExtractor<OfMode<defaultOfMode>, toArgs...>::type;

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
};

template <typename... toArgs>
struct Qsub_s<std::tuple<toArgs...>> : Qsub_s<toArgs...>
{
};

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto Qsub(const apFixed<fromArgs1...> f1, const apFixed<fromArgs2...> f2)
{
    return Qsub_s<toArgs...>::apply(f1, f2);
}

template <typename apFixedType, size_t N>
class apFixedVec
{
public:
    std::array<apFixedType, N> data;

    apFixedVec() = default;

    apFixedVec(std::initializer_list<apFixedType> init)
    {
        if (init.size() > N)
            throw std::invalid_argument("Initializer list larger than vector size.");
        std::copy(init.begin(), init.end(), data.begin());
    }

    inline constexpr apFixedType &operator[](size_t index)
    {
        return data[index];
    }

    inline constexpr const apFixedType &operator[](size_t index) const
    {
        return data[index];
    }

    inline constexpr size_t size() const
    {
        return N;
    }

    void display(std::string name = "")
    {
        if (name != "")
        {
            std::cout << name << std::endl;
        }
        for (size_t i = 0; i < N; i++)
        {
            data[i].display();
        }
    }
};

template <typename apFixedType, size_t M, size_t N>
class apFixedMat
{
public:
    std::array<apFixedVec<apFixedType, N>, M> data;

    apFixedMat() = default;

    apFixedMat(std::initializer_list<apFixedType> init)
    {
        for (size_t i = 0; i < M; i++)
        {
            std::copy(init.begin() + i * N, init.begin() + (i + 1) * N, data[i].data.begin());
        }
    }

    inline constexpr apFixedVec<apFixedType, N> &operator[](size_t index)
    {
        return data[index];
    }

    inline constexpr const apFixedVec<apFixedType, N> &operator[](size_t index) const
    {
        return data[index];
    }

    void display(std::string name = "")
    {
        if (name != "")
        {
            std::cout << name << std::endl;
        }
        for (size_t i = 0; i < M; i++)
        {
            for (size_t j = 0; j < N; j++)
            {
                if (name != "")
                {
                    data[i][j].display();
                }
                else
                {
                    data[i][j].display(std::to_string(i) + " " + std::to_string(j) + " ");
                }
            }
            std::cout << std::endl;
        }
    }
};

// ------------------- Qgemul -------------------
template <bool Value = false>
struct QgemulTransposedA;

template <bool Value = false>
struct QgemulTransposedB;

template <typename... Args>
struct QgemulAddArgs;

template <typename... Args>
struct QgemulAddArgs<apFixed<Args...>> : QgemulAddArgs<Args...>
{
};

template <typename... Args>
struct QgemulMulArgs;

template <typename... Args>
struct QgemulMulArgs<apFixed<Args...>> : QgemulMulArgs<Args...>
{
};

template <typename... interiorArgs, typename... toArgs, typename... fromArgsA, typename... fromArgsB, size_t rowC, size_t colC, size_t rowA, size_t colA, size_t rowB, size_t colB>
void Qgemul(apFixedMat<apFixed<toArgs...>, rowC, colC> &C, const apFixedMat<apFixed<fromArgsA...>, rowA, colA> &A, const apFixedMat<apFixed<fromArgsB...>, rowB, colB> &B)
{
    static constexpr auto toInt = tagExtractor<intBits<defaultIntBits>, toArgs...>::value;
    static constexpr auto toFrac = tagExtractor<fracBits<defaultFracBits>, toArgs...>::value;
    static constexpr auto toIsSigned = tagExtractor<isSigned<defaultIsSigned>, toArgs...>::value;
    using toQuMode = tagExtractor<QuMode<defaultQuMode>, toArgs...>::type;
    using toOfMode = tagExtractor<OfMode<defaultOfMode>, toArgs...>::type;

    static constexpr auto fromIntA = tagExtractor<intBits<defaultIntBits>, fromArgsA...>::value;
    static constexpr auto fromFracA = tagExtractor<fracBits<defaultFracBits>, fromArgsA...>::value;

    static constexpr auto fromIntB = tagExtractor<intBits<defaultIntBits>, fromArgsB...>::value;
    static constexpr auto fromFracB = tagExtractor<fracBits<defaultFracBits>, fromArgsB...>::value;

    static constexpr auto isTransposedA = tagExtractor<QgemulTransposedA<false>, fromArgsA...>::value;
    static constexpr auto isTransposedB = tagExtractor<QgemulTransposedB<false>, fromArgsB...>::value;

    using addArgs = tagExtractor<QgemulAddArgs<>, interiorArgs...>::type;
    using mulArgs = tagExtractor<QgemulMulArgs<>, interiorArgs...>::type;

    static_assert((!isTransposedA && !isTransposedB && (colA == rowB && rowA == rowC && colB == colC)) || (!isTransposedA && isTransposedB && (colA == colB && rowA == rowC && rowB == colC)) || (isTransposedA && !isTransposedB && (rowA == rowB && colA == rowC && colB == colC)) || (isTransposedA && isTransposedB && (rowA == colB && colA == rowC && rowB == colC)), "Size mismatch when calling Qgemul");

    for (size_t i = 0; i < rowC; i++)
    {
        for (size_t j = 0; j < colC; j++)
        {
            apFixed<addArgs> sum = 0;
            for (size_t k = 0; k < (isTransposedA ? rowA : colA); k++)
            {
                auto a = isTransposedA ? A[k][i] : A[i][k];
                auto b = isTransposedB ? B[j][k] : B[k][j];

                sum = Qadd_s<addArgs>::apply(sum, Qmul_s<mulArgs>::apply(a, b));
            }
            C[i][j] = sum;
        }
    }
}
