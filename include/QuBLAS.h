#pragma once

#include <any>
#include <array>
#include <bitset>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <iostream>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <type_traits>
#include <vector>

// ------------------- debug -------------------
constexpr bool debug = false;

// ------------------- TypeList -------------------

template <typename... Types>
struct TypeList
{
    static inline constexpr size_t size = sizeof...(Types);
};

// 特化，用于提取头部和尾部类型（通过继承获得）
template <typename Head, typename... Tail>
struct TypeList<Head, Tail...>
{
    static inline constexpr size_t size = sizeof...(Tail) + 1;
    using head = Head;              // 当前头部类型
    using tail = TypeList<Tail...>; // 余下部分形成的TypeList
};

// 基本定义
template <int index, typename List>
struct TypeAt_s;

// 特化：当下标为0时，直接返回头部类型
template <typename Head, typename... Tail>
struct TypeAt_s<0, TypeList<Head, Tail...>>
{
    using Result = Head;
};

// 特化：当下标大于0时，递归地移除类型列表的头部类型并对剩余列表和下标-1进行求解
template <int index, typename Head, typename... Tail>
struct TypeAt_s<index, TypeList<Head, Tail...>>
{
    static_assert(index < sizeof...(Tail) + 1, "Index out of bounds");
    using Result = typename TypeAt_s<index - 1, TypeList<Tail...>>::Result;
};

template <size_t N, typename List>
using TypeAt = typename TypeAt_s<N, List>::Result;

// 辅助类型
// 基础判断，非TypeList
template <typename T>
struct is_typelist : std::false_type
{};

// 特化，是TypeList
template <typename... Types>
struct is_typelist<TypeList<Types...>> : std::true_type
{};

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
    using type = TypeList<Args...>;
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
    using type = TypeList<Args2...>;
};

// 特别地，有可能会是一个复合类型。这个情况应该只会出现在BLAS函数中的复合Tag中，用于拆封传入的apFixed<...>类型
template <template <typename...> class Tag, typename... Args, typename... Args2, typename... Args3, template <typename...> class innerWrapper>
    requires(!std::is_same_v<innerWrapper<Args2...>, TypeList<Args2...>>)
struct tagExtractor<Tag<Args...>, Tag<innerWrapper<Args2...>>, Args3...>
{
    using type = TypeList<Args2...>;
};

// 也很特别的，apFixed<...>可能传入了一个tuple，这个时候需要拆封tuple
template <typename Tag, typename... Args>
struct tagExtractor<Tag, TypeList<Args...>> : tagExtractor<Tag, Args...>
{
};

// 匹配失败，类型不符，继续递归
template <typename Tag, typename Tag2, typename... Args>
struct tagExtractor<Tag, Tag2, Args...> : tagExtractor<Tag, Args...>
{
};

// ------------------- concept -------------------

template <typename T, typename... Types>
concept within = (std::is_same_v<T, Types> || ...);

template <typename T>
concept longlongInt = within<T, long long int, unsigned long long int>;

template <typename T>
concept shortInt = within<T, int, unsigned int>;

template <typename T>
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
    inline static constexpr returnType input(T val)
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
        throw std::runtime_error("Not implemented yet");
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

    inline constexpr double output()
    {
        return shifter<fracB>::output(data);
    }

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

template <typename T>
struct is_apFixed : std::false_type
{};

template <typename... Types>
struct is_apFixed<apFixed<Types...>> : std::true_type
{};

// ------------------- Basic Operations -------------------

// a strucrt to merge two apFixed types
template <typename... Args>
struct apFixedMerge;

template <typename... toArgs, typename... Args1, typename... Args2>
struct apFixedMerge<apFixed<toArgs...>, apFixed<Args1...>, apFixed<Args2...>>
{
    static constexpr auto fromInt1 = apFixed<Args1...>::intB;
    static constexpr auto fromInt2 = apFixed<Args2...>::intB;
    static constexpr auto fromFrac1 = apFixed<Args1...>::fracB;
    static constexpr auto fromFrac2 = apFixed<Args2...>::fracB;

    using fromQuMode1 = typename apFixed<Args1...>::QuM;
    using fromQuMode2 = typename apFixed<Args2...>::QuM;
    using fromOfMode1 = typename apFixed<Args1...>::OfM;
    using fromOfMode2 = typename apFixed<Args2...>::OfM;

    using fromQuMode = std::conditional_t<std::is_same_v<fromQuMode1, fromQuMode2>, fromQuMode1, defaultQuMode>;
    using fromOfMode = std::conditional_t<std::is_same_v<fromOfMode1, fromOfMode2>, fromOfMode1, defaultOfMode>;

    static constexpr auto toInt = tagExtractor<intBits<std::max(fromInt1, fromInt2)>, toArgs...>::value;
    static constexpr auto toFrac = tagExtractor<fracBits<std::max(fromFrac1, fromFrac2)>, toArgs...>::value;
    static constexpr auto toIsSigned = tagExtractor<isSigned<defaultIsSigned>, toArgs...>::value;
    using toQuMode = tagExtractor<QuMode<fromQuMode>, toArgs...>::type;
    using toOfMode = tagExtractor<OfMode<fromOfMode>, toArgs...>::type;

    static constexpr int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
    static constexpr int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;
};

template <typename... toArgs>
struct Qmul_s
{
    template <typename... fromArgs1, typename... fromArgs2>
    inline static constexpr auto apply(const apFixed<fromArgs1...> f1, const apFixed<fromArgs2...> f2)
    {
        using merger = apFixedMerge<apFixed<toArgs...>, apFixed<fromArgs1...>, apFixed<fromArgs2...>>;

        auto fullProduct = static_cast<std::conditional_t<merger::toIsSigned, long long, unsigned long long>>(f1.data) * f2.data;
        auto fracProduct = fracConvert<merger::fromFrac1 + merger::fromFrac2, merger::toFrac, QuMode<typename merger::toQuMode>>::convert(fullProduct);
        auto intProduct = intConvert<merger::toInt, merger::toFrac, merger::toIsSigned, OfMode<typename merger::toOfMode>>::convert(fracProduct);

        return apFixed<intBits<merger::toInt>,
                       fracBits<merger::toFrac>,
                       QuMode<typename merger::toQuMode>,
                       OfMode<typename merger::toOfMode>,
                       isSigned<merger::toIsSigned>>(intProduct, DirectAssignTag{});
    }
};

template <template <typename...> class innerWrapper, typename... toArgs>
struct Qmul_s<innerWrapper<toArgs...>> : Qmul_s<toArgs...>
{
};

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto Qmul(const apFixed<fromArgs1...> f1, const apFixed<fromArgs2...> f2)
{
    return Qmul_s<toArgs...>::apply(f1, f2);
}

template <typename... fromArgs1, typename... fromArgs2>
inline constexpr auto operator*(const apFixed<fromArgs1...> &f1, const apFixed<fromArgs2...> &f2)
{
    return Qmul<>(f1, f2);
}

template <typename... toArgs>
struct Qadd_s
{
    template <typename... fromArgs1, typename... fromArgs2>
    inline static constexpr auto apply(const apFixed<fromArgs1...> f1, const apFixed<fromArgs2...> f2)
    {
        using merger = apFixedMerge<apFixed<toArgs...>, apFixed<fromArgs1...>, apFixed<fromArgs2...>>;

        auto fullSum = static_cast<long long int>(f1.data << merger::shiftA) + static_cast<long long int>(f2.data << merger::shiftB);

        auto fracSum = fracConvert<std::max(merger::fromFrac1, merger::fromFrac2), merger::toFrac, QuMode<typename merger::toQuMode>>::convert(fullSum);

        auto intSum = intConvert<merger::toInt, merger::toFrac, merger::toIsSigned, OfMode<typename merger::toOfMode>>::convert(fracSum);

        return apFixed<intBits<merger::toInt>,
                       fracBits<merger::toFrac>,
                       QuMode<typename merger::toQuMode>,
                       OfMode<typename merger::toOfMode>,
                       isSigned<merger::toIsSigned>>(intSum, DirectAssignTag{});
    }
};

template <template <typename...> class innerWrapper, typename... toArgs>
struct Qadd_s<innerWrapper<toArgs...>> : Qadd_s<toArgs...>
{
};

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto Qadd(const apFixed<fromArgs1...> f1, const apFixed<fromArgs2...> f2)
{
    return Qadd_s<toArgs...>::apply(f1, f2);
}

template <typename... fromArgs1, typename... fromArgs2>
inline constexpr auto operator+(const apFixed<fromArgs1...> &f1, const apFixed<fromArgs2...> &f2)
{
    return Qadd<>(f1, f2);
}

template <typename... toArgs>
struct Qdiv_s
{
    template <typename... fromArgs1, typename... fromArgs2>
    inline static constexpr auto apply(const apFixed<fromArgs1...> f1, const apFixed<fromArgs2...> f2)
    {
        using merger = apFixedMerge<apFixed<toArgs...>, apFixed<fromArgs1...>, apFixed<fromArgs2...>>;

        if (f2.data == 0)
        {
            return apFixed<intBits<merger::toInt>,
                           fracBits<merger::toFrac>,
                           QuMode<typename merger::toQuMode>,
                           OfMode<typename merger::toOfMode>,
                           isSigned<merger::toIsSigned>>(0, DirectAssignTag{});
        }

        auto fullQuotient = (static_cast<long long int>(f1.data) << merger::shiftA << merger::toFrac) / (static_cast<long long int>(f2.data) << merger::shiftB);
        auto intQuotient = intConvert<merger::toInt, merger::toFrac, merger::toIsSigned, OfMode<typename merger::toOfMode>>::convert(fullQuotient);

        return apFixed<intBits<merger::toInt>,
                       fracBits<merger::toFrac>,
                       QuMode<typename merger::toQuMode>,
                       OfMode<typename merger::toOfMode>,
                       isSigned<merger::toIsSigned>>(intQuotient, DirectAssignTag{});
    }
};

template <template <typename...> class innerWrapper, typename... toArgs>
struct Qdiv_s<innerWrapper<toArgs...>> : Qdiv_s<toArgs...>
{
};

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto Qdiv(const apFixed<fromArgs1...> f1, const apFixed<fromArgs2...> f2)
{
    return Qdiv_s<toArgs...>::apply(f1, f2);
}

template <typename... fromArgs1, typename... fromArgs2>
inline constexpr auto operator/(const apFixed<fromArgs1...> &f1, const apFixed<fromArgs2...> &f2)
{
    return Qdiv<>(f1, f2);
}

template <typename... toArgs>
struct Qsub_s
{
    template <typename... fromArgs1, typename... fromArgs2>
    inline static constexpr auto apply(const apFixed<fromArgs1...> f1, const apFixed<fromArgs2...> f2)
    {
        using merger = apFixedMerge<apFixed<toArgs...>, apFixed<fromArgs1...>, apFixed<fromArgs2...>>;

        auto fullSub = static_cast<long long int>(f1.data << merger::shiftA) - static_cast<long long int>(f2.data << merger::shiftB);

        auto fracSub = fracConvert<std::max(merger::fromFrac1, merger::fromFrac2), merger::toFrac, QuMode<typename merger::toQuMode>>::convert(fullSub);

        auto intSub = intConvert<merger::toInt, merger::toFrac, merger::toIsSigned, OfMode<typename merger::toOfMode>>::convert(fracSub);

        return apFixed<intBits<merger::toInt>,
                       fracBits<merger::toFrac>,
                       QuMode<typename merger::toQuMode>,
                       OfMode<typename merger::toOfMode>,
                       isSigned<merger::toIsSigned>>(intSub, DirectAssignTag{});
    }
};

template <template <typename...> class innerWrapper, typename... toArgs>
struct Qsub_s<innerWrapper<toArgs...>> : Qsub_s<toArgs...>
{
};

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto Qsub(const apFixed<fromArgs1...> f1, const apFixed<fromArgs2...> f2)
{
    return Qsub_s<toArgs...>::apply(f1, f2);
}

template <typename... fromArgs1, typename... fromArgs2>
inline constexpr auto operator-(const apFixed<fromArgs1...> &f1, const apFixed<fromArgs2...> &f2)
{
    return Qsub<>(f1, f2);
}

template <typename... fromArgs1>
inline constexpr auto operator-(const apFixed<fromArgs1...> &f1)
{

    return apFixed<fromArgs1...>(-f1.data, DirectAssignTag{});
}

template <typename... fromArgs>
inline constexpr auto Qabs(const apFixed<fromArgs...> &f1)
{
    return f1.data < 0 ? apFixed<fromArgs...>(-f1.data, DirectAssignTag{}) : f1;
}

// ------------------- Comparison -------------------
// seems dummy, maybe optimize later
template <typename... Args>
struct Qcmp_s;

template <typename... Args1, typename... Args2>
struct Qcmp_s<apFixed<Args1...>, apFixed<Args2...>>
{
    static constexpr auto fracBits1 = tagExtractor<fracBits<defaultFracBits>, Args1...>::value;
    static constexpr auto fracBits2 = tagExtractor<fracBits<defaultFracBits>, Args2...>::value;

    // the value to left shift for each number
    static constexpr auto shift1 = fracBits2 > fracBits1 ? fracBits2 - fracBits1 : 0;
    static constexpr auto shift2 = fracBits1 > fracBits2 ? fracBits1 - fracBits2 : 0;

    static constexpr auto apply(const apFixed<Args1...> &f1, const apFixed<Args2...> &f2)
    {
        return (f1.data << shift1) <=> (f2.data << shift2);
    }
};

template <typename... Args1, typename... Args2>
inline constexpr auto operator<=>(const apFixed<Args1...> &f1, const apFixed<Args2...> &f2)
{
    return Qcmp_s<apFixed<Args1...>, apFixed<Args2...>>::apply(f1, f2);
}

// ------------------- Vector and Matrix -------------------

template <size_t... dims>
struct dimList
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
    struct elemSizeForIndexTail
    {
        static inline constexpr size_t value = std::accumulate(dimArray.begin() + index2, dimArray.end(), 1, std::multiplies<size_t>());
    };

    // for example, dimList<2,2,3,4>
    // absoluteIndex<0,1,1,1> = 0*2*3*4 + 1*3*4 + 1*4 + 1 = 17
    template <size_t... index>
        requires(sizeof...(index) == dimSize)
    struct absoluteIndex_s
    {
        template <size_t loc, size_t... index2>
        struct compute;

        template <size_t loc, size_t firstIndex, size_t... indexLeft>
        struct compute<loc, firstIndex, indexLeft...>
        {
            static inline constexpr size_t value = firstIndex * elemSizeForIndexTail<loc + 1>::value + compute<loc + 1, indexLeft...>::value;
        };

        template <size_t firstIndex>
        struct compute<dimSize - 1, firstIndex>
        {
            static inline constexpr size_t value = firstIndex;
        };

        static inline constexpr size_t value = compute<0, index...>::value;
    };

    template <size_t... index>
        requires(sizeof...(index) == dimSize)
    using absoluteIndex = absoluteIndex_s<index...>::value;
};

// integrated vector and matrix
template <size_t... dims, typename... Args>
class apFixed<dimList<dims...>, apFixed<Args...>>
{
public:
    std::array<apFixed<Args...>, dimList<dims...>::elemSize> data;

    // initialize with a list of values
    apFixed(std::initializer_list<apFixed<Args...>> list)
    {
        if (list.size() != dimList<dims...>::elemSize)
        {
            throw std::runtime_error("The size of the list does not match the size of the matrix");
        }
        std::copy(list.begin(), list.end(), data.begin());
    }

    template <size_t... index>
    inline constexpr auto get()
    {
        return data[dimList<dims...>::template absoluteIndex_s<index...>::value];
        // return data[dimList<dims...>::template absoluteIndex<index...>];
    }

    template <typename... Ints>
        requires(sizeof...(Ints) == dimList<dims...>::dimSize)
    inline constexpr auto operator[](Ints... index)
    {
        // testing just return the sum of index
        return  data[(index+...)];
    }
};

template <size_t... dims>
class apFixed<dimList<dims...>> : public apFixed<dimList<dims...>, apFixed<>>
{
    using apFixed<dimList<dims...>, apFixed<>>::apFixed;
};