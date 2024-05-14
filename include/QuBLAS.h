#pragma once

#include <array>
#include <bitset>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <functional>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

// ------------------- Random -------------------

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<int> dis(std::numeric_limits<int>::min(), std::numeric_limits<int>::max()); // 整数的全范围分布

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
        std::unreachable();
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
        int fillVal = dis(gen);

        static constexpr auto mask = ~((1u << 31u) - 1u - ((1u << (intBitsInput + fracBitsInput)) - 1u));
        this->data = fillVal > 0 ? fillVal & mask : fillVal | ~mask;
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
    }

    void display(std::string name = "") const
    {
        if (name != "")
        {
            std::cout << name << " :";
        }
        std::cout << std::endl;
        std::cout << "intBits: " << intB << " fracBits: " << fracB << " isSigned: " << isS << " ";
        std::cout << std::endl;
        std::cout << "Binary: " << std::bitset<intB + fracB + (isS ? 1 : 0)>(data) << std::endl;
        std::cout << "Hex: " << std::hex << data << std::dec << std::endl;

        std::cout << "Decimal: " << shifter<fracB>::toDouble(data) << std::endl;
        std::cout << std::endl;
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

    template <typename... Types>
    constexpr Qu_s(Types... values) : data{values...} {}

    constexpr Qu_s() {}

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

        displayHelper(std::make_index_sequence<dim<dims...>::elemSize>());
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

// ------------------- element wise operations -------------------

// contain all the trash that is not supposed to be used
namespace elementWise {
// completed empty struct just to convey the dims
template <size_t... dims>
struct indice;

template <typename A, typename B, typename accumulated = indice<>>
struct BroadcastHelper;

template <size_t... Dims1, size_t... accumulatedDims>
struct BroadcastHelper<dim<Dims1...>, dim<>, indice<accumulatedDims...>> : BroadcastHelper<dim<Dims1...>, dim<1>, indice<accumulatedDims...>>
{
};

template <size_t... Dims2, size_t... accumulatedDims>
struct BroadcastHelper<dim<>, dim<Dims2...>, indice<accumulatedDims...>> : BroadcastHelper<dim<1>, dim<Dims2...>, indice<accumulatedDims...>>
{
};

template <size_t... accumulatedDims>
struct BroadcastHelper<dim<>, dim<>, indice<accumulatedDims...>>
{
    inline constexpr static bool canBroadcast = true;
    using resultDim = dim<accumulatedDims...>;
};

template <size_t sameDim, size_t... Dims1, size_t... Dims2, size_t... accumulatedDims>
struct BroadcastHelper<dim<sameDim, Dims1...>, dim<sameDim, Dims2...>, indice<accumulatedDims...>>
{
    using next = BroadcastHelper<dim<Dims1...>, dim<Dims2...>, indice<accumulatedDims..., sameDim>>;
    inline constexpr static bool canBroadcast = next::canBroadcast;
    using resultDim = typename next::resultDim;
};

template <size_t firstDim1, size_t firstDim2, size_t... Dims1, size_t... Dims2, size_t... accumulatedDims>
    requires(firstDim1 != firstDim2)
struct BroadcastHelper<dim<firstDim1, Dims1...>, dim<firstDim2, Dims2...>, indice<accumulatedDims...>>
{
    inline constexpr static bool oneExists = (firstDim1 == 1 || firstDim2 == 1);

    using next = BroadcastHelper<dim<Dims1...>, dim<Dims2...>, indice<accumulatedDims..., oneExists ? std::max(firstDim1, firstDim2) : firstDim1>>;

    inline constexpr static bool canBroadcast = oneExists ? next::canBroadcast : false;
    using resultDim = std::conditional_t<oneExists, typename next::resultDim, std::nullptr_t>;
};

template <typename T>
struct dimGet_s;

template <size_t... dims>
struct dimGet_s<indice<dims...>>
{
    template <size_t... dims2, typename... Args>
    static inline constexpr auto &get(Qu_s<dim<dims2...>, Args...> &f)
    {
        return f.template get<dims...>();
    }

    template <size_t... dims2, typename... Args>
    static inline constexpr const auto &get(const Qu_s<dim<dims2...>, Args...> &f)
    {
        return f.template get<dims...>();
    }
};

template <typename T, typename dim, size_t... dims, typename... Args>
inline constexpr auto &dimGet(Qu_s<dim, Args...> &f)
{
    return dimGet_s<T>::get(f);
}

template <typename T, typename dim, size_t... dims, typename... Args>
inline constexpr const auto &dimGet(const Qu_s<dim, Args...> &f)
{
    return dimGet_s<T>::get(f);
}

template <typename... indices>
struct numList;

template <typename... Type>
struct parallel;

template <typename... nums1, typename... nums2, typename... nums3, typename... toArgs>
struct parallel<numList<nums1...>, numList<nums2...>, numList<nums3...>, toArgs...>
{
    template <size_t... dims1, size_t... dims2, size_t... dims3, typename... Args1, typename... Args2, typename... Args3>
    static void executeMulition(const Qu_s<dim<dims1...>, Args1...> &f1, const Qu_s<dim<dims2...>, Args2...> &f2, Qu_s<dim<dims3...>, Args3...> &f3)
    {
        ((dimGet<nums3>(f3) = Qmul<toArgs...>(dimGet<nums1>(f1), dimGet<nums2>(f2))), ...);
    }

    template <size_t... dims1, size_t... dims2, size_t... dims3, typename... Args1, typename... Args2, typename... Args3>
    static void executeAddition(const Qu_s<dim<dims1...>, Args1...> &f1, const Qu_s<dim<dims2...>, Args2...> &f2, Qu_s<dim<dims3...>, Args3...> &f3)
    {
        ((dimGet<nums3>(f3) = Qadd<toArgs...>(dimGet<nums1>(f1), dimGet<nums2>(f2))), ...);
    }

    template <size_t... dims1, size_t... dims2, size_t... dims3, typename... Args1, typename... Args2, typename... Args3>
    static void executeSubtraction(const Qu_s<dim<dims1...>, Args1...> &f1, const Qu_s<dim<dims2...>, Args2...> &f2, Qu_s<dim<dims3...>, Args3...> &f3)
    {
        ((dimGet<nums3>(f3) = Qsub<toArgs...>(dimGet<nums1>(f1), dimGet<nums2>(f2))), ...);
    }

    template <size_t... dims1, size_t... dims2, size_t... dims3, typename... Args1, typename... Args2, typename... Args3>
    static void executeDivision(const Qu_s<dim<dims1...>, Args1...> &f1, const Qu_s<dim<dims2...>, Args2...> &f2, Qu_s<dim<dims3...>, Args3...> &f3)
    {
        ((dimGet<nums3>(f3) = Qdiv<toArgs...>(dimGet<nums1>(f1), dimGet<nums2>(f2))), ...);
    }
};

// ----------------- numsExtenderParallel -----------------

template <size_t N, typename T>
struct numsExtender;

template <size_t... num, size_t N>
struct numsExtender<N, indice<num...>>
{
    using result = indice<num..., N>;
};

template <typename... Args>
struct numsListExtender;

template <typename... num, size_t... N>
struct numsListExtender<numList<num...>, std::index_sequence<N...>>
{
    using result = numList<typename numsExtender<N, num>::result...>;
};

//-------------------- numListDuplicator --------------------

// 基本模板，不做任何事，只定义类型
template <typename List1, typename List2>
struct Concatenate;

// 特化版本，用于实际连接两个numList
template <typename... Nums1, typename... Nums2>
struct Concatenate<numList<Nums1...>, numList<Nums2...>>
{
    using type = numList<Nums1..., Nums2...>;
};

// 前向声明
template <typename List, size_t N, typename... Accumulated>
struct Duplicate;

// 终止条件特化版本，当N为0时终止递归
template <typename List, typename... Accumulated>
struct Duplicate<List, 0, Accumulated...>
{
    using type = numList<>;
};

// N > 0 的情况，递归展开
template <typename List, size_t N, typename... Accumulated>
struct Duplicate
{
    using type = typename Concatenate<
        typename Duplicate<List, 1>::type,
        typename Duplicate<List, N - 1, Accumulated...>::type>::type;
};

// 特化N = 1的情况，直接返回List
template <typename List, typename... Accumulated>
struct Duplicate<List, 1, Accumulated...>
{
    using type = List;
};

template <typename List, size_t N>
struct numListDuplicator
{
    using type = typename Duplicate<List, N>::type;
};

// ----------------- numsDuplicator -----------------

// 重复每个元素loop次的辅助模板
template <typename Seq, typename Loop>
struct repeat_seq_impl;

template <size_t... Loop, size_t... I>
struct repeat_seq_impl<std::index_sequence<I...>, std::index_sequence<Loop...>>
{

    template <size_t N>
    using repeat = std::index_sequence<((void)Loop, N)...>;

    // 连接多个index_sequence
    template <typename... Sequences>
    struct concat;

    template <size_t... I1, size_t... I2, typename... Rest>
    struct concat<std::index_sequence<I1...>, std::index_sequence<I2...>, Rest...>
    {
        using type = typename concat<std::index_sequence<I1..., I2...>, Rest...>::type;
    };

    template <size_t... I2>
    struct concat<std::index_sequence<I2...>>
    {
        using type = std::index_sequence<I2...>;
    };

    using type = typename concat<repeat<I>...>::type;
};

// 用户接口
template <int N, size_t Loop>
struct makeExtIdxSeq
{
    using type = typename repeat_seq_impl<std::make_index_sequence<N>, std::make_index_sequence<Loop>>::type;
};

// ----------------- begin -----------------

template <typename T>
struct indexSeqToNumList;

template <size_t... index>
struct indexSeqToNumList<std::index_sequence<index...>>
{
    using type = numList<indice<index>...>;
};

template <typename T>
struct guillotine;

template <template <auto...> typename list, auto first, auto... indice>
struct guillotine<list<first, indice...>>
{
    using type = list<indice...>;
};

template <typename... Args>
struct indexModifier;

template <size_t... num, size_t... dims, size_t firstNum, size_t firstDim, size_t... accuNum>
struct indexModifier<indice<firstNum, num...>, dim<firstDim, dims...>, indice<accuNum...>>
{
    static constexpr size_t newNum = firstDim == 1 ? 0 : firstNum;
    using res = indexModifier<indice<num...>, dim<dims...>, indice<accuNum..., newNum>>::res;
};

// 终止
template <size_t... accuNum, size_t firstNum, size_t... num>
struct indexModifier<indice<firstNum, num...>, dim<>, indice<accuNum...>>
{
    using res = indice<accuNum...>;
};

template <size_t... accuNum>
struct indexModifier<indice<>, dim<>, indice<accuNum...>>
{
    using res = indice<accuNum...>;
};

template <typename... Args>
struct indexModifierParallel;

template <typename... indices, size_t... dims>
struct indexModifierParallel<numList<indices...>, dim<dims...>>
{
    using res = numList<typename indexModifier<indices, dim<dims...>, indice<>>::res...>;
};

template <typename... Args>
struct elemwiseIndexCalculator;

template <size_t... dims1, size_t... dims2>
struct elemwiseIndexCalculator<dim<dims1...>, dim<dims2...>>
{

    using Cdim = typename BroadcastHelper<dim<dims1...>, dim<dims2...>>::resultDim;

    template <typename... Args>
    struct begin;

    template <size_t... dims>
    struct begin<numList<>, dim<dims...>>
    {
        static constexpr size_t initDim = dim<dims...>::dimArray[0];

        using initList = indexSeqToNumList<std::make_index_sequence<initDim>>::type;

        using res = begin<initList, typename guillotine<dim<dims...>>::type>::res;
    };

    template <typename... accuNums, size_t... dims>
    struct begin<numList<accuNums...>, dim<dims...>>

    {
        static constexpr size_t initDim = dim<dims...>::dimArray[0];
        using duplicatedList = numListDuplicator<numList<accuNums...>, initDim>::type;
        using numToAdd = makeExtIdxSeq<initDim, sizeof...(accuNums)>::type;

        using newList = numsListExtender<duplicatedList, numToAdd>::result;

        using res = begin<newList, typename guillotine<dim<dims...>>::type>::res;
    };

    template <typename... accuNums>
    struct begin<numList<accuNums...>, dim<>>
    {
        using res = numList<accuNums...>;
    };

    using outputIndexList = begin<numList<>, Cdim>::res;
    using input1IndexList = indexModifierParallel<outputIndexList, dim<dims1...>>::res;
    using input2IndexList = indexModifierParallel<outputIndexList, dim<dims2...>>::res;
};

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

template <typename... Args>
struct Merger;

template <int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2, typename... toArgs>
struct Merger<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, toArgs...>
{
    using fromQuMode = std::conditional_t<std::is_same_v<fromQuMode1, fromQuMode2>, fromQuMode1, defaultQuMode>;
    using fromOfMode = std::conditional_t<std::is_same_v<fromOfMode1, fromOfMode2>, fromOfMode1, defaultOfMode>;

    static inline constexpr auto toInt = tagExtractor<intBits<std::max(fromInt1, fromInt2)>, toArgs...>::value;
    static inline constexpr auto toFrac = tagExtractor<fracBits<std::max(fromFrac1, fromFrac2)>, toArgs...>::value;
    static inline constexpr auto toIsSigned = tagExtractor<isSigned<fromIsSigned1 || fromIsSigned2>, toArgs...>::value;
    using toQuMode = tagExtractor<QuMode<fromQuMode>, toArgs...>::type;
    using toOfMode = tagExtractor<OfMode<fromOfMode>, toArgs...>::type;

    using resType = Qu_s<intBits<toInt>, fracBits<toFrac>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>>;
};

template <typename... Args>
struct Qop;

template <int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2, typename... toArgs>
    requires(!isA<typename TypeList<toArgs...>::head, Qu_s<>>)
struct Qop<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, toArgs...>
{
    using merger = Merger<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, toArgs...>;

    static inline constexpr int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
    static inline constexpr int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;

    inline static constexpr auto mul(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> f2)
    {
        auto fullProduct = static_cast<long long int>(f1.data) * static_cast<long long int>(f2.data);
        auto fracProduct = fracConvert<fromFrac1 + fromFrac2, merger::toFrac, QuMode<typename merger::toQuMode>>::convert(fullProduct);
        auto intProduct = intConvert<merger::toInt, merger::toFrac, merger::toIsSigned, OfMode<typename merger::toOfMode>>::convert(fracProduct);

        return Qu_s<intBits<merger::toInt>, fracBits<merger::toFrac>, isSigned<merger::toIsSigned>, QuMode<typename merger::toQuMode>, OfMode<typename merger::toOfMode>>(intProduct, DirectAssignTag());
    }

    inline static constexpr auto add(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> f2)
    {
        auto fullSum = static_cast<long long int>(f1.data << shiftA) + static_cast<long long int>(f2.data << shiftB);
        auto fracSum = fracConvert<std::max(fromFrac1, fromFrac2), merger::toFrac, QuMode<typename merger::toQuMode>>::convert(fullSum);
        auto intSum = intConvert<merger::toInt, merger::toFrac, merger::toIsSigned, OfMode<typename merger::toOfMode>>::convert(fracSum);

        return Qu_s<intBits<merger::toInt>, fracBits<merger::toFrac>, isSigned<merger::toIsSigned>, QuMode<typename merger::toQuMode>, OfMode<typename merger::toOfMode>>(intSum, DirectAssignTag());
    }

    inline static constexpr auto sub(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> f2)
    {
        auto fullDiff = static_cast<long long int>(f1.data << shiftA) - static_cast<long long int>(f2.data << shiftB);
        auto fracDiff = fracConvert<std::max(fromFrac1, fromFrac2), merger::toFrac, QuMode<typename merger::toQuMode>>::convert(fullDiff);
        auto intDiff = intConvert<merger::toInt, merger::toFrac, merger::toIsSigned, OfMode<typename merger::toOfMode>>::convert(fracDiff);

        return Qu_s<intBits<merger::toInt>, fracBits<merger::toFrac>, isSigned<merger::toIsSigned>, QuMode<typename merger::toQuMode>, OfMode<typename merger::toOfMode>>(intDiff, DirectAssignTag());
    }

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

    inline static constexpr auto abs(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> f1)
    {
        auto absVal = std::abs(f1.data);
        return Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>(absVal, DirectAssignTag());
    }

    inline static constexpr auto neg(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> f1)
    {
        auto negVal = -f1.data;
        return Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<true>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>(negVal, DirectAssignTag());
    }

    inline static constexpr auto cmp(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> f2)
    {
        return (f1.data << shiftA) <=> (f2.data << shiftB);
    }

    inline static constexpr auto eq(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> f2)
    {
        return (f1.data << shiftA) == (f2.data << shiftB);
    }
};

template <typename... fromArgs1, typename... fromArgs2, typename... toArgs>
struct Qop<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, Qu_s<toArgs...>> : Qop<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, toArgs...>
{
};

template <size_t... dims1, size_t... dims2, int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2, typename... toArgs>
    requires(!isA<typename TypeList<toArgs...>::head, Qu_s<>>)
struct Qop<Qu_s<dim<dims1...>, Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>>, Qu_s<dim<dims2...>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>>, toArgs...>
{
    using resDim = elementWise::BroadcastHelper<dim<dims1...>, dim<dims2...>>::resultDim;
    static constexpr bool canBroadcast = elementWise::BroadcastHelper<dim<dims1...>, dim<dims2...>>::canBroadcast;

    static_assert(canBroadcast, "The dimensions of the two matrices are not compatible for element-wise addition");

    using outIndex = elementWise::elemwiseIndexCalculator<dim<dims1...>, dim<dims2...>>::outputIndexList;
    using in1Index = elementWise::elemwiseIndexCalculator<dim<dims1...>, dim<dims2...>>::input1IndexList;
    using in2Index = elementWise::elemwiseIndexCalculator<dim<dims1...>, dim<dims2...>>::input2IndexList;

    using merger = Merger<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, toArgs...>;

    static inline constexpr int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
    static inline constexpr int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;

    inline static constexpr auto mul(const Qu_s<dim<dims1...>, Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>> &f1, const Qu_s<dim<dims2...>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>> &f2)
    {
        static Qu_s<resDim, Qu_s<intBits<merger::toInt>, fracBits<merger::toFrac>, isSigned<merger::toIsSigned>, QuMode<typename merger::toQuMode>, OfMode<typename merger::toOfMode>>> res;
        elementWise::parallel<in1Index, in2Index, outIndex, toArgs...>::executeMulition(f1, f2, res);
        return res;
    }

    template <size_t... dims3, int toIntBits, int toFracBits, bool toIsSigned, typename toQuMode, typename toOfMode>
    inline static constexpr void mul(Qu_s<dim<dims3...>, Qu_s<intBits<toIntBits>, fracBits<toFracBits>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>>> &res, const Qu_s<dim<dims1...>, Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>> &f1, const Qu_s<dim<dims2...>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>> &f2)
    {
        elementWise::parallel<in1Index, in2Index, outIndex, toArgs...>::executeMulition(f1, f2, res);
    }

    inline static constexpr auto add(const Qu_s<dim<dims1...>, Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>> &f1, const Qu_s<dim<dims2...>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>> &f2)
    {
        static Qu_s<resDim, Qu_s<intBits<merger::toInt>, fracBits<merger::toFrac>, isSigned<merger::toIsSigned>, QuMode<typename merger::toQuMode>, OfMode<typename merger::toOfMode>>> res;
        elementWise::parallel<in1Index, in2Index, outIndex, toArgs...>::executeAddition(f1, f2, res);
        return res;
    }

    template <size_t... dims3, int toIntBits, int toFracBits, bool toIsSigned, typename toQuMode, typename toOfMode>
    inline static constexpr void add(Qu_s<dim<dims3...>, Qu_s<intBits<toIntBits>, fracBits<toFracBits>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>>> &res, const Qu_s<dim<dims1...>, Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>> &f1, const Qu_s<dim<dims2...>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>> &f2)
    {
        elementWise::parallel<in1Index, in2Index, outIndex, toArgs...>::executeAddition(f1, f2, res);
    }

    inline static constexpr auto sub(const Qu_s<dim<dims1...>, Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>> &f1, const Qu_s<dim<dims2...>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>> &f2)
    {
        static Qu_s<resDim, Qu_s<intBits<merger::toInt>, fracBits<merger::toFrac>, isSigned<merger::toIsSigned>, QuMode<typename merger::toQuMode>, OfMode<typename merger::toOfMode>>> res;
        elementWise::parallel<in1Index, in2Index, outIndex, toArgs...>::executeSubtraction(f1, f2, res);
        return res;
    }

    template <size_t... dims3, int toIntBits, int toFracBits, bool toIsSigned, typename toQuMode, typename toOfMode>
    inline static constexpr void sub(Qu_s<dim<dims3...>, Qu_s<intBits<toIntBits>, fracBits<toFracBits>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>>> &res, const Qu_s<dim<dims1...>, Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>> &f1, const Qu_s<dim<dims2...>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>> &f2)
    {
        elementWise::parallel<in1Index, in2Index, outIndex, toArgs...>::executeSubtraction(f1, f2, res);
    }

    inline static constexpr auto div(const Qu_s<dim<dims1...>, Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>> &f1, const Qu_s<dim<dims2...>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>> &f2)
    {
        static Qu_s<resDim, Qu_s<intBits<merger::toInt>, fracBits<merger::toFrac>, isSigned<merger::toIsSigned>, QuMode<typename merger::toQuMode>, OfMode<typename merger::toOfMode>>> res;
        elementWise::parallel<in1Index, in2Index, outIndex, toArgs...>::executeDivision(f1, f2, res);
        return res;
    }

    template <size_t... dims3, int toIntBits, int toFracBits, bool toIsSigned, typename toQuMode, typename toOfMode>
    inline static constexpr void div(Qu_s<dim<dims3...>, Qu_s<intBits<toIntBits>, fracBits<toFracBits>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>>> &res, const Qu_s<dim<dims1...>, Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>> &f1, const Qu_s<dim<dims2...>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>> &f2)
    {
        elementWise::parallel<in1Index, in2Index, outIndex, toArgs...>::executeDivision(f1, f2, res);
    }
};

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto Qmul(const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    return Qop<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, toArgs...>::mul(f1, f2);
}

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2, typename... resArgs>
inline constexpr void Qmul(Qu_s<resArgs...> &res, const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    Qop<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, toArgs...>::mul(res, f1, f2);
}

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto Qadd(const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    return Qop<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, toArgs...>::add(f1, f2);
}

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2, typename... resArgs>
inline constexpr void Qadd(Qu_s<resArgs...> &res, const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    Qop<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, toArgs...>::add(res, f1, f2);
}

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto Qsub(const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    return Qop<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, toArgs...>::sub(f1, f2);
}

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2, typename... resArgs>
inline constexpr void Qsub(Qu_s<resArgs...> &res, const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    Qop<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, toArgs...>::sub(res, f1, f2);
}

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto Qdiv(const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    return Qop<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, toArgs...>::div(f1, f2);
}

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2, typename... resArgs>
inline constexpr void Qdiv(Qu_s<resArgs...> &res, const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    Qop<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, toArgs...>::div(res, f1, f2);
}

template <typename... toArgs, typename... fromArgs>
inline constexpr auto Qabs(const Qu_s<fromArgs...> &f1)
{
    return Qop<Qu_s<fromArgs...>, Qu_s<fromArgs...>, toArgs...>::abs(f1);
}

template <typename... toArgs, typename... fromArgs>
inline constexpr auto Qneg(const Qu_s<fromArgs...> &f1)
{
    return Qop<Qu_s<fromArgs...>, Qu_s<fromArgs...>, toArgs...>::neg(f1);
}

// operator overloading
template <typename... fromArgs1, typename... fromArgs2>
inline constexpr auto operator*(const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    return Qmul<>(f1, f2);
}

template <typename... fromArgs1, typename... fromArgs2>
inline constexpr auto operator+(const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    return Qadd<>(f1, f2);
}

template <typename... fromArgs1, typename... fromArgs2>
inline constexpr auto operator-(const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    return Qsub<>(f1, f2);
}

template <typename... fromArgs1, typename... fromArgs2>
inline constexpr auto operator/(const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    return Qdiv<>(f1, f2);
}

template <typename... fromArgs>
inline constexpr auto operator-(const Qu_s<fromArgs...> &f1)
{
    return Qneg<>(f1);
}

template <typename... fromArgs1, typename... fromArgs2>
inline constexpr auto operator<=>(const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    return Qop<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>>::cmp(f1, f2);
}

template <typename... fromArgs1, typename... fromArgs2>
inline constexpr bool operator==(const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    return Qop<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>>::eq(f1, f2);
}

template <typename... fromArgs1, typename... fromArgs2>
inline constexpr bool operator!=(const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    return ~(Qop<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>>::eq(f1, f2));
}

// ------------------- Advanced Nonlinear Universal Subprograms -------------------
// the operations like lookup table, linear/polynomial fitting, etc. used to implement the non-linear operation in asic
// note that the operations are not standard BLAS operations, use ANUS:: to get access to them

namespace ANUS {
// polynomial fitting
template <auto... Coeffs>
struct Polyner;

//    co0 * (x + co1) * (x + co2) * ... * (x + coN)
//  currently does not support element-wise quantization like Qpoly<list>(x)
template <size_t len, typename... args, Qu_s<dim<len>, args...> Coeffs>
struct Polyner<Coeffs>
{
    template <size_t... I, typename... xArgs>
    static inline auto execute_impl(const Qu_s<xArgs...> x, std::index_sequence<I...>)
    {
        return Coeffs.template get<0>() * (... * (x + Coeffs.template get<I + 1>()));
    }

    template <typename... xArgs>
    static inline auto execute(const Qu_s<xArgs...> x)
    {
        return execute_impl(x, std::make_index_sequence<len - 1>());
    }
};

template <Qu_s Coeffs, typename... args>
inline auto constexpr Qpoly(const Qu_s<args...> x)
{
    return Polyner<Coeffs>::execute(x);
}

// lookup tables

// some pre-defined functions, stored as std::function

// sprt
inline static constexpr auto sqrtFunc = [](double x) { return std::sqrt(x); };

// reciprocal
inline static constexpr auto reciprocalFunc = [](double x) { return 1.0 / x; };

// reciprocal square root
inline static constexpr auto rsqrtFunc = [](double x) { return 1.0 / std::sqrt(x); };

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
    template <size_t layer,size_t len, typename ...fromArgs>
    static auto reduce_impl(const Qu_s<dim<len>, fromArgs...> &quants)
    {
        using type = typename ReducerTypeSelector<sizeof...(Args) != 0, layer>::type;

        static Qu_s<dim<(len + 1) / 2>, typename std::conditional_t<std::is_same_v<type, std::nullptr_t>, Qu<fromArgs...>, type>> res;
        if constexpr (len == 1)
        {
            return quants.template get<0>();
        }
        else
        {
            [&res=res, &quants=quants]<size_t... I>(std::index_sequence<I...>)
            {
                ((res.template get<I>() = Qadd<type>(quants.template get<I * 2>(), quants.template get<I * 2 + 1>())), ...);
            }(std::make_index_sequence<(len + 1) / 2>());
            
            if constexpr (len %2 !=0)
            {
                res.template get<(len + 1) / 2>() = quants.template get<len - 1>();
            }

            return reduce_impl<layer + 1>(res);
        }
    }

    template <size_t len, typename ...fromArgs>
    static auto reduce(const Qu_s<dim<len>, fromArgs...> &quants)
    {
        return reduce_impl<0>(quants);
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
requires (Qu_s<dim<rowA, colA>, ArgsA...>::isElementQu) || (Qu_s<dim<rowB, colB>, ArgsB...>::isElementQu) || (Qu_s<dim<rowC, colC>, ArgsC...>::isElementQu)
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
requires (!Qu_s<dim<rowA, colA>, ArgsA...>::isElementQu) && (!Qu_s<dim<rowB, colB>, ArgsB...>::isElementQu) && (!Qu_s<dim<rowC, colC>, ArgsC...>::isElementQu)
struct Qgemul_s<QgemulTransposedA<isTransposedA>, QgemulTransposedB<isTransposedB>, QgemulAddArgs<addArgs...>, QgemulMulArgs<mulArgs...>, Qu_s<dim<rowC, colC>, ArgsC...>, Qu_s<dim<rowA, colA>, ArgsA...>, Qu_s<dim<rowB, colB>, ArgsB...>>
{
    static_assert(
        (!isTransposedA && !isTransposedB && (colA == rowB && rowA == rowC && colB == colC)) ||
            (!isTransposedA && isTransposedB && (colA == colB && rowA == rowC && rowB == colC)) ||
            (isTransposedA && !isTransposedB && (rowA == rowB && colA == rowC && colB == colC)) ||
            (isTransposedA && isTransposedB && (rowA == colB && colA == rowC && rowB == colC)),
        "Size mismatch when calling Qgemul");


    // the intermediate vector for the dot product
    using mulMerger = Merger<Qu<ArgsA...>, Qu<ArgsB...>, mulArgs...>;
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
inline void Qgemul(Qu_s<dim<rowC, colC>, ArgsC...> &C, const Qu_s<dim<rowA, colA>, ArgsA...> &A, const Qu_s<dim<rowB, colB>, ArgsB...> &B)
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

// Gram matrix type generator
template <size_t N, typename... Args>
struct GramMatrix_s;

template <size_t N, typename... diagArgs, typename... offDiagArgs>
struct GramMatrix_s<N, Qu_s<diagArgs...>, Qu_s<offDiagArgs...>>
{
    template <typename T>
    struct helper;

    template <size_t... I>
    struct helper<std::index_sequence<I...>>
    {
        using type = TypeList<std::conditional_t<(I % (N + 1) == 0), Qu_s<diagArgs...>, Qu_s<offDiagArgs...>>...>;
    };

    using type = Qu<dim<N, N>, typename helper<std::make_index_sequence<N * N>>::type>;
};

template <size_t N, typename... Args>
using GramMatrix = typename GramMatrix_s<N, Args...>::type;

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
requires (Qu_s<dim<rowA, colA>, ArgsA...>::isElementQu) && (Qu_s<dim<rowC, colC>, ArgsC...>::isElementQu)
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
 
    static inline Qu_s<dim<isTransposed ? colA : rowA>,  std::conditional_t<sizeof...(diagMulArgs) == 0, Qu<ArgsA...>, Qu<diagMulArgs...>>> diagMulRes;
    static inline Qu_s<dim<isTransposed ? colA : rowA>,  std::conditional_t<sizeof...(offDiagMulArgs) == 0, Qu<ArgsA...>, Qu<offDiagMulArgs...>>> offDiagMulRes;

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
inline void Qgramul(Qu_s<dim<rowC, colC>, ArgsC...> &C, const Qu_s<dim<rowA, colA>, ArgsA...> &A)
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
requires (Qu_s<dim<sizeY>, ArgsY...>::isElementQu || Qu_s<dim<rowA, colA>, ArgsA...>::isElementQu || Qu_s<dim<sizeX>, ArgsX...>::isElementQu)
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
        ((execute_inner<I>(y, A, x, std::make_index_sequence < sizeX > ()), ...));
    }

    template <size_t I, size_t... J>
    static inline void execute_inner(Qu_s<dim<sizeY>, ArgsY...> &y, const Qu_s<dim<rowA, colA>, ArgsA...> &A, const Qu_s<dim<sizeX>, ArgsX...> &x, std::index_sequence<J...>)
    {
        auto addRes = Qreduce<addArgs...>(Qmul<mulArgs...>(A.template get<isTransposedA ? J : I, isTransposedA ? I : J>(), x.template get<J>())...);

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
requires (!Qu_s<dim<sizeY>, ArgsY...>::isElementQu && !Qu_s<dim<rowA, colA>, ArgsA...>::isElementQu && !Qu_s<dim<sizeX>, ArgsX...>::isElementQu)
struct Qgemv_s<QgemvTransposedA<isTransposedA>, QgemvAddArgs<addArgs...>, QgemvMulArgs<mulArgs...>, Qu_s<dim<sizeY>, ArgsY...>, Qu_s<dim<rowA, colA>, ArgsA...>, Qu_s<dim<sizeX>, ArgsX...>, QgemvAlpha<alpha>, QgemvBeta<beta>>
{
    static_assert(
        (!isTransposedA && (colA == sizeX && rowA == sizeY)) ||
            (isTransposedA && (rowA == sizeX && colA == sizeY)),
        "Size mismatch when calling Qgemv");

    using mulMerger = Merger<Qu<ArgsA...>, Qu<ArgsX...>, mulArgs...>;
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
inline void Qgemv(Qu_s<dim<sizeY>, ArgsY...> &y, const Qu_s<dim<rowA, colA>, ArgsA...> &A, const Qu_s<dim<sizeX>, ArgsX...> &x)
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
inline void Qpotrf(Qu_s<dim<row, col>, Args...> &A)
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
//         b[i] /= L[i * n + i];
//     }

//     // 后向替代
//     for (int i = n - 1; i >= 0; --i) {
//         for (int j = i + 1; j < n; ++j) {
//             b[i] -= L[j * n + i] * b[j];
//         }
//         b[i] /= L[i * n + i];
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
inline void Qpotrs(const Qu_s<dim<row, col>, LArgs...> &L, Qu_s<dim<bRow>, bArgs...> &b)
{
    Qpotrs_s<Qu_s<dim<row, col>, LArgs...>, Qu_s<dim<bRow>, bArgs...>>::execute(L, b);
}
