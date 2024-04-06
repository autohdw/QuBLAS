#pragma once

#include <any>
#include <array>
#include <bitset>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <iostream>
#include <memory>
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
// base version
template <size_t N, typename... Args>
class Qvec;

// specialization for pass in apFixedType
template <size_t N, typename apFixedType>
class Qvec<N, apFixedType>
{
public:
    std::array<apFixedType, N> data;

    Qvec() = default;

    Qvec(std::initializer_list<apFixedType> init)
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
        for (int i = 0; i < N; i++)
        {
            data[i].display();
        }
    }

    inline std::array<double, N> output()
    {
        std::array<double, N> output;
        for (int i = 0; i < N; i++)
        {
            output[i] = data[i].output();
        }
        return output;
    }
};

// specialization for pass in only N
template <size_t N>
class Qvec<N> : public Qvec<N, apFixed<>>
{
    // 委托构造函数
    using Qvec<N, apFixed<>>::Qvec;
};

// specialization for pass in TypeList

template <size_t N, typename... Types>
class Qvec<N, TypeList<Types...>>
{
    // not implemented yet
};

template <size_t M, size_t N, typename apFixedType = apFixed<>>
class Qmat
{
public:
    std::array<Qvec<N, apFixedType>, M> data;

    Qmat() = default;

    Qmat(std::initializer_list<apFixedType> init)
    {
        for (int i = 0; i < M; i++)
        {
            std::copy(init.begin() + i * N, init.begin() + (i + 1) * N, data[i].data.begin());
        }
    }

    inline constexpr Qvec<N, apFixedType> &operator[](size_t index)
    {
        return data[index];
    }

    inline constexpr const Qvec<N, apFixedType> &operator[](size_t index) const
    {
        return data[index];
    }

    void display(std::string name = "")
    {
        if (name != "")
        {
            std::cout << name << std::endl;
        }
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
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

    inline std::array<std::array<double, N>, M> output()
    {
        std::array<std::array<double, N>, M> output;
        for (int i = 0; i < M; i++)
        {
            output[i] = data[i].output();
        }
        return output;
    }
};

// ===================== BLAS =====================
// ------------------- Reducer -------------------
// it's not a standard BLAS operation, but exists in realistic ASIC design

template <std::size_t Alen, typename apFixedType>
struct Accumulator
{
    static inline Qvec<(Alen + 1) / 2, apFixedType> output;

    template <std::size_t... I, typename inputT>
    static inline void accumulate_impl(const Qvec<Alen, inputT> &input, std::index_sequence<I...>)
    {
        ((I * 2 + 1 < Alen
              ? output[I] = Qadd<apFixedType>(input[I * 2], input[I * 2 + 1])
              : output[I] = input[I * 2]),
         ...);
    }

    template <typename inputT>
    static inline void accumulate(const Qvec<Alen, inputT> &input)
    {
        accumulate_impl(input, std::make_index_sequence<(Alen + 1) / 2>{});
    }
};

template <std::size_t len, typename... Types>
struct Reducer;

template <std::size_t len, typename... Types>
struct Reducer<len, TypeList<Types...>>
{

    template <typename listLeft, typename vecT>
    static inline auto reduce_impl(const Qvec<len, vecT> &input)
    {

        if constexpr (len > 1)
        {
            static_assert(listLeft::size > 0, "The input TypeList does not have enough Types");
            using head = listLeft::head;
            using tail = listLeft::tail;
            Accumulator<len, head>::accumulate(input);
            return Reducer<(len + 1) / 2, tail>::reduce(Accumulator<len, head>::output);
        }
        else
        {
            return input[0];
        }
    }

    template <typename vecT>
    static inline auto reduce(const Qvec<len, vecT> &input)
    {
        return reduce_impl<TypeList<Types...>>(input);
    }
};

template <std::size_t len, typename... Types>
struct Reducer<len, apFixed<Types...>>
{
    template <typename vecT>
    static inline auto reduce_impl(const Qvec<len, vecT> &input)
    {

        if constexpr (len > 1)
        {
            Accumulator<len, apFixed<Types...>>::accumulate(input);
            return Reducer<(len + 1) / 2, apFixed<Types...>>::reduce(Accumulator<len, apFixed<Types...>>::output);
        }
        else
        {
            return input[0];
        }
    }

    template <typename vecT>
    static inline auto reduce(const Qvec<len, vecT> &input)
    {
        return reduce_impl(input);
    }
};

template <typename... Types, size_t len, typename vecTypes>
auto inline Qreduce(const Qvec<len, vecTypes> &input)
{
    if constexpr (sizeof...(Types) == 0)
    {
        // Qreduce()
        return Reducer<len, vecTypes>::reduce(input);
    }
    else
    {
        using FirstType = std::tuple_element_t<0, std::tuple<Types...>>;
        if constexpr (is_typelist<FirstType>::value)
        {
            // Qreduce<TypeList<...>>()
            return Reducer<len, FirstType>::reduce(input);
        }
        else if constexpr (is_apFixed<FirstType>::value)
        {
            if constexpr (sizeof...(Types) == 1)
            {
                // Qreduce<apFixed<...>>()
                return Reducer<len, FirstType>::reduce(input);
            }
            else
            {
                // Qreduce<apFixed<...>, apFixed<...>, ...>()
                return Reducer<len, TypeList<Types...>>::reduce(input);
            }
        }
        else
        {
            // Qreduce<intBits<...>, fracBits<...>, isSigned<...>, OfMode<...>>()
            return Reducer<len, apFixed<Types...>>::reduce(input);
        }
    }
}

// ------------------- ve -------------------

template <std::size_t Alen, typename apFixedType>
struct Qve_s
{
    static inline Qvec<Alen, apFixedType> output;

    template <std::size_t... I, typename inputT1, typename inputT2>
    static inline void mul_impl(const Qvec<Alen, inputT1> &input1, const Qvec<Alen, inputT2> &input2, std::index_sequence<I...>)
    {
        (((output[I] = Qmul<apFixedType>(input1[I], input2[I])), ...));
    }

    template <std::size_t... I, typename inputT1, typename...Args>
    static inline void mul_impl(const Qvec<Alen, inputT1> &input1, const apFixed<Args...> &input2, std::index_sequence<I...>)
    {
        (((output[I] = Qmul<apFixedType>(input1[I], input2)), ...));
    }

    template <typename inputT1, typename inputT2>
    static inline auto &mul(const Qvec<Alen, inputT1> &input1, const Qvec<Alen, inputT2> input2)
    {
        mul_impl(input1, input2, std::make_index_sequence<Alen>{});
        return output;
    }

    template <typename inputT1, typename...Args>
    static inline auto &mul(const Qvec<Alen, inputT1> &input1, const apFixed<Args...> &input2)
    {
        mul_impl(input1, input2, std::make_index_sequence<Alen>{});
        return output;
    }

    template <std::size_t... I, typename inputT1, typename inputT2>
    static inline void add_impl(const Qvec<Alen, inputT1> &input1, const Qvec<Alen, inputT2> &input2, std::index_sequence<I...>)
    {
        (((output[I] = Qadd<apFixedType>(input1[I], input2[I])), ...));
    }

    template <std::size_t... I, typename inputT1, typename...Args>
    static inline void add_impl(const Qvec<Alen, inputT1> &input1, const apFixed<Args...> &input2, std::index_sequence<I...>)
    {
        (((output[I] = Qadd<apFixedType>(input1[I], input2)), ...));
    }

    template <typename inputT1, typename inputT2>
    static inline auto &add(const Qvec<Alen, inputT1> &input1, const Qvec<Alen, inputT2> input2)
    {
        add_impl(input1, input2, std::make_index_sequence<Alen>{});
        return output;
    }

    template <typename inputT1, typename...Args>
    static inline auto &add(const Qvec<Alen, inputT1> &input1, const apFixed<Args...> &input2)
    {
        add_impl(input1, input2, std::make_index_sequence<Alen>{});
        return output;
    }

    template <std::size_t... I, typename inputT1, typename inputT2>
    static inline void sub_impl(const Qvec<Alen, inputT1> &input1, const Qvec<Alen, inputT2> &input2, std::index_sequence<I...>)
    {
        (((output[I] = Qsub<apFixedType>(input1[I], input2[I])), ...));
    }

    template <std::size_t... I, typename inputT1, typename...Args>
    static inline void sub_impl(const Qvec<Alen, inputT1> &input1, const apFixed<Args...> &input2, std::index_sequence<I...>)
    {
        (((output[I] = Qsub<apFixedType>(input1[I], input2)), ...));
    }

    template <std::size_t... I, typename inputT1, typename...Args>
    static inline void sub_impl(const apFixed<Args...> &input1, const Qvec<Alen, inputT1> &input2, std::index_sequence<I...>)
    {
        (((output[I] = Qsub<apFixedType>(input1, input2[I])), ...));
    }

    template <typename inputT1, typename inputT2>
    static inline auto &sub(const Qvec<Alen, inputT1> &input1, const Qvec<Alen, inputT2> input2)
    {
        sub_impl(input1, input2, std::make_index_sequence<Alen>{});
        return output;
    }

    template <typename inputT1, typename...Args>
    static inline auto &sub(const Qvec<Alen, inputT1> &input1, const apFixed<Args...> &input2)
    {
        sub_impl(input1, input2, std::make_index_sequence<Alen>{});
        return output;
    }

    template <typename inputT1, typename...Args>
    static inline auto &sub(const apFixed<Args...> &input1, const Qvec<Alen, inputT1> &input2)
    {
        sub_impl(input1, input2, std::make_index_sequence<Alen>{});
        return output;
    }

    template <std::size_t... I, typename inputT1, typename inputT2>
    static inline void div_impl(const Qvec<Alen, inputT1> &input1, const Qvec<Alen, inputT2> &input2, std::index_sequence<I...>)
    {
        (((output[I] = Qdiv<apFixedType>(input1[I], input2[I])), ...));
    }

    template <std::size_t... I, typename inputT1, typename...Args>
    static inline void div_impl(const Qvec<Alen, inputT1> &input1, const apFixed<Args...> &input2, std::index_sequence<I...>)
    {
        (((output[I] = Qdiv<apFixedType>(input1[I], input2)), ...));
    }

    template <std::size_t... I, typename inputT1, typename...Args>
    static inline void div_impl(const apFixed<Args...> &input1, const Qvec<Alen, inputT1> &input2, std::index_sequence<I...>)
    {
        (((output[I] = Qdiv<apFixedType>(input1, input2[I])), ...));
    }

    template <typename inputT1, typename inputT2>
    static inline auto &div(const Qvec<Alen, inputT1> &input1, const Qvec<Alen, inputT2> input2)
    {
        div_impl(input1, input2, std::make_index_sequence<Alen>{});
        return output;
    }

    template <typename inputT1, typename...Args>
    static inline auto &div(const Qvec<Alen, inputT1> &input1, const apFixed<Args...> &input2)
    {
        div_impl(input1, input2, std::make_index_sequence<Alen>{});
        return output;
    }

    template <typename inputT1, typename...Args>
    static inline auto &div(const apFixed<Args...> &input1, const Qvec<Alen, inputT1> &input2)
    {
        div_impl(input1, input2, std::make_index_sequence<Alen>{});
        return output;
    }

};

template <typename vecTypes1, typename vecTypes2, typename... Types>
struct QveTypeHelper
{
    template <typename T1, typename T2>
    struct defaultType
    {
        using merger = apFixedMerge<apFixed<>, T1, T2>;
        using type = apFixed<intBits<merger::toInt>, fracBits<merger::toFrac>, QuMode<typename merger::toQuMode>, OfMode<typename merger::toOfMode>, isSigned<merger::toIsSigned>>;
    };

    template <typename... Ts>
    struct customType
    {
        using FirstType = std::tuple_element_t<0, std::tuple<Ts...>>;
        using type = std::conditional_t<is_apFixed<FirstType>::value, FirstType, apFixed<Ts...>>;
    };

    using outputType = typename std::conditional_t<
        sizeof...(Types) == 0,
        defaultType<vecTypes1, vecTypes2>,
        customType<Types...>>::type;
};

// Do not use auto& res = Qve<...>(...), use auto res = instead
template <typename... Types, size_t len1, size_t len2, typename vecTypes1, typename vecTypes2>
inline auto &Qvem(const Qvec<len1, vecTypes1> &input1, const Qvec<len2, vecTypes2> &input2)
{
    static_assert(len1 == len2, "The two vectors must have the same length");
    using outputType = typename QveTypeHelper<vecTypes1, vecTypes2, Types...>::outputType;
    return Qve_s<len1, outputType>::mul(input1, input2);
}

template <typename... Types, size_t len, typename vecTypes, typename...Args>
inline auto &Qvem(const Qvec<len, vecTypes> &input1, const apFixed<Args...> &input2)
{
    using outputType = typename QveTypeHelper<vecTypes, apFixed<Args...>, Types...>::outputType;
    return Qve_s<len, outputType>::mul(input1, input2);
}

template <size_t len1, size_t len2, typename vecTypes1, typename vecTypes2>
inline auto &operator*(const Qvec<len1, vecTypes1> &input1, const Qvec<len2, vecTypes2> &input2)
{
    return Qvem<>(input1, input2);
}

template <size_t len, typename vecTypes, typename...Args>
inline auto &operator*(const Qvec<len, vecTypes> &input1, const apFixed<Args...> &input2)
{
    return Qvem<>(input1, input2);
}

template <size_t len, typename vecTypes, typename...Args>
inline auto &operator*(const apFixed<Args...> &input1, const Qvec<len, vecTypes> &input2)
{
    return Qvem<>(input2, input1);
}

template <typename... Types, size_t len1, size_t len2, typename vecTypes1, typename vecTypes2>
inline auto &Qvea(const Qvec<len1, vecTypes1> &input1, const Qvec<len2, vecTypes2> &input2)
{
    static_assert(len1 == len2, "The two vectors must have the same length");
    using outputType = typename QveTypeHelper<vecTypes1, vecTypes2, Types...>::outputType;
    return Qve_s<len1, outputType>::add(input1, input2);
}

template <typename... Types, size_t len, typename vecTypes, typename...Args>
inline auto &Qvea(const Qvec<len, vecTypes> &input1, const apFixed<Args...> &input2)
{
    using outputType = typename QveTypeHelper<vecTypes, apFixed<Args...>, Types...>::outputType;
    return Qve_s<len, outputType>::add(input1, input2);
}

template <size_t len1, size_t len2, typename vecTypes1, typename vecTypes2>
inline auto &operator+(const Qvec<len1, vecTypes1> &input1, const Qvec<len2, vecTypes2> &input2)
{
    return Qvea<>(input1, input2);
}

template <size_t len, typename vecTypes, typename...Args>
inline auto &operator+(const Qvec<len, vecTypes> &input1, const apFixed<Args...> &input2)
{
    return Qvea<>(input1, input2);
}

template <size_t len, typename vecTypes, typename...Args>
inline auto &operator+(const apFixed<Args...> &input1, const Qvec<len, vecTypes> &input2)
{
    return Qvea<>(input2, input1);
}

template <typename... Types, size_t len1, size_t len2, typename vecTypes1, typename vecTypes2>
inline auto &Qves(const Qvec<len1, vecTypes1> &input1, const Qvec<len2, vecTypes2> &input2)
{
    static_assert(len1 == len2, "The two vectors must have the same length");
    using outputType = typename QveTypeHelper<vecTypes1, vecTypes2, Types...>::outputType;
    return Qve_s<len1, outputType>::sub(input1, input2);
}

template <typename... Types, size_t len, typename vecTypes, typename...Args>
inline auto &Qves(const Qvec<len, vecTypes> &input1, const apFixed<Args...> &input2)
{
    using outputType = typename QveTypeHelper<vecTypes, apFixed<Args...>, Types...>::outputType;
    return Qve_s<len, outputType>::sub(input1, input2);
}

template <typename... Types, size_t len, typename vecTypes, typename...Args>
inline auto &Qves(const apFixed<Args...> &input1, const Qvec<len, vecTypes> &input2)
{
    using outputType = typename QveTypeHelper<apFixed<Args...>, vecTypes, Types...>::outputType;
    return Qve_s<len, outputType>::sub(input1, input2);
}

template <size_t len1, size_t len2, typename vecTypes1, typename vecTypes2>
inline auto &operator-(const Qvec<len1, vecTypes1> &input1, const Qvec<len2, vecTypes2> &input2)
{
    return Qves<>(input1, input2);
}

template <size_t len, typename vecTypes, typename...Args>
inline auto &operator-(const Qvec<len, vecTypes> &input1, const apFixed<Args...> &input2)
{
    return Qves<>(input1, input2);
}

template <size_t len, typename vecTypes, typename...Args>
inline auto &operator-(const apFixed<Args...> &input1, const Qvec<len, vecTypes> &input2)
{
    return Qves<>(input1, input2);
}

template <typename... Types, size_t len1, size_t len2, typename vecTypes1, typename vecTypes2>
inline auto &Qved(const Qvec<len1, vecTypes1> &input1, const Qvec<len2, vecTypes2> &input2)
{
    static_assert(len1 == len2, "The two vectors must have the same length");
    using outputType = typename QveTypeHelper<vecTypes1, vecTypes2, Types...>::outputType;
    return Qve_s<len1, outputType>::div(input1, input2);
}

template <typename... Types, size_t len, typename vecTypes, typename...Args>
inline auto &Qved(const Qvec<len, vecTypes> &input1, const apFixed<Args...> &input2)
{
    using outputType = typename QveTypeHelper<vecTypes, apFixed<Args...>, Types...>::outputType;
    return Qve_s<len, outputType>::div(input1, input2);
}

template <typename... Types, size_t len, typename vecTypes, typename...Args>
inline auto &Qved(const apFixed<Args...> &input1, const Qvec<len, vecTypes> &input2)
{
    using outputType = typename QveTypeHelper<apFixed<Args...>, vecTypes, Types...>::outputType;
    return Qve_s<len, outputType>::div(input1, input2);
}

template <size_t len1, size_t len2, typename vecTypes1, typename vecTypes2>
inline auto &operator/(const Qvec<len1, vecTypes1> &input1, const Qvec<len2, vecTypes2> &input2)
{
    return Qved<>(input1, input2);
}

template <size_t len, typename vecTypes, typename...Args>
inline auto &operator/(const Qvec<len, vecTypes> &input1, const apFixed<Args...> &input2)
{
    return Qved<>(input1, input2);
}

template <size_t len, typename vecTypes, typename...Args>
inline auto &operator/(const apFixed<Args...> &input1, const Qvec<len, vecTypes> &input2)
{
    return Qved<>(input1, input2);
}
    
// ------------------- Qgemul -------------------

template <bool Value>
struct QgemulTransposedA;

template <bool Value>
struct QgemulTransposedB;

template <typename... Args>
struct QgemulAddArgs;

template <typename... Args>
struct QgemulMulArgs;

template <typename... interiorArgs>
struct Qgemul_s
{
    using addArgs = tagExtractor<QgemulAddArgs<>, interiorArgs...>::type;
    using mulArgs = tagExtractor<QgemulMulArgs<>, interiorArgs...>::type;

    template <typename... toArgs, typename... fromArgsA, typename... fromArgsB, size_t rowC, size_t colC, size_t rowA, size_t colA, size_t rowB, size_t colB>
    inline static void apply(Qmat<rowC, colC, apFixed<toArgs...>> &C, const Qmat<rowA, colA, apFixed<fromArgsA...>> &A, const Qmat<rowB, colB, apFixed<fromArgsB...>> &B)
    {
        static constexpr auto isTransposedA = tagExtractor<QgemulTransposedA<false>, interiorArgs...>::value;
        static constexpr auto isTransposedB = tagExtractor<QgemulTransposedB<false>, interiorArgs...>::value;

        static_assert(
            (!isTransposedA && !isTransposedB && (colA == rowB && rowA == rowC && colB == colC)) ||
                (!isTransposedA && isTransposedB && (colA == colB && rowA == rowC && rowB == colC)) ||
                (isTransposedA && !isTransposedB && (rowA == rowB && colA == rowC && colB == colC)) ||
                (isTransposedA && isTransposedB && (rowA == colB && colA == rowC && rowB == colC)),
            "Size mismatch when calling Qgemul");

        for (int i = 0; i < rowC; i++)
        {
            for (int j = 0; j < colC; j++)
            {

                apFixed<addArgs> sum = 0;

                for (int k = 0; k < (isTransposedA ? rowA : colA); k++)
                {
                    auto a = isTransposedA ? A[k][i] : A[i][k];
                    auto b = isTransposedB ? B[j][k] : B[k][j];

                    sum = Qadd<addArgs>(sum, Qmul<mulArgs>(a, b));
                }
                C[i][j] = sum;
            }
        }
    }

    // special version for C = op(A^T) * op(A)
    template <typename... toArgs, typename... fromArgsA, size_t rowC, size_t colC, size_t rowA, size_t colA>
    inline static void apply(Qmat<rowC, colC, apFixed<toArgs...>> &C, const Qmat<rowA, colA, apFixed<fromArgsA...>> &A)
    {
        static constexpr auto isTransposedA = tagExtractor<QgemulTransposedA<false>, interiorArgs...>::value;

        static_assert((isTransposedA ? (rowA == colC) : (colA == colC)) && (rowC == colC), "Size mismatch when calling Qgemul(self-transpose mul version)");

        for (int i = 0; i < rowC; i++)
        {
            for (int j = 0; j < colC; j++)
            {
                apFixed<addArgs> sum = 0;
                for (int k = 0; k < (!isTransposedA ? rowA : colA); k++)
                {
                    auto a = !isTransposedA ? A[k][i] : A[i][k];
                    auto b = !isTransposedA ? A[k][j] : A[j][k];

                    sum = Qadd<addArgs>(sum, Qmul<mulArgs>(a, b));
                }
                C[i][j] = sum;
                if (i != j)
                {
                    C[j][i] = sum;
                }
            }
        }
    }
};

template <typename... interiorArgs, typename... toArgs, typename... fromArgsA, typename... fromArgsB, size_t rowC, size_t colC, size_t rowA, size_t colA, size_t rowB, size_t colB>
inline void Qgemul(Qmat<rowC, colC, apFixed<toArgs...>> &C, const Qmat<rowA, colA, apFixed<fromArgsA...>> &A, const Qmat<rowB, colB, apFixed<fromArgsB...>> &B)
{
    Qgemul_s<interiorArgs...>::apply(C, A, B);
}

template <typename... interiorArgs, typename... toArgs, typename... fromArgsA, size_t rowC, size_t colC, size_t rowA, size_t colA>
inline void Qgemul(Qmat<rowC, colC, apFixed<toArgs...>> &C, const Qmat<rowA, colA, apFixed<fromArgsA...>> &A)
{
    Qgemul_s<interiorArgs...>::apply(C, A);
}

// ------------------- Qgemv -------------------
// Perform the operation y = beta * y + alpha * op(A) * x.

template <bool Value = false>
struct QgemvTransposedA;

template <typename... Args>
struct QgemvAddArgs;

template <typename... Args>
struct QgemvMulArgs;

template <apFixed alpha>
struct QgemvAlpha;

template <apFixed beta>
struct QgemvBeta;

template <typename... interiorArgs>
struct Qgemv_s
{
    using addArgs = tagExtractor<QgemvAddArgs<>, interiorArgs...>::type;
    using mulArgs = tagExtractor<QgemvMulArgs<>, interiorArgs...>::type;

    template <typename... toArgs, typename... fromArgsAlpha, typename... fromArgsBeta, typename... fromArgsA, typename... fromArgsX, typename... fromArgsY, size_t rowA, size_t colA, size_t rowX, size_t rowY>
    inline static void apply(Qvec<rowY, apFixed<toArgs...>> &y, const apFixed<fromArgsBeta...> bata, const apFixed<fromArgsAlpha...> alpha, const Qmat<rowA, colA, apFixed<fromArgsA...>> &A, const Qvec<rowX, apFixed<fromArgsX...>> &x)
    {
        static constexpr auto isTransposedA = tagExtractor<QgemvTransposedA<false>, interiorArgs...>::value;

        static_assert((!isTransposedA && (colA == rowX && rowA == rowY)) || (isTransposedA && (rowA == rowX && colA == rowY)), "Size mismatch when calling Qgemv");

        auto static constexpr outerLoop = isTransposedA ? colA : rowA;
        auto static constexpr innerLoop = isTransposedA ? rowA : colA;

        for (int i = 0; i < outerLoop; i++)
        {
            auto betaY = Qmul<mulArgs>(y[i], bata);

            apFixed<addArgs> AxAddTemp = 0;

            for (int j = 0; j < innerLoop; j++)
            {
                auto AxMul = Qmul<mulArgs>(isTransposedA ? A[j][i] : A[i][j], x[j]);
                AxAddTemp = Qadd<addArgs>(AxAddTemp, AxMul);
            }

            auto alphaAxAdd = Qmul<mulArgs>(alpha, AxAddTemp);

            y[i] = Qadd<addArgs>(betaY, alphaAxAdd);
        }
    }

    // special version for alpha and beta be template parameters
    template <typename... toArgs, typename... fromArgsA, typename... fromArgsX, typename... fromArgsY, size_t rowA, size_t colA, size_t rowX, size_t rowY>
    inline static void apply(Qvec<rowY, apFixed<toArgs...>> &y, const Qmat<rowA, colA, apFixed<fromArgsA...>> &A, const Qvec<rowX, apFixed<fromArgsX...>> &x)
    {
        static constexpr auto isTransposedA = tagExtractor<QgemvTransposedA<false>, interiorArgs...>::value;

        auto static constexpr defaultBeta = apFixed<toArgs...>(0);
        auto static constexpr defaultAlpha = apFixed<toArgs...>(1);

        auto static constexpr beta = tagExtractor<QgemvBeta<defaultBeta>, interiorArgs...>::value;
        auto static constexpr alpha = tagExtractor<QgemvAlpha<defaultAlpha>, interiorArgs...>::value;

        static_assert((!isTransposedA && (colA == rowX && rowA == rowY)) || (isTransposedA && (rowA == rowX && colA == rowY)), "Size mismatch when calling Qgemv");

        auto static constexpr outerLoop = isTransposedA ? colA : rowA;
        auto static constexpr innerLoop = isTransposedA ? rowA : colA;

        if constexpr (beta.data != 0)
        {
            for (int i = 0; i < outerLoop; i++)
            {
                auto betaY = Qmul<mulArgs>(y[i], beta);
                apFixed<addArgs> AxAddTemp = 0;
                for (int j = 0; j < innerLoop; j++)
                {
                    auto AxMul = Qmul<mulArgs>(isTransposedA ? A[j][i] : A[i][j], x[j]);
                    AxAddTemp = Qadd<addArgs>(AxAddTemp, AxMul);

                    if constexpr (alpha != apFixed<toArgs...>(1))
                    {
                        auto alphaAxAdd = Qmul<mulArgs>(alpha, AxAddTemp);
                        y[i] = Qadd<addArgs>(betaY, alphaAxAdd);
                    }
                    else
                    {
                        y[i] = Qadd<addArgs>(betaY, AxAddTemp);
                    }
                }
            }
        }
        else
        {

            for (int i = 0; i < outerLoop; i++)
            {
                apFixed<addArgs> AxAddTemp = 0;
                for (int j = 0; j < innerLoop; j++)
                {
                    auto AxMul = Qmul<mulArgs>(isTransposedA ? A[j][i] : A[i][j], x[j]);
                    AxAddTemp = Qadd<addArgs>(AxAddTemp, AxMul);
                }
                if constexpr (alpha != apFixed<toArgs...>(1))
                {
                    y[i] = Qmul<mulArgs>(alpha, AxAddTemp);
                }
                else
                {
                    y[i] = AxAddTemp;
                }
            }
        }
    }
};

template <typename... interiorArgs, typename... toArgs, typename... fromArgsAlpha, typename... fromArgsBeta, typename... fromArgsA, typename... fromArgsX, typename... fromArgsY, size_t rowA, size_t colA, size_t rowX, size_t rowY>
inline void Qgemv(Qvec<rowY, apFixed<toArgs...>> &y, const apFixed<fromArgsBeta...> beta, const apFixed<fromArgsAlpha...> alpha, const Qmat<rowA, colA, apFixed<fromArgsA...>> &A, const Qvec<rowX, apFixed<fromArgsX...>> &x)
{
    Qgemv_s<interiorArgs...>::apply(y, beta, alpha, A, x);
}

template <typename... interiorArgs, typename... toArgs, typename... fromArgsA, typename... fromArgsX, typename... fromArgsY, size_t rowA, size_t colA, size_t rowX, size_t rowY>
inline void Qgemv(Qvec<rowY, apFixed<toArgs...>> &y, const Qmat<rowA, colA, apFixed<fromArgsA...>> &A, const Qvec<rowX, apFixed<fromArgsX...>> &x)
{
    Qgemv_s<interiorArgs...>::apply(y, A, x);
}

// ------------------- Qgetrf -------------------

template <typename... Args>
struct QgetrfDivArgs;

template <typename... Args>
struct QgetrfSubArgs;

template <typename... Args>
struct QgetrfMulArgs;

template <typename... interiorArgs>
struct Qgetrf_s
{
    using divArgs = tagExtractor<QgetrfDivArgs<>, interiorArgs...>::type;
    using subArgs = tagExtractor<QgetrfSubArgs<>, interiorArgs...>::type;
    using mulArgs = tagExtractor<QgetrfMulArgs<>, interiorArgs...>::type;

    template <typename... ArgsA, size_t N>
    inline static void apply(Qmat<N, N, apFixed<ArgsA...>> &A, std::array<size_t, N> &ipiv)
    {
        for (int i = 0; i < N; i++)
        {
            ipiv[i] = i;
        }

        for (int k = 0; k < N; ++k)
        {
            apFixed<ArgsA...> maxVal = 0;
            int i_max = k;

            for (int i = k; i < N; ++i)
            {
                auto absVal = Qabs(A[i][k]);
                if (absVal > maxVal)
                {
                    maxVal = absVal;
                    i_max = i;
                }
            }

            if (maxVal.data == 0)
            {
                // throw std::runtime_error("Matrix is singular");
                // theoretically, this indicates the matrix is singular
                // however, this may occur when the fractional bits are not enough
                // so we just return
            }

            std::swap(ipiv[k], ipiv[i_max]);
            std::swap(A[k], A[i_max]);

            for (int i = k + 1; i < N; ++i)
            {
                A[i][k] = Qdiv<divArgs>(A[i][k], A[k][k]);
                for (int j = k + 1; j < N; ++j)
                {
                    A[i][j] = Qsub<subArgs>(A[i][j], Qmul<mulArgs>(A[i][k], A[k][j]));
                }
            }
        }
    }
};

template <typename... interiorArgs, typename... ArgsA, size_t N>
inline void Qgetrf(Qmat<N, N, apFixed<ArgsA...>> &A, std::array<size_t, N> &ipiv)
{
    Qgetrf_s<interiorArgs...>::apply(A, ipiv);
}

// ------------------- Qgetrs -------------------

template <typename... Args>
struct QgetrsDivArgs;

template <typename... Args>
struct QgetrsSubArgs;

template <typename... Args>
struct QgetrsMulArgs;

template <typename... interiorArgs>
struct Qgetrs_s
{
    using divArgs = tagExtractor<QgetrsDivArgs<>, interiorArgs...>::type;
    using subArgs = tagExtractor<QgetrsSubArgs<>, interiorArgs...>::type;
    using mulArgs = tagExtractor<QgetrsMulArgs<>, interiorArgs...>::type;

    template <typename... ArgsA, typename... ArgsB, size_t N>
    inline static void apply(Qmat<N, N, apFixed<ArgsA...>> &A, std::array<size_t, N> &ipiv, Qvec<N, apFixed<ArgsB...>> &b)
    {
        static Qvec<N, apFixed<ArgsB...>> b_permuted;

        for (int i = 0; i < N; i++)
        {
            b_permuted[i] = b[ipiv[i]];
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < i; j++)
            {
                b_permuted[i] = Qsub<subArgs>(b_permuted[i], Qmul<mulArgs>(A[i][j], b_permuted[j]));
            }
        }

        for (int i = N - 1; i >= 0; i--)
        {
            for (int j = i + 1; j < N; j++)
            {
                b_permuted[i] = Qsub<subArgs>(b_permuted[i], Qmul<mulArgs>(A[i][j], b_permuted[j]));
            }
            b_permuted[i] = Qdiv<divArgs>(b_permuted[i], A[i][i]);
        }

        for (int i = 0; i < N; i++)
        {
            b[i] = b_permuted[i];
        }
    }
};

template <typename... interiorArgs, typename... ArgsA, typename... ArgsB, size_t N>
inline void Qgetrs(Qmat<N, N, apFixed<ArgsA...>> &A, std::array<size_t, N> &ipiv, Qvec<N, apFixed<ArgsB...>> &b)
{
    Qgetrs_s<interiorArgs...>::apply(A, ipiv, b);
}
