#pragma once

#include <algorithm>
#include <array>
#include <bit>
#include <bitset>
#include <cmath>
#include <compare>
#include <concepts>
#include <complex>
#include <csignal>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <format>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <numeric>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <sys/resource.h>
#include <sys/types.h>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

inline namespace QuBLAS {

// ------------------- Random -------------------

// The engines and distributions are stateful.  Keeping one instance per
// thread preserves the existing deterministic seed without introducing a
// data race when independent tensors are filled or shuffled concurrently.
inline thread_local std::random_device rd;
inline thread_local std::mt19937 gen(1);
inline thread_local std::uniform_int_distribution<uint64_t> UniRand(
    std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max());
inline thread_local std::normal_distribution<double> NormRand(0, 1);

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

template <size_t num_words>
std::array<uint64_t, num_words> string_to_big_integer(const std::string &str)
{
    std::array<uint64_t, num_words> result{};
    result.fill(0);

    bool is_negative = false;
    size_t index = 0;

    // Handle sign
    if (str[index] == '-')
    {
        is_negative = true;
        index++;
    }
    else if (str[index] == '+')
    {
        index++;
    }

    while (index < str.size())
    {
        char c = str[index++];
        if (c < '0' || c > '9')
        {
            throw std::invalid_argument("Invalid character in number string");
        }
        uint8_t digit = c - '0';

        // Multiply result by 10 and add digit
        uint64_t carry = digit;
        for (size_t i = 0; i < num_words; ++i)
        {
            __uint128_t temp = (__uint128_t)result[i] * 10 + carry;
            result[i] = static_cast<uint64_t>(temp);
            carry = static_cast<uint64_t>(temp >> 64);
        }
        if (carry != 0)
        {
            throw std::overflow_error("Number too large to fit in the specified number of words");
        }
    }

    if (is_negative)
    {
        // Take two's complement
        uint64_t carry = 1;
        for (size_t i = 0; i < num_words; ++i)
        {
            result[i] = ~result[i] + carry;
            if (result[i] != 0)
            {
                carry = 0;
            }
        }
    }

    return result;
}

constexpr void divide_by_uint64(const uint64_t *numerator, size_t num_words, uint64_t divisor, uint64_t *quotient, uint64_t &remainder)
{
    remainder = 0;
    for (size_t i = num_words; i-- > 0;)
    {
        __uint128_t dividend = ((__uint128_t)remainder << 64) | numerator[i];
        quotient[i] = static_cast<uint64_t>(dividend / divisor);
        remainder = static_cast<uint64_t>(dividend % divisor);
    }
}

template <size_t num_words>
constexpr auto big_integer_to_string(const std::array<uint64_t, num_words> &value)
{
    bool is_negative = false;
    uint64_t highest_word = value[num_words - 1];
    if (highest_word & (uint64_t(1) << 63))
    {
        is_negative = true;
    }
    std::array<uint64_t, num_words> magnitude;
    if (is_negative)
    {
        uint64_t carry = 1;
        for (size_t i = 0; i < num_words; ++i)
        {
            magnitude[i] = ~value[i] + carry;
            if (magnitude[i] != 0)
                carry = 0;
        }
    }
    else
    {
        magnitude = value;
    }

    std::string digits;
    if (std::all_of(magnitude.begin(), magnitude.end(), [](uint64_t w) { return w == 0; }))
    {
        digits = "0";
    }
    else
    {
        while (!std::all_of(magnitude.begin(), magnitude.end(), [](uint64_t w) { return w == 0; }))
        {
            uint64_t remainder = 0;
            std::array<uint64_t, num_words> quotient{};
            divide_by_uint64(magnitude.data(), num_words, 10, quotient.data(), remainder);
            digits.push_back('0' + remainder);
            magnitude = quotient;
        }
        std::reverse(digits.begin(), digits.end());
    }

    if (is_negative)
    {
        digits.insert(digits.begin(), '-');
    }

    return digits;
}

// ---------------------------- ArbiInt ----------------------------
// Fixed-capacity signed two's-complement integer. Every width uses the same
// little-endian limb representation; N controls result-width algebra while the
// unused part of the top limb carries the physical sign extension.
template <size_t N>
    requires(N > 0)
class ArbiInt
{
public:
    static constexpr size_t num_bits = N;
    static constexpr size_t num_words = (N + 63) / 64;
    static constexpr size_t top_bits = N % 64;
    static constexpr uint64_t mask = top_bits == 0
                                         ? std::numeric_limits<uint64_t>::max()
                                         : (uint64_t{1} << top_bits) - 1;

    std::array<uint64_t, num_words> data{};

    constexpr ArbiInt() = default;

    static constexpr ArbiInt allOnes()
    {
        ArbiInt result;
        result.data.fill(std::numeric_limits<uint64_t>::max());
        if constexpr (top_bits != 0)
            result.data.back() = mask;
        return result;
    }

    static constexpr ArbiInt maximum()
    {
        ArbiInt result;
        result.data.fill(std::numeric_limits<uint64_t>::max());
        constexpr size_t sign_offset = (N - 1) % 64;
        result.data.back() = sign_offset == 0
                                 ? uint64_t{0}
                                 : (uint64_t{1} << sign_offset) - 1;
        return result;
    }

    static constexpr ArbiInt allZeros()
    {
        ArbiInt result;
        if constexpr (top_bits != 0)
            result.data.back() = ~mask;
        return result;
    }

    static constexpr ArbiInt minimum()
    {
        ArbiInt result;
        constexpr size_t sign_offset = (N - 1) % 64;
        result.data.back() = std::numeric_limits<uint64_t>::max()
                             << sign_offset;
        return result;
    }

    constexpr bool isZero() const
    {
        return std::all_of(data.begin(), data.end(),
                           [](uint64_t word) { return word == 0; });
    }

    constexpr bool isNegative() const
    {
        return (data.back() >> 63) != 0;
    }

    constexpr bool isPositive() const
    {
        return !isNegative() && !isZero();
    }

    // Canonicalize a value that has deliberately been truncated to N logical
    // bits. Ordinary arithmetic does not call this: it widens first and keeps
    // the exact carry, matching the fixed-point layer's historical contract.
    constexpr void signExtendLogicalTop()
    {
        if constexpr (top_bits != 0)
        {
            constexpr uint64_t sign_bit = uint64_t{1} << (top_bits - 1);
            const uint64_t logical = data.back() & mask;
            data.back() = (logical & sign_bit) != 0 ? logical | ~mask : logical;
        }
    }

    template <typename T>
        requires std::is_integral_v<T>
    constexpr ArbiInt(T value)
    {
        if constexpr (N <= 32)
        {
            data[0] = static_cast<uint64_t>(
                static_cast<int64_t>(static_cast<int32_t>(value)));
        }
        else if constexpr (N <= 64)
        {
            data[0] = static_cast<uint64_t>(static_cast<int64_t>(value));
        }
        else
        {
            uint64_t extension = 0;
            if constexpr (std::is_signed_v<T>)
            {
                if (value < 0)
                    extension = std::numeric_limits<uint64_t>::max();
            }
            data.fill(extension);
            data[0] = static_cast<uint64_t>(value);
        }
    }

    template <size_t M>
    constexpr ArbiInt(const ArbiInt<M> &other)
    {
        constexpr size_t copied_words = std::min(num_words, ArbiInt<M>::num_words);
        std::copy_n(other.data.begin(), copied_words, data.begin());

        if constexpr (num_words > copied_words)
        {
            const uint64_t extension = other.isNegative()
                                           ? std::numeric_limits<uint64_t>::max()
                                           : uint64_t{0};
            std::fill(data.begin() + copied_words, data.end(), extension);
        }

        // Preserve the old small-storage conversion rule even though storage
        // is now uniformly a uint64_t limb.
        if constexpr (N <= 32)
        {
            data[0] = static_cast<uint64_t>(
                static_cast<int64_t>(static_cast<int32_t>(data[0])));
        }
    }

    constexpr ArbiInt(double value)
    {
        loadFromDouble<0>(value);
    }

    template <int fracB>
    constexpr void loadFromDouble(double value)
    {
        data.fill(0);

        const uint64_t bits = std::bit_cast<uint64_t>(value);
        const bool negative = (bits >> 63) != 0;
        const uint64_t exponent_bits = (bits >> 52) & 0x7ff;
        const uint64_t fraction = bits & 0x000fffffffffffffull;
        if (exponent_bits == 0x7ff)
            return;

        const uint64_t significand = exponent_bits == 0
                                         ? fraction
                                         : fraction | 0x0010000000000000ull;
        const int64_t shift = exponent_bits == 0
                                  ? static_cast<int64_t>(fracB) - 1074
                                  : static_cast<int64_t>(exponent_bits) - 1075 + fracB;

        if (shift >= 0)
        {
            const size_t word_shift = static_cast<size_t>(shift / 64);
            const unsigned bit_shift = static_cast<unsigned>(shift % 64);
            if (word_shift < num_words)
            {
                data[word_shift] = significand << bit_shift;
                if (bit_shift != 0 && word_shift + 1 < num_words)
                    data[word_shift + 1] = significand >> (64 - bit_shift);
            }
        }
        else if (shift > -64)
        {
            data[0] = significand >> -shift;
        }

        if (negative)
        {
            uint64_t carry = 1;
            for (auto &word : data)
            {
                const uint64_t inverted = ~word;
                word = inverted + carry;
                carry = carry != 0 && word == 0;
            }
        }

        if constexpr (N <= 32)
        {
            data[0] = static_cast<uint64_t>(
                static_cast<int64_t>(static_cast<int32_t>(data[0])));
        }
    }

    ArbiInt(const std::string &text)
    {
        if constexpr (N <= 64)
        {
            const int64_t value = std::stoll(text);
            uint64_t raw = static_cast<uint64_t>(value);
            if constexpr (N < 64)
            {
                constexpr uint64_t logical_mask = (uint64_t{1} << N) - 1;
                raw &= logical_mask;
                if (((raw >> (N - 1)) & 1) != 0)
                    raw |= ~logical_mask;
            }
            data[0] = raw;
        }
        else
        {
            data = string_to_big_integer<num_words>(text);
        }
    }

    constexpr operator bool() const
    {
        return !isZero();
    }

    ArbiInt &fill()
    {
        for (auto &word : data)
            word = UniRand(gen);
        signExtendLogicalTop();
        return *this;
    }

    constexpr auto toString() const
    {
        return big_integer_to_string(data);
    }

    constexpr double toDouble() const
    {
        return toDoubleScaled(0);
    }

    constexpr double toDoubleScaled(int binaryScale) const
    {
        const bool negative = isNegative();
        std::array<uint64_t, num_words> magnitude{};
        if (negative)
        {
            uint64_t carry = 1;
            for (size_t i = 0; i < num_words; ++i)
            {
                const uint64_t inverted = ~data[i];
                magnitude[i] = inverted + carry;
                carry = carry != 0 && magnitude[i] == 0;
            }
        }
        else
        {
            magnitude = data;
        }

        size_t used_words = num_words;
        while (used_words > 0 && magnitude[used_words - 1] == 0)
            --used_words;
        if (used_words == 0)
            return 0.0;

        const size_t high_word = used_words - 1;
        const size_t high_bit = high_word * 64 +
                                (63 - static_cast<size_t>(
                                          std::countl_zero(magnitude[high_word])));
        const int64_t scaled_exponent = static_cast<int64_t>(high_bit) + binaryScale;
        if (scaled_exponent > 1023)
            return negative ? -std::numeric_limits<double>::infinity()
                            : std::numeric_limits<double>::infinity();
        if (scaled_exponent < -1075)
            return negative ? -0.0 : 0.0;

        const auto shifted_right_low64 = [&magnitude](size_t shift) constexpr {
            const size_t word = shift / 64;
            const unsigned offset = shift % 64;
            if (word >= num_words)
                return uint64_t{0};

            uint64_t result = magnitude[word] >> offset;
            if (offset != 0 && word + 1 < num_words)
                result |= magnitude[word + 1] << (64 - offset);
            return result;
        };

        const auto bit_is_set = [&magnitude](size_t bit) constexpr {
            const size_t word = bit / 64;
            return word < num_words &&
                   ((magnitude[word] >> (bit % 64)) & 1) != 0;
        };

        const auto any_bit_below = [&magnitude](size_t exclusive) constexpr {
            const size_t complete_words = std::min(exclusive / 64, num_words);
            for (size_t i = 0; i < complete_words; ++i)
                if (magnitude[i] != 0)
                    return true;

            const unsigned remainder = exclusive % 64;
            if (complete_words < num_words && remainder != 0)
            {
                const uint64_t low_mask = (uint64_t{1} << remainder) - 1;
                return (magnitude[complete_words] & low_mask) != 0;
            }
            return false;
        };

        uint64_t significand = 0;
        int exponent = static_cast<int>(scaled_exponent);
        if (exponent >= -1022)
        {
            const size_t bit_length = high_bit + 1;
            if (bit_length <= 53)
            {
                significand = magnitude[0] << (53 - bit_length);
            }
            else
            {
                const size_t discarded = bit_length - 53;
                significand = shifted_right_low64(discarded);
                const bool guard = bit_is_set(discarded - 1);
                const bool sticky = any_bit_below(discarded - 1);
                if (guard && (sticky || (significand & 1) != 0))
                    ++significand;

                if (significand == (uint64_t{1} << 53))
                {
                    significand >>= 1;
                    ++exponent;
                    if (exponent > 1023)
                        return negative ? -std::numeric_limits<double>::infinity()
                                        : std::numeric_limits<double>::infinity();
                }
            }

            const double result = std::ldexp(static_cast<double>(significand),
                                             exponent - 52);
            return negative ? -result : result;
        }

        const int64_t scale_to_subnormal = static_cast<int64_t>(binaryScale) + 1074;
        if (scale_to_subnormal >= 0)
        {
            significand = magnitude[0] << static_cast<unsigned>(scale_to_subnormal);
        }
        else
        {
            const size_t discarded = static_cast<size_t>(-scale_to_subnormal);
            significand = shifted_right_low64(discarded);
            const bool guard = bit_is_set(discarded - 1);
            const bool sticky = any_bit_below(discarded - 1);
            if (guard && (sticky || (significand & 1) != 0))
                ++significand;
        }

        const double result = std::ldexp(static_cast<double>(significand), -1074);
        return negative ? -result : result;
    }

    constexpr auto toBinary() const
    {
        std::string result;
        if constexpr (N <= 32)
        {
            result = std::bitset<32>(data[0]).to_string();
        }
        else
        {
            for (size_t i = num_words; i-- > 0;)
                result += std::bitset<64>(data[i]).to_string();
        }
        return result;
    }

    void display(std::string name = "") const
    {
        if (!name.empty())
            std::cout << name << ":" << std::endl;
        std::cout << "N: " << N << std::endl;
        std::cout << "Binary:  " << toBinary() << std::endl;
        std::cout << "Decimal: " << toString() << std::endl;
        std::cout << std::endl;
    }
};

template <size_t N>
constexpr uint64_t arbiWord(const ArbiInt<N> &value, size_t index)
{
    if (index < ArbiInt<N>::num_words)
        return value.data[index];
    return value.isNegative() ? std::numeric_limits<uint64_t>::max() : 0;
}

template <size_t N>
constexpr void setArbiWord(ArbiInt<N> &value, size_t index, uint64_t word)
{
    if (index < ArbiInt<N>::num_words)
        value.data[index] = word;
}

template <size_t N, size_t M>
constexpr auto operator+(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    constexpr size_t R = std::max(N, M) + 1;
    ArbiInt<R> result;
    uint64_t carry = 0;
    for (size_t i = 0; i < ArbiInt<R>::num_words; ++i)
    {
        const uint64_t a = arbiWord(lhs, i);
        const uint64_t b = arbiWord(rhs, i);
        const uint64_t partial = a + b;
        const bool first_carry = partial < a;
        const uint64_t sum = partial + carry;
        const bool second_carry = sum < partial;
        result.data[i] = sum;
        carry = first_carry || second_carry;
    }
    return result;
}

template <size_t N, size_t M>
constexpr auto operator-(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    constexpr size_t R = std::max(N, M) + 1;
    ArbiInt<R> result;
    uint64_t borrow = 0;
    for (size_t i = 0; i < ArbiInt<R>::num_words; ++i)
    {
        const uint64_t a = arbiWord(lhs, i);
        const uint64_t b = arbiWord(rhs, i);
        const uint64_t subtrahend = b + borrow;
        const bool add_overflow = borrow != 0 && subtrahend == 0;
        result.data[i] = a - subtrahend;
        borrow = add_overflow || a < subtrahend;
    }
    return result;
}

template <size_t N>
constexpr auto operator-(const ArbiInt<N> &value)
{
    ArbiInt<N + 1> result;
    uint64_t carry = 1;
    for (size_t i = 0; i < ArbiInt<N + 1>::num_words; ++i)
    {
        const uint64_t inverted = ~arbiWord(value, i);
        result.data[i] = inverted + carry;
        carry = carry != 0 && result.data[i] == 0;
    }
    return result;
}

template <size_t N, size_t M>
constexpr auto operator*(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    constexpr size_t R = N + M;
    ArbiInt<R> result;

    // Multiplication of finite sign-extended two's-complement vectors is the
    // ordinary unsigned convolution modulo the result's physical word width.
    for (size_t i = 0; i < ArbiInt<R>::num_words; ++i)
    {
        __uint128_t carry = 0;
        for (size_t j = 0; i + j < ArbiInt<R>::num_words; ++j)
        {
            const size_t k = i + j;
            const __uint128_t product =
                static_cast<__uint128_t>(arbiWord(lhs, i)) * arbiWord(rhs, j);
            const __uint128_t accumulated = product + result.data[k] + carry;
            result.data[k] = static_cast<uint64_t>(accumulated);
            carry = accumulated >> 64;
        }
    }
    return result;
}

// Signed two's-complement division.  The extra result bit represents
// min_value / -1 without overflow.  Remainder follows the dividend sign, as
// in C++ truncation-toward-zero division; quantization-specific correction is
// deliberately performed by the fixed-point layer afterwards.
template <size_t N, size_t M>
struct ArbiDivResult
{
    static constexpr size_t width = std::max(N, M) + 1;
    ArbiInt<width> quotient;
    ArbiInt<width> remainder;
};

template <size_t N, size_t M>
constexpr auto divmod(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    constexpr size_t R = std::max(N, M) + 1;
    constexpr size_t W = (R + 63) / 64;
    using words_t = std::array<uint64_t, W>;

    const bool lhs_negative = lhs.isNegative();
    const bool rhs_negative = rhs.isNegative();

    auto magnitude = []<size_t K>(const ArbiInt<K> &value) constexpr {
        words_t words{};
        for (size_t i = 0; i < W; ++i)
            words[i] = arbiWord(value, i);
        if (value.isNegative())
        {
            uint64_t carry = 1;
            for (size_t i = 0; i < W; ++i)
            {
                const uint64_t inverted = ~words[i];
                words[i] = inverted + carry;
                carry = carry && words[i] == 0;
            }
        }
        return words;
    };

    const words_t dividend = magnitude(lhs);
    const words_t divisor = magnitude(rhs);
    bool divisor_zero = true;
    for (uint64_t word : divisor)
        divisor_zero &= word == 0;
    if (divisor_zero)
        throw std::domain_error("ArbiInt division by zero");

    words_t quotient{};
    words_t remainder{};

    auto unsigned_ge = [](const words_t &a, const words_t &b) constexpr {
        for (size_t i = W; i-- > 0;)
        {
            if (a[i] != b[i])
                return a[i] > b[i];
        }
        return true;
    };

    auto unsigned_subtract = [](words_t &a, const words_t &b) constexpr {
        uint64_t borrow = 0;
        for (size_t i = 0; i < W; ++i)
        {
            const uint64_t before = a[i];
            const uint64_t subtrahend = b[i] + borrow;
            const bool add_overflow = borrow && subtrahend == 0;
            a[i] = before - subtrahend;
            borrow = add_overflow || before < subtrahend;
        }
    };

    for (size_t bit = W * 64; bit-- > 0;)
    {
        uint64_t carry = (dividend[bit / 64] >> (bit % 64)) & 1;
        for (size_t i = 0; i < W; ++i)
        {
            const uint64_t next = remainder[i] >> 63;
            remainder[i] = (remainder[i] << 1) | carry;
            carry = next;
        }
        if (unsigned_ge(remainder, divisor))
        {
            unsigned_subtract(remainder, divisor);
            quotient[bit / 64] |= uint64_t{1} << (bit % 64);
        }
    }

    auto apply_sign = [](words_t &words, bool negative) constexpr {
        if (!negative)
            return;
        uint64_t carry = 1;
        for (size_t i = 0; i < W; ++i)
        {
            const uint64_t inverted = ~words[i];
            words[i] = inverted + carry;
            carry = carry && words[i] == 0;
        }
    };
    apply_sign(quotient, lhs_negative != rhs_negative);
    apply_sign(remainder, lhs_negative);

    ArbiDivResult<N, M> result;
    for (size_t i = 0; i < W; ++i)
    {
        setArbiWord(result.quotient, i, quotient[i]);
        setArbiWord(result.remainder, i, remainder[i]);
    }
    return result;
}

template <size_t N, size_t M>
constexpr auto operator/(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    return divmod(lhs, rhs).quotient;
}

template <size_t N, size_t M>
constexpr auto operator%(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    return divmod(lhs, rhs).remainder;
}

// For canonical logical values, static shifts change the type width so no
// mathematical information is lost. Deliberate headroom values may still hit
// the physical top-limb sign bit at an exact 64-bit boundary.
template <int shift, size_t N>
constexpr auto staticShiftRight(const ArbiInt<N> &value);

template <int shift, size_t N>
    requires(shift > 0)
constexpr auto staticShiftLeftImpl(const ArbiInt<N> &value)
{
    ArbiInt<N + static_cast<size_t>(shift)> result;
    constexpr size_t output_words = (N + shift + 63) / 64;
    constexpr size_t word_shift = shift / 64;
    constexpr size_t bit_shift = shift % 64;

    for (size_t i = 0; i < output_words; ++i)
    {
        uint64_t word = 0;
        if (i >= word_shift)
        {
            const size_t source_index = i - word_shift;
            word = arbiWord(value, source_index) << bit_shift;
            if constexpr (bit_shift != 0)
            {
                if (source_index > 0)
                    word |= arbiWord(value, source_index - 1) >> (64 - bit_shift);
            }
        }
        setArbiWord(result, i, word);
    }
    return result;
}

template <int shift, size_t N>
constexpr auto staticShiftLeft(const ArbiInt<N> &value)
{
    if constexpr (shift > 0)
        return staticShiftLeftImpl<shift>(value);
    else if constexpr (shift < 0)
        return staticShiftRight<-shift>(value);
    else
        return value;
}

template <int shift, size_t N>
constexpr auto staticShiftRight(const ArbiInt<N> &value)
{
    if constexpr (shift < 0)
    {
        return staticShiftLeft<-shift>(value);
    }
    else if constexpr (shift == 0)
    {
        return value;
    }
    else if constexpr (static_cast<size_t>(shift) >= N)
    {
        ArbiInt<1> result;
        result.data[0] = value.isNegative()
                             ? std::numeric_limits<uint64_t>::max()
                             : uint64_t{0};
        return result;
    }
    else
    {
        constexpr size_t R = N - static_cast<size_t>(shift);
        constexpr size_t word_shift = shift / 64;
        constexpr size_t bit_shift = shift % 64;
        ArbiInt<R> result;
        for (size_t i = 0; i < ArbiInt<R>::num_words; ++i)
        {
            const uint64_t low = arbiWord(value, i + word_shift);
            if constexpr (bit_shift == 0)
            {
                result.data[i] = low;
            }
            else
            {
                const uint64_t high = arbiWord(value, i + word_shift + 1);
                result.data[i] = (low >> bit_shift) |
                                 (high << (64 - bit_shift));
            }
        }
        return result;
    }
}

template <size_t N, size_t M>
constexpr bool operator==(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    constexpr size_t words = std::max(ArbiInt<N>::num_words,
                                      ArbiInt<M>::num_words);
    for (size_t i = 0; i < words; ++i)
        if (arbiWord(lhs, i) != arbiWord(rhs, i))
            return false;
    return true;
}

template <size_t N, size_t M>
constexpr auto operator<=>(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    if (lhs.isNegative() != rhs.isNegative())
        return lhs.isNegative() ? std::strong_ordering::less
                                : std::strong_ordering::greater;

    constexpr size_t words = std::max(ArbiInt<N>::num_words,
                                      ArbiInt<M>::num_words);
    for (size_t i = words; i-- > 0;)
    {
        const uint64_t a = arbiWord(lhs, i);
        const uint64_t b = arbiWord(rhs, i);
        if (a != b)
            return a < b ? std::strong_ordering::less
                         : std::strong_ordering::greater;
    }
    return std::strong_ordering::equal;
}

template <size_t N, size_t M>
constexpr auto operator^(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    ArbiInt<std::max(N, M)> result;
    for (size_t i = 0; i < decltype(result)::num_words; ++i)
        result.data[i] = arbiWord(lhs, i) ^ arbiWord(rhs, i);
    return result;
}

template <size_t N, size_t M>
constexpr auto operator&(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    ArbiInt<std::max(N, M)> result;
    for (size_t i = 0; i < decltype(result)::num_words; ++i)
        result.data[i] = arbiWord(lhs, i) & arbiWord(rhs, i);
    return result;
}

template <size_t N, size_t M>
constexpr auto operator|(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    ArbiInt<std::max(N, M)> result;
    for (size_t i = 0; i < decltype(result)::num_words; ++i)
        result.data[i] = arbiWord(lhs, i) | arbiWord(rhs, i);
    return result;
}

template <size_t N>
constexpr auto operator~(const ArbiInt<N> &value)
{
    ArbiInt<N> result;
    for (size_t i = 0; i < ArbiInt<N>::num_words; ++i)
        result.data[i] = ~value.data[i];
    return result;
}

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

template <int fromFrac, int toFrac, typename QuMode>
struct fracConvert;

template <int discardedBits, size_t N>
    requires(discardedBits > 0)
inline constexpr auto splitQuantizedBits(const ArbiInt<N> &val)
{
    auto floor = staticShiftRight<discardedBits>(val);
    // Computing r = x - floor(x / 2^d) * 2^d avoids signed-mask bugs when d
    // is exactly 32, 64, 128, ... .  The remainder is always in [0, 2^d).
    auto remainder = val - staticShiftLeft<discardedBits>(floor);
    return std::pair{floor, remainder};
}

template <int discardedBits>
inline constexpr auto quantizationHalf()
{
    static_assert(discardedBits > 0);
    // Start with two bits so the half value never occupies a sign bit.
    return staticShiftLeft<discardedBits - 1>(ArbiInt<2>(1));
}

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<RND::POS_INF>>
{
    template <size_t N>
    inline static constexpr auto convert(ArbiInt<N> val)
    {
        if constexpr (fromFrac <= toFrac)
        {
            return staticShiftLeft<toFrac - fromFrac>(val);
        }
        else
        {
            constexpr int discarded = fromFrac - toFrac;
            auto [floor, remainder] = splitQuantizedBits<discarded>(val);
            constexpr auto half = quantizationHalf<discarded>();
            return floor + ArbiInt<1>(remainder >= half);
        }
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<RND::NEG_INF>>
{
    template <size_t N>
    inline static constexpr auto convert(ArbiInt<N> val)
    {
        if constexpr (fromFrac <= toFrac)
        {
            return staticShiftLeft<toFrac - fromFrac>(val);
        }
        else
        {
            constexpr int discarded = fromFrac - toFrac;
            auto [floor, remainder] = splitQuantizedBits<discarded>(val);
            constexpr auto half = quantizationHalf<discarded>();
            return floor + ArbiInt<1>(remainder > half);
        }
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<RND::ZERO>>
{
    template <size_t N>
    inline static constexpr auto convert(ArbiInt<N> val)
    {
        if constexpr (fromFrac <= toFrac)
        {
            return staticShiftLeft<toFrac - fromFrac>(val);
        }
        else
        {
            constexpr int discarded = fromFrac - toFrac;
            auto [floor, remainder] = splitQuantizedBits<discarded>(val);
            constexpr auto half = quantizationHalf<discarded>();
            const bool increment = remainder > half ||
                                   (remainder == half && val.isNegative());
            return floor + ArbiInt<1>(increment);
        }
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<RND::INF>>
{
    template <size_t N>
    inline static constexpr auto convert(ArbiInt<N> val)
    {
        if constexpr (fromFrac <= toFrac)
        {
            return staticShiftLeft<toFrac - fromFrac>(val);
        }
        else
        {
            constexpr int discarded = fromFrac - toFrac;
            auto [floor, remainder] = splitQuantizedBits<discarded>(val);
            constexpr auto half = quantizationHalf<discarded>();
            const bool increment = remainder > half ||
                                   (remainder == half && !val.isNegative());
            return floor + ArbiInt<1>(increment);
        }
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<RND::CONV>>
{
    template <size_t N>
    inline static constexpr auto convert(ArbiInt<N> val)
    {
        if constexpr (fromFrac <= toFrac)
        {
            return staticShiftLeft<toFrac - fromFrac>(val);
        }
        else
        {
            constexpr int discarded = fromFrac - toFrac;
            auto [floor, remainder] = splitQuantizedBits<discarded>(val);
            constexpr auto half = quantizationHalf<discarded>();
            const bool floor_is_odd = (arbiWord(floor, 0) & 1) != 0;
            const bool increment = remainder > half ||
                                   (remainder == half && floor_is_odd);
            return floor + ArbiInt<1>(increment);
        }
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<TRN::TCPL>>
{
    inline static constexpr auto convert(auto val)
    {
        return staticShiftRight<fromFrac - toFrac>(val);
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<TRN::SMGN>>
{
    template <size_t N>
    inline static constexpr auto convert(ArbiInt<N> val)
    {
        constexpr int resN_ = static_cast<int>(N) + (toFrac - fromFrac);
        constexpr size_t resN = (resN_ < 1) ? 1 : resN_;

        using resType = ArbiInt<resN>;

        if constexpr (fromFrac <= toFrac)
        {
            return resType(staticShiftLeft<toFrac - fromFrac>(val));
        }
        else
        {
            constexpr int discarded = fromFrac - toFrac;
            auto [floor, remainder] = splitQuantizedBits<discarded>(val);
            const bool increment = val.isNegative() && !remainder.isZero();
            return resType(floor + ArbiInt<1>(increment));
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

template <int toInt, int toFrac, bool toIsSigned, typename OfMode>
struct intConvert;

template <size_t ResultWidth, size_t KeptBits, bool SignExtend, size_t N>
inline constexpr auto wrapArbiLowBits(const ArbiInt<N> &val)
{
    static_assert(ResultWidth > 0);
    static_assert(KeptBits <= ResultWidth);
    ArbiInt<ResultWidth> result;
    if constexpr (KeptBits == 0)
    {
        return result;
    }
    else
    {
        constexpr size_t physical_words = (ResultWidth + 63) / 64;
        constexpr size_t full_words = KeptBits / 64;
        constexpr size_t partial_bits = KeptBits % 64;
        const bool negative = SignExtend &&
                              (((arbiWord(val, (KeptBits - 1) / 64) >>
                                 ((KeptBits - 1) % 64)) &
                                1) != 0);

        for (size_t i = 0; i < physical_words; ++i)
        {
            uint64_t word;
            if (i < full_words)
            {
                word = arbiWord(val, i);
            }
            else if constexpr (partial_bits != 0)
            {
                if (i == full_words)
                {
                    constexpr uint64_t mask = (uint64_t{1} << partial_bits) - 1;
                    word = arbiWord(val, i) & mask;
                    if (negative)
                        word |= ~mask;
                }
                else
                {
                    word = negative ? std::numeric_limits<uint64_t>::max() : 0;
                }
            }
            else
            {
                word = negative ? std::numeric_limits<uint64_t>::max() : 0;
            }
            setArbiWord(result, i, word);
        }
        return result;
    }
}

template <size_t N>
inline constexpr void setArbiBit(ArbiInt<N> &value, size_t bit, bool set)
{
    const size_t word_index = bit / 64;
    const uint64_t mask = uint64_t{1} << (bit % 64);
    uint64_t word = arbiWord(value, word_index);
    word = set ? word | mask : word & ~mask;
    setArbiWord(value, word_index, word);
}

template <int toInt, int toFrac, bool toIsSigned>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<SAT::TCPL>>
{
    template <size_t N>
    inline static constexpr auto convert(ArbiInt<N> val)
    {
        constexpr auto floor = ArbiInt<1 + toInt + toFrac>::maximum();
        constexpr auto ceil = toIsSigned ? ArbiInt<1 + toInt + toFrac>::minimum() : ArbiInt<1 + toInt + toFrac>(0);

        if (val > floor)
        {
            return floor;
        }
        else if (val < ceil)
        {
            return ceil;
        }
        else
        {
            return ArbiInt<1 + toInt + toFrac>(val);
        }
    }
};

template <int toInt, int toFrac, bool toIsSigned>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<SAT::ZERO>>
{
    template <size_t N>
    inline static constexpr auto convert(ArbiInt<N> val)
    {
        constexpr auto floor = ArbiInt<1 + toInt + toFrac>::maximum();
        constexpr auto ceil = toIsSigned ? ArbiInt<1 + toInt + toFrac>::minimum() : ArbiInt<1 + toInt + toFrac>(0);

        constexpr auto zeroRes = ArbiInt<1 + toInt + toFrac>(0);

        if (val > floor)
        {
            return zeroRes;
        }
        else if (val < ceil)
        {
            return zeroRes;
        }
        else
        {
            return ArbiInt<1 + toInt + toFrac>(val);
        }
    }
};

template <int toInt, int toFrac, bool toIsSigned>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<SAT::SMGN>>
{
    template <size_t N>
    inline static constexpr auto convert(ArbiInt<N> val)
    {
        constexpr auto floor = ArbiInt<1 + toInt + toFrac>::maximum();
        constexpr auto ceil = toIsSigned ? ArbiInt<1 + toInt + toFrac>(ArbiInt<1 + toInt + toFrac>::minimum() + ArbiInt<1>(1)) : ArbiInt<1 + toInt + toFrac>(0);

        if (val > floor)
        {
            return floor;
        }
        else if (val < ceil)
        {
            return ceil;
        }
        else
        {
            return ArbiInt<1 + toInt + toFrac>(val);
        }
    }
};

template <int toInt, int toFrac, bool toIsSigned>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<WRP::TCPL>>
{

    inline static constexpr auto convert(auto val)
    {
        constexpr size_t result_width = 1 + toInt + toFrac;
        if constexpr (toIsSigned)
        {
            return wrapArbiLowBits<result_width, result_width, true>(val);
        }
        else
        {
            return wrapArbiLowBits<result_width, result_width - 1, false>(val);
        }
    }
};

template <auto Count>
consteval size_t normalizedWrapSaturationBits(size_t limit)
{
    using count_type = std::remove_cv_t<decltype(Count)>;
    if constexpr (std::is_arithmetic_v<count_type> || std::is_enum_v<count_type>)
    {
        const long double count = static_cast<long double>(Count);
        if (!(count > 0))
            return 0;
        if (count >= static_cast<long double>(limit))
            return limit;
        return static_cast<size_t>(count);
    }
    else if constexpr (requires { static_cast<size_t>(Count); })
    {
        const size_t count = static_cast<size_t>(Count);
        return std::min(count, limit);
    }
    else
    {
        // The historical tag is template<auto>.  Keep otherwise-valid NTTPs
        // source-compatible by treating an uncountable value as N == 0.
        return 0;
    }
}

template <int toInt, int toFrac, bool toIsSigned, auto N>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<WRP::TCPL_SAT<N>>>
{
    inline static constexpr auto convert(auto val)
    {
        constexpr size_t result_width = 1 + toInt + toFrac;
        constexpr size_t effective_width = toIsSigned ? result_width : result_width - 1;
        constexpr size_t saturation_bits =
            normalizedWrapSaturationBits<N>(effective_width);

        constexpr auto maximum = ArbiInt<result_width>::maximum();
        constexpr auto minimum = toIsSigned ? ArbiInt<result_width>::minimum()
                                             : ArbiInt<result_width>(0);
        const bool overflow = val > maximum || val < minimum;

        if constexpr (toIsSigned)
        {
            auto result = wrapArbiLowBits<result_width, result_width, true>(val);
            if (!overflow || saturation_bits == 0)
                return result;

            const bool sign = val.isNegative();
            setArbiBit(result, result_width - 1, sign);
            for (size_t i = 1; i < saturation_bits; ++i)
                setArbiBit(result, result_width - 1 - i, !sign);
            // Re-extend the forced target sign through unused physical bits.
            return wrapArbiLowBits<result_width, result_width, true>(result);
        }
        else
        {
            auto result = wrapArbiLowBits<result_width, result_width - 1, false>(val);
            if (!overflow || saturation_bits == 0)
                return result;

            for (size_t i = 0; i < saturation_bits; ++i)
                setArbiBit(result, effective_width - 1 - i, true);
            return result;
        }
    }
};

template <int Value>
struct intBits;

template <int Value>
struct fracBits;

template <bool Value>
struct isSigned;

constexpr int defaultIntBits = 8;
constexpr int defaultFracBits = 8;
constexpr bool defaultIsSigned = true;
using defaultQuMode = TRN::TCPL;
using defaultOfMode = WRP::TCPL;

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
    static_assert(0 <= (intBitsInput + fracBitsInput), "The total number of bits must be non-negative.");

    inline static constexpr int intB = intBitsInput;
    inline static constexpr int fracB = fracBitsInput;
    inline static constexpr bool isS = isSignedInput;
    using QuM_t = QuModeInput;
    using OfM_t = OfModeInput;
    inline static constexpr int QuM = QuModeInput::value;
    inline static constexpr int OfM = OfModeInput::value;

    // Low-level escape hatch: intentionally public, intentionally unstable.
    // Users may inspect or manipulate the raw ArbiInt, but its representation
    // and helper surface are outside QuBLAS' compatibility contract.
    // No matter whether the sign bit is requested by the user, the internal
    // fixed-point representation always carries one sign bit.
    ArbiInt<1 + intB + fracB> data;

    inline constexpr Qu_s(double val)
    {
        // Every finite IEEE-754 binary64 value is an integer multiple of
        // 2^-1074.  This fixed exact representation covers subnormals and the
        // full normal exponent range; fracConvert then performs the selected
        // quantization before intConvert applies overflow handling.
        ArbiInt<2099> buffer;
        buffer.template loadFromDouble<1074>(val);

        data = intConvert<intB, fracB, isS, OfMode<OfM_t>>::convert(fracConvert<1074, fracB, QuMode<QuM_t>>::convert(buffer));
    }

    template <typename T>
        requires std::is_integral_v<std::remove_cv_t<T>>
    inline constexpr Qu_s(T val)
    {
        using input_t = std::remove_cv_t<T>;
        // One additional bit gives every unsigned input a zero sign bit while
        // retaining the complete range of a signed input.
        constexpr size_t inputWidth = std::numeric_limits<input_t>::digits + 1;
        const ArbiInt<inputWidth> buffer(val);
        const auto scaled = fracConvert<0, fracB, QuMode<QuM_t>>::convert(buffer);
        data = intConvert<intB, fracB, isS, OfMode<OfM_t>>::convert(scaled);
    }

    inline constexpr Qu_s() : data() {}

    // from another static Qu_s
    template <int intBitsFrom, int fracBitsFrom, bool isSignedFrom, typename QuModeFrom, typename OfModeFrom>
    inline constexpr Qu_s(const Qu_s<intBits<intBitsFrom>, fracBits<fracBitsFrom>, isSigned<isSignedFrom>, QuMode<QuModeFrom>, OfMode<OfModeFrom>> &val)
    {
        if constexpr (intBitsFrom == intBitsInput && fracBitsFrom == fracBitsInput && isSignedFrom == isSignedInput && std::is_same_v<QuModeFrom, QuModeInput> && std::is_same_v<OfModeFrom, OfModeInput>)
        {
            data = val.data;
        }
        else
        {
            data = intConvert<intB, fracB, isS, OfMode<OfM_t>>::convert(fracConvert<fracBitsFrom, fracBitsInput, QuMode<QuM_t>>::convert(val.data));

            // data = fracConvert<fracBitsFrom, fracBitsInput, QuMode<QuM_t>>::convert(val.data);
        }
    }

    inline double toDouble() const
    {
        return data.toDoubleScaled(-fracB);
    }

    inline void display(std::string name = "") const
    {
        if (name != "")
        {
            std::cout << name << " :" << std::endl;
        }

        std::cout << "intBits: " << intB << " fracBits: " << fracB << " isSigned: " << isS << std::endl;

        std::cout << "Binary: " << this->toString() << " " << this->data.toString() << std::endl;

        std::cout << "Decimal: " << this->toDouble() << std::endl;
        std::cout << std::endl;
    }

    inline constexpr auto toString() const
    {
        std::string originalBinary = this->data.toBinary();
        std::string binary = originalBinary.substr(originalBinary.size() - isS - intB - fracB, intB + fracB + isS);
        return binary;
    }

    inline Qu_s &fill()
    {
        this->data.fill();
        if constexpr (!isS)
        {
            constexpr size_t storageWidth = 1 + intB + fracB;
            constexpr size_t valueWidth = intB + fracB;
            this->data = wrapArbiLowBits<storageWidth, valueWidth, false>(this->data);
        }

        return *this;
    }

    inline Qu_s &fill(int val)
    {
        *this = Qu_s(val);

        return *this;
    }

    // overload for std::cout
    friend std::ostream &operator<<(std::ostream &os, const Qu_s &qu)
    {
        os << qu.toDouble();
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

// ------------------- Strict value-tag facade -------------------
//
// Qu keeps the original type-tag grammar.  Q is a deliberately separate
// value-tag facade: it offers terse literals without weakening or changing the
// legacy spelling.

namespace detail {

template <typename Legacy>
struct value_tag
{
    using legacy = Legacy;
};

template <typename>
inline constexpr int legacy_tag_category = 0;
template <int Value>
inline constexpr int legacy_tag_category<intBits<Value>> = 1;
template <int Value>
inline constexpr int legacy_tag_category<fracBits<Value>> = 2;
template <bool Value>
inline constexpr int legacy_tag_category<isSigned<Value>> = 3;
template <typename Legacy>
inline constexpr int legacy_tag_category<QuMode<Legacy>> = 4;
template <typename Legacy>
inline constexpr int legacy_tag_category<OfMode<Legacy>> = 5;

template <typename>
inline constexpr int value_tag_category = 0;
template <typename Legacy>
inline constexpr int value_tag_category<value_tag<Legacy>> =
    legacy_tag_category<Legacy>;

template <int Category, auto... Tags>
inline constexpr size_t value_tag_count =
    (size_t{0} + ... +
     (value_tag_category<std::remove_cvref_t<decltype(Tags)>> == Category));

template <char... Digits>
consteval int decimal_digits()
{
    static_assert(sizeof...(Digits) > 0 &&
                  ((Digits >= '0' && Digits <= '9') && ...));
    uint64_t value = 0;
    ((value = value * 10 + (Digits - '0')), ...);
    if (value > static_cast<uint64_t>(std::numeric_limits<int>::max()))
        throw "QuBLAS bit-count literal does not fit in int";
    return static_cast<int>(value);
}

template <auto... Tags>
consteval bool valid_q_tag_pack()
{
    return ((value_tag_category<std::remove_cvref_t<decltype(Tags)>> != 0) &&
            ...) &&
           value_tag_count<1, Tags...> <= 1 &&
           value_tag_count<2, Tags...> <= 1 &&
           value_tag_count<3, Tags...> <= 1 &&
           value_tag_count<4, Tags...> <= 1 &&
           value_tag_count<5, Tags...> <= 1;
}

template <typename T>
struct is_fixed_scalar : std::false_type
{};

template <int Integer, int Fractional, bool Signed, typename Quantization,
          typename Overflow>
struct is_fixed_scalar<
    Qu_s<intBits<Integer>, fracBits<Fractional>, isSigned<Signed>,
         QuMode<Quantization>, OfMode<Overflow>>> : std::true_type
{};

template <typename T>
inline constexpr bool is_fixed_scalar_v =
    is_fixed_scalar<std::remove_cvref_t<T>>::value;

} // namespace detail

template <char... Digits>
consteval auto operator""_i()
{
    return detail::value_tag<
        intBits<detail::decimal_digits<Digits...>()>>{};
}

template <char... Digits>
consteval auto operator""_f()
{
    return detail::value_tag<
        fracBits<detail::decimal_digits<Digits...>()>>{};
}

template <int Value>
constexpr auto operator-(detail::value_tag<fracBits<Value>>)
{
    return detail::value_tag<fracBits<-Value>>{};
}

inline constexpr detail::value_tag<isSigned<true>> signed_;
inline constexpr detail::value_tag<isSigned<false>> unsigned_;

namespace rnd {
inline constexpr detail::value_tag<QuMode<RND::POS_INF>> pos_inf;
inline constexpr detail::value_tag<QuMode<RND::NEG_INF>> neg_inf;
inline constexpr detail::value_tag<QuMode<RND::ZERO>> zero;
inline constexpr detail::value_tag<QuMode<RND::INF>> inf;
inline constexpr detail::value_tag<QuMode<RND::CONV>> conv;
} // namespace rnd

namespace trn {
inline constexpr detail::value_tag<QuMode<TRN::TCPL>> tcpl;
inline constexpr detail::value_tag<QuMode<TRN::SMGN>> smgn;
} // namespace trn

namespace sat {
inline constexpr detail::value_tag<OfMode<SAT::TCPL>> tcpl;
inline constexpr detail::value_tag<OfMode<SAT::ZERO>> zero;
inline constexpr detail::value_tag<OfMode<SAT::SMGN>> smgn;
} // namespace sat

namespace wrp {
inline constexpr detail::value_tag<OfMode<WRP::TCPL>> tcpl;
template <auto Bits>
    requires(std::is_integral_v<decltype(Bits)> && Bits >= 0)
inline constexpr detail::value_tag<OfMode<WRP::TCPL_SAT<Bits>>> tcpl_sat;
} // namespace wrp

template <auto... Tags>
concept QValueTagPack = detail::valid_q_tag_pack<Tags...>();

template <auto... Tags>
    requires QValueTagPack<Tags...>
using Q = Qu<typename std::remove_cvref_t<decltype(Tags)>::legacy...>;

// ------------------- Compile-time exact literals -------------------

template <size_t N>
struct fixed_string
{
    char value[N];

    constexpr fixed_string(const char (&text)[N])
    {
        std::copy_n(text, N, value);
    }

    inline static constexpr size_t extent = N;
    constexpr size_t size() const { return N - 1; }
    constexpr char operator[](size_t index) const { return value[index]; }
    constexpr auto operator<=>(const fixed_string &) const = default;
};

template <size_t N>
fixed_string(const char (&)[N]) -> fixed_string<N>;

namespace detail {

struct binary_literal_info
{
    bool valid = true;
    bool negative = false;
    size_t digits = 0;
    int fractional = 0;
};

template <fixed_string Text>
consteval binary_literal_info inspect_binary_literal()
{
    binary_literal_info info;
    bool sawDigit = false;
    bool sawPoint = false;
    for (size_t index = 0; index < Text.size(); ++index)
    {
        const char c = Text[index];
        if ((c == '+' || c == '-') && index == 0)
        {
            info.negative = c == '-';
            continue;
        }
        if (c == '0' || c == '1')
        {
            sawDigit = true;
            ++info.digits;
            info.fractional += sawPoint;
            continue;
        }
        if (c == '.' && !sawPoint)
        {
            sawPoint = true;
            continue;
        }
        info.valid = false;
    }
    info.valid &= sawDigit;
    return info;
}

template <fixed_string Text>
class binary_literal_proxy
{
    inline static constexpr auto info = inspect_binary_literal<Text>();
    static_assert(info.valid,
                  "A _bq literal accepts one optional leading sign, binary "
                  "digits, and at most one radix point.");

    static constexpr auto magnitude()
    {
        ArbiInt<info.digits + 1> result;
        size_t outputBit = 0;
        for (size_t index = Text.size(); index-- > 0;)
        {
            if (Text[index] == '0' || Text[index] == '1')
            {
                if (Text[index] == '1')
                    setArbiBit(result, outputBit, true);
                ++outputBit;
            }
        }
        return result;
    }

    template <typename Target, size_t Width>
    static constexpr Target convert(const ArbiInt<Width> &raw)
    {
        auto fractional =
            fracConvert<info.fractional, Target::fracB,
                        QuMode<typename Target::QuM_t>>::convert(raw);
        auto bounded = intConvert<Target::intB, Target::fracB, Target::isS,
                                  OfMode<typename Target::OfM_t>>::convert(
            fractional);
        Target result;
        result.data = bounded;
        return result;
    }

public:
    template <typename Target>
        requires is_fixed_scalar_v<Target>
    constexpr auto as() const
    {
        using target_type = std::remove_cvref_t<Target>;
        constexpr auto rawMagnitude = magnitude();
        if constexpr (info.negative)
            return convert<target_type>(-rawMagnitude);
        else
            return convert<target_type>(rawMagnitude);
    }
};

} // namespace detail

template <fixed_string Text>
consteval auto operator""_bq()
{
    return detail::binary_literal_proxy<Text>{};
}

template <typename Target>
struct to_type
{
    using type = Target;
};

template <typename Target>
inline constexpr to_type<Target> to{};

template <fixed_string Text, typename Target>
    requires detail::is_fixed_scalar_v<Target>
constexpr auto operator|(detail::binary_literal_proxy<Text> literal,
                         to_type<Target>)
{
    return literal.template as<Target>();
}

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

    inline Qu_s &fill(auto... dis)
        requires(sizeof...(dis) <= 1)
    {
        real.fill(dis...);
        imag.fill(dis...);
        return *this;
    }

    inline Qu_s &fill(auto realInput, auto imagInput)
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

// std::mdspan only available in clang 18, we need to support gcc
template <size_t... dims>
struct dim
{
    static inline constexpr size_t dimSize = sizeof...(dims);
    static inline constexpr size_t elemSize = (size_t{1} * ... * dims);

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
    static inline constexpr size_t absoluteIndex = absoluteIndex_s<index...>::value;
};

// Compile-time half-open ranges for the C++23 multidimensional subscript DSL.
template <size_t First, size_t Last>
struct slice_t
{
    static_assert(First < Last, "A slice range must be non-empty.");
    inline static constexpr size_t first = First;
    inline static constexpr size_t last = Last;
};

// A range reads as a value directly inside the subscript:
// tensor[1, all, slice<0, 5>].
template <size_t First, size_t Last>
inline constexpr slice_t<First, Last> slice{};

struct all_t
{};

inline constexpr all_t all{};

template <typename T>
concept SliceSelector =
    std::same_as<std::remove_cvref_t<T>, all_t> ||
    isA<std::remove_cvref_t<T>, slice_t<0, 1>>;

template <typename T>
concept TensorSliceSelector =
    SliceSelector<T> || std::integral<std::remove_cvref_t<T>>;

template <typename Tensor, typename... Selectors>
class SliceView;

template <size_t... dims, typename Arg>
    requires(isA<Arg, Qu_s<>>)
class Qu_s<dim<dims...>, Arg>
{
public:
    constexpr void ensureStorage()
    {
        if constexpr (onHeap)
        {
            if (data.size() != dim<dims...>::elemSize)
            {
                data.resize(dim<dims...>::elemSize);
            }
        }
    }

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

    inline static constexpr bool onHeap = dim<dims...>::elemSize > 1000;

    // when the size is too large, use std::vector instead of std::array
    using storage_t = std::conditional_t<onHeap, std::vector<Arg>, std::array<Arg, dim<dims...>::elemSize>>;

    storage_t data;

    using size = dim<dims...>;

    // 构造函数
    constexpr Qu_s()
    {
        ensureStorage();
    }

    constexpr Qu_s(auto... values)
    {
        ensureStorage();

        if constexpr (sizeof...(values) == dim<dims...>::elemSize)
        {
            data = {values...};
        }
        else
        {
            throw std::invalid_argument("The number of values does not match the size of the Qu_s.");
        }
    }

    template <typename SquareBracketIndexableType>
        requires isSquareBracketIndexable<SquareBracketIndexableType>
    constexpr Qu_s(const SquareBracketIndexableType &val)
    {
        ensureStorage();

        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            data[i] = val[i];
        }
    }

    // 拷贝构造函数
    constexpr Qu_s(const Qu_s<dim<dims...>, Arg> &val)
    {
        ensureStorage();

        std::copy(val.data.begin(), val.data.end(), data.begin());
    }

    // 来自不同类型的Qu_s，逐个元素转换
    template <typename fromArg>
    constexpr Qu_s(const Qu_s<dim<dims...>, fromArg> &val)
    {
        ensureStorage();

        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            data[i] = val.data[i];
        }
    }

    // // 移动构造函数
    // // 来自相同类型的Qu_s, 直接移动std::array
    // constexpr Qu_s(Qu_s<dim<dims...>, Arg> &&val) : data(std::move(val.data)) {}

    // 移动构造函数
    // 来自相同类型的Qu_s, 直接移动std::array或者std::vector
    constexpr Qu_s(Qu_s<dim<dims...>, Arg> &&val) : data(std::move(val.data))
    {
        // A tensor has a fixed logical extent.  Keep that invariant even for a
        // moved-from heap-backed tensor, since all indexing APIs rely on it.
        val.ensureStorage();
    }

    // 来自不同类型的Qu_s，逐个元素转换
    template <typename fromArg>
    constexpr Qu_s(Qu_s<dim<dims...>, fromArg> &&val)
    {
        ensureStorage();
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            data[i] = std::move(val.data[i]);
        }
    }

    // 拷贝赋值运算符
    // 来自相同类型的Qu_s, 直接拷贝std::array或者std::vector
    constexpr Qu_s &operator=(const Qu_s<dim<dims...>, Arg> &val)
    {
        if (this != &val)
        {
            ensureStorage();
            std::copy_n(val.data.begin(), dim<dims...>::elemSize, data.begin());
        }
        return *this;
    }

    // 来自不同类型的Qu_s，逐个元素转换
    template <typename fromArg>
    constexpr Qu_s &operator=(const Qu_s<dim<dims...>, fromArg> &val)
    {
        ensureStorage();
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
        if (this != &val)
        {
            data = std::move(val.data);
            val.ensureStorage();
        }
        return *this;
    }

    // 来自不同类型的Qu_s，逐个元素转换
    template <typename fromArg>
    constexpr Qu_s &operator=(Qu_s<dim<dims...>, fromArg> &&val)
    {
        ensureStorage();
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            data[i] = std::move(val.data[i]);
        }
        return *this;
    }

    inline Qu_s &clear()
    {
        ensureStorage();
        std::fill(data.begin(), data.end(), Arg{});
        return *this;
    }

    inline Qu_s &fill(auto... dis)
    {
        for (size_t i = 0; i < dim<dims...>::elemSize; i++)
        {
            data[i].fill(dis...);
        }
        return *this;
    }

    inline Qu_s &shuffle()
    {
        std::shuffle(data.begin(), data.end(), gen);
        return *this;
    }

    // get
    template <auto... index>
    inline constexpr auto &get()
    {
        return data[dim<dims...>::template absoluteIndex_s<index...>::value];
    }

    template <auto... index>
    inline constexpr const auto &get() const
    {
        return data[dim<dims...>::template absoluteIndex_s<index...>::value];
    }

    // operator[]
    inline constexpr auto &operator[](auto... index)
        requires(sizeof...(index) == dim<dims...>::dimSize && sizeof...(index) > 1 &&
                 (std::is_convertible_v<decltype(index), size_t> && ...))
    {
        return data[calculateIndex(0, index...)];
    }

    inline constexpr const auto &operator[](auto... index) const
        requires(sizeof...(index) == dim<dims...>::dimSize && sizeof...(index) > 1 &&
                 (std::is_convertible_v<decltype(index), size_t> && ...))
    {
        return data[calculateIndex(0, index...)];
    }

    inline constexpr auto operator[](this auto &&self, auto... selectors)
        requires(sizeof...(selectors) == dim<dims...>::dimSize &&
                 (TensorSliceSelector<decltype(selectors)> && ...) &&
                 !(std::integral<std::remove_cvref_t<decltype(selectors)>> && ...))
    {
        using self_t = decltype(self);
        return SliceView<self_t, std::remove_cvref_t<decltype(selectors)>...>(
            std::forward<self_t>(self), selectors...);
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

        std::cout << std::endl;
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

template <typename T>
struct isScalar_s
{
    static inline constexpr bool value = false;
};

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

template <typename QuT, size_t... dims>
struct isScalar_s<Qu_s<dim<dims...>, QuT>>
{
    static inline constexpr bool value = false;
};

template <typename T>
inline constexpr bool isScalar = isScalar_s<T>::value;

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
    using type = TypeList<Args...>;
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

    static inline constexpr auto toInt = tagExtractor<intBits<fullPrecision ? fromInt1 + fromInt2 + (fromIsSigned1 && fromIsSigned2) : std::max(fromInt1, fromInt2)>, toArgs...>::value;
    static inline constexpr auto toFrac = tagExtractor<fracBits<fullPrecision ? fromFrac1 + fromFrac2 : std::max(fromFrac1, fromFrac2)>, toArgs...>::value;
    static inline constexpr auto toIsSigned = tagExtractor<isSigned<fromIsSigned1 || fromIsSigned2>, toArgs...>::value;
    using toQuMode = tagExtractor<QuMode<fromQuMode>, toArgs...>::type;
    using toOfMode = tagExtractor<OfMode<fromOfMode>, toArgs...>::type;

    using resType = Qu_s<intBits<toInt>, fracBits<toFrac>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>>;
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

    using resType = Qu_s<intBits<toInt>, fracBits<toFrac>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>>;
};

template <typename... Args>
struct SubMerger;

template <typename... toArgs, int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2>
struct SubMerger<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, TypeList<toArgs...>>
{
    static inline constexpr bool fullPrecision = (std::is_same_v<FullPrec, toArgs> || ...);

    using fromQuMode = std::conditional_t<std::is_same_v<fromQuMode1, fromQuMode2>, fromQuMode1, defaultQuMode>;
    using fromOfMode = std::conditional_t<std::is_same_v<fromOfMode1, fromOfMode2>, fromOfMode1, defaultOfMode>;

    static inline constexpr auto toInt = tagExtractor<intBits<fullPrecision ? std::max(fromInt1, fromInt2) + (fromIsSigned1 || fromIsSigned2) : std::max(fromInt1, fromInt2)>, toArgs...>::value;
    static inline constexpr auto toFrac = tagExtractor<fracBits<std::max(fromFrac1, fromFrac2)>, toArgs...>::value;
    static inline constexpr auto toIsSigned = tagExtractor<isSigned<fullPrecision ? true : (fromIsSigned1 || fromIsSigned2)>, toArgs...>::value;
    using toQuMode = tagExtractor<QuMode<fromQuMode>, toArgs...>::type;
    using toOfMode = tagExtractor<OfMode<fromOfMode>, toArgs...>::type;

    using resType = Qu_s<intBits<toInt>, fracBits<toFrac>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>>;
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
        // print the debug info
        // std::cout << "mul: " << merger::toInt << " " << merger::toFrac << " " << std::endl;

        auto fullProduct = f1.data * f2.data;

        auto fracProduct = fracConvert<fromFrac1 + fromFrac2, merger::toFrac, QuMode<typename merger::toQuMode>>::convert(fullProduct);

        auto intProduct = intConvert<merger::toInt, merger::toFrac, merger::toIsSigned, OfMode<typename merger::toOfMode>>::convert(fracProduct);

        Qu_s<intBits<merger::toInt>, fracBits<merger::toFrac>, isSigned<merger::toIsSigned>, QuMode<typename merger::toQuMode>, OfMode<typename merger::toOfMode>> result;
        result.data = intProduct;

        // debug info
        // std::cout << f1.toDouble() << " * " << f2.toDouble() << " = " << result.toDouble() << std::endl;

        return result;
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

        auto fullSum = staticShiftLeft<shiftA>(f1.data) + staticShiftLeft<shiftB>(f2.data);

        auto fracSum = fracConvert<std::max(fromFrac1, fromFrac2), merger::toFrac, QuMode<typename merger::toQuMode>>::convert(fullSum);

        auto intSum = intConvert<merger::toInt, merger::toFrac, merger::toIsSigned, OfMode<typename merger::toOfMode>>::convert(fracSum);

        Qu_s<intBits<merger::toInt>, fracBits<merger::toFrac>, isSigned<merger::toIsSigned>, QuMode<typename merger::toQuMode>, OfMode<typename merger::toOfMode>> result;
        result.data = intSum;

        // debug info
        // std::cout << f1.toDouble() << " + " << f2.toDouble() << " = " << result.toDouble() << std::endl;

        return result;
    }
};

template <typename... Args>
struct Qsub_s;

// specialization for both inputs being static Qu_s
template <typename... toArgs, int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2>
    requires(!isA<typename TypeList<toArgs...>::head, Qu_s<>>)
struct Qsub_s<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, TypeList<toArgs...>>
{
    using merger = SubMerger<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, TypeList<toArgs...>>;

    static inline constexpr int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
    static inline constexpr int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;

    inline static constexpr auto sub(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> f2)
    {
        // // print the requesting Quantization parameters for debugging
        // std::cout << "sub: " << merger::toInt << " " << merger::toFrac << " " << std::endl;

        auto fullDiff = staticShiftLeft<shiftA>(f1.data) - staticShiftLeft<shiftB>(f2.data);

        auto fracDiff = fracConvert<std::max(fromFrac1, fromFrac2), merger::toFrac, QuMode<typename merger::toQuMode>>::convert(fullDiff);

        auto intDiff = intConvert<merger::toInt, merger::toFrac, merger::toIsSigned, OfMode<typename merger::toOfMode>>::convert(fracDiff);

        Qu_s<intBits<merger::toInt>, fracBits<merger::toFrac>, isSigned<merger::toIsSigned>, QuMode<typename merger::toQuMode>, OfMode<typename merger::toOfMode>> result;
        result.data = intDiff;

        return result;
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

    // The exact target raw value is
    //   (f1.raw / f2.raw) * 2^(fromFrac2 - fromFrac1 + toFrac).
    // Apply a positive shift to one side of the rational value rather than
    // right-shifting either side and discarding information before division.
    static inline constexpr int rawShift = fromFrac2 - fromFrac1 + merger::toFrac;

    template <int shift, size_t N>
    inline static constexpr auto scaleRaw(const ArbiInt<N> &value)
    {
        if constexpr (shift == 0)
        {
            return value;
        }
        else
        {
            // Multiplication avoids left-shifting a negative built-in signed
            // value while still producing the exact two's-complement result.
            constexpr auto powerOfTwo = staticShiftLeft<shift>(ArbiInt<2>(1));
            return value * powerOfTwo;
        }
    }

    template <size_t width, size_t N>
    inline static constexpr auto magnitude(const ArbiInt<N> &value)
    {
        ArbiInt<width> promoted(value);
        if (value.isNegative())
        {
            return ArbiInt<width>(-promoted);
        }
        return promoted;
    }

    inline static constexpr auto div(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> f2)
    {
        const auto numerator = scaleRaw<(rawShift > 0 ? rawShift : 0)>(f1.data);
        const auto denominator = scaleRaw<(rawShift < 0 ? -rawShift : 0)>(f2.data);
        const bool negativeResult = numerator.isNegative() != denominator.isNegative();

        // divmod throws std::domain_error for a zero denominator.  Keep that
        // failure visible to callers instead of silently manufacturing zero.
        const auto division = divmod(numerator, denominator);
        constexpr size_t roundedWidth = decltype(division.quotient)::num_bits + 1;
        using rounded_type = ArbiInt<roundedWidth>;
        rounded_type rounded(division.quotient);

        const auto adjustAwayFromZero = [&rounded, negativeResult]() constexpr {
            if (negativeResult)
            {
                rounded = rounded_type(rounded - ArbiInt<1>(1));
            }
            else
            {
                rounded = rounded_type(rounded + ArbiInt<1>(1));
            }
        };

        if (!division.remainder.isZero())
        {
            if constexpr (std::is_same_v<typename merger::toQuMode, TRN::TCPL>)
            {
                // divmod truncates toward zero; a negative non-integral result
                // needs one step toward -infinity for two's-complement truncation.
                if (negativeResult)
                {
                    adjustAwayFromZero();
                }
            }
            else if constexpr (!std::is_same_v<typename merger::toQuMode, TRN::SMGN>)
            {
                constexpr size_t magnitudeWidth = std::max(decltype(division.remainder)::num_bits,
                                                            decltype(denominator)::num_bits) +
                                                  2;
                const auto remainderMagnitude = magnitude<magnitudeWidth>(division.remainder);
                const auto divisorMagnitude = magnitude<magnitudeWidth>(denominator);
                const auto twiceRemainder = staticShiftLeft<1>(remainderMagnitude);
                const auto distanceComparison = twiceRemainder <=> divisorMagnitude;

                if (distanceComparison > 0)
                {
                    adjustAwayFromZero();
                }
                else if (distanceComparison == 0)
                {
                    if constexpr (std::is_same_v<typename merger::toQuMode, RND::POS_INF>)
                    {
                        if (!negativeResult)
                        {
                            adjustAwayFromZero();
                        }
                    }
                    else if constexpr (std::is_same_v<typename merger::toQuMode, RND::NEG_INF>)
                    {
                        if (negativeResult)
                        {
                            adjustAwayFromZero();
                        }
                    }
                    else if constexpr (std::is_same_v<typename merger::toQuMode, RND::INF>)
                    {
                        adjustAwayFromZero();
                    }
                    else if constexpr (std::is_same_v<typename merger::toQuMode, RND::CONV>)
                    {
                        if ((arbiWord(rounded, 0) & uint64_t{1}) != 0)
                        {
                            adjustAwayFromZero();
                        }
                    }
                    // RND::ZERO keeps the toward-zero quotient at a tie.
                }
            }
        }

        auto intQuotient = intConvert<merger::toInt, merger::toFrac, merger::toIsSigned, OfMode<typename merger::toOfMode>>::convert(rounded);

        Qu_s<intBits<merger::toInt>, fracBits<merger::toFrac>, isSigned<merger::toIsSigned>, QuMode<typename merger::toQuMode>, OfMode<typename merger::toOfMode>> result;
        result.data = intQuotient;

        return result;
    }
};

// abs
template <typename... Args>
struct Qabs_s;

// specialization for static Qu_s
template <typename... toArgs, int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode>
struct Qabs_s<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, TypeList<toArgs...>>
{

    inline static constexpr auto abs(const Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>> f)
    {
        if constexpr (!fromIsSigned)
        {
            return f;
        }
        else
        {

            Qu_s<intBits<fromInt + 1>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>> result;

            if (f.data.isNegative())
            {
                result.data = -f.data;
            }
            else
            {
                result.data = f.data;
            }

            return result;
        }
    }
};

// neg
template <typename... Args>
struct Qneg_s;

template <typename... Args>
struct NegMerger;

template <typename... toArgs, int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode>
struct NegMerger<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, TypeList<toArgs...>>
{
    static inline constexpr auto toInt = tagExtractor<intBits<fromInt + (fromIsSigned ? 1 : 0)>, toArgs...>::value;
    static inline constexpr auto toFrac = tagExtractor<fracBits<fromFrac>, toArgs...>::value;
    static inline constexpr auto toIsSigned = tagExtractor<isSigned<true>, toArgs...>::value;
    using toQuMode = tagExtractor<QuMode<fromQuMode>, toArgs...>::type;
    using toOfMode = tagExtractor<OfMode<fromOfMode>, toArgs...>::type;

    using resType = Qu_s<intBits<toInt>, fracBits<toFrac>, isSigned<toIsSigned>, QuMode<toQuMode>, OfMode<toOfMode>>;
};

// specialization for static Qu_s
template <typename... toArgs, int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode>
struct Qneg_s<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, TypeList<toArgs...>>
{
    using sourceType = Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>;
    using merger = NegMerger<sourceType, TypeList<toArgs...>>;

    inline static constexpr auto neg(const Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>> f)
    {
        const auto fullNegation = -f.data;
        const auto scaled = fracConvert<fromFrac, merger::toFrac, QuMode<typename merger::toQuMode>>::convert(fullNegation);
        const auto converted = intConvert<merger::toInt, merger::toFrac, merger::toIsSigned, OfMode<typename merger::toOfMode>>::convert(scaled);

        typename merger::resType result;
        result.data = converted;

        return result;
    }
};

// specialization for complex
template <typename... toArgs, typename... realArgs, typename... imagArgs>
struct Qneg_s<Qu_s<Qu_s<realArgs...>, Qu_s<imagArgs...>>, TypeList<toArgs...>>
{
    inline static auto neg(const Qu_s<Qu_s<realArgs...>, Qu_s<imagArgs...>> f)
    {
        auto realNeg = Qneg<toArgs...>(f.real);
        auto imagNeg = Qneg<toArgs...>(f.imag);
        return Qcomplex<decltype(realNeg), decltype(imagNeg)>(realNeg, imagNeg);
    }
};

template <typename... Args>
struct Qcmp_s;

// specialization for static Qu_s
template <typename... toArgs, int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2>
struct Qcmp_s<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, TypeList<toArgs...>>
{
    static inline constexpr int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
    static inline constexpr int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;

    inline static constexpr auto cmp(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> f2)
    {
        return staticShiftLeft<shiftA>(f1.data) <=> staticShiftLeft<shiftB>(f2.data);
    }
};

template <typename... Args>
struct Qeq_s;
template <typename... toArgs, int fromInt1, int fromFrac1, bool fromIsSigned1, typename fromQuMode1, typename fromOfMode1, int fromInt2, int fromFrac2, bool fromIsSigned2, typename fromQuMode2, typename fromOfMode2>
struct Qeq_s<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, TypeList<toArgs...>>
{
    static inline constexpr int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
    static inline constexpr int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;

    inline static constexpr auto eq(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> f2)
    {
        return staticShiftLeft<shiftA>(f1.data) == staticShiftLeft<shiftB>(f2.data);
    }
};


// specialization for complex
template <typename... toArgs, typename... realArgs, typename... imagArgs>
struct Qeq_s<Qu_s<Qu_s<realArgs...>, Qu_s<imagArgs...>>, Qu_s<Qu_s<realArgs...>, Qu_s<imagArgs...>>, TypeList<toArgs...>>
{
    inline static auto eq(const Qu_s<Qu_s<realArgs...>, Qu_s<imagArgs...>> f1, const Qu_s<Qu_s<realArgs...>, Qu_s<imagArgs...>> f2)
    {
        return Qeq<toArgs...>(f1.real, f2.real) && Qeq<toArgs...>(f1.imag, f2.imag);
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
struct acT
{
    using list = MergerArgsWrapper<Args...>;
};

template <typename... Args>
struct bdT
{
    using list = MergerArgsWrapper<Args...>;
};

template <typename... Args>
struct adT
{
    using list = MergerArgsWrapper<Args...>;
};

template <typename... Args>
struct bcT
{
    using list = MergerArgsWrapper<Args...>;
};

template <typename... Args>
struct acbdT
{
    using list = MergerArgsWrapper<Args...>;
};

template <typename... Args>
struct adbcT
{
    using list = MergerArgsWrapper<Args...>;
};

// used for Qmul(c1, c2) without any additional arguments
template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2>
struct Qmul_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TypeList<>> : Qmul_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, BasicComplexMul<>>
{};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct Qmul_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, BasicComplexMul<toArgs...>>
{
    using mulACType = tagExtractor<acT<toArgs...>, toArgs...>::type::list;
    using mulBDType = tagExtractor<bdT<toArgs...>, toArgs...>::type::list;
    using mulADType = tagExtractor<adT<toArgs...>, toArgs...>::type::list;
    using mulBCType = tagExtractor<bcT<toArgs...>, toArgs...>::type::list;

    using subACBDType = tagExtractor<acbdT<toArgs...>, toArgs...>::type::list;
    using addADBCType = tagExtractor<adbcT<toArgs...>, toArgs...>::type::list;

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
struct abT
{
    using list = MergerArgsWrapper<Args...>;
};

template <typename... Args>
struct cdT
{
    using list = MergerArgsWrapper<Args...>;
};

template <typename... Args>
struct baT
{
    using list = MergerArgsWrapper<Args...>;
};

template <typename... Args>
struct abcT
{
    using list = MergerArgsWrapper<Args...>;
};

template <typename... Args>
struct cdbT
{
    using list = MergerArgsWrapper<Args...>;
};

template <typename... Args>
struct badT
{
    using list = MergerArgsWrapper<Args...>;
};

template <typename... Args>
struct ABT
{
    using list = MergerArgsWrapper<Args...>;
};

template <typename... Args>
struct BCT
{
    using list = MergerArgsWrapper<Args...>;
};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct Qmul_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TFComplexMul<toArgs...>>
{
    using addabType = tagExtractor<abT<toArgs...>, toArgs...>::type::list;
    using addcdType = tagExtractor<cdT<toArgs...>, toArgs...>::type::list;
    using subbaType = tagExtractor<baT<toArgs...>, toArgs...>::type::list;
    using mulabcType = tagExtractor<abcT<toArgs...>, toArgs...>::type::list;
    using mulcdbType = tagExtractor<cdbT<toArgs...>, toArgs...>::type::list;
    using mulbadType = tagExtractor<badT<toArgs...>, toArgs...>::type::list;
    using subABType = tagExtractor<ABT<toArgs...>, toArgs...>::type::list;
    using subBCType = tagExtractor<BCT<toArgs...>, toArgs...>::type::list;

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
struct realT
{
    using list = MergerArgsWrapper<Args...>;
};

template <typename... Args>
struct imagT
{
    using list = MergerArgsWrapper<Args...>;
};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct Qadd_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TypeList<toArgs...>>
{
    using realType = tagExtractor<realT<toArgs...>, toArgs...>::type::list;
    using imagType = tagExtractor<imagT<toArgs...>, toArgs...>::type::list;

    inline static constexpr auto add(const Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>> f1, const Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>> f2)
    {
        auto realPart = Qadd<realType>(f1.real, f2.real);
        auto imagPart = Qadd<imagType>(f1.imag, f2.imag);

        // get the type of the real part and the imaginary part
        Qcomplex<decltype(realPart), decltype(imagPart)> res(realPart, imagPart);
        return res;
    }
};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2, typename... QuArgs1, typename... QuArgs2>
struct Qadd_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TypeList<Qu_s<QuArgs1...>, Qu_s<QuArgs2...>>> : Qadd_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TypeList<realT<QuArgs1...>, imagT<QuArgs2...>>>
{};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct Qsub_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TypeList<toArgs...>>
{
    using realType = tagExtractor<realT<toArgs...>, toArgs...>::type::list;
    using imagType = tagExtractor<imagT<toArgs...>, toArgs...>::type::list;

    inline static constexpr auto sub(const Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>> f1, const Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>> f2)
    {
        auto realPart = Qsub<realType>(f1.real, f2.real);
        auto imagPart = Qsub<imagType>(f1.imag, f2.imag);

        // get the type of the real part and the imaginary part
        Qcomplex<decltype(realPart), decltype(imagPart)> res(realPart, imagPart);
        return res;
    }
};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2, typename... QuArgs1, typename... QuArgs2>
struct Qsub_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TypeList<Qu_s<QuArgs1...>, Qu_s<QuArgs2...>>> : Qsub_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TypeList<realT<QuArgs1...>, imagT<QuArgs2...>>>
{};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct Qdiv_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, toArgs...>
{
    inline static constexpr auto div(const Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, const Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>)
    {
        throw std::runtime_error("Complex division is not supported yet.");
    }
};

// ------------------- Real-Complex Operations -------------------

// Real-Complex multiplication
template <typename... realArgs1, typename... realArgs2, typename... imagArgs2, typename... toArgs>
struct Qmul_s<Qu_s<realArgs1...>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TypeList<toArgs...>>
{
    using realMulType = tagExtractor<realT<toArgs...>, toArgs...>::type;
    using imagMulType = tagExtractor<imagT<toArgs...>, toArgs...>::type;

    inline static constexpr auto mul(const Qu_s<realArgs1...> f1, const Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>> f2)
    {

        auto realPart = Qmul<typename realMulType::list>(f1, f2.real);
        auto imagPart = Qmul<typename imagMulType::list>(f1, f2.imag);

        // get the type of the real part and the imaginary part
        Qcomplex<decltype(realPart), decltype(imagPart)> res(realPart, imagPart);
        return res;
    }
};

template <typename... realArgs1, typename... realArgs2, typename... imagArgs2, typename... QuArgs1, typename... QuArgs2>
struct Qmul_s<Qu_s<realArgs1...>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TypeList<Qu_s<QuArgs1...>, Qu_s<QuArgs2...>>> : Qmul_s<Qu_s<realArgs1...>, Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>, TypeList<realT<QuArgs1...>, imagT<QuArgs2...>>>
{};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... toArgs>
struct Qmul_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<realArgs2...>, TypeList<toArgs...>>
{
    using realMulType = tagExtractor<realT<toArgs...>, toArgs...>::type;
    using imagMulType = tagExtractor<imagT<toArgs...>, toArgs...>::type;

    inline static constexpr auto mul(const Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>> f1, const Qu_s<realArgs2...> f2)
    {
        auto realPart = Qmul<typename realMulType::list>(f1.real, f2);
        auto imagPart = Qmul<typename imagMulType::list>(f1.imag, f2);

        // get the type of the real part and the imaginary part
        Qcomplex<decltype(realPart), decltype(imagPart)> res(realPart, imagPart);
        return res;
    }
};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... QuArgs1, typename... QuArgs2>
struct Qmul_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<realArgs2...>, TypeList<Qu_s<QuArgs1...>, Qu_s<QuArgs2...>>> : Qmul_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<realArgs2...>, TypeList<realT<QuArgs1...>, imagT<QuArgs2...>>>
{};

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
        auto imagPart = Qsub<toArgs...>(Qu_s<realArgs1...>(), f2.imag);

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
    inline static constexpr auto div(const Qu_s<realArgs1...>, const Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>>)
    {
        throw std::runtime_error("Real-Complex division is not supported yet.");
    }
};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... toArgs>
struct Qdiv_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<realArgs2...>, TypeList<toArgs...>>
{
    using realDivType = tagExtractor<realT<toArgs...>, toArgs...>::type;
    using imagDivType = tagExtractor<imagT<toArgs...>, toArgs...>::type;

    inline static constexpr auto div(const Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>> f1, const Qu_s<realArgs2...> f2)
    {
        auto realPart = Qdiv<typename realDivType::list>(f1.real, f2);
        auto imagPart = Qdiv<typename imagDivType::list>(f1.imag, f2);

        // get the type of the real part and the imaginary part
        Qcomplex<decltype(realPart), decltype(imagPart)> res(realPart, imagPart);

        return res;
    }
};

template <typename... realArgs1, typename... imagArgs1, typename... realArgs2, typename... QuArgs1, typename... QuArgs2>
struct Qdiv_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<realArgs2...>, TypeList<Qu_s<QuArgs1...>, Qu_s<QuArgs2...>>> : Qdiv_s<Qu_s<Qu_s<realArgs1...>, Qu_s<imagArgs1...>>, Qu_s<realArgs2...>, TypeList<realT<QuArgs1...>, imagT<QuArgs2...>>>
{};

// ------------------- Basic tensor operations -------------------

template <typename T>
inline constexpr bool isScalarOperand = isScalar<std::remove_cvref_t<T>>;

template <typename T, typename = void>
struct isTensorOperand_s : std::false_type
{};

template <typename T>
struct isTensorOperand_s<T, std::void_t<typename T::size>>
    : std::bool_constant<!isScalarOperand<T>>
{};

// Keep the structural Qu_s<dim<...>, Arg> recognition used by the original
// overload set.  In particular Arg may itself be a TypeList tag bundle and
// therefore need not expose a nested size member.
template <size_t... dims, typename Arg>
struct isTensorOperand_s<Qu_s<dim<dims...>, Arg>, void> : std::true_type
{};

template <typename T>
inline constexpr bool isTensorOperand = isTensorOperand_s<std::remove_cvref_t<T>>::value;

template <typename T, typename = void>
struct tensorSize_s;

template <typename T>
struct tensorSize_s<T, std::void_t<typename T::size>>
{
    using type = typename T::size;
};

template <size_t... dims, typename Arg>
struct tensorSize_s<Qu_s<dim<dims...>, Arg>, void>
{
    using type = dim<dims...>;
};

template <typename T>
using tensorSize = typename tensorSize_s<std::remove_cvref_t<T>>::type;

template <typename T1, typename T2, bool = isTensorOperand<T1> && isTensorOperand<T2>>
struct hasSameTensorSize_s : std::false_type
{};

template <typename T1, typename T2>
struct hasSameTensorSize_s<T1, T2, true>
    : std::is_same<tensorSize<T1>, tensorSize<T2>>
{};

template <typename T1, typename T2>
inline constexpr bool hasSameTensorSize = hasSameTensorSize_s<T1, T2>::value;

template <typename T1, typename T2>
inline constexpr bool isTensorOperandPair =
    (isTensorOperand<T1> && isScalarOperand<T2>) ||
    (isScalarOperand<T1> && isTensorOperand<T2>) ||
    hasSameTensorSize<T1, T2>;

template <typename... Args>
struct sizeMerger;

template <typename T1, typename T2>
    requires hasSameTensorSize<T1, T2>
struct sizeMerger<T1, T2>
{
    using size = tensorSize<T1>;
};

template <typename T1, typename T2>
    requires(isTensorOperand<T1> && isScalarOperand<T2>)
struct sizeMerger<T1, T2>
{
    using size = tensorSize<T1>;
};

template <typename T1, typename T2>
    requires(isScalarOperand<T1> && isTensorOperand<T2>)
struct sizeMerger<T1, T2>
{
    using size = tensorSize<T2>;
};

// use [] to call the object if it is a tensor, otherwise just return the object
template <typename T>
inline constexpr auto autoCall(const T &obj, auto... index)
{
    if constexpr (isScalarOperand<T>)
    {
        return obj;
    }
    else
    {
        return obj[index...];
    }
}

// Encode the operand value category in the expression type: lvalues are kept
// by reference while rvalues are owned by the expression.  This avoids a
// runtime discriminated union and keeps temporary expression chains alive.
template <typename T>
class ExpressionOperand
{
    using value_type = std::remove_cvref_t<T>;
    inline static constexpr bool storesReference = std::is_lvalue_reference_v<T>;
    using storage_type = std::conditional_t<storesReference,
                                            std::reference_wrapper<const value_type>,
                                            value_type>;

    storage_type value;

    inline static constexpr storage_type store(T &&operand)
    {
        if constexpr (storesReference)
        {
            return std::cref(operand);
        }
        else
        {
            return std::forward<T>(operand);
        }
    }

public:
    explicit constexpr ExpressionOperand(T &&operand)
        : value(store(std::forward<T>(operand))) {}

    inline constexpr const value_type &get() const
    {
        if constexpr (storesReference)
        {
            return value.get();
        }
        else
        {
            return value;
        }
    }
};

// A lazy tensor is only a shape plus an unnamed computation.  The closure is
// the complete AST; named operands are references and temporary operands are
// values inside the ExpressionOperand tuple captured by `lift` below.
template <typename Size, typename Compute>
class LazyTensor
{
    [[no_unique_address]] Compute compute;

public:
    using size = Size;

    explicit inline constexpr LazyTensor(Compute value)
        : compute(std::move(value)) {}

    template <typename Self, typename... Index>
    inline constexpr decltype(auto) operator[](this const Self &self,
                                               Index... index)
        requires((sizeof...(Index) == 1 ||
                  (sizeof...(Index) == Size::dimSize &&
                   sizeof...(Index) > 1)) &&
                 (std::convertible_to<Index, size_t> && ...))
    {
        return self.compute(index...);
    }

    template <typename Self, typename... Selectors>
    inline constexpr auto operator[](this Self &&self, Selectors... selectors)
        requires(sizeof...(Selectors) == Size::dimSize &&
                 (TensorSliceSelector<Selectors> && ...) &&
                 !(std::integral<std::remove_cvref_t<Selectors>> && ...))
    {
        return SliceView<Self &&, std::remove_cvref_t<Selectors>...>(
            std::forward<Self>(self), selectors...);
    }

    template <typename Self>
    inline constexpr auto eval(this const Self &self)
    {
        if constexpr (Self::size::dimSize == 0)
        {
            return self[size_t{}];
        }
        else
        {
            using element_type = std::remove_cvref_t<decltype(self[size_t{}])>;
            using result_type = Qu_s<typename Self::size, element_type>;
            return result_type(self);
        }
    }
};

template <typename T>
concept LazyTensorNode =
    isTensorOperand<T> &&
    requires(const std::remove_cvref_t<T> &expression) { expression.eval(); };

template <LazyTensorNode Expr>
inline constexpr auto eval(Expr &&expression)
{
    return std::forward<Expr>(expression).eval();
}

template <typename Size, typename Compute>
inline constexpr auto lazy(Compute &&compute)
{
    return LazyTensor<Size, std::remove_cvref_t<Compute>>(
        std::forward<Compute>(compute));
}

template <typename Size, typename Op, typename... Operands>
inline constexpr auto lift(Op &&operation, Operands &&...operands)
{
    using captures = std::tuple<ExpressionOperand<Operands &&>...>;
    return lazy<Size>(
        [op = std::forward<Op>(operation),
         values = captures(ExpressionOperand<Operands &&>(
             std::forward<Operands>(operands))...)](auto... index) constexpr {
            auto element = [&](const auto &value) -> decltype(auto) {
                return autoCall(value.get(), index...);
            };
            return std::apply(
                [&](const auto &...value) -> decltype(auto) {
                    return std::invoke(op, element(value)...);
                },
                values);
        });
}

// ------------------- Functions -------------------

// scalar functions

template <typename... toArgs, typename QuT1, typename QuT2>
    requires isScalar<QuT1> && isScalar<QuT2>
inline constexpr auto Qmul(const QuT1 f1, const QuT2 f2)
{
    return Qmul_s<QuT1, QuT2, MergerArgsWrapper<toArgs...>>::mul(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2>
    requires isScalar<QuT1> && isScalar<QuT2>
inline constexpr auto Qadd(const QuT1 f1, const QuT2 f2)
{
    return Qadd_s<QuT1, QuT2, MergerArgsWrapper<toArgs...>>::add(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2>
    requires isScalar<QuT1> && isScalar<QuT2>
inline constexpr auto Qsub(const QuT1 f1, const QuT2 f2)
{
    return Qsub_s<QuT1, QuT2, MergerArgsWrapper<toArgs...>>::sub(f1, f2);
}

template <typename... toArgs, typename QuT1, typename QuT2>
    requires isScalar<QuT1> && isScalar<QuT2>
inline constexpr auto Qdiv(const QuT1 f1, const QuT2 f2)
{
    return Qdiv_s<QuT1, QuT2, MergerArgsWrapper<toArgs...>>::div(f1, f2);
}

template <typename... toArgs, typename QuT>
    requires isScalar<QuT>
inline constexpr auto Qabs(const QuT f)
{
    return Qabs_s<QuT, MergerArgsWrapper<toArgs...>>::abs(f);
}

template <typename... toArgs, typename QuT>
    requires isScalar<QuT>
inline constexpr auto Qneg(const QuT f)
{
    return Qneg_s<QuT, MergerArgsWrapper<toArgs...>>::neg(f);
}

template <typename... toArgs, typename QuT1, typename QuT2>
    requires isScalar<QuT1> && isScalar<QuT2>
inline constexpr auto Qeq(const QuT1 f1, const QuT2 f2)
{
    return Qeq_s<QuT1, QuT2, MergerArgsWrapper<toArgs...>>::eq(f1, f2);
}

// operator overloading
template <typename... QuArgs1, typename... QuArgs2>
    requires isScalar<Qu_s<QuArgs1...>> && isScalar<Qu_s<QuArgs2...>>
inline constexpr auto operator*(const Qu_s<QuArgs1...> f1, const Qu_s<QuArgs2...> f2)
{
    return Qmul(f1, f2);
}

template <typename... QuArgs1, typename... QuArgs2>
    requires isScalar<Qu_s<QuArgs1...>> && isScalar<Qu_s<QuArgs2...>>
inline constexpr auto operator+(const Qu_s<QuArgs1...> f1, const Qu_s<QuArgs2...> f2)
{
    return Qadd(f1, f2);
}

template <typename... QuArgs1, typename... QuArgs2>
    requires isScalar<Qu_s<QuArgs1...>> && isScalar<Qu_s<QuArgs2...>>
inline constexpr auto operator-(const Qu_s<QuArgs1...> f1, const Qu_s<QuArgs2...> f2)
{
    return Qsub(f1, f2);
}

template <typename... QuArgs1, typename... QuArgs2>
    requires isScalar<Qu_s<QuArgs1...>> && isScalar<Qu_s<QuArgs2...>>
inline constexpr auto operator/(const Qu_s<QuArgs1...> f1, const Qu_s<QuArgs2...> f2)
{
    return Qdiv(f1, f2);
}

template <typename... QuArgs>
    requires isScalar<Qu_s<QuArgs...>>
inline constexpr auto operator-(const Qu_s<QuArgs...> f1)
{
    return Qneg(f1);
}

template <typename... QuArgs1, typename... QuArgs2>
    requires isScalar<Qu_s<QuArgs1...>> && isScalar<Qu_s<QuArgs2...>>
inline constexpr auto operator<=>(const Qu_s<QuArgs1...> f1, const Qu_s<QuArgs2...> f2)
{
    return Qcmp_s<Qu_s<QuArgs1...>, Qu_s<QuArgs2...>, MergerArgsWrapper<>>::cmp(f1, f2);
}

template <typename... QuArgs1, typename... QuArgs2>
    requires isScalar<Qu_s<QuArgs1...>> && isScalar<Qu_s<QuArgs2...>>
inline constexpr auto operator==(const Qu_s<QuArgs1...> f1, const Qu_s<QuArgs2...> f2)
{
    return Qeq(f1, f2);
}

// tensor functions
template <typename... toArgs, typename QuT1, typename QuT2>
    requires isTensorOperandPair<QuT1, QuT2>
inline constexpr auto Qmul(QuT1 &&f1, QuT2 &&f2)
{
    using T1 = std::remove_cvref_t<QuT1>;
    using T2 = std::remove_cvref_t<QuT2>;
    using Size = typename sizeMerger<T1, T2>::size;
    return lift<Size>(
        [](const auto &left, const auto &right) {
            return Qmul<toArgs...>(left, right);
        },
        std::forward<QuT1>(f1), std::forward<QuT2>(f2));
}

template <typename... toArgs, typename QuT1, typename QuT2>
    requires isTensorOperandPair<QuT1, QuT2>
inline constexpr auto Qadd(QuT1 &&f1, QuT2 &&f2)
{
    using T1 = std::remove_cvref_t<QuT1>;
    using T2 = std::remove_cvref_t<QuT2>;
    using Size = typename sizeMerger<T1, T2>::size;
    return lift<Size>(
        [](const auto &left, const auto &right) {
            return Qadd<toArgs...>(left, right);
        },
        std::forward<QuT1>(f1), std::forward<QuT2>(f2));
}

template <typename... toArgs, typename QuT1, typename QuT2>
    requires isTensorOperandPair<QuT1, QuT2>
inline constexpr auto Qsub(QuT1 &&f1, QuT2 &&f2)
{
    using T1 = std::remove_cvref_t<QuT1>;
    using T2 = std::remove_cvref_t<QuT2>;
    using Size = typename sizeMerger<T1, T2>::size;
    return lift<Size>(
        [](const auto &left, const auto &right) {
            return Qsub<toArgs...>(left, right);
        },
        std::forward<QuT1>(f1), std::forward<QuT2>(f2));
}

template <typename... toArgs, typename QuT1, typename QuT2>
    requires isTensorOperandPair<QuT1, QuT2>
inline constexpr auto Qdiv(QuT1 &&f1, QuT2 &&f2)
{
    using T1 = std::remove_cvref_t<QuT1>;
    using T2 = std::remove_cvref_t<QuT2>;
    using Size = typename sizeMerger<T1, T2>::size;
    return lift<Size>(
        [](const auto &left, const auto &right) {
            return Qdiv<toArgs...>(left, right);
        },
        std::forward<QuT1>(f1), std::forward<QuT2>(f2));
}

template <typename... toArgs, typename QuT>
    requires isTensorOperand<QuT>
inline constexpr auto Qabs(QuT &&f)
{
    using T = std::remove_cvref_t<QuT>;
    return lift<typename T::size>(
        [](const auto &value) { return Qabs<toArgs...>(value); },
        std::forward<QuT>(f));
}

template <typename... toArgs, typename QuT>
    requires isTensorOperand<QuT>
inline constexpr auto Qneg(QuT &&f)
{
    using T = std::remove_cvref_t<QuT>;
    return lift<typename T::size>(
        [](const auto &value) { return Qneg<toArgs...>(value); },
        std::forward<QuT>(f));
}

// operator overloading
template <typename QuT1, typename QuT2>
    requires isTensorOperandPair<QuT1, QuT2>
inline constexpr auto operator*(QuT1 &&f1, QuT2 &&f2)
{
    return Qmul(std::forward<QuT1>(f1), std::forward<QuT2>(f2));
}

template <typename QuT1, typename QuT2>
    requires isTensorOperandPair<QuT1, QuT2>
inline constexpr auto operator+(QuT1 &&f1, QuT2 &&f2)
{
    return Qadd(std::forward<QuT1>(f1), std::forward<QuT2>(f2));
}

template <typename QuT1, typename QuT2>
    requires isTensorOperandPair<QuT1, QuT2>
inline constexpr auto operator-(QuT1 &&f1, QuT2 &&f2)
{
    return Qsub(std::forward<QuT1>(f1), std::forward<QuT2>(f2));
}

template <typename QuT1, typename QuT2>
    requires isTensorOperandPair<QuT1, QuT2>
inline constexpr auto operator/(QuT1 &&f1, QuT2 &&f2)
{
    return Qdiv(std::forward<QuT1>(f1), std::forward<QuT2>(f2));
}

template <typename QuT>
    requires isTensorOperand<QuT>
inline constexpr auto operator-(QuT &&f1)
{
    return Qneg(std::forward<QuT>(f1));
}

// ------------------- Slice -------------------

template <typename Selector, size_t SourceExtent>
struct SliceSelectorTraits;

template <size_t SourceExtent>
struct SliceSelectorTraits<all_t, SourceExtent>
{
    inline static constexpr size_t start = 0;
    inline static constexpr size_t extent = SourceExtent;
};

template <size_t First, size_t Last, size_t SourceExtent>
struct SliceSelectorTraits<slice_t<First, Last>, SourceExtent>
{
    static_assert(Last <= SourceExtent, "A slice range is outside its source extent.");
    inline static constexpr size_t start = First;
    inline static constexpr size_t extent = Last - First;
};

template <typename SourceSize, typename SelectorTuple>
struct SliceShape
{
    template <size_t... I>
    inline static consteval size_t rank(std::index_sequence<I...>)
    {
        return (size_t{0} + ... +
                (std::integral<std::tuple_element_t<I, SelectorTuple>> ? 0 : 1));
    }

    inline static constexpr size_t outputRank =
        rank(std::make_index_sequence<SourceSize::dimSize>{});

    inline static constexpr auto extents = []<size_t... I>(
                                                std::index_sequence<I...>) {
        std::array<size_t, outputRank> result{};
        size_t output = 0;
        auto append = [&]<size_t Axis> {
            using selector = std::tuple_element_t<Axis, SelectorTuple>;
            if constexpr (!std::integral<selector>)
            {
                result[output++] =
                    SliceSelectorTraits<selector,
                                        SourceSize::dimArray[Axis]>::extent;
            }
        };
        (append.template operator()<I>(), ...);
        return result;
    }(std::make_index_sequence<SourceSize::dimSize>{});

    template <size_t... I>
    static auto make(std::index_sequence<I...>) -> dim<extents[I]...>;

    using type = decltype(make(std::make_index_sequence<outputRank>{}));
};

template <typename Tensor, typename... Selectors>
class SliceView
{
    using tensor_t = std::remove_cvref_t<Tensor>;
    using source_size = typename tensor_t::size;
    using selector_tuple = std::tuple<Selectors...>;

    static_assert(source_size::dimSize > 0, "A slice needs at least one axis.");
    static_assert(sizeof...(Selectors) == source_size::dimSize,
                  "A tensor slice needs exactly one selector per axis.");
    static_assert((TensorSliceSelector<Selectors> && ...));
    static_assert((!std::integral<Selectors> || ...),
                  "An all-integral subscript is an element access, not a slice.");

public:
    using size = typename SliceShape<source_size, selector_tuple>::type;

private:

    inline static constexpr bool storesReference =
        std::is_lvalue_reference_v<Tensor>;
    using referred_t = std::remove_reference_t<Tensor>;
    using storage_t = std::conditional_t<
        storesReference, std::reference_wrapper<referred_t>, tensor_t>;

    storage_t storage;
    selector_tuple selectors;

    inline static constexpr storage_t store(Tensor tensor)
    {
        if constexpr (storesReference)
            return std::ref(tensor);
        else
            return std::forward<Tensor>(tensor);
    }

    inline constexpr decltype(auto) target()
    {
        if constexpr (storesReference)
            return storage.get();
        else
            return (storage);
    }

    inline constexpr decltype(auto) target() const
    {
        if constexpr (storesReference)
            return storage.get();
        else
            return std::as_const(storage);
    }

    template <size_t I>
    inline static constexpr size_t localAxis = []<size_t... Before>(
                                                    std::index_sequence<Before...>) {
        return (size_t{0} + ... +
                (std::integral<std::tuple_element_t<Before, selector_tuple>>
                     ? 0
                     : 1));
    }(std::make_index_sequence<I>{});

    template <size_t I>
    inline constexpr size_t sourceIndex(
        const std::array<size_t, size::dimSize> &local) const
    {
        using selector = std::tuple_element_t<I, selector_tuple>;
        if constexpr (std::integral<selector>)
        {
            const auto raw = std::get<I>(selectors);
            if constexpr (std::signed_integral<selector>)
                if (raw < 0)
                    throw std::out_of_range("Slice index is out of range.");

            const size_t source = static_cast<size_t>(raw);
            if (source >= source_size::dimArray[I])
                throw std::out_of_range("Slice index is out of range.");
            return source;
        }
        else
        {
            using traits =
                SliceSelectorTraits<selector, source_size::dimArray[I]>;
            constexpr size_t axis = localAxis<I>;
            if (local[axis] >= traits::extent)
                throw std::out_of_range("Slice index is out of range.");
            return traits::start + local[axis];
        }
    }

    template <typename Self, size_t... I>
    inline static constexpr decltype(auto) access(
        Self &self, const std::array<size_t, size::dimSize> &local,
        std::index_sequence<I...>)
    {
        return self.target()[self.template sourceIndex<I>(local)...];
    }

    template <typename Self>
    inline static constexpr decltype(auto) accessFlat(Self &self, size_t flat)
    {
        if (flat >= size::elemSize)
            throw std::out_of_range("Slice index is out of range.");

        std::array<size_t, size::dimSize> local{};
        for (size_t axis = 0; axis < size::dimSize; ++axis)
        {
            local[axis] = flat % size::dimArray[axis];
            flat /= size::dimArray[axis];
        }
        return access(self, local,
                      std::make_index_sequence<source_size::dimSize>{});
    }

public:
    explicit inline constexpr SliceView(Tensor tensor, Selectors... selected)
        : storage(store(std::forward<Tensor>(tensor))),
          selectors(std::move(selected)...) {}

    inline constexpr decltype(auto) operator[](this auto &&self, size_t flat)
    {
        return accessFlat(self, flat);
    }

    inline constexpr decltype(auto) operator[](this auto &&self, auto... index)
        requires(sizeof...(index) == size::dimSize &&
                 sizeof...(index) > 1 &&
                 (std::is_convertible_v<decltype(index), size_t> && ...))
    {
        std::array<size_t, size::dimSize> local{
            static_cast<size_t>(index)...};
        return access(self, local,
                      std::make_index_sequence<source_size::dimSize>{});
    }

    template <typename Self, typename... Next>
    inline constexpr auto operator[](this Self &&self, Next... selectors)
        requires(sizeof...(Next) == size::dimSize &&
                 (TensorSliceSelector<Next> && ...) &&
                 !(std::integral<std::remove_cvref_t<Next>> && ...))
    {
        return SliceView<Self &&, std::remove_cvref_t<Next>...>(
            std::forward<Self>(self), selectors...);
    }
};

// ------------------- Advanced Nonlinear Universal Subprograms -------------------
// the operations like lookup table, linear/polynomial fitting, etc. used to implement the non-linear operation in asic
// note that the operations are not standard BLAS operations, use ANUS:: to get access to them

namespace ANUS {

// polynomial fitting
template <auto a0>
inline static constexpr auto Qpoly(auto)
{
    return a0;
}

// return a0 + a1 * x + a2 * x^2 + ...
template <auto a0, auto a1, auto... as>
inline static constexpr auto Qpoly(auto x)
{
    return Qadd<decltype(a0)>(
        a0,
        Qmul<decltype(a0)>(
            x,
            Qpoly<a1, as...>(x)));
}

// segmented linear fitting
template <double BreakPoint, auto... as>
struct Segment
{
    static constexpr double breakpoint = BreakPoint;

    inline static constexpr auto func(auto x)
    {
        return Qpoly<as...>(x);
    }
};

template <typename Segment1, typename... Rest>
constexpr auto Qapprox(auto x)
{
    if (x.toDouble() < Segment1::breakpoint)
    {
        // return Segment1::func(x);
        return decltype(x){Segment1::func(x)};
    }
    else
    {
        if constexpr (sizeof...(Rest) > 0)
        {
            return Qapprox<Rest...>(x);
        }
        else
        {
            // 如果超过最后一个分段点，使用最后一个函数
            // return Segment1::func(x);
            return decltype(x){Segment1::func(x)};
        }
    }
}

template <typename... Args>
struct Qapprox_s
{
    inline static constexpr auto execute(auto x)
    {
        return Qapprox<Args...>(x);
    }
};

} // namespace ANUS

// ===================== BLAS =====================
// ------------------- Reducer -------------------
// it's not a standard BLAS operation, but tree-based reduction is a common operation in asic design

template <typename... Args>
struct Reducer
{
    inline static constexpr size_t layerCount = sizeof...(Args);

    // The sentinel makes the untyped Qreduce<> spelling participate in the
    // same tree as an explicitly typed reduction. Once a non-empty layer list
    // is exhausted, its last type continues to describe every deeper layer.
    template <size_t layer>
    using layerType = TypeAt<
        layerCount == 0 ? 0 : (layer < layerCount ? layer : layerCount - 1),
        TypeList<Args..., std::nullptr_t>>;

    template <typename type, typename T>
    static constexpr auto quantizeCarry(T &&value)
    {
        if constexpr (std::is_same_v<type, std::nullptr_t>)
        {
            return std::forward<T>(value);
        }
        else if constexpr (isTensorOperand<T>)
        {
            return lift<tensorSize<T>>(
                [](const auto &element) { return type(element); },
                std::forward<T>(value));
        }
        else
        {
            return type(std::forward<T>(value));
        }
    }

    // Each instantiation consumes one balanced tree layer. Tuple CTAD owns all
    // intermediate values, while the explicit object parameter supplies the
    // recursive call without a family of helper specializations.
    inline static constexpr auto reduceTree =
        []<size_t layer, typename Tuple>(this auto self, Tuple quants) -> auto {
        constexpr size_t len = std::tuple_size_v<Tuple>;
        static_assert(len > 0, "Qreduce requires at least one input.");

        if constexpr (len == 1)
        {
            return std::get<0>(std::move(quants));
        }
        else
        {
            using type = layerType<layer>;
            return [&]<size_t... I>(std::index_sequence<I...>) -> auto {
                if constexpr (len % 2 == 0)
                {
                    return self.template operator()<layer + 1>(std::tuple{
                        Qadd<type>(std::move(std::get<I * 2>(quants)),
                                   std::move(std::get<I * 2 + 1>(quants)))...});
                }
                else
                {
                    // The unpaired value crosses the same quantization boundary
                    // as every paired result at this layer.
                    return self.template operator()<layer + 1>(std::tuple{
                        Qadd<type>(std::move(std::get<I * 2>(quants)),
                                   std::move(std::get<I * 2 + 1>(quants)))...,
                        quantizeCarry<type>(
                            std::move(std::get<len - 1>(quants)))});
                }
            }(std::make_index_sequence<len / 2>{});
        }
    };

    template <typename... Ts>
        requires(sizeof...(Ts) != 1 || !(isTensorOperand<Ts> && ...))
    static constexpr auto reduce(Ts... quants)
    {
        if constexpr (sizeof...(Ts) == 0)
        {
            static_assert(sizeof...(Ts) > 0, "Qreduce requires at least one input.");
        }
        else
        {
            return reduceTree.template operator()<0>(
                std::tuple{std::move(quants)...});
        }
    }

    // Concrete tensors and lazy expressions share one materialization path.
    // Linear indexing deliberately flattens every rank before building the
    // compile-time tuple tree.
    template <typename TensorT>
        requires isTensorOperand<TensorT>
    static constexpr auto reduce(const TensorT &quants)
    {
        constexpr size_t len = tensorSize<TensorT>::elemSize;

        if constexpr (len == 0)
        {
            static_assert(len > 0, "Qreduce requires a non-empty tensor.");
        }
        else
        {
            return [&]<size_t... I>(std::index_sequence<I...>) {
                return reduceTree.template operator()<0>(
                    std::tuple{quants[I]...});
            }(std::make_index_sequence<len>{});
        }
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

// Decimal literals are exact rationals.  Their ArbiInt width grows with the
// text, then the target Qu type's own division policy performs quantisation.
namespace detail {

struct decimal_literal_info
{
    bool valid = true;
    bool negative = false;
    size_t digits = 0;
    size_t fractional = 0;
};

template <fixed_string Text>
consteval decimal_literal_info inspect_decimal_literal()
{
    decimal_literal_info result;
    bool point = false;
    bool digit = false;

    for (size_t i = 0; i < Text.size(); ++i)
    {
        const char c = Text[i];
        if (i == 0 && (c == '+' || c == '-'))
        {
            result.negative = c == '-';
            continue;
        }
        if (c == '.' && !point)
        {
            point = true;
            continue;
        }
        if (c < '0' || c > '9')
            return {.valid = false};

        digit = true;
        ++result.digits;
        result.fractional += point;
    }

    result.valid = digit;
    return result;
}

template <fixed_string Text>
struct decimal_literal_proxy
{
    inline static constexpr auto literal = inspect_decimal_literal<Text>();
    static_assert(literal.valid,
                  "A _dq literal accepts one optional leading sign, decimal "
                  "digits, and at most one radix point");

    inline static constexpr size_t width = literal.digits * 4 + 2;

    static constexpr auto append(ArbiInt<width> value, uint64_t digit = 0)
    {
        return ArbiInt<width>(value * ArbiInt<5>(10) + ArbiInt<5>(digit));
    }

    static constexpr auto magnitude()
    {
        ArbiInt<width> value;
        for (size_t i = 0; i < Text.size(); ++i)
            if (Text[i] >= '0' && Text[i] <= '9')
                value = append(value, Text[i] - '0');
        return value;
    }

    static constexpr auto denominator()
    {
        ArbiInt<width> value(1);
        for (size_t i = 0; i < literal.fractional; ++i)
            value = append(value);
        return value;
    }

    template <typename Target>
        requires is_fixed_scalar_v<Target>
    constexpr auto as() const
    {
        using target_type = std::remove_cvref_t<Target>;
        using exact_integer =
            Qu<intBits<static_cast<int>(width - 1)>, fracBits<0>, isSigned<true>>;

        exact_integer numerator;
        exact_integer divisor;
        constexpr auto absolute = magnitude();
        numerator.data = literal.negative ? ArbiInt<width>(-absolute) : absolute;
        divisor.data = denominator();
        return Qdiv<target_type>(numerator, divisor);
    }
};

} // namespace detail

template <fixed_string Text>
consteval auto operator""_dq()
{
    return detail::decimal_literal_proxy<Text>{};
}

template <fixed_string Text, typename Target>
    requires detail::is_fixed_scalar_v<Target>
constexpr auto operator|(detail::decimal_literal_proxy<Text> literal,
                         to_type<Target>)
{
    return literal.template as<Target>();
}

// ------------------- Static einsum -------------------
// A formula is compiled into one label graph.  Matrix products, diagonals,
// outer products, traces and N-operand contractions are merely different data
// in that graph; none needs its own expression class.
namespace detail {

constexpr bool isEinsumLabel(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

constexpr bool isEinsumSpace(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

template <size_t Axes, size_t Operands>
struct einsum_syntax
{
    bool valid = true;
    std::array<unsigned char, Axes> inputs{};
    std::array<unsigned char, Axes> outputs{};
    std::array<unsigned char, Axes> contractions{};
    std::array<size_t, Operands + 1> offsets{};
    size_t outputRank = 0;
    size_t contractionRank = 0;
};

template <fixed_string Equation, size_t Axes, size_t Operands>
consteval auto parseEinsum(const std::array<size_t, Operands> &ranks,
                           const std::array<size_t, Axes> &axisExtents)
{
    einsum_syntax<Axes, Operands> syntax;
    std::array<size_t, 256> occurrences{};
    std::array<size_t, 256> extents{};
    std::array<bool, 256> outputSeen{};

    size_t arrow = Equation.size();
    size_t arrows = 0;
    for (size_t i = 0; i + 1 < Equation.size(); ++i)
        if (Equation[i] == '-' && Equation[i + 1] == '>')
        {
            arrow = i;
            ++arrows;
        }
    syntax.valid &= arrows <= 1;

    size_t operand = 0;
    size_t localAxis = 0;
    size_t axis = 0;
    for (size_t i = 0; i < arrow; ++i)
    {
        const char c = Equation[i];
        if (isEinsumSpace(c))
            continue;
        if (c == ',')
        {
            syntax.valid &= operand < Operands && localAxis == ranks[operand];
            ++operand;
            localAxis = 0;
            if (operand <= Operands)
                syntax.offsets[operand] = axis;
            continue;
        }
        if (!isEinsumLabel(c) || operand >= Operands ||
            localAxis >= ranks[operand] || axis >= Axes)
        {
            syntax.valid = false;
            continue;
        }

        const auto label = static_cast<unsigned char>(c);
        syntax.inputs[axis] = label;
        if (occurrences[label]++ == 0)
            extents[label] = axisExtents[axis];
        else
            syntax.valid &= extents[label] == axisExtents[axis];
        ++axis;
        ++localAxis;
    }

    syntax.valid &= Operands > 0 && operand + 1 == Operands &&
                    operand < Operands && localAxis == ranks[operand] &&
                    axis == Axes;
    syntax.offsets[Operands] = axis;

    if (arrows == 1)
    {
        for (size_t i = arrow + 2; i < Equation.size(); ++i)
        {
            const char c = Equation[i];
            if (isEinsumSpace(c))
                continue;
            if (!isEinsumLabel(c))
            {
                syntax.valid = false;
                continue;
            }
            const auto label = static_cast<unsigned char>(c);
            if (occurrences[label] == 0 || outputSeen[label] ||
                syntax.outputRank >= Axes)
            {
                syntax.valid = false;
                continue;
            }
            outputSeen[label] = true;
            syntax.outputs[syntax.outputRank++] = label;
        }
    }
    else
    {
        // Implicit output follows first appearance, which is more useful for a
        // DSL than imposing an unrelated alphabetical ordering.
        for (size_t i = 0; i < Axes; ++i)
        {
            const auto label = syntax.inputs[i];
            if (occurrences[label] == 1 && !outputSeen[label])
            {
                outputSeen[label] = true;
                syntax.outputs[syntax.outputRank++] = label;
            }
        }
    }

    std::array<bool, 256> contractionSeen{};
    for (size_t i = 0; i < Axes; ++i)
    {
        const auto label = syntax.inputs[i];
        if (!outputSeen[label] && !contractionSeen[label])
        {
            contractionSeen[label] = true;
            syntax.contractions[syntax.contractionRank++] = label;
            syntax.valid &= extents[label] > 0;
        }
    }
    return syntax;
}

template <fixed_string Equation, typename... Shapes>
struct einsum_plan
{
    inline static constexpr size_t operandCount = sizeof...(Shapes);
    inline static constexpr size_t axisCount = (size_t{0} + ... + Shapes::dimSize);
    inline static constexpr std::array<size_t, operandCount> ranks = {
        Shapes::dimSize...};

    inline static constexpr auto axisExtents = [] {
        std::array<size_t, axisCount> result{};
        size_t position = 0;
        ([&] {
            for (size_t extent : Shapes::dimArray)
                result[position++] = extent;
        }(), ...);
        return result;
    }();

    inline static constexpr auto syntax =
        parseEinsum<Equation>(ranks, axisExtents);

    inline static constexpr auto labelExtents = [] {
        std::array<size_t, 256> result{};
        for (size_t i = 0; i < axisCount; ++i)
            result[syntax.inputs[i]] = axisExtents[i];
        return result;
    }();

    inline static constexpr size_t contractionSpace = [] {
        size_t result = 1;
        for (size_t i = 0; i < syntax.contractionRank; ++i)
            result *= labelExtents[syntax.contractions[i]];
        return result;
    }();

    template <size_t... I>
    static auto makeSize(std::index_sequence<I...>)
        -> dim<labelExtents[syntax.outputs[I]]...>;

    using size = decltype(makeSize(
        std::make_index_sequence<syntax.outputRank>{}));
};

template <fixed_string Equation, bool AllTensor, typename... Operands>
struct einsum_compatible : std::false_type
{};

template <fixed_string Equation, typename... Operands>
struct einsum_compatible<Equation, true, Operands...>
    : std::bool_constant<
          einsum_plan<Equation, tensorSize<Operands>...>::syntax.valid>
{};

} // namespace detail

template <fixed_string Equation, typename... Operands>
concept EinsumCompatible = detail::einsum_compatible<
    Equation,
    (sizeof...(Operands) > 0 && (isTensorOperand<Operands> && ...)),
    std::remove_cvref_t<Operands>...>::value;

template <fixed_string Equation, typename... Operands>
    requires EinsumCompatible<Equation, Operands...>
inline constexpr auto einsum(Operands &&...operands)
{
    using plan = detail::einsum_plan<
        Equation, tensorSize<std::remove_cvref_t<Operands>>...>;
    using size = typename plan::size;
    using coordinates = std::array<size_t, 256>;
    using operand_types = std::tuple<std::remove_cvref_t<Operands>...>;
    using captures = std::tuple<ExpressionOperand<Operands &&>...>;

    return lazy<size>(
        [values = captures(ExpressionOperand<Operands &&>(
             std::forward<Operands>(operands))...)]<typename... Index>(
            Index... index) constexpr
            requires((sizeof...(Index) == 1 ||
                      (sizeof...(Index) == size::dimSize &&
                       sizeof...(Index) > 1)) &&
                     (std::convertible_to<Index, size_t> && ...))
        {
            coordinates at{};
            if constexpr (sizeof...(Index) == 1)
            {
                size_t flat = std::array<size_t, 1>{
                    static_cast<size_t>(index)...}[0];
                if (flat >= size::elemSize)
                    throw std::out_of_range(
                        "einsum output index is out of range");

                for (size_t axis = 0; axis < plan::syntax.outputRank; ++axis)
                {
                    const auto label = plan::syntax.outputs[axis];
                    const auto extent = plan::labelExtents[label];
                    at[label] = flat % extent;
                    flat /= extent;
                }
            }
            else
            {
                const std::array<size_t, size::dimSize> local{
                    static_cast<size_t>(index)...};
                for (size_t axis = 0; axis < size::dimSize; ++axis)
                {
                    if (local[axis] >= size::dimArray[axis])
                        throw std::out_of_range(
                            "einsum output index is out of range");
                    at[plan::syntax.outputs[axis]] = local[axis];
                }
            }

            auto operandValue = [&]<size_t I>(const coordinates &where)
                -> decltype(auto) {
                using operand_type = std::tuple_element_t<I, operand_types>;
                using shape = tensorSize<operand_type>;
                size_t flat = 0;
                size_t stride = 1;
                for (size_t axis = 0; axis < shape::dimSize; ++axis)
                {
                    const auto label =
                        plan::syntax.inputs[plan::syntax.offsets[I] + axis];
                    flat += where[label] * stride;
                    stride *= shape::dimArray[axis];
                }
                return std::get<I>(values).get()[flat];
            };

            auto productAt = [&](const coordinates &where) {
                auto multiply = [&]<size_t I>(this auto self, auto product)
                    -> auto {
                    if constexpr (I == sizeof...(Operands))
                        return product;
                    else
                        return self.template operator()<I + 1>(Qmul<FullPrec>(
                            product,
                            operandValue.template operator()<I>(where)));
                };

                if constexpr (sizeof...(Operands) == 1)
                    return operandValue.template operator()<0>(where);
                else
                    return multiply.template operator()<1>(
                        operandValue.template operator()<0>(where));
            };

            auto contract = [&]<size_t Offset, size_t Count>(
                                this auto self, coordinates where) -> auto {
                if constexpr (Count == 1)
                {
                    size_t flat = Offset;
                    for (size_t axis = 0;
                         axis < plan::syntax.contractionRank; ++axis)
                    {
                        const auto label = plan::syntax.contractions[axis];
                        const auto extent = plan::labelExtents[label];
                        where[label] = flat % extent;
                        flat /= extent;
                    }
                    return productAt(where);
                }
                else
                {
                    constexpr size_t left = Count / 2;
                    return Qadd<FullPrec>(
                        self.template operator()<Offset, left>(where),
                        self.template operator()<Offset + left,
                                                 Count - left>(where));
                }
            };

            return contract.template operator()<0, plan::contractionSpace>(at);
        });
}

// ------------------- Typed Einstein notation -------------------
// `ein` is both sides of the notation, so tensors themselves remain blissfully
// unaware of the DSL:
//
//   ein[_i, _k] <<= ein[A, _i, _j] * ein[B, _j, _k];
namespace indices {

template <char Label>
struct axis
{
    inline static constexpr char value = Label;
    using ein_axis = void;
};

template <typename T>
concept Axis = requires { typename std::remove_cvref_t<T>::ein_axis; };

template <char... Labels>
struct axes
{
    inline static constexpr std::array<char, sizeof...(Labels)> values{Labels...};
    inline static constexpr size_t count = sizeof...(Labels);
};

template <typename T, char... Labels>
class indexed
{
    using storage = std::conditional_t<std::is_lvalue_reference_v<T>, T,
                                       std::remove_cvref_t<T>>;
    storage tensor;

public:
    using labels = axes<Labels...>;
    using ein_factor = void;

    inline constexpr explicit indexed(T &&value)
        : tensor(std::forward<T>(value)) {}

    inline constexpr decltype(auto) take() &&
    {
        if constexpr (std::is_lvalue_reference_v<T>)
            return (tensor);
        else
            return std::move(tensor);
    }
};

template <typename... Factors>
struct product
{
    std::tuple<Factors...> factors;
};

template <char... Labels>
struct output
{};

template <typename T>
concept Factor = requires { typename std::remove_cvref_t<T>::ein_factor; };

template <Factor L, Factor R>
inline constexpr auto operator*(L &&left, R &&right)
{
    return product<std::remove_cvref_t<L>, std::remove_cvref_t<R>>{
        {std::forward<L>(left), std::forward<R>(right)}};
}

template <typename... L, Factor R>
inline constexpr auto operator*(product<L...> &&left, R &&right)
{
    return product<L..., std::remove_cvref_t<R>>{std::tuple_cat(
        std::move(left.factors), std::tuple{std::forward<R>(right)})};
}

template <typename Output, typename... Factors>
consteval auto equation()
{
    constexpr size_t extent =
        (Factors::labels::count + ...) + sizeof...(Factors) + Output::count + 2;
    char text[extent]{};
    size_t at = 0;
    size_t operand = 0;
    auto emit = [&]<typename Labels> {
        for (char label : Labels::values)
            text[at++] = label;
        if (++operand < sizeof...(Factors))
            text[at++] = ',';
    };
    (emit.template operator()<typename Factors::labels>(), ...);
    text[at++] = '-';
    text[at++] = '>';
    for (char label : Output::values)
        text[at++] = label;
    return fixed_string{text};
}

template <char... Out, typename... Factors>
inline constexpr auto operator<<=(output<Out...>, product<Factors...> &&terms)
{
    return std::apply(
        []<typename... F>(F &&...factor) {
            return einsum<equation<axes<Out...>, Factors...>()>(
                std::move(factor).take()...);
        },
        std::move(terms.factors));
}

template <char... Out, Factor F>
inline constexpr auto operator<<=(output<Out...>, F &&factor)
{
    using factor_type = std::remove_cvref_t<F>;
    return einsum<equation<axes<Out...>, factor_type>()>(
        std::move(factor).take());
}

struct ein_t
{
    template <Axis... I>
    inline constexpr auto operator[](I...) const
    {
        return output<std::remove_cvref_t<I>::value...>{};
    }

    template <typename T, Axis... I>
        requires(isTensorOperand<T> && tensorSize<T>::dimSize == sizeof...(I))
    inline constexpr auto operator[](T &&tensor, I...) const
    {
        return indexed<T &&, std::remove_cvref_t<I>::value...>(
            std::forward<T>(tensor));
    }
};

inline constexpr ein_t ein;
inline constexpr axis<'a'> _a; inline constexpr axis<'b'> _b;
inline constexpr axis<'c'> _c; inline constexpr axis<'d'> _d;
inline constexpr axis<'e'> _e; inline constexpr axis<'f'> _f;
inline constexpr axis<'g'> _g; inline constexpr axis<'h'> _h;
inline constexpr axis<'i'> _i; inline constexpr axis<'j'> _j;
inline constexpr axis<'k'> _k; inline constexpr axis<'l'> _l;
inline constexpr axis<'m'> _m; inline constexpr axis<'n'> _n;
inline constexpr axis<'o'> _o; inline constexpr axis<'p'> _p;
inline constexpr axis<'q'> _q; inline constexpr axis<'r'> _r;
inline constexpr axis<'s'> _s; inline constexpr axis<'t'> _t;
inline constexpr axis<'u'> _u; inline constexpr axis<'v'> _v;
inline constexpr axis<'w'> _w; inline constexpr axis<'x'> _x;
inline constexpr axis<'y'> _y; inline constexpr axis<'z'> _z;

} // namespace indices

} // namespace QuBLAS

// Keep formatting at the language boundary: the scalar itself only knows its
// bits and value, while std::format supplies the surface syntax.
namespace std {

template <int IntBits, int FracBits, bool Signed, typename Quantization,
          typename Overflow>
struct formatter<
    QuBLAS::Qu_s<QuBLAS::intBits<IntBits>, QuBLAS::fracBits<FracBits>,
                 QuBLAS::isSigned<Signed>, QuBLAS::QuMode<Quantization>,
                 QuBLAS::OfMode<Overflow>>,
    char>
{
    char view = 'f';
    std::formatter<double, char> number;
    std::formatter<std::string_view, char> text;

    constexpr auto parse(std::format_parse_context &context)
    {
        auto it = context.begin();
        if (it != context.end() && (*it == 'b' || *it == 'x' || *it == 'X' || *it == 'q'))
        {
            view = *it++;
            context.advance_to(it);
            return text.parse(context);
        }
        return number.parse(context);
    }

    template <typename Context>
    auto format(const auto &value, Context &context) const
    {
        if (view == 'b')
        {
            const auto bits = value.toString();
            return text.format(std::string_view(bits), context);
        }

        if (view == 'q')
        {
            const auto description =
                std::format("Q<{}_i, {}_f, {}>({})", IntBits, FracBits,
                            Signed ? "signed_" : "unsigned_", value.toDouble());
            return text.format(std::string_view(description), context);
        }

        if (view == 'x' || view == 'X')
        {
            auto bits = value.toString();
            bits.insert(0, (4 - bits.size() % 4) % 4, '0');
            std::string hex;
            constexpr std::string_view digits = "0123456789abcdef";
            for (size_t i = 0; i < bits.size(); i += 4)
            {
                unsigned nibble = 0;
                for (size_t j = 0; j < 4; ++j)
                    nibble = nibble * 2 + static_cast<unsigned>(bits[i + j] - '0');
                hex += digits[nibble];
            }
            if (view == 'X')
                std::ranges::transform(hex, hex.begin(), [](char c) {
                    return static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
                });
            return text.format(std::string_view(hex), context);
        }

        return number.format(value.toDouble(), context);
    }
};

} // namespace std
