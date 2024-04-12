#pragma once

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

// 匹配失败，类型不符，继续递归
template <typename Tag, typename Tag2, typename... Args>
struct tagExtractor<Tag, Tag2, Args...> : tagExtractor<Tag, Args...>
{
};

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

    template <typename T>
    inline static constexpr int input(T val)
    {
        if constexpr (shift >= 0)
        {
            return static_cast<int>(static_cast<double>(val) * (1 << shift));
        }
        else
        {

            if (val < (1 << (-shift)))
            {
                return (static_cast<int>((static_cast<double>(val) * (1 << (-shift))) / (1 << (-shift)))) >> (-shift);
            }
            else
            {
                return static_cast<int>(static_cast<double>(val) / (1 << (-shift)));
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
    inline static auto convert(int val)
    {
        if constexpr (fromFrac <= toFrac)
        {
            return static_cast<long long int>(val) << (toFrac - fromFrac);
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
    inline static auto convert(int val)
    {
        if constexpr (fromFrac <= toFrac)
        {
            return static_cast<long long int>(val) << (toFrac - fromFrac);
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
    inline static auto convert(int val)
    {
        if constexpr (fromFrac <= toFrac)
        {
            return static_cast<long long int>(val) << (toFrac - fromFrac);
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
    inline static auto convert(int val)
    {
        using returnType = long long int;
        if constexpr (fromFrac <= toFrac)
        {
            return static_cast<returnType>(val) << (toFrac - fromFrac);
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
    inline static auto convert(int val)
    {
        using returnType = long long int;
        if constexpr (fromFrac <= toFrac)
        {
            return static_cast<returnType>(val) << (toFrac - fromFrac);
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
    inline static auto convert(int val)
    {
        return shifter<fromFrac - toFrac>::shiftRight(static_cast<long long int>(val));
    }
};

// template <int fromFrac, int toFrac>
// struct fracConvert<fromFrac, toFrac, QuMode<TRN::SMGN>>
// {
//     template <typename T>
//     inline static auto convert(T val)
//     {
//         using returnType =long long int;

//         if constexpr (fromFrac < toFrac)
//         {
//             return static_cast<returnType>(val) << (toFrac - fromFrac);
//         }
//         else
//         {
//             if (val >= 0)
//             {
//                 return static_cast<returnType>(val) >> (fromFrac - toFrac);
//             }
//             else
//             {
//                 return -((-static_cast<returnType>(val)) >> (fromFrac - toFrac));
//             }
//         }
//     }
// };

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
    inline static auto convert(long long int val)
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
    inline static auto convert(long long int val)
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
    inline static auto convert(long long int val)
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

    inline static auto convert(long long int val)
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
            return static_cast<int>(val & mask);
        }
    }
};

template <int toInt, int toFrac, bool toIsSigned, auto N>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<WRP::TCPL_SAT<N>>>
{
    inline static auto convert(long long int val)
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
        data = shifter<fracB>::template input<T>(val);

        data = fracConvert<fracBitsInput, fracB, QuMode<QuM>>::convert(data);
        data = intConvert<intBitsInput, fracBitsInput, isSignedInput, OfMode<OfM>>::convert(data);
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

    inline constexpr double output() const
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
        std::cout << "intBits: " << intB << " fracBits: " << fracB << " isSigned: " << isS << " ";
        std::cout << std::endl;
        std::cout << "Binary: " << std::bitset<intB + fracB + (isS ? 1 : 0)>(data) << std::endl;
        std::cout << "Hex: " << std::hex << data << std::dec << std::endl;

        std::cout << "Decimal: " << shifter<fracB>::output(data) << std::endl;
    }

    template <int intBitsFrom, int fracBitsFrom, bool isSignedFrom, typename QuModeFrom, typename OfModeFrom>
    inline constexpr bool operator!=(const Qu_s<intBits<intBitsFrom>, fracBits<fracBitsFrom>, isSigned<isSignedFrom>, QuMode<QuModeFrom>, OfMode<OfModeFrom>> &val)
    {
        return (this->output()) != val.output();
    }

    template <int intBitsFrom, int fracBitsFrom, bool isSignedFrom, typename QuModeFrom, typename OfModeFrom>
    inline constexpr bool operator==(const Qu_s<intBits<intBitsFrom>, fracBits<fracBitsFrom>, isSigned<isSignedFrom>, QuMode<QuModeFrom>, OfMode<OfModeFrom>> &val)
    {
        return (this->output()) == val.output();
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

template <size_t... dims, typename... Args>
class Qu_s<dim<dims...>, Args...>
{
public:
    using headType = typename TypeList<Args...>::head;

    static inline constexpr bool isElementQu = isA<headType, TypeList<>>;

    using QuType = Qu<Args...>;

    using arrayType = std::conditional_t<isElementQu, typename toTuple<headType>::type, std::array<QuType, dim<dims...>::elemSize>>;

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
            constexpr size_t nextDimProduct = dim<dims...>::template elemSizeForIndexHead<sizeof...(dims) - sizeof...(Rest) - 1>::value;
            return calculateIndex(accum + first * nextDimProduct, rest...);
        }
    }

    template <typename... Types>
    Qu_s(Types... values) : data{values...} {}

    Qu_s() {}

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

    void display(std::string name = "")
    {
        if constexpr (isElementQu)
        {
            static_assert(!isElementQu, "Not implemented yet");
        }
        else
        {
            if (name != "")
            {
                std::cout << name << " :";
            }
            std::cout << std::endl;
            for (size_t i = 0; i < dim<dims...>::elemSize; i++)
            {
                data[i].display();
            }
        }
    }
};

template <typename... Args, size_t... dims>
struct QuInputHelper<dim<dims...>, Args...>
{
    using type = Qu_s<dim<dims...>, Args...>;
};

template <typename... Args, size_t... dims>
struct QuInputHelper<dim<dims...>, Qu_s<Args...>>
{
    using type = Qu_s<dim<dims...>, Args...>;
};

// ------------------- element wise operations -------------------

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
} // namespace elementWise

// ------------------- Basic Operations -------------------
template <typename... Args>
struct Qop;

template <int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2, typename... toArgs>
struct Qop<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, toArgs...>
{
    using fromQuMode = std::conditional_t<std::is_same_v<fromQuMode1, fromQuMode2>, fromQuMode1, defaultQuMode>;
    using fromOfMode = std::conditional_t<std::is_same_v<fromOfMode1, fromOfMode2>, fromOfMode1, defaultOfMode>;

    static inline constexpr auto toInt = tagExtractor<intBits<std::max(fromInt1, fromInt2)>, toArgs...>::value;
    static inline constexpr auto toFrac = tagExtractor<fracBits<std::max(fromFrac1, fromFrac2)>, toArgs...>::value;
    static inline constexpr auto toIsSigned = tagExtractor<isSigned<defaultIsSigned>, toArgs...>::value;
    using toQuMode = tagExtractor<QuMode<fromQuMode>, toArgs...>::type;
    using toOfMode = tagExtractor<OfMode<fromOfMode>, toArgs...>::type;

    static inline constexpr int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
    static inline constexpr int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;

    inline static constexpr auto mul(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> &f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> &f2)
    {
        auto fullProduct = static_cast<std::conditional_t<toIsSigned, long long, unsigned long long>>(f1.data) * f2.data;
        auto fracProduct = fracConvert<fromFrac1 + fromFrac2, toFrac, QuMode<toQuMode>>::convert(fullProduct);
        auto intProduct = intConvert<toInt, toFrac, toIsSigned, OfMode<toOfMode>>::convert(fracProduct);

        return Qu_s<intBits<toInt>, fracBits<toFrac>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>>(intProduct, DirectAssignTag());
    }

    inline static constexpr auto add(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> &f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> &f2)
    {

        auto fullSum = static_cast<long long int>(f1.data << shiftA) + static_cast<long long int>(f2.data << shiftB);
        auto fracSum = fracConvert<std::max(fromFrac1, fromFrac2), toFrac, QuMode<toQuMode>>::convert(fullSum);
        auto intSum = intConvert<toInt, toFrac, toIsSigned, OfMode<toOfMode>>::convert(fracSum);

        return Qu_s<intBits<toInt>, fracBits<toFrac>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>>(intSum, DirectAssignTag());
    }

    inline static constexpr auto sub(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> &f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> &f2)
    {
        auto fullDiff = static_cast<long long int>(f1.data << shiftA) - static_cast<long long int>(f2.data << shiftB);
        auto fracDiff = fracConvert<std::max(fromFrac1, fromFrac2), toFrac, QuMode<toQuMode>>::convert(fullDiff);
        auto intDiff = intConvert<toInt, toFrac, toIsSigned, OfMode<toOfMode>>::convert(fracDiff);

        return Qu_s<intBits<toInt>, fracBits<toFrac>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>>(intDiff, DirectAssignTag());
    }

    inline static constexpr auto div(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> &f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> &f2)
    {
        if (f2.data == 0)
        {
            return Qu_s<intBits<toInt>, fracBits<toFrac>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>>(0, DirectAssignTag());
        }

        auto fullQuotient = (static_cast<long long int>(f1.data) << shiftA << toFrac) / (static_cast<long long int>(f2.data) << shiftB);
        auto intQuotient = intConvert<toInt, toFrac, toIsSigned, OfMode<toOfMode>>::convert(fullQuotient);

        return Qu_s<intBits<toInt>, fracBits<toFrac>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>>(intQuotient, DirectAssignTag());
    }

    inline static constexpr auto abs(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> &f1)
    {
        auto absVal = std::abs(f1.data);
        return Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>(absVal, DirectAssignTag());
    }

    inline static constexpr auto neg(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> &f1)
    {
        auto negVal = -f1.data;
        return Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<true>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>(negVal, DirectAssignTag());
    }

    inline static constexpr auto cmp(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> &f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> &f2)
    {
        return (f1.data << shiftA) <=> (f2.data << shiftB);
    }
};

template <size_t... dims1, size_t... dims2, int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2, typename... toArgs>
struct Qop<Qu_s<dim<dims1...>, intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<dim<dims2...>, intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, toArgs...>
{
    using resDim = elementWise::BroadcastHelper<dim<dims1...>, dim<dims2...>>::resultDim;
    static constexpr bool canBroadcast = elementWise::BroadcastHelper<dim<dims1...>, dim<dims2...>>::canBroadcast;

    static_assert(canBroadcast, "The dimensions of the two matrices are not compatible for element-wise addition");

    using outIndex = elementWise::elemwiseIndexCalculator<dim<dims1...>, dim<dims2...>>::outputIndexList;
    using in1Index = elementWise::elemwiseIndexCalculator<dim<dims1...>, dim<dims2...>>::input1IndexList;
    using in2Index = elementWise::elemwiseIndexCalculator<dim<dims1...>, dim<dims2...>>::input2IndexList;

    using fromQuMode = std::conditional_t<std::is_same_v<fromQuMode1, fromQuMode2>, fromQuMode1, defaultQuMode>;
    using fromOfMode = std::conditional_t<std::is_same_v<fromOfMode1, fromOfMode2>, fromOfMode1, defaultOfMode>;

    static inline constexpr auto toInt = tagExtractor<intBits<std::max(fromInt1, fromInt2)>, toArgs...>::value;
    static inline constexpr auto toFrac = tagExtractor<fracBits<std::max(fromFrac1, fromFrac2)>, toArgs...>::value;
    static inline constexpr auto toIsSigned = tagExtractor<isSigned<defaultIsSigned>, toArgs...>::value;
    using toQuMode = tagExtractor<QuMode<fromQuMode>, toArgs...>::type;
    using toOfMode = tagExtractor<OfMode<fromOfMode>, toArgs...>::type;

    static inline constexpr int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
    static inline constexpr int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;

    inline static constexpr auto mul(const Qu_s<dim<dims1...>, intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> &f1, const Qu_s<dim<dims2...>, intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> &f2)
    {
        static Qu_s<resDim, intBits<toInt>, fracBits<toFrac>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>> res;
        elementWise::parallel<in1Index, in2Index, outIndex, toArgs...>::executeMulition(f1, f2, res);
        return res;
    }

    inline static constexpr auto add(const Qu_s<dim<dims1...>, intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> &f1, const Qu_s<dim<dims2...>, intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> &f2)
    {
        static Qu_s<resDim, intBits<toInt>, fracBits<toFrac>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>> res;
        elementWise::parallel<in1Index, in2Index, outIndex, toArgs...>::executeAddition(f1, f2, res);
        return res;
    }

    inline static constexpr auto sub(const Qu_s<dim<dims1...>, intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> &f1, const Qu_s<dim<dims2...>, intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> &f2)
    {
        static Qu_s<resDim, intBits<toInt>, fracBits<toFrac>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>> res;
        elementWise::parallel<in1Index, in2Index, outIndex, toArgs...>::executeSubtraction(f1, f2, res);
        return res;
    }

    inline static constexpr auto div(const Qu_s<dim<dims1...>, intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> &f1, const Qu_s<dim<dims2...>, intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> &f2)
    {
        static Qu_s<resDim, intBits<toInt>, fracBits<toFrac>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>> res;
        elementWise::parallel<in1Index, in2Index, outIndex, toArgs...>::executeDivision(f1, f2, res);
        return res;
    }
};

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto Qmul(const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    return Qop<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, toArgs...>::mul(f1, f2);
}

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto Qadd(const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    return Qop<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, toArgs...>::add(f1, f2);
}

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto Qsub(const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    return Qop<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, toArgs...>::sub(f1, f2);
}

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto Qdiv(const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    return Qop<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, toArgs...>::div(f1, f2);
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
template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto operator*(const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    return Qmul<toArgs...>(f1, f2);
}

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto operator+(const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    return Qadd<toArgs...>(f1, f2);
}

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto operator-(const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    return Qsub<toArgs...>(f1, f2);
}

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto operator/(const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    return Qdiv<toArgs...>(f1, f2);
}

template <typename... toArgs, typename... fromArgs>
inline constexpr auto operator-(const Qu_s<fromArgs...> &f1)
{
    return Qneg<toArgs...>(f1);
}

template <typename... toArgs, typename... fromArgs1, typename... fromArgs2>
inline constexpr auto operator<=>(const Qu_s<fromArgs1...> &f1, const Qu_s<fromArgs2...> &f2)
{
    return Qop<Qu_s<fromArgs1...>, Qu_s<fromArgs2...>, toArgs...>::cmp(f1, f2);
}
