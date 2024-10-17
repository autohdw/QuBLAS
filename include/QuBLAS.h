#pragma once

#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <complex>
#include <csignal>
#include <cstddef>
#include <cstring>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <stdexcept>
#include <sys/resource.h>
#include <sys/types.h>
#include <type_traits>
#include <utility>

inline namespace QuBLAS {

// ------------------- Random -------------------

static std::random_device rd;
static std::mt19937 gen(1);                                                                                                         // 1 is the seed
static std::uniform_int_distribution<uint64_t> UniRand(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max()); // 整数的全范围分布
static std::normal_distribution<double> NormRand(0, 1);                                                                             // 正态分布

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
constexpr std::string big_integer_to_string(const std::array<uint64_t, num_words> &value)
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
// This class template represents an arbitrary-precision integer with N bits.
// The kernel of the implementation is a std::array of uint64_t, which stores the integer in little-endian order.
// Actually a N-bit integer is stored with 64 * ceil(N / 64) bits, the overflow is algorithmically handled and will not happen in practice. So many operations are implemented with the assumption that the integer is not overflowed.

// General template declaration
template <size_t N>
class ArbiInt;

// Specialization for N in (0, 64], using a single integer
template <size_t N>
    requires(N > 0 && N <= 64)
class ArbiInt<N>
{
public:
    using data_t = std::conditional_t<(N <= 32), int32_t, int64_t>;
    static constexpr size_t num_bits = N;
    data_t data;

    // Default constructor
    constexpr ArbiInt() : data(0) {}

    // special constructor that return a ArbiInt with the last N bits set to 1
    static constexpr ArbiInt<N> allOnes()
    {
        ArbiInt<N> result;
        result.data = ~(~data_t(0) << N);
        return result;
    }

    // special constructor that return a ArbiInt with the last N bits set to 0 adn and the rest set to 1
    static constexpr ArbiInt<N> allZeros()
    {
        ArbiInt<N> result;
        result.data = ~data_t(0) << N;
        return result;
    }

    constexpr auto isZero() const
    {
        return data == 0;
    }

    constexpr auto isNegative() const
    {
        return data < 0;
    }

    constexpr auto isPositive() const
    {
        return data > 0;
    }

    // Constructor

    // Constructor from another ArbiInt
    template <size_t M>
        requires(M > 0 && M <= 64)
    constexpr ArbiInt(const ArbiInt<M> &other)
    {
        data = other.data;
    }

    template <size_t M>
        requires(M > 64)
    constexpr ArbiInt(const ArbiInt<M> &other)
    {
        data = other.data[0];
    }

    constexpr ArbiInt(double val)
    {
        loadFromDouble<0>(val);
    }

    template <int fracB>
    constexpr void loadFromDouble(double val)
    {
        if (val == 0.0 || std::isnan(val) || std::isinf(val))
        {
            data = 0;
            return;
        }

        // Extract the sign, exponent, and mantissa from the double
        const uint64_t doubleAsUint64 = std::bit_cast<uint64_t>(val);
        const bool sign = (doubleAsUint64 >> 63) != 0;
        const int64_t exponent = ((doubleAsUint64 >> 52) & 0x7FF) - 1023;
        uint64_t mantissa = (doubleAsUint64 & 0xFFFFFFFFFFFFFull) | 0x10000000000000ull; // Add the implicit leading 1

        // Calculate the total shift required
        const int64_t shift = exponent + fracB - 52;

        // Initialize data
        int64_t result = 0;

        if (shift >= 0)
        {
            if (shift < 64)
            {
                uint64_t shiftedMantissa = mantissa << shift;
                result = static_cast<int64_t>(shiftedMantissa);
            }
            else
            {
                // Shift too large, result becomes zero or overflows
                result = 0;
            }
        }
        else // shift < 0
        {
            if (-shift < 64)
            {
                uint64_t shiftedMantissa = mantissa >> (-shift);
                result = static_cast<int64_t>(shiftedMantissa);
            }
            else
            {
                // Shift too large, result becomes zero
                result = 0;
            }
        }

        // Apply the sign
        if (sign)
        {
            result = -result;
        }

        data = result;
    }

    // Assignment from string
    ArbiInt(const std::string &str)
    {
        // Convert string to int64_t
        int64_t value = std::stoll(str);
        data = static_cast<data_t>(value);

        // Extend or mask to N bits
        if constexpr (N < 64)
        {
            // Mask to N bits while preserving the sign
            data = static_cast<data_t>((static_cast<int64_t>(data) << (64 - N)) >> (64 - N));
        }
    }

    // operator bool
    constexpr operator bool() const
    {
        return data != 0;
    }

    auto fill()
    {
        // generate a random number with the full range of - 2^(N-1) to 2^(N-1) - 1
        static std::uniform_int_distribution<__int128_t> dist(-(__int128_t(1) << (N - 1)), (__int128_t(1) << (N - 1)) - 1);

        data = static_cast<data_t>(dist(gen));

        return *this;
    }

    constexpr auto toString() const
    {
        return std::to_string(data);
    }

    constexpr auto toDouble() const
    {
        return static_cast<double>(data);
    }

    constexpr auto uToDouble() const
    {
        uint64_t tmp = (num_bits == 64 ? data : data & ((1ll << num_bits) -1));
        return static_cast<double>(static_cast<unsigned long long> (tmp));
    }

    constexpr auto toBinary() const
    {
        return std::bitset < N < 32 ? 32 : 64 > (data).to_string();
    }

    void display(std::string name = "") const
    {
        if (!name.empty())
        {
            std::cout << name << ":" << std::endl;
        }
        std::cout << "Binary:  " << std::bitset < N <= 32 ? 32 : 64 > (data) << std::endl;
        std::cout << "Decimal: " << data << std::endl;
        std::cout << std::endl;
    }
};

template <size_t N>
    requires(N > 64)
class ArbiInt<N>
{
public:
    static constexpr size_t num_bits = N;
    static constexpr size_t num_words = (N + 63) / 64;
    std::array<uint64_t, num_words> data;

    // Default constructor
    constexpr ArbiInt()
    {
        data.fill(0);
    }

    // special constructor that return a ArbiInt with the last N bits set to 1
    static constexpr ArbiInt<N> allOnes()
    {
        ArbiInt<N> result;
        result.data.fill(~uint64_t(0));
        result.data[num_words - 1] = ~uint64_t(0) >> (64 - N % 64);
        return result;
    }

    // special constructor that return a ArbiInt with the last N bits set to 0 adn and the rest set to 1
    static constexpr ArbiInt<N> allZeros()
    {
        ArbiInt<N> result;
        result.data.fill(0);
        result.data[num_words - 1] = ~uint64_t(0) << (N % 64);
        return result;
    }

    constexpr auto isZero() const
    {
        return std::all_of(data.begin(), data.end(), [](uint64_t w) { return w == 0; });
    }

    constexpr bool isNegative() const
    {
        return data[num_words - 1] >> 63;
    }

    constexpr bool isPositive() const
    {
        return data[num_words - 1] >> 63 == 0;
    }

    static constexpr uint64_t mask = (static_cast<uint64_t>(1) << (N % 64)) - 1;

    // Constructor from arithmetic types
    template <typename T>
        requires std::is_integral_v<T>
    constexpr ArbiInt(T val)
    {
        data.fill(0);
        data[0] = static_cast<uint64_t>(val);

        // sign extension of the higher uint64_ts, all 1 or all 0 according to whether the 64-th bit of the lowest uint64_t is 1
        uint64_t sign_extension = static_cast<uint64_t>(static_cast<int64_t>(data[0]) >> 63);
        for (size_t i = 1; i < num_words; ++i)
        {
            data[i] = sign_extension;
        }
    }

    constexpr ArbiInt(double val)
    {
        loadFromDouble<0>(val);
    }

    template <int fracB>
    constexpr void loadFromDouble(double val)
    {
        for (auto &word : data)
            word = 0;

        // Handle zero, NaN, and infinity
        if (val == 0.0 || std::isnan(val) || std::isinf(val))
            return;

        const uint64_t doubleAsUint64 = std::bit_cast<uint64_t>(val);
        const uint64_t sign = doubleAsUint64 >> 63;
        const int64_t exponent = ((doubleAsUint64 >> 52) & 0x7FF) - 1023;
        const uint64_t mantissa = (doubleAsUint64 & 0xFFFFFFFFFFFFFull) | 0x10000000000000ull;

        // Calculate the total shift required
        int64_t shift = exponent + fracB - 52;

        if (shift >= 0)
        {
            // Left shift the mantissa
            int64_t wordShift = shift / 64;
            int64_t bitShift = shift % 64;

            if (wordShift < num_words)
            {
                data[wordShift] |= mantissa << bitShift;

                if (bitShift != 0 && (wordShift + 1) < num_words)
                {
                    data[wordShift + 1] |= mantissa >> (64 - bitShift);
                }
            }
        }
        else
        {
            int64_t totalShift = -shift;

            if (totalShift < 64)
            {
                data[0] = mantissa >> totalShift;
            }
            else if (totalShift < 64 * num_words)
            {
                int64_t wordShift = totalShift / 64;
                int64_t bitShift = totalShift % 64;

                if (bitShift == 0)
                {
                    if (wordShift < num_words)
                    {
                        data[wordShift] = mantissa;
                    }
                }
                else
                {
                    if (wordShift < num_words)
                    {
                        data[wordShift] |= mantissa >> bitShift;
                    }
                    if ((wordShift + 1) < num_words)
                    {
                        data[wordShift + 1] |= mantissa << (64 - bitShift);
                    }
                }
            }
        }

        if (sign)
        {
            // Invert the bits
            for (auto &word : data)
            {
                word = ~word;
            }

            uint64_t carry = 1;
            for (size_t i = 0; i < num_words; ++i)
            {
                uint64_t sum = data[i] + carry;
                carry = (sum < data[i]) ? 1 : 0;
                data[i] = sum;
                if (!carry)
                    break;
            }
        }
    }

    // Assignment from string
    ArbiInt(const std::string &str)
    {
        data = string_to_big_integer<num_words>(str);
    }

    template <size_t M>
        requires(ArbiInt<M>::num_words == num_words)
    constexpr ArbiInt(const ArbiInt<M> &other)
    {
        std::copy(other.data.begin(), other.data.end(), data.begin());
    }

    template <size_t M>
        requires(M > 0 && M <= 64)
    constexpr ArbiInt(const ArbiInt<M> &other)
    {
        data[0] = other.data;

        // sign extension of the higher uint64_ts, all 1 or all 0 according to whether the 64-th bit of the lowest uint64_t is 1
        uint64_t sign_extension = static_cast<uint64_t>(static_cast<int64_t>(data[0]) >> 63);
        for (size_t i = 1; i < num_words; ++i)
        {
            data[i] = sign_extension;
        }
    }

    template <size_t M>
        requires(M > 64 && ArbiInt<M>::num_words != num_words)
    constexpr ArbiInt(const ArbiInt<M> &other)
    {
        constexpr size_t copyLen = std::min(ArbiInt<M>::num_words, ArbiInt<N>::num_words);

        std::copy(other.data.begin(), other.data.begin() + copyLen, data.begin());

        // sign extension of the higher uint64_ts, all 1 or all 0 according to whether the 64-th bit of the lowest uint64_t is 1
        uint64_t sign_extension = static_cast<uint64_t>(static_cast<int64_t>(data[copyLen - 1]) >> 63);
        for (size_t i = copyLen; i < num_words; ++i)
        {
            data[i] = sign_extension;
        }
    }

    // operator bool
    constexpr operator bool() const
    {
        return !std::all_of(data.begin(), data.end(), [](uint64_t w) { return w == 0; });
    }

    auto fill()
    {
        if constexpr (N % 64 == 0)
        {
            for (size_t i = 0; i < num_words; ++i)
            {
                data[i] = UniRand(gen);
            }
        }
        else
        {
            for (size_t i = 0; i < num_words - 1; ++i)
            {
                data[i] = UniRand(gen);
            }

            // generate a random number with the full range of - 2^(N%64-1) to 2^(N%64-1) - 1
            static std::uniform_int_distribution<uint64_t> dist(-(int64_t(1) << (N % 64 - 1)), (int64_t(1) << (N % 64 - 1)) - 1);
            data[num_words - 1] = dist(gen);
        }
        return *this;
    }

    constexpr auto toString() const
    {
        return big_integer_to_string(data);
    }

    constexpr double toDouble() const
    {

        // 确定符号
        const bool negative = (data[num_words - 1] >> 63) != 0;

        // 计算绝对值（使用位操作优化）
        std::array<uint64_t, num_words> mag = {};
        if (negative)
        {
            // 取反加一，使用位操作优化
            uint64_t carry = 1;
            for (std::size_t i = 0; i < num_words; ++i)
            {
                uint64_t inverted = ~data[i];
                mag[i] = inverted + carry;
                if (carry && mag[i] == 0)
                {
                    carry = 1;
                }
                else
                {
                    carry = (mag[i] < inverted) ? 1 : 0;
                }
            }
        }
        else
        {
            // 正数，直接复制
            mag = data;
        }

        // 找到最高非零字，以减少不必要的计算
        std::size_t highest_non_zero_word = num_words;
        while (highest_non_zero_word > 0 && mag[highest_non_zero_word - 1] == 0)
        {
            --highest_non_zero_word;
        }

        // 将绝对值转换为double（替代ldexp）
        double result = 0.0;
        constexpr double two_pow_64 = 18446744073709551616.0; // 2^64

        for (std::size_t i = highest_non_zero_word; i-- > 0;)
        {
            result = result * two_pow_64 + static_cast<double>(mag[i]);
        }

        // 应用符号
        if (negative)
        {
            result = -result;
        }

        return result;
    }

    constexpr double uToDouble() const //Unsigned conversion
    {
        // 计算绝对值（使用位操作优化）
        std::array<uint64_t, num_words> mag = {};
        mag = data;

        // 找到最高非零字，以减少不必要的计算
        std::size_t highest_non_zero_word = num_words;
        while (highest_non_zero_word > 0 && mag[highest_non_zero_word - 1] == 0)
        {
            --highest_non_zero_word;
        }

        int zbits = num_bits % 64;
        if(zbits) mag[highest_non_zero_word - 1] &= (1ll << zbits) - 1;


        // 将绝对值转换为double（替代ldexp）
        double result = 0.0;
        constexpr double two_pow_64 = 18446744073709551616.0; // 2^64

        for (std::size_t i = highest_non_zero_word; i-- > 0;)
        {
            result = result * two_pow_64 + static_cast<double>(mag[i]);
        }

        return result;
    }    

    constexpr auto toBinary() const
    {
        std::string result;
        for (int i = num_words - 1; i >= 0; --i)
        {
            result += std::bitset<64>(data[i]).to_string();
        }
        return result;
    }

    void display(std::string name = "") const
    {
        if (!name.empty())
        {
            std::cout << name << ":" << std::endl;
        }

        std::cout << "Binary:  ";
        for (int i = num_words - 1; i >= 0; --i)
        {
            std::cout << std::bitset<64>(data[i]) << " ";
        }
        std::cout << std::endl;

        std::cout << "Decimal: " << big_integer_to_string(data) << std::endl;
        std::cout << std::endl;
    }
};

// operator+

// special case for each input smaller than 64 bits and the result is also smaller than 64 bits
template <size_t N, size_t M>
    requires(N < 64 && M < 64)
constexpr auto operator+(const ArbiInt<N> lhs, const ArbiInt<M> rhs)
{
    ArbiInt<std::max(N, M) + 1> result; // the result may need one more bit
    result.data = lhs.data + rhs.data;
    return result;
}

// super special case for a 64-bit integer promoted to 65-bit integer
template <size_t N, size_t M>
    requires(N <= 64 && M <= 64) && (N == 64 || M == 64)
constexpr auto operator+(const ArbiInt<N> lhs, const ArbiInt<M> rhs)
{

    ArbiInt<65> result;

    // transform the 64-bit integer to 128-bit integer
    __int128_t sum = static_cast<__int128_t>(lhs.data) + static_cast<__int128_t>(rhs.data);

    // store the lower 64 bits
    result.data[0] = static_cast<uint64_t>(sum);
    result.data[1] = static_cast<uint64_t>(sum >> 64);

    return result;
}

// general case for a integer larger than 64 bits with a integer smaller than 64 bits
template <size_t N, size_t M>
    requires(N > 64 && M <= 64)
constexpr auto operator+(const ArbiInt<N> &lhs, const ArbiInt<M> rhs)
{
    constexpr size_t R = N + 1;
    ArbiInt<R> result;

    constexpr size_t res_words = ArbiInt<R>::num_words;
    constexpr size_t lhs_words = ArbiInt<N>::num_words;

    // Compute sign extensions using arithmetic right shift
    int64_t lhs_sign_extension = static_cast<int64_t>(lhs.data[lhs_words - 1]) >> 63;
    int64_t rhs_sign_extension = static_cast<int64_t>(rhs.data) >> 63;

    __uint128_t carry = 0;
    for (size_t i = 0; i < res_words; ++i)
    {
        uint64_t lhs_word = (i < lhs_words) ? lhs.data[i] : static_cast<uint64_t>(lhs_sign_extension);
        uint64_t rhs_word = (i == 0) ? rhs.data : static_cast<uint64_t>(rhs_sign_extension);

        __uint128_t sum = static_cast<__uint128_t>(lhs_word) + rhs_word + carry;
        result.data[i] = static_cast<uint64_t>(sum);
        carry = sum >> 64;
    }

    return result;
}

// general case for a integer smaller than 64 bits with a integer larger than 64 bits
template <size_t N, size_t M>
    requires(N <= 64 && M > 64)
constexpr auto operator+(const ArbiInt<N> lhs, const ArbiInt<M> &rhs)
{
    return rhs + lhs;
}

template <size_t N, size_t M>
    requires(N > 64 && M > 64)
constexpr auto operator+(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    // The result may need one more bit to store potential overflow
    constexpr size_t R = std::max(N, M) + 1;
    ArbiInt<R> result;

    constexpr size_t res_words = ArbiInt<R>::num_words;
    constexpr size_t lhs_words = ArbiInt<N>::num_words;
    constexpr size_t rhs_words = ArbiInt<M>::num_words;

    // Compute sign extensions using arithmetic right shift
    int64_t lhs_sign_extension = static_cast<int64_t>(lhs.data[lhs_words - 1]) >> 63;
    int64_t rhs_sign_extension = static_cast<int64_t>(rhs.data[rhs_words - 1]) >> 63;

    __uint128_t carry = 0;
    for (size_t i = 0; i < res_words; ++i)
    {
        uint64_t lhs_word = (i < lhs_words) ? lhs.data[i] : static_cast<uint64_t>(lhs_sign_extension);
        uint64_t rhs_word = (i < rhs_words) ? rhs.data[i] : static_cast<uint64_t>(rhs_sign_extension);

        __uint128_t sum = static_cast<__uint128_t>(lhs_word) + rhs_word + carry;

        result.data[i] = static_cast<uint64_t>(sum);

        carry = sum >> 64;
    }

    return result;
}

// operator-

// Special case for N < 64 and M < 64
template <size_t N, size_t M>
    requires(N < 64 && M < 64)
constexpr auto operator-(const ArbiInt<N> lhs, const ArbiInt<M> rhs)
{
    ArbiInt<std::max(N, M) + 1> result;
    result.data = lhs.data - rhs.data;
    return result;
}

// Special case when either N or M is exactly 64
template <size_t N, size_t M>
    requires(N <= 64 && M <= 64) && (N == 64 || M == 64)
constexpr auto operator-(const ArbiInt<N> lhs, const ArbiInt<M> rhs)
{
    ArbiInt<65> result;
    __int128_t diff = static_cast<__int128_t>(lhs.data) - static_cast<__int128_t>(rhs.data);
    result.data[0] = static_cast<uint64_t>(diff);
    result.data[1] = static_cast<uint64_t>(diff >> 64);
    return result;
}

// General case for N > 64 and M <= 64
template <size_t N, size_t M>
    requires(N > 64 && M <= 64)
constexpr auto operator-(const ArbiInt<N> &lhs, const ArbiInt<M> rhs)
{
    constexpr size_t R = N + 1;
    ArbiInt<R> result;

    constexpr size_t res_words = ArbiInt<R>::num_words;
    constexpr size_t lhs_words = ArbiInt<N>::num_words;

    // Precompute sign bit positions
    constexpr size_t lhs_sign_bit_pos = N - 1;
    constexpr size_t lhs_sign_word_index = lhs_sign_bit_pos / 64;
    constexpr size_t lhs_sign_bit_in_word = lhs_sign_bit_pos % 64;
    int64_t lhs_sign_extension = static_cast<int64_t>(lhs.data[lhs_sign_word_index]) >> lhs_sign_bit_in_word;

    __int128_t borrow = 0;
    for (size_t i = 0; i < res_words; ++i)
    {
        uint64_t lhs_word = (i < lhs_words) ? lhs.data[i] : static_cast<uint64_t>(lhs_sign_extension);
        uint64_t rhs_word = (i == 0) ? rhs.data : 0;

        __int128_t diff = static_cast<__int128_t>(lhs_word) - rhs_word - borrow;
        result.data[i] = static_cast<uint64_t>(diff);
        borrow = (diff < 0) ? 1 : 0;
    }

    return result;
}

// General case for N <= 64 and M > 64
template <size_t N, size_t M>
    requires(N <= 64 && M > 64)
constexpr auto operator-(const ArbiInt<N> lhs, const ArbiInt<M> &rhs)
{
    constexpr size_t R = M + 1;
    ArbiInt<R> lhs_promoted = lhs; // Promote lhs to match the size of rhs
    return lhs_promoted - rhs;
}

// General case for N > 64 and M > 64
template <size_t N, size_t M>
    requires(N > 64 && M > 64)
constexpr auto operator-(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    constexpr size_t R = std::max(N, M) + 1;
    ArbiInt<R> result;

    constexpr size_t res_words = ArbiInt<R>::num_words;
    constexpr size_t lhs_words = ArbiInt<N>::num_words;
    constexpr size_t rhs_words = ArbiInt<M>::num_words;

    // Precompute sign bit positions
    constexpr size_t lhs_sign_bit_pos = N - 1;
    constexpr size_t lhs_sign_word_index = lhs_sign_bit_pos / 64;
    constexpr size_t lhs_sign_bit_in_word = lhs_sign_bit_pos % 64;
    constexpr size_t rhs_sign_bit_pos = M - 1;
    constexpr size_t rhs_sign_word_index = rhs_sign_bit_pos / 64;
    constexpr size_t rhs_sign_bit_in_word = rhs_sign_bit_pos % 64;
    int64_t lhs_sign_extension = static_cast<int64_t>(lhs.data[lhs_sign_word_index]) >> lhs_sign_bit_in_word;
    int64_t rhs_sign_extension = static_cast<int64_t>(rhs.data[rhs_sign_word_index]) >> rhs_sign_bit_in_word;

    __int128_t borrow = 0;
    for (size_t i = 0; i < res_words; ++i)
    {
        uint64_t lhs_word = (i < lhs_words) ? lhs.data[i] : static_cast<uint64_t>(lhs_sign_extension);
        uint64_t rhs_word = (i < rhs_words) ? rhs.data[i] : static_cast<uint64_t>(rhs_sign_extension);

        __int128_t diff = static_cast<__int128_t>(lhs_word) - rhs_word - borrow;
        result.data[i] = static_cast<uint64_t>(diff);
        borrow = (diff < 0) ? 1 : 0;
    }

    return result;
}

// Unary minus operator for ArbiInt<N>
template <size_t N>
    requires(N < 64)
constexpr auto operator-(const ArbiInt<N> &x)
{
    ArbiInt<N + 1> result;
    result.data = -static_cast<ArbiInt<N + 1>::data_t>(x.data);
    return result;
}

template <size_t N>
    requires(N >= 64)
constexpr auto operator-(const ArbiInt<N> &x)
{
    ArbiInt<N + 1> result;

    uint64_t carry = 1;
    for (size_t i = 0; i < ArbiInt<N>::num_words; ++i)
    {
        uint64_t temp = ~x.data[i] + carry;
        result.data[i] = temp;
        carry = (temp < carry);
    }

    if constexpr (N % 64 == 0)
    {
        result.data[ArbiInt<N>::num_words] = carry;
    }

    return result;
}

// template <size_t N>
//     requires(N <= 64)
// // Negation without promotion, won't change the size of the integer and may cause overflow
// constexpr auto negWithoutPromotion(const ArbiInt<N> &x)
// {
//     ArbiInt<N> result;
//     result.data = -x.data;
//     return result;
// }

// template <size_t N>
//     requires(N > 64)
// // Negation without promotion, won't change the size of the integer and may cause overflow
// constexpr auto negWithoutPromotion(const ArbiInt<N> &x)
// {
//     ArbiInt<N> result;

//     uint64_t carry = 1;
//     for (size_t i = 0; i < ArbiInt<N>::num_words; ++i)
//     {
//         uint64_t temp = ~x.data[i] + carry;
//         result.data[i] = temp;
//         carry = (temp < carry);
//     }

//     return result;
// }

// operator*

template <size_t N, size_t M>
    requires(M + N <= 64)
constexpr auto operator*(const ArbiInt<N> lhs, const ArbiInt<M> rhs)
{
    ArbiInt<N + M> result;
    result.data = lhs.data * rhs.data;
    return result;
}

template <size_t N, size_t M>
    requires(M + N > 64 && (N <= 64 && M <= 64))
constexpr auto operator*(const ArbiInt<N> lhs, const ArbiInt<M> rhs)
{
    ArbiInt<N + M> result;

    __int128_t product = static_cast<__int128_t>(lhs.data) * static_cast<__int128_t>(rhs.data);

    result.data[0] = static_cast<uint64_t>(product);
    result.data[1] = static_cast<uint64_t>(product >> 64);

    return result;
}

template <size_t N, size_t M>
    requires(N <= 64 && M > 64)
constexpr auto operator*(const ArbiInt<N> lhs, const ArbiInt<M> &rhs)
{
    return rhs * lhs;
}

template <size_t N, size_t M>
    requires(N > 64 && M <= 64)
constexpr auto operator*(const ArbiInt<N> &lhs, const ArbiInt<M> rhs)
{
    constexpr size_t R = N + M;
    using ResultType = ArbiInt<R>;
    ResultType result;
    result.data.fill(0);

    // Sign extraction
    bool lhs_negative = (lhs.data[lhs.num_words - 1] >> ((N - 1) % 64));
    bool rhs_negative = (rhs.data >> 63) & 1;
    bool result_negative = lhs_negative ^ rhs_negative;

    // Manage negativity upfront for rhs
    uint64_t rhs_abs = rhs_negative ? ~rhs.data + 1 : rhs.data;

    __uint128_t carry = 0;
    for (size_t i = 0; i < lhs.num_words; ++i)
    {
        // Adjust lhs value based on its sign
        uint64_t lhs_val = lhs.data[i];
        if (lhs_negative)
            lhs_val = ~lhs_val + (i == 0); // Apply two's complement logic depending on the index

        __uint128_t prod = (__uint128_t)lhs_val * rhs_abs + carry;
        result.data[i] = static_cast<uint64_t>(prod);
        carry = prod >> 64; // Handle the carry for the next word
    }
    // Handle the final carry if there is room in the result space
    if (lhs.num_words < result.num_words)
    {
        result.data[lhs.num_words] = static_cast<uint64_t>(carry);
    }

    // Convert result to two's complement if the resulting sign is negative
    if (result_negative)
    {
        uint64_t carry = 1;
        for (size_t i = 0; i < result.num_words; ++i)
        {
            result.data[i] = ~result.data[i] + carry;
            carry = result.data[i] < carry; // Update carry for the next loop if there was an overflow
        }
    }

    return result;
}

template <size_t N, size_t M>
    requires(N > 64 && M > 64)
constexpr auto operator*(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    constexpr size_t R = N + M;
    using ResultType = ArbiInt<R>;
    ResultType result;

    auto &lhs_data = lhs.data;
    auto &rhs_data = rhs.data;

    // 符号处理的优化：只计算一次最终符号，只在最后需要时执行补码
    bool lhs_negative = (lhs_data[lhs.num_words - 1] >> ((N - 1) % 64));
    bool rhs_negative = (rhs_data[rhs.num_words - 1] >> ((M - 1) % 64));
    bool result_negative = lhs_negative ^ rhs_negative;

    // Direct multiplication of absolute values if not considering two's complement
    // 假设数据已经为正值
    for (size_t i = 0; i < lhs.num_words; ++i)
    {
        uint64_t lhs_val = lhs_data[i];
        if (lhs_negative)
            lhs_val = ~lhs_val + (i == 0);
        for (size_t j = 0; j < rhs.num_words; ++j)
        {
            uint64_t rhs_val = rhs_data[j];
            if (rhs_negative)
                rhs_val = ~rhs_val + (j == 0);
            __uint128_t product = __uint128_t(lhs_val) * rhs_val;
            size_t k = i + j;
            if (k < result.num_words)
            {
                __uint128_t sum = product + result.data[k];
                result.data[k] = sum; // Store low bits
                if (k + 1 < result.num_words)
                {
                    result.data[k + 1] += sum >> 64; // Carry to the next
                }
            }
        }
    }

    // 仅在结果为负时转换
    if (result_negative)
    {
        uint64_t carry = 1;
        for (size_t i = 0; i < result.num_words; ++i)
        {
            result.data[i] = ~result.data[i] + carry;
            carry = result.data[i] < carry;
        }
    }

    return result;
}

// operator /
template <size_t N, size_t M>
    requires(N <= 64 && M <= 64)
constexpr auto operator/(const ArbiInt<N> lhs, const ArbiInt<M> rhs)
{
    ArbiInt<64> result;
    result.data = lhs.data / rhs.data;
    return result;
}

// 辅助函数：比较两个大数的绝对值大小
inline int compareAbs(const std::string &a, const std::string &b)
{
    if (a.size() != b.size())
        return a.size() > b.size() ? 1 : -1;
    for (size_t i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
            return a[i] > b[i] ? 1 : -1;
    }
    return 0;
}

// 辅助函数：大数减法
inline std::string subtract(const std::string &a, const std::string &b)
{
    std::string result;
    int carry = 0;
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;

    while (i >= 0 || j >= 0 || carry)
    {
        int digitA = i >= 0 ? a[i] - '0' : 0;
        int digitB = j >= 0 ? b[j] - '0' : 0;
        int diff = digitA - digitB - carry;

        if (diff < 0)
        {
            diff += 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        result = char(diff + '0') + result;
        i--;
        j--;
    }

    // 移除前导零
    auto start = result.find_first_not_of('0');
    if (start != std::string::npos)
    {
        return result.substr(start);
    }
    else
    {
        return "0";
    }
}

// 执行大数除法
inline std::string divideString(const std::string &dividend, const std::string &divisor)
{
    if (divisor == "0")
    {
        throw std::runtime_error("Division by zero.");
    }

    // 处理符号
    bool negResult = (dividend[0] == '-') ^ (divisor[0] == '-');
    std::string absDividend = dividend[0] == '-' ? dividend.substr(1) : dividend;
    std::string absDivisor = divisor[0] == '-' ? divisor.substr(1) : divisor;

    if (compareAbs(absDividend, absDivisor) < 0)
    {
        return "0"; // 被除数比除数小，商为0
    }

    std::string result;
    std::string current = "";
    for (char digit : absDividend)
    {
        current += digit; // 逐个数字处理
        current.erase(0, current.find_first_not_of('0'));
        if (current.empty())
            current = "0";

        int count = 0;
        while (compareAbs(current, absDivisor) >= 0)
        {
            current = subtract(current, absDivisor);
            count++;
        }
        result += char(count + '0');
    }

    result.erase(0, result.find_first_not_of('0')); // 移除结果的前导零
    if (result.empty())
        result = "0";

    return negResult ? '-' + result : result;
}

template <size_t N, size_t M>
    requires(N > 64 || M > 64)
[[deprecated("Division for large integers is currently implemented using string conversion. It is not efficient and may be slow for large numbers.")]]
auto operator/(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    auto dividend = lhs.toString();
    auto divisor = rhs.toString();

    std::string result = divideString(dividend, divisor);

    return ArbiInt<N - M>(result);
}

// operator <<
// specially, the static shift left is designed for no overflow guaranteed
template <int shift, size_t N>
    requires(shift > 0) && (N + shift <= 64)
constexpr auto staticShiftLeft(const ArbiInt<N> &x)
{
    ArbiInt<N + shift> result;

    result.data = static_cast<typename ArbiInt<N + shift>::data_t>(x.data) << shift;

    return result;
}

template <int shift, size_t N>
    requires(shift > 0) && (N + shift > 64) && (N <= 64)
constexpr auto staticShiftLeft(const ArbiInt<N> &x)
{
    ArbiInt<N + shift> result;

    // check if the shifted bits will occupy 2 uint64_t
    if ((N + shift) / 64 == shift / 64)
    {
        result.data[shift / 64] = x.data << (shift % 64);
    }
    else
    {
        __uint128_t temp = static_cast<__uint128_t>(x.data) << (shift % 64);
        result.data[shift / 64] = static_cast<uint64_t>(temp);
        result.data[shift / 64 + 1] = static_cast<uint64_t>(temp >> 64);
    }

    return result;
}

template <int shift, size_t N>
    requires(shift > 0) && (N > 64) && (shift % 64 == 0)
constexpr auto staticShiftLeft(const ArbiInt<N> &x)
{
    ArbiInt<N + shift> result;

    // directly copy
    // std::memcpy(result.data.data() + shift / 64, x.data.data(), sizeof(uint64_t) * ArbiInt<N>::num_words);
    std::copy(x.data.begin(), x.data.end(), result.data.begin() + shift / 64);

    return result;
}
template <int shift, size_t N>
    requires(shift > 0) && (N > 64) && (shift % 64 != 0)
constexpr auto staticShiftLeft(const ArbiInt<N> &x)
{
    constexpr size_t num_words_in = ArbiInt<N>::num_words;
    constexpr size_t num_words_out = ArbiInt<N + shift>::num_words;
    constexpr size_t word_shift = shift / 64;
    constexpr size_t bit_shift = shift % 64;

    ArbiInt<N + shift> result;

    // 判断x是否为负数
    uint64_t sign_bit_mask = uint64_t(1) << 63;
    bool x_is_negative = x.data[num_words_in - 1] & sign_bit_mask;
    uint64_t sign_extension_word = x_is_negative ? ~uint64_t(0) : uint64_t(0);

    // 扩展数据以包含符号扩展位
    std::array<uint64_t, num_words_in + 1> extended_data;
    for (size_t i = 0; i < num_words_in; ++i)
    {
        extended_data[i] = x.data[i];
    }
    extended_data[num_words_in] = sign_extension_word;

    // 初始化结果数据为0
    for (size_t i = 0; i < num_words_out; ++i)
    {
        result.data[i] = 0;
    }

    // 执行左移操作
    for (size_t i = 0; i <= num_words_in; ++i)
    {
        uint64_t current = extended_data[i];
        size_t new_index = i + word_shift;

        if (new_index < num_words_out)
        {
            result.data[new_index] |= current << bit_shift;
        }
        if (bit_shift != 0 && new_index + 1 < num_words_out)
        {
            result.data[new_index + 1] |= current >> (64 - bit_shift);
        }
    }

    // 已经通过符号扩展处理高位数据，无需额外处理

    return result;
}

template <int shift, size_t N>
    requires(shift < 0)
constexpr auto staticShiftLeft(const ArbiInt<N> &x)
{
    return staticShiftRight<-shift>(x);
}

template <int shift, size_t N>
    requires(shift == 0)
constexpr auto staticShiftLeft(const ArbiInt<N> &x)
{
    return x;
}

// operator >>

template <int shift, size_t N>
    requires(shift > 0) && (N <= 64)
constexpr auto staticShiftRight(const ArbiInt<N> &x)
{
    static_assert(N >= shift, "Right shift out of range");

    ArbiInt<N - shift> result;

    result.data = x.data >> shift;

    return result;
}

template <int shift, size_t N>
    requires(shift > 0) && (N > 64) && (N - shift <= 64)
constexpr auto staticShiftRight(const ArbiInt<N> &x)
{
    // get the highest 128 bits and shift right
    ArbiInt<N - shift> result;

    constexpr size_t num_words = ArbiInt<N>::num_words;

    __uint128_t high = static_cast<__uint128_t>(x.data[num_words - 1]) << 64;
    __uint128_t low = static_cast<__uint128_t>(x.data[num_words - 2]);

    __uint128_t temp = high | low;

    constexpr size_t actual_shift = shift - 64 * (num_words - 2);

    result.data = static_cast<__int128_t>(temp) >> actual_shift;

    return result;
}

template <int shift, size_t N>
    requires(shift > 0) && (N > 64) && (N - shift > 64) && (shift % 64 == 0)
constexpr auto staticShiftRight(const ArbiInt<N> &x)
{
    ArbiInt<N - shift> result;
    std::copy(x.data.begin() + shift / 64, x.data.end(), result.data.begin());
    return result;
}

template <int shift, size_t N>
    requires(shift > 0) && (N > 64) && (N - shift > 64) && (shift % 64 != 0)
constexpr auto staticShiftRight(const ArbiInt<N> &x)
{
    constexpr size_t shift_words = shift / 64; // Number of complete 64-bit blocks to shift right
    constexpr size_t shift_bits = shift % 64;  // Remaining bits to shift right
    constexpr size_t num_input_words = ArbiInt<N>::num_words;
    constexpr size_t num_output_words = ArbiInt<N - shift>::num_words;
    ArbiInt<N - shift> result;

    // Determine the sign extension word based on the sign of x
    bool is_negative = static_cast<int64_t>(x.data[num_input_words - 1]) < 0;
    uint64_t sign_extension_word = is_negative ? ~uint64_t(0) : uint64_t(0);

    for (size_t i = 0; i < num_output_words; ++i)
    {
        // Get the source words with proper sign extension
        uint64_t low_word = 0;
        uint64_t high_word = 0;

        size_t low_index = i + shift_words;
        size_t high_index = i + shift_words + 1;

        // Retrieve low_word, or sign extension if out of bounds
        if (low_index < num_input_words)
            low_word = x.data[low_index];
        else
            low_word = sign_extension_word;

        // Retrieve high_word, or sign extension if out of bounds
        if (high_index < num_input_words)
            high_word = x.data[high_index];
        else
            high_word = sign_extension_word;

        // Perform the shift and combine the bits
        result.data[i] = (low_word >> shift_bits) | (high_word << (64 - shift_bits));
    }

    return result;
}

template <int shift, size_t N>
    requires(shift < 0)
constexpr auto staticShiftRight(const ArbiInt<N> &x)
{
    return staticShiftLeft<-shift>(x);
}

template <int shift, size_t N>
    requires(shift == 0)
constexpr auto staticShiftRight(const ArbiInt<N> &x)
{
    return x;
}

template <size_t N>
auto dynamicShiftLeft(const ArbiInt<N> &x, int shift) //Size remain the same, shifting doesn't change size.
{
    ArbiInt<N> ret;
    if constexpr (N <= 64) ret.data = x.data << shift;
    else
    {
        for(int i = N/64 ; i >= 0 ; i--)
        {
            if((shift & 63) == 0) ret.data[i] = i >= shift/64 ? x.data[i - shift/64] : 0;
            else ret.data[i] = ((i - shift/64 >= 0 ? x.data[i - shift/64] : 0) << (shift & 63)) | ((i - shift/64 - 1 >= 0 ? x.data[i - 1 - shift/64] : 0) >> (64 - (shift & 63)));
        }
    }
    return ret;
}

template <size_t N>
auto dynamicShiftRight(const ArbiInt<N> &x, int shift) //Size remain the same, shifting doesn't change size.
{
    ArbiInt<N> ret;
    if constexpr (N <= 64) ret.data = x.data >> shift;
    else
    {
        for(int i = 0 ; i <= N/64 ; i++)
        {
            if((shift & 63) == 0) ret.data[i] = i + shift/64 <= N/64 ? x.data[i + shift/64] : 0;
            else ret.data[i] = ((i + shift/64 <= N/64 ? x.data[i + shift/64] : 0) >> (shift & 63)) | ((i + shift/64 + 1 <= N/64 ? x.data[i + 1 + shift/64] : 0) << (64 - (shift & 63)));
        }
    }
    return ret;
}

template <size_t N, size_t M>
    requires(N <= 64 && M <= 64)
constexpr bool operator==(const ArbiInt<N> lhs, const ArbiInt<M> rhs)
{
    return lhs.data == rhs.data;
}

template <size_t N, size_t M>
    requires(N > 64 && M <= 64)
constexpr bool operator==(const ArbiInt<N> &lhs, const ArbiInt<M> rhs)
{
    return static_cast<int64_t>(lhs.data[0]) == static_cast<int64_t>(rhs.data);
}

template <size_t N, size_t M>
    requires(N <= 64 && M > 64)
constexpr bool operator==(const ArbiInt<N> lhs, const ArbiInt<M> &rhs)
{
    return static_cast<int64_t>(lhs.data) == static_cast<int64_t>(rhs.data[0]);
}

template <size_t N, size_t M>
    requires(N > 64 && M > 64)
constexpr bool operator==(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    constexpr size_t num_words_N = ArbiInt<N>::num_words;
    constexpr size_t num_words_M = ArbiInt<M>::num_words;

    constexpr size_t min_words = (num_words_N < num_words_M) ? num_words_N : num_words_M;

    // check the uint64_t within the range of min_words
    for (size_t i = 0; i < min_words; ++i)
    {
        if (lhs.data[i] != rhs.data[i])
        {
            return false;
        }
    }
    return true;
}

template <size_t N, size_t M>
    requires(N <= 64 && M <= 64)
constexpr bool operator!=(const ArbiInt<N> lhs, const ArbiInt<M> rhs)
{
    return !(lhs == rhs);
}

template <size_t N, size_t M>
    requires(N > 64 && M <= 64)
constexpr bool operator!=(const ArbiInt<N> &lhs, const ArbiInt<M> rhs)
{
    return !(lhs == rhs);
}

template <size_t N, size_t M>
    requires(N <= 64 && M > 64)
constexpr bool operator!=(const ArbiInt<N> lhs, const ArbiInt<M> &rhs)
{
    return !(lhs == rhs);
}

template <size_t N, size_t M>
    requires(N > 64 && M > 64)
constexpr bool operator!=(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    return !(lhs == rhs);
}

template <size_t N, size_t M>
    requires(N <= 64 && M <= 64)
constexpr auto operator<=>(const ArbiInt<N> lhs, const ArbiInt<M> rhs)
{
    return lhs.data <=> rhs.data;
}

// For lhs > 64 bits and rhs <= 64 bits
template <size_t N, size_t M>
    requires(N > 64 && M <= 64)
constexpr auto operator<=>(const ArbiInt<N> &lhs, const ArbiInt<M> rhs)
{
    int64_t rhs_ext = (rhs.data < 0) ? -1LL : 0LL; // 符号扩展rhs的值
    for (int i = ArbiInt<N>::num_words - 1; i > 0; --i)
    {
        if (static_cast<int64_t>(lhs.data[i]) != rhs_ext)
        {
            return static_cast<int64_t>(lhs.data[i]) <=> rhs_ext;
        }
    }
    return static_cast<int64_t>(lhs.data[0]) <=> static_cast<int64_t>(rhs.data);
}

// For lhs <= 64 bits and rhs > 64 bits
template <size_t N, size_t M>
    requires(N <= 64 && M > 64)
constexpr auto operator<=>(const ArbiInt<N> lhs, const ArbiInt<M> &rhs)
{
    int64_t lhs_ext = (lhs.data < 0) ? -1LL : 0LL; // 符号扩展lhs的值
    for (int i = ArbiInt<M>::num_words - 1; i > 0; --i)
    {
        if (static_cast<int64_t>(rhs.data[i]) != lhs_ext)
        {
            return lhs_ext <=> static_cast<int64_t>(rhs.data[i]);
        }
    }
    return static_cast<int64_t>(lhs.data) <=> static_cast<int64_t>(rhs.data[0]);
}

// For both lhs and rhs > 64 bits
template <size_t N, size_t M>
    requires(N > 64 && M > 64)
constexpr auto operator<=>(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    int64_t lhs_ext = (lhs.data[ArbiInt<N>::num_words - 1] >> 63) ? -1LL : 0LL;
    int64_t rhs_ext = (rhs.data[ArbiInt<M>::num_words - 1] >> 63) ? -1LL : 0LL;
    int max_words = std::max(ArbiInt<N>::num_words, ArbiInt<M>::num_words);
    for (int i = max_words - 1; i >= 0; --i)
    {
        int64_t lhs_word = (i < ArbiInt<N>::num_words) ? lhs.data[i] : lhs_ext;
        int64_t rhs_word = (i < ArbiInt<M>::num_words) ? rhs.data[i] : rhs_ext;
        if (lhs_word != rhs_word)
            return lhs_word <=> rhs_word;
    }
    return lhs_ext <=> rhs_ext;
}

// operator ^
template <size_t N, size_t M>
    requires(N <= 64 && M <= 64)
constexpr auto operator^(const ArbiInt<N> lhs, const ArbiInt<M> rhs)
{
    ArbiInt<std::max(N, M)> result;
    result.data = lhs.data ^ rhs.data;
    return result;
}

template <size_t N, size_t M>
    requires(N > 64 && M <= 64)
constexpr auto operator^(const ArbiInt<N> &lhs, const ArbiInt<M> rhs)
{
    ArbiInt<N> result = lhs;
    result.data[0] ^= static_cast<uint64_t>(rhs.data);
    return result;
}

template <size_t N, size_t M>
    requires(N <= 64 && M > 64)
constexpr auto operator^(const ArbiInt<N> lhs, const ArbiInt<M> &rhs)
{
    ArbiInt<M> result = rhs;
    result.data[0] ^= static_cast<uint64_t>(lhs.data);
    return result;
}

template <size_t N, size_t M>
    requires(N > 64 && M > 64)
constexpr auto operator^(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    ArbiInt<std::max(N, M)> result = M > N ? rhs : lhs;
    for (size_t i = 0; i < std::min(ArbiInt<N>::num_words, ArbiInt<M>::num_words); ++i)
    {
        result.data[i] = lhs.data[i] ^ rhs.data[i];
    }
    return result;
}

// operator &

template <size_t N, size_t M>
    requires(N <= 64 && M <= 64)
constexpr auto operator&(const ArbiInt<N> lhs, const ArbiInt<M> rhs)
{
    ArbiInt<std::max(N, M)> result;
    result.data = lhs.data & rhs.data;
    return result;
}

template <size_t N, size_t M>
    requires(N > 64 && M <= 64)
constexpr auto operator&(const ArbiInt<N> &lhs, const ArbiInt<M> rhs)
{
    ArbiInt<N> result;
    result.data[0] = lhs.data[0] & static_cast<uint64_t>(rhs.data);
    return result;
}

template <size_t N, size_t M>
    requires(N <= 64 && M > 64)
constexpr auto operator&(const ArbiInt<N> lhs, const ArbiInt<M> &rhs)
{
    ArbiInt<M> result;
    result.data[0] = static_cast<uint64_t>(lhs.data) & rhs.data[0];
    return result;
}

template <size_t N, size_t M>
    requires(N > 64 && M > 64)
constexpr auto operator&(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    ArbiInt<std::max(N, M)> result;
    for (size_t i = 0; i < std::min(ArbiInt<N>::num_words, ArbiInt<M>::num_words); ++i)
    {
        result.data[i] = lhs.data[i] & rhs.data[i];
    }
    return result;
}

// operator |

template <size_t N, size_t M>
    requires(N <= 64 && M <= 64)
constexpr auto operator|(const ArbiInt<N> lhs, const ArbiInt<M> rhs)
{
    ArbiInt<std::max(N, M)> result;
    result.data = lhs.data | rhs.data;
    return result;
}

template <size_t N, size_t M>
    requires(N > 64 && M <= 64)
constexpr auto operator|(const ArbiInt<N> &lhs, const ArbiInt<M> rhs)
{
    ArbiInt<N> result = lhs;
    result.data[0] |= static_cast<uint64_t>(rhs.data);
    return result;
}

template <size_t N, size_t M>
    requires(N <= 64 && M > 64)
constexpr auto operator|(const ArbiInt<N> lhs, const ArbiInt<M> &rhs)
{
    ArbiInt<M> result = rhs;
    result.data[0] |= static_cast<uint64_t>(lhs.data);
    return result;
}

template <size_t N, size_t M>
    requires(N > 64 && M > 64)
constexpr auto operator|(const ArbiInt<N> &lhs, const ArbiInt<M> &rhs)
{
    ArbiInt<std::max(N, M)> result = M > N ? rhs : lhs;
    for (size_t i = 0; i < std::min(ArbiInt<N>::num_words, ArbiInt<M>::num_words); ++i)
    {
        result.data[i] = lhs.data[i] | rhs.data[i];
    }
    return result;
}

// operator ~
template <size_t N>
    requires(N <= 64)
constexpr auto operator~(const ArbiInt<N> x)
{
    ArbiInt<N> result;
    result.data = ~x.data;
    return result;
}

template <size_t N>
    requires(N > 64)
constexpr auto operator~(const ArbiInt<N> &x)
{
    ArbiInt<N> result;
    for (size_t i = 0; i < ArbiInt<N>::num_words; ++i)
    {
        result.data[i] = ~x.data[i];
    }
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

struct FLT
{
    struct DEFAULTFLT{inline static constexpr int value = 7;};
};
// clang-format on

template <int fromFrac, int toFrac, typename QuMode>
struct fracConvert;

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

            auto Xh = staticShiftRight<fromFrac - toFrac>(val);

            constexpr auto mask = ArbiInt<fromFrac - toFrac>::allOnes();

            auto Xl = val & mask;

            constexpr auto T = staticShiftLeft<fromFrac - toFrac - 1>(ArbiInt<1>::allOnes());

            bool flag = Xl >= T;

            auto oneOrZero = ArbiInt<1>(flag);

            return Xh + oneOrZero;
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

            auto Xh = staticShiftRight<fromFrac - toFrac>(val);

            constexpr auto mask = ArbiInt<fromFrac - toFrac>::allOnes();

            auto Xl = val & mask;

            constexpr auto T = staticShiftLeft<fromFrac - toFrac - 1>(ArbiInt<1>::allOnes());

            bool flag = Xl > T;

            auto oneOrZero = ArbiInt<1>(flag);

            return Xh + oneOrZero;
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

            auto Xh = staticShiftRight<fromFrac - toFrac>(val);

            constexpr auto mask = ArbiInt<fromFrac - toFrac>::allOnes();

            auto Xl = val & mask;

            constexpr auto T = staticShiftLeft<fromFrac - toFrac - 1>(ArbiInt<1>::allOnes());

            bool flag = Xl > T || (Xl == T && (val.isNegative()));

            auto oneOrZero = ArbiInt<1>(flag);

            return Xh + oneOrZero;
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

            auto Xh = staticShiftRight<fromFrac - toFrac>(val);

            constexpr auto mask = ArbiInt<fromFrac - toFrac>::allOnes();

            auto Xl = val & mask;

            constexpr auto T = staticShiftLeft<fromFrac - toFrac - 1>(ArbiInt<1>::allOnes());

            bool flag = Xl > T || (Xl == T && (val.isPositive()));

            auto oneOrZero = ArbiInt<1>(flag);

            return Xh + oneOrZero;
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
            constexpr auto mask = ArbiInt<fromFrac - toFrac>::allZeros();
            auto floor_raw = val & mask;

            auto ceil = floor_raw + staticShiftLeft<fromFrac - toFrac>(ArbiInt<1>::allOnes());
            ArbiInt<N + 1> floor = floor_raw;
            if (floor + ceil == staticShiftLeft<1>(val))
            {
                constexpr auto mask2 = staticShiftLeft<fromFrac - toFrac>(ArbiInt<1>::allOnes());

                if (floor & mask2)
                {
                    return staticShiftRight<fromFrac - toFrac>(ceil);
                }
                else
                {
                    return staticShiftRight<fromFrac - toFrac>(floor);
                }
            }

            return (val - floor) < (ceil - val) ? staticShiftRight<fromFrac - toFrac>(floor) : staticShiftRight<fromFrac - toFrac>(ceil);
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
        if constexpr (fromFrac <= toFrac)
        {
            return staticShiftLeft<toFrac - fromFrac>(val);
        }
        else
        {
            constexpr auto one = staticShiftLeft<fromFrac - toFrac>(ArbiInt<1>::allOnes());

            if (val.isNegative())
            {
                return staticShiftRight<fromFrac - toFrac>(val + one);
            }
            else
            {
                ArbiInt<N + 1> temp = val;
                return staticShiftRight<fromFrac - toFrac>(temp);
            }
        }
    }
};

template <int toBits, typename QuMode>
struct fracConvert_FixedToFloatval;

template <int toBits>
struct fracConvert_FixedToFloatval<toBits, QuMode<FLT::DEFAULTFLT>>
{
    template <size_t N>
    inline static constexpr auto convert(ArbiInt<N> val)
    {
        ArbiInt<1200> buf; //might overflow???? 1200 not enough?
        if(val.isNegative()) val = -val;
        if constexpr (N <= 64)
        {
            int pos = N - 1;
            while (((val.data >> pos) & 1) == 0 && pos >= 0) pos--; // Optimization available
            if (pos > 0)
            {
                //expData = pos + bias - val.fracB; //Possible overflow
                buf = val;
                if (pos >= toBits) buf = dynamicShiftRight(buf , pos - toBits);
                else buf = dynamicShiftLeft(buf , toBits - pos); 
            }
            else buf = 0;
        }
        else
        {
            int pos1 = N / 64, pos2 = 63;
            while (val.data[pos1] == 0 && pos1 >= 0) pos1--;
            if (pos1 >= 0)
            {
                while ((val.data[pos1] >> pos2 & 1) == 0 && pos2 >= 0) pos2--;
                //expData = 64 * pos1 + pos2 + bias - val.fracB; //Possible overflow
                buf = val;
                if (64 * pos1 + pos2 >= toBits) buf = dynamicShiftRight(buf , 64 * pos1 + pos2 - toBits);
                else buf = dynamicShiftLeft(buf , toBits - (64 * pos1 + pos2));
            }
            else buf = 0;                
        }
        return buf;
    }
};

template <int fromFrac, int toExpBits, typename QuMode>
struct fracConvert_FixedToFloatexp;

template <int fromFrac, int toExpBits>
struct fracConvert_FixedToFloatexp<fromFrac, toExpBits,QuMode<FLT::DEFAULTFLT>>
{
    static constexpr ArbiInt<toExpBits> bias = staticShiftLeft<toExpBits - 1>(ArbiInt<1>(1));

    template <size_t N>
    inline static constexpr auto convert(ArbiInt<N> val)
    {
        //bias.display();
        ArbiInt<1200> buf;
        if(val.isNegative()) val = -val;
        if constexpr (N <= 64)
        {
            int pos = N - 1;
            while (((val.data >> pos) & 1) == 0 && pos >= 0) pos--; // Optimization available
            if (pos > 0) buf = bias + ArbiInt<64>(pos - fromFrac); //Possible overflow
            else buf = 0;
        }
        else
        {
            int pos1 = N / 64, pos2 = 63;
            while (val.data[pos1] == 0 && pos1 >= 0) pos1--;
            while ((val.data[pos1] >> pos2 & 1) == 0 && pos2 >= 0) pos2--;
            if (pos1 >= 0) buf = bias + ArbiInt<64>(64 * pos1 + pos2 - fromFrac); //Possible overflow
            else buf = 0;
            //buf.display();
        }
        return buf;
    }
};

template <int fromBits, int toBits>
struct fracConvert_FloatToFloatval;

template <int fromBits, int toBits>
struct fracConvert_FloatToFloatval
{
    template <size_t N>
    inline static constexpr auto convert(ArbiInt<N> val)
    {
        ArbiInt<1200> buf;
        if constexpr(fromBits <= toBits) buf = staticShiftLeft<toBits - fromBits>(val);
        else buf = staticShiftRight<fromBits - toBits>(val);
        return buf;
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

template <int toInt, int toFrac, bool toIsSigned>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<SAT::TCPL>>
{
    template <size_t N>
    inline static constexpr auto convert(ArbiInt<N> val)
    {
        constexpr auto floor = ArbiInt<N>(ArbiInt<toInt + toFrac>::allOnes());

        constexpr auto ceil = toIsSigned ? ArbiInt<N>(ArbiInt<toInt + toFrac>::allZeros()) : ArbiInt<N>(0);

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
            return val;
        }
    }
};

template <int toInt, int toFrac, bool toIsSigned>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<SAT::ZERO>>
{
    template <size_t N>
    inline static constexpr auto convert(ArbiInt<N> val)
    {
        constexpr auto floor = ArbiInt<toInt + toFrac>::allOnes();
        constexpr auto ceil = toIsSigned ? ArbiInt<toInt + toFrac>::allZeros() : ArbiInt<N>(0);

        constexpr auto zeroRes = ArbiInt<N>(0);

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
            return val;
        }
    }
};

template <int toInt, int toFrac, bool toIsSigned>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<SAT::SMGN>>
{
    template <size_t N>
    inline static constexpr auto convert(ArbiInt<N> val)
    {
        constexpr auto floor = ArbiInt<N>(ArbiInt<toInt + toFrac>::allOnes());
        constexpr auto ceil = toIsSigned ? ArbiInt<N>(ArbiInt<toInt + toFrac>::allZeros() + ArbiInt<1>(1)) : ArbiInt<N>(0);

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
            return val;
        }
    }
};

template <int toInt, int toFrac, bool toIsSigned>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<WRP::TCPL>>
{

    inline static constexpr auto convert(auto val)
    {
        if constexpr (toIsSigned)
        {
            constexpr auto mask = ArbiInt<toInt + toFrac + 1>::allOnes();

            auto maskedVal = val & mask;

            if (staticShiftRight<toFrac + toInt>(maskedVal))
            {
                constexpr auto mask2 = ~mask;

                return maskedVal | mask2;
            }
            else
            {
                return maskedVal;
            }
        }
        else
        {
            constexpr auto mask = ArbiInt<toInt + toFrac>::allOnes();

            return val & mask;
        }
    }
};

template <int toInt, int toFrac, bool toIsSigned, auto N>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<WRP::TCPL_SAT<N>>>
{
    inline static constexpr auto convert(auto val)
    {
        // not implemented
        return val;
    }
};

template <int Value>
struct intBits;

template <int Value>
struct fracBits;

template <int Value>
struct expBits;

template <int Value>
struct valBits;

template <bool Value>
struct isSigned;

constexpr int defaultIntBits = 8;
constexpr int defaultFracBits = 8;
constexpr bool defaultIsSigned = true;
using defaultQuMode = TRN::TCPL;
using defaultOfMode = SAT::TCPL;
using defaultFloatMode = FLT::DEFAULTFLT;

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

    // no matter whether the sign bit is commanded by the user, the actual implementation will always have a sign bit
    ArbiInt<1 + intB + fracB> data;

    inline constexpr Qu_s(double val)
    {
        static ArbiInt<1200 + 1200> buffer;
        buffer.template loadFromDouble<1200 + fracB>(val);

        data = intConvert<intB, fracB, isS, OfMode<OfM_t>>::convert(fracConvert<1200 + fracB, fracB, QuMode<QuM_t>>::convert(buffer));
    }

    inline constexpr Qu_s() : data() {}

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

            // data = fracConvert<fracBitsFrom, fracBitsInput, QuMode<QuM_t>>::convert(val.data);
        }
    }

    inline double toDouble() const
    {
        return data.toDouble() / std::pow(2, fracB);
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
        std::string binary = originalBinary.substr(originalBinary.size() - 1 - intB - fracB, intB + fracB + 1);
        return binary;
    }

    inline auto fill()
    {
        this->data.fill();

        return *this;
    }

    inline auto fill(int val)
    {
        this->data = val;

        return *this;
    }

    // overload for std::cout
    friend std::ostream &operator<<(std::ostream &os, const Qu_s &qu)
    {
        os << qu.toDouble();
        return os;
    }
};

template<typename ... Args>
struct containExp_s
{
    static constexpr bool value = (isA<Args, expBits<1>> || ...);
};


template <typename... Args>
struct QuInputHelper
{
    static constexpr bool containExp = containExp_s<Args...>::value;

    inline static constexpr auto intB = tagExtractor<intBits<defaultIntBits>, Args...>::value;
    inline static constexpr auto fracB = tagExtractor<fracBits<defaultFracBits>, Args...>::value;
    inline static constexpr auto isS = tagExtractor<isSigned<defaultIsSigned>, Args...>::value;
    inline static constexpr auto expB = tagExtractor<expBits<4>, Args...>::value;
    inline static constexpr auto valB = tagExtractor<valBits<4>, Args...>::value;
    
    using QuM = tagExtractor<QuMode<defaultQuMode>, Args...>::type;
    using OfM = tagExtractor<OfMode<defaultOfMode>, Args...>::type;
    using FM = tagExtractor<QuMode<defaultFloatMode>, Args...>::type;

    using type = std::conditional_t< containExp, Qu_s<expBits<expB>, valBits<valB>, QuMode<FM>, OfMode<FM>>, Qu_s<intBits<intB>, fracBits<fracB>, isSigned<isS>, QuMode<QuM>, OfMode<OfM>> >;
};

template <typename... Args>
struct QuInputHelper<Qu_s<Args...>> : QuInputHelper<Args...>
{};

template <typename... Args>
using Qu = typename QuInputHelper<Args...>::type;
// ------------------- Float -------------------
template <int expBitsInput, int valBitsInput, typename QuModeInput, typename OfModeInput>
class Qu_s<expBits<expBitsInput>, valBits<valBitsInput>, QuMode<QuModeInput>, OfMode<OfModeInput>>
{
public:
    inline static constexpr int expB = expBitsInput;
    inline static constexpr int valB = valBitsInput;
  
    using QuM_t = QuModeInput;
    using OfM_t = OfModeInput;
    inline static constexpr int QuM = QuModeInput::value;
    inline static constexpr int OfM = OfModeInput::value;

    inline static constexpr uint64_t maxVal = (1 << valB) - 1;
    inline static constexpr ArbiInt<expBitsInput> bias = staticShiftLeft<expBitsInput - 1>(ArbiInt<1>(1));


    ArbiInt<expB> expData;
    ArbiInt<valB> valData;
    bool signData;

    inline constexpr Qu_s() {}

    inline void toQuFloat(double val)
    {
        uint64_t sourceBits = reinterpret_cast<uint64_t &>(val);
        //std::cout << "sourceBits: " << std::bitset<64>(sourceBits) << std::endl;

        constexpr uint64_t leadingOne = (uint64_t)1 << 52;

        uint64_t sign = sourceBits >> 63;                            // 1 bit
        //std::cout << "sign: " << sign << std::endl;
        uint64_t exp = (sourceBits << 1) >> 53;                      // 11 bits
        //std::cout << "exp: " << std::bitset<11>(exp) <<  " " << exp << std::endl;
        uint64_t frac = (sourceBits & 0xFFFFFFFFFFFFF); // 52 bits
        //std::cout << "frac: " << std::bitset<52>(frac) <<  " " << frac << std::endl;
        
        expData = exp + bias - 1023;
        //std::printf("%d--\n",valB);
        //expData.display();
        
        if constexpr(valB >= 52) valData = frac << (valB - 52);
        else valData = frac >> (52 - valB);
        //valData.display();

        signData = (val < 0);
    }

    inline long double toDouble()
    {
        double ret = valData.uToDouble() * pow(0.5, valB) + 1;

        double pw = (expData - bias).uToDouble();

        if(signData) ret = -ret;

        return ret * std::pow(2, pw);
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    Qu_s(T val)
    {
        toQuFloat((double)val);
    }

    template <typename T>
        requires std::is_arithmetic_v<T>
    inline Qu_s& operator=(T val)
    {
        toQuFloat((double)val);
        return *this;
    }


    template <int intBitsFrom, int fracBitsFrom, bool isSignedFrom, typename QuModeFrom, typename OfModeFrom>
    inline Qu_s& operator=(const Qu_s<intBits<intBitsFrom>, fracBits<fracBitsFrom>, isSigned<isSignedFrom>, QuMode<QuModeFrom>, OfMode<OfModeFrom>> val)
    {
        valData = fracConvert_FixedToFloatval<valB, QuMode<QuM_t>>::convert(val.data);
        expData = fracConvert_FixedToFloatexp<val.fracB, expB, QuMode<QuM_t>>::convert(val.data);
        //(expData - bias).display();
        signData = val.data.isNegative();
        return *this;
    }
    
    template <int expBitsFrom, int valBitsFrom, typename QuModeFrom, typename OfModeFrom>
    inline Qu_s& operator=(Qu_s<expBits<expBitsFrom>, valBits<valBitsFrom>, QuMode<QuModeFrom>, OfMode<OfModeFrom>> val)
    {
        valData = fracConvert_FloatToFloatval<val.valB, valB>::convert(val.valData);
        expData = val.expData - val.bias + bias;
        signData = val.signData;
        return *this;
    }

    inline void display()
    {
        valData.display();
        printf("Decimal: %Lf\n",toDouble());
    }
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

    using size = dim<dims...>;

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
        return std::get<dim<dims...>::template absoluteIndex_s<index...>::value>(data);
    }

    template <auto... index>
    inline constexpr const auto &get() const
    {
        return std::get<dim<dims...>::template absoluteIndex_s<index...>::value>(data);
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

    static inline constexpr auto toInt = tagExtractor<intBits<fullPrecision ? fromInt1 + fromInt2 : std::max(fromInt1, fromInt2)>, toArgs...>::value;
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
    using merger = AddMerger<Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>>, Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>>, TypeList<toArgs...>>;

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

    static inline constexpr int shiftA = fromFrac2 > fromFrac1 ? fromFrac2 - fromFrac1 : 0;
    static inline constexpr int shiftB = fromFrac1 > fromFrac2 ? fromFrac1 - fromFrac2 : 0;

    inline static constexpr auto div(const Qu_s<intBits<fromInt1>, fracBits<fromFrac1>, isSigned<fromIsSigned1>, QuMode<fromQuMode1>, OfMode<fromOfMode1>> f1, const Qu_s<intBits<fromInt2>, fracBits<fromFrac2>, isSigned<fromIsSigned2>, QuMode<fromQuMode2>, OfMode<fromOfMode2>> f2)
    {
        if (f2.data == 0)
        {
            return Qu_s<intBits<merger::toInt>, fracBits<merger::toFrac>, isSigned<merger::toIsSigned>, QuMode<typename merger::toQuMode>, OfMode<typename merger::toOfMode>>();
        }

        auto fullQuotient = staticShiftLeft<shiftA + merger::toFrac>(f1.data) / staticShiftLeft<shiftB>(f2.data);

        auto intQuotient = intConvert<merger::toInt, merger::toFrac, merger::toIsSigned, OfMode<typename merger::toOfMode>>::convert(fullQuotient);

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

// specialization for static Qu_s
template <typename... toArgs, int fromInt, int fromFrac, bool fromIsSigned, typename fromQuMode, typename fromOfMode>
struct Qneg_s<Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>>, TypeList<toArgs...>>
{
    inline static constexpr auto neg(const Qu_s<intBits<fromInt>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>> f)
    {
        Qu_s<intBits<fromInt + 1>, fracBits<fromFrac>, isSigned<fromIsSigned>, QuMode<fromQuMode>, OfMode<fromOfMode>> result;
        result.data = -f.data;

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
    using subbaType = tagExtractor<baT<toArgs...>, toArgs...>::type;
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
    inline static constexpr auto div(const Qu_s<realArgs1...> f1, const Qu_s<Qu_s<realArgs2...>, Qu_s<imagArgs2...>> f2)
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

template <typename... Args>
struct sizeMerger;

template <size_t... dims1, typename QuT1, size_t... dims2, typename QuT2>
// requires QuT1::size == QuT2::size
    requires std::is_same_v<typename QuT1::size, typename QuT2::size>
struct sizeMerger<Qu_s<dim<dims1...>, QuT1>, Qu_s<dim<dims2...>, QuT2>>
{
    using size = dim<dims1...>;
};

template <size_t... dims1, typename QuT1, typename QuT2>
    requires isScalar<QuT2>
struct sizeMerger<Qu_s<dim<dims1...>, QuT1>, QuT2>
{
    using size = dim<dims1...>;
};

template <size_t... dims2, typename QuT2, typename QuT1>
    requires isScalar<QuT1>
struct sizeMerger<QuT1, Qu_s<dim<dims2...>, QuT2>>
{
    using size = dim<dims2...>;
};

// use [] to call the object if it is a tensor, otherwise just return the object
template <typename T>
inline auto autoCall(const T &obj, auto... index)
{
    if constexpr (isScalar<T>)
    {
        return obj;
    }
    else
    {
        return obj[index...];
    }
}

template <typename... Args>
class MulExpression;

template <typename QuT1, typename QuT2, typename... toArgs>
class MulExpression<QuT1, QuT2, toArgs...>
{
    const QuT1 &q1;
    const QuT2 &q2;

public:
    using size = typename sizeMerger<QuT1, QuT2>::size;

    MulExpression(const QuT1 &f1, const QuT2 &f2)
        : q1(f1), q2(f2) {}

    auto operator[](auto... index) const
    {
        return Qmul<toArgs...>(autoCall(q1, index...), autoCall(q2, index...));
    }
};

template <typename... Args>
struct QmulTensor_s;

template <typename QuT1, typename QuT2, typename... toArgs>
struct QmulTensor_s<QuT1, QuT2, toArgs...>
{
    inline static constexpr auto mul(const QuT1 &f1, const QuT2 &f2)
    {
        return MulExpression<QuT1, QuT2, toArgs...>(f1, f2);
    }
};

template <typename... Args>
class AddExpression;

template <typename QuT1, typename QuT2, typename... toArgs>
class AddExpression<QuT1, QuT2, toArgs...>
{
    const QuT1 &q1;
    const QuT2 &q2;

public:
    using size = typename sizeMerger<QuT1, QuT2>::size;

    AddExpression(const QuT1 &f1, const QuT2 &f2)
        : q1(f1), q2(f2) {}

    auto operator[](auto... index) const
    {
        return Qadd<toArgs...>(autoCall(q1, index...), autoCall(q2, index...));
    }
};

template <typename... Args>
struct QaddTensor_s;

template <typename QuT1, typename QuT2, typename... toArgs>
struct QaddTensor_s<QuT1, QuT2, toArgs...>
{
    inline static constexpr auto add(const QuT1 &f1, const QuT2 &f2)
    {
        return AddExpression<QuT1, QuT2, toArgs...>(f1, f2);
    }
};

template <typename... Args>
class SubExpression;

template <typename QuT1, typename QuT2, typename... toArgs>
class SubExpression<QuT1, QuT2, toArgs...>
{
    const QuT1 &q1;
    const QuT2 &q2;

public:
    using size = typename sizeMerger<QuT1, QuT2>::size;

    SubExpression(const QuT1 &f1, const QuT2 &f2)
        : q1(f1), q2(f2) {}

    auto operator[](auto... index) const
    {
        return Qsub<toArgs...>(autoCall(q1, index...), autoCall(q2, index...));
    }
};

template <typename... Args>
struct QsubTensor_s;

template <typename QuT1, typename QuT2, typename... toArgs>
struct QsubTensor_s<QuT1, QuT2, toArgs...>
{
    inline static constexpr auto sub(const QuT1 &f1, const QuT2 &f2)
    {
        return SubExpression<QuT1, QuT2, toArgs...>(f1, f2);
    }
};

template <typename... Args>
class DivExpression;

template <typename QuT1, typename QuT2, typename... toArgs>
class DivExpression<QuT1, QuT2, toArgs...>
{
    const QuT1 &q1;
    const QuT2 &q2;

public:
    using size = typename sizeMerger<QuT1, QuT2>::size;

    DivExpression(const QuT1 &f1, const QuT2 &f2)
        : q1(f1), q2(f2) {}

    auto operator[](auto... index) const
    {
        return Qdiv<toArgs...>(autoCall(q1, index...), autoCall(q2, index...));
    }
};

template <typename... Args>
struct QdivTensor_s;

template <typename QuT1, typename QuT2, typename... toArgs>
struct QdivTensor_s<QuT1, QuT2, toArgs...>
{
    inline static constexpr auto div(const QuT1 &f1, const QuT2 &f2)
    {
        return DivExpression<QuT1, QuT2, toArgs...>(f1, f2);
    }
};

template <typename... Args>
class AbsExpression;

template <typename QuT, typename... toArgs>
class AbsExpression<QuT, toArgs...>
{
    const QuT &q;

public:
    using size = typename QuT::size;

    AbsExpression(const QuT &f)
        : q(f) {}

    auto operator[](auto... index) const
    {
        return Qabs<toArgs...>(q[index...]);
    }
};

template <typename... Args>
struct QabsTensor_s;

template <typename QuT, typename... toArgs>
struct QabsTensor_s<QuT, toArgs...>
{
    inline static constexpr auto abs(const QuT &f)
    {
        return AbsExpression<QuT, toArgs...>(f);
    }
};

template <typename... Args>
class NegExpression;

template <typename QuT, typename... toArgs>
class NegExpression<QuT, toArgs...>
{
    const QuT &q;

public:
    using size = typename QuT::size;

    NegExpression(const QuT &f)
        : q(f) {}

    auto operator[](auto... index) const
    {
        return Qneg<toArgs...>(q[index...]);
    }
};

template <typename... Args>
struct QnegTensor_s;

template <typename QuT, typename... toArgs>
struct QnegTensor_s<QuT, toArgs...>
{
    inline static constexpr auto neg(const QuT &f)
    {
        return NegExpression<QuT, toArgs...>(f);
    }
};

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

// tensor functions
template <typename... toArgs, typename... QuArgs1, typename... QuArgs2>
    requires(!isScalar<Qu_s<QuArgs1...>>) || (!isScalar<Qu_s<QuArgs2...>>)
inline constexpr auto Qmul(const Qu_s<QuArgs1...> &f1, const Qu_s<QuArgs2...> &f2)
{
    return QmulTensor_s<Qu_s<QuArgs1...>, Qu_s<QuArgs2...>, toArgs...>::mul(f1, f2);
}

template <typename... toArgs, typename... QuArgs1, typename... QuArgs2>
    requires(!isScalar<Qu_s<QuArgs1...>>) || (!isScalar<Qu_s<QuArgs2...>>)
inline constexpr auto Qadd(const Qu_s<QuArgs1...> &f1, const Qu_s<QuArgs2...> &f2)
{
    return QaddTensor_s<Qu_s<QuArgs1...>, Qu_s<QuArgs2...>, toArgs...>::add(f1, f2);
}

template <typename... toArgs, typename... QuArgs1, typename... QuArgs2>
    requires(!isScalar<Qu_s<QuArgs1...>>) || (!isScalar<Qu_s<QuArgs2...>>)
inline constexpr auto Qsub(const Qu_s<QuArgs1...> &f1, const Qu_s<QuArgs2...> &f2)
{
    return QsubTensor_s<Qu_s<QuArgs1...>, Qu_s<QuArgs2...>, toArgs...>::sub(f1, f2);
}

template <typename... toArgs, typename... QuArgs1, typename... QuArgs2>
    requires(!isScalar<Qu_s<QuArgs1...>>) || (!isScalar<Qu_s<QuArgs2...>>)
inline constexpr auto Qdiv(const Qu_s<QuArgs1...> &f1, const Qu_s<QuArgs2...> &f2)
{
    return QdivTensor_s<Qu_s<QuArgs1...>, Qu_s<QuArgs2...>, toArgs...>::div(f1, f2);
}

template <typename... toArgs, typename... QuArgs>
    requires(!isScalar<Qu_s<QuArgs...>>)
inline constexpr auto Qabs(const Qu_s<QuArgs...> &f)
{
    return QabsTensor_s<Qu_s<QuArgs...>, toArgs...>::abs(f);
}

template <typename... toArgs, typename... QuArgs>
    requires(!isScalar<Qu_s<QuArgs...>>)
inline constexpr auto Qneg(const Qu_s<QuArgs...> &f)
{
    return QnegTensor_s<Qu_s<QuArgs...>, toArgs...>::neg(f);
}

// operator overloading
template <typename... QuArgs1, typename... QuArgs2>
    requires(!isScalar<Qu_s<QuArgs1...>>) || (!isScalar<Qu_s<QuArgs2...>>)
inline constexpr auto operator*(const Qu_s<QuArgs1...> &f1, const Qu_s<QuArgs2...> &f2)
{
    return Qmul(f1, f2);
}

template <typename... QuArgs1, typename... QuArgs2>
    requires(!isScalar<Qu_s<QuArgs1...>>) || (!isScalar<Qu_s<QuArgs2...>>)
inline constexpr auto operator+(const Qu_s<QuArgs1...> &f1, const Qu_s<QuArgs2...> &f2)
{
    return Qadd(f1, f2);
}

template <typename... QuArgs1, typename... QuArgs2>
    requires(!isScalar<Qu_s<QuArgs1...>>) || (!isScalar<Qu_s<QuArgs2...>>)
inline constexpr auto operator-(const Qu_s<QuArgs1...> &f1, const Qu_s<QuArgs2...> &f2)
{
    return Qsub(f1, f2);
}

template <typename... QuArgs1, typename... QuArgs2>
    requires(!isScalar<Qu_s<QuArgs1...>>) || (!isScalar<Qu_s<QuArgs2...>>)
inline constexpr auto operator/(const Qu_s<QuArgs1...> &f1, const Qu_s<QuArgs2...> &f2)
{
    return Qdiv(f1, f2);
}

template <typename... QuArgs>
    requires(!isScalar<Qu_s<QuArgs...>>)
inline constexpr auto operator-(const Qu_s<QuArgs...> &f1)
{
    return Qneg(f1);
}

} // namespace QuBLAS