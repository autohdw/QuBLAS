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
#include <sys/resource.h>
#include <sys/types.h>
#include <type_traits>
#include <utility>

inline namespace QuBLAS {

// ------------------- Random -------------------

static std::random_device rd;
static std::mt19937 gen(rd());
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

    template <typename T>
        requires std::is_arithmetic_v<T>
    constexpr ArbiInt(T val)
    {
        data = static_cast<data_t>(val);

        // extend the sign bit to the higher bits
        if constexpr (N < 64)
        {
            data = static_cast<data_t>(static_cast<int64_t>(data) << (64 - N) >> (64 - N));
        }
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

    // float and double
    template <typename T>
        requires std::is_floating_point_v<T>
    constexpr ArbiInt(T val)
    {
        data.fill(0);

        // Handle whether the input value is negative
        bool isNegative = (val < 0);
        val = std::abs(val);

        // Calculate the number of words needed
        size_t words_needed = 0;
        T temp_val = val;
        while (temp_val != 0)
        {
            temp_val /= static_cast<T>(std::numeric_limits<uint64_t>::max()) + 1;
            words_needed++;
        }

        // Fill the data array
        for (size_t i = 0; i < words_needed && i < num_words; i++)
        {
            data[i] = static_cast<uint64_t>(std::fmod(val, static_cast<T>(std::numeric_limits<uint64_t>::max()) + 1));
            val /= static_cast<T>(std::numeric_limits<uint64_t>::max()) + 1;
        }

        if (isNegative)
        {
            for (size_t i = 0; i < num_words; i++)
            {
                data[i] = ~data[i]; // Bitwise NOT for two's complement
            }
            data[0]++; // Adding 1 to the least significant word to complete two's complement
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
        uint64_t sign_extension = static_cast<uint64_t>(data[0] >> 63);
        for (size_t i = 1; i < num_words; ++i)
        {
            data[i] = sign_extension;
        }
    }

    template <size_t M>
        requires(M > 64) && (M < N)
    constexpr ArbiInt(const ArbiInt<M> &other)
    {
        std::memcpy(data.data(), other.data.data(), sizeof(uint64_t) * other.num_words);

        // sign extension of the higher uint64_ts, all 1 or all 0 according to whether the 64-th bit of the lowest uint64_t is 1
        uint64_t sign_extension = static_cast<uint64_t>(data[other.num_words - 1] >> 63);
        for (size_t i = other.num_words; i < num_words; ++i)
        {
            data[i] = sign_extension;
        }
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

    // Precompute sign bit positions at compile time
    constexpr size_t lhs_sign_bit_pos = N - 1;
    constexpr size_t lhs_sign_word_index = lhs_sign_bit_pos / 64;
    constexpr size_t lhs_sign_bit_in_word = lhs_sign_bit_pos % 64;

    // Compute sign extensions using arithmetic right shift
    int64_t lhs_sign_extension = static_cast<int64_t>(lhs.data[lhs_sign_word_index]) >> lhs_sign_bit_in_word;
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

    // Precompute sign bit positions at compile time
    constexpr size_t lhs_sign_bit_pos = N - 1;
    constexpr size_t lhs_sign_word_index = lhs_sign_bit_pos / 64;
    constexpr size_t lhs_sign_bit_in_word = lhs_sign_bit_pos % 64;

    constexpr size_t rhs_sign_bit_pos = M - 1;
    constexpr size_t rhs_sign_word_index = rhs_sign_bit_pos / 64;
    constexpr size_t rhs_sign_bit_in_word = rhs_sign_bit_pos % 64;

    // Compute sign extensions using arithmetic right shift
    int64_t lhs_sign_extension = static_cast<int64_t>(lhs.data[lhs_sign_word_index]) >> lhs_sign_bit_in_word;
    int64_t rhs_sign_extension = static_cast<int64_t>(rhs.data[rhs_sign_word_index]) >> rhs_sign_bit_in_word;

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
    std::memcpy(result.data.data() + shift / 64, x.data.data(), sizeof(uint64_t) * ArbiInt<N>::num_words);

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
    result.data.fill(0);

    // 确定输入数是否为负数
    constexpr size_t sign_bit_pos = (N - 1) % 64;
    constexpr size_t sign_word_index = (N - 1) / 64;
    bool is_negative = (x.data[sign_word_index] >> sign_bit_pos) & 1;

    // 预计算符号扩展位，0xFFFFFFFFFFFFFFFF 或 0x0
    uint64_t sign_extend = is_negative ? ~uint64_t(0) : uint64_t(0);

    if constexpr (bit_shift == 0)
    {
        // 位移是64的倍数，直接复制并处理符号扩展
        for (size_t i = 0; i < num_words_in; ++i)
        {
            result.data[i + word_shift] = x.data[i];
        }

        // 符号扩展高位
        for (size_t i = num_words_in + word_shift; i < num_words_out; ++i)
        {
            result.data[i] = sign_extend;
        }
    }
    else
    {
        for (size_t i = 0; i <= num_words_in; ++i)
        {
            uint64_t curr = (i < num_words_in) ? x.data[i] : sign_extend;
            uint64_t next = (i + 1 < num_words_in) ? x.data[i + 1] : sign_extend;

            uint64_t lower = curr << bit_shift;
            uint64_t upper = next >> (64 - bit_shift);

            size_t res_index = i + word_shift;
            if (res_index < num_words_out)
                result.data[res_index] |= lower;
            if (res_index + 1 < num_words_out)
                result.data[res_index + 1] |= upper;
        }
    }

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

    __int128_t temp = static_cast<__int128_t>((static_cast<__uint128_t>(x.data[num_words - 1]) << 64) | static_cast<__uint128_t>(x.data[num_words - 2]));
    result.data = static_cast<ArbiInt<N - shift>::data_t>(temp >> (shift % 64));

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
    static constexpr size_t shift_words = shift / 64; // 计算完整的64位块的右移数量
    static constexpr size_t shift_bits = shift % 64;  // 计算剩余的位右移数量
    static constexpr size_t num_input_words = ArbiInt<N>::num_words;
    static constexpr size_t num_output_words = ArbiInt<N - shift>::num_words;

    ArbiInt<N - shift> result;
    result.data.fill(0);

    // 使用128位整数进行合并和位移
    for (size_t i = 0; i < num_output_words; ++i)
    {
        if (i + shift_words < num_input_words)
        {
            __uint128_t temp = static_cast<__uint128_t>(x.data[i + shift_words]) >> shift_bits;

            if (shift_bits > 0 && i + shift_words + 1 < num_input_words)
            {
                temp |= static_cast<__uint128_t>(x.data[i + shift_words + 1]) << (64 - shift_bits);
            }

            result.data[i] = static_cast<uint64_t>(temp);
        }
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

// comparison operators

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



template <int fromFrac, int toFrac, typename QuMode>
struct fracConvert;



template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<RND::POS_INF>>
{
    inline static constexpr auto convert(auto val)
    {
        if constexpr (fromFrac <= toFrac)
        {
            return staticShiftLeft<toFrac - fromFrac>(val);
        }
        else {

            return staticShiftRight<fromFrac - toFrac>(val);
 
        }

         
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<RND::NEG_INF>>
{
    inline static constexpr auto convert(auto val)
    {
        return 0;
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<RND::ZERO>>
{
    inline static constexpr auto convert(auto val)
    {
        return 0;
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<RND::INF>>
{
    inline static constexpr auto convert(auto val)
    {
        return 0;
    }
};

template <int fromFrac, int toFrac>
struct fracConvert<fromFrac, toFrac, QuMode<RND::CONV>>
{
    inline static constexpr auto convert(auto val)
    {

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
    inline static constexpr auto convert(auto val)
    {
        if constexpr (fromFrac <= toFrac)
        {
            return staticShiftLeft<toFrac - fromFrac>(val);
        }
        else
        {
            constexpr auto one = staticShiftLeft<fromFrac - toFrac - 1>(ArbiInt<1>::allOnes());
            constexpr auto zero = ArbiInt<fromFrac - toFrac>(0);


            auto oneOrZero = val.isNegative() ? one : zero;

            oneOrZero.display("oneOrZero");

            val.display("val");

            (val + oneOrZero).display("val + oneOrZero");

            return staticShiftRight<fromFrac - toFrac>(val + oneOrZero);
    
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

template <int toInt, int toFrac, bool toIsSigned>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<SAT::TCPL>>
{
    template <size_t N>
        requires(N <= 64)
    inline static constexpr auto convert(ArbiInt<N> val)
    {
        using innerType = ArbiInt<N>::data_t;

        constexpr innerType maxVal = ((innerType)1 << (toInt + toFrac)) - 1;
        std::cout << "maxVal: " << maxVal << std::endl;
        constexpr innerType minVal = toIsSigned ? -maxVal : 0;
        std::cout << "minVal: " << minVal << std::endl;

        return ArbiInt<N>(std::clamp(val.data, minVal, maxVal));
    }

    template <size_t N>
        requires(N > 64)
    inline static constexpr auto convert(ArbiInt<N> val)
    {
        // the maxVal should be all 1 in the last toInt + toFrac bits
        constexpr auto maxVal = ArbiInt<1 + toInt + toFrac>::allOnes();
        constexpr auto minVal = toIsSigned ? -maxVal : 0;

        if (val < minVal)
        {
            return ArbiInt<N>(minVal);
        }
        else if (val > maxVal)
        {
            return ArbiInt<N>(maxVal);
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
    inline static constexpr auto convert(auto val)
    {
        return 0;
    }
};

template <int toInt, int toFrac, bool toIsSigned>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<SAT::SMGN>>
{
    inline static constexpr auto convert(auto val)
    {
        return 0;
    }
};

template <int toInt, int toFrac, bool toIsSigned>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<WRP::TCPL>>
{

    inline static constexpr auto convert(auto val)
    {
        return 0;
    }
};

template <int toInt, int toFrac, bool toIsSigned, auto N>
struct intConvert<toInt, toFrac, toIsSigned, OfMode<WRP::TCPL_SAT<N>>>
{
    inline static constexpr auto convert(auto val)
    {
        return 0;
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
using defaultOfMode = SAT::TCPL;

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

    template <typename T>
        requires std::is_arithmetic_v<T>
    inline constexpr Qu_s(T val)
    {
        if constexpr (1 + intB + fracB > 64)
        {
            // clang-format off
            const uint64_t doubleAsUint64 = *reinterpret_cast<const uint64_t*>(&val);
            const uint64_t sign = doubleAsUint64 >> 63;
            const int64_t exponent = ((doubleAsUint64 >> 52) & 0x7FF) - 1023;
            const uint64_t mantissa = (doubleAsUint64 & 0xFFFFFFFFFFFFFull) | 0x10000000000000ull;

            const int64_t effectivePos = exponent + fracB;

            if (effectivePos >= 0)
            {
                int p = effectivePos >> 6; 
                int r = effectivePos & 0x3F;

                const uint64_t m1 = (mantissa >> (52 - r)) & ((uint64_t(1) << (64 - r)) - 1);
                const uint64_t m2 = (mantissa << (r + 12)) & 0xFFFFFFFFFFFFFFFFull;

                if (p < data.num_words) data.data[p] |= m1;
                if (r <= 12 && (p - 1) < data.num_words) data.data[p - 1] |= m2;
            }
            else
            {
                const int64_t adjustedDelta = 52 - effectivePos;
                const uint64_t m3 = (mantissa >> adjustedDelta) & 0xFFFFFFFFFFFFFFFFull;

                if (adjustedDelta >= 0)
                {
                    data.data[0] |= m3;
                }
                else
                {
                    int p = (-adjustedDelta) >> 6; 
                    int r = (-adjustedDelta) & 0x3F; 

                    const uint64_t m4 = (mantissa >> r) & 0xFFFFFFFFFFFFFFFFull;
                    const uint64_t m5 = (mantissa << (64 - r)) & 0xFFFFFFFFFFFFFFFFull;

                    if (p < data.num_words) data.data[p] |= m4;
                    if ((p - 1) < data.num_words) data.data[p - 1] |= m5;
                }
            }

            if (sign)
            {
                for (auto& word : data.data) word = ~word;
                auto p = data.data.begin();
                while (p != data.data.end() && !*p++) ++p;
            }
            // clang-format on
        }
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
            // data = intConvert<intB, fracB, isS, OfMode<OfM_t>>::convert(fracConvert<fracBitsFrom, fracBitsInput, QuMode<QuM_t>>::convert(val.data));

            data = fracConvert<fracBitsFrom, fracBitsInput, QuMode<QuM_t>>::convert(val.data);
        }
    }

    double toDouble() const
    {
        return data.toDouble() / std::pow(2, fracB);
    }

    void display(std::string name = "") const
    {
        if (name != "")
        {
            std::cout << name << " :" << std::endl;
        }

        std::cout << "intBits: " << intB << " fracBits: " << fracB << " isSigned: " << isS << std::endl;
        std::cout << "Binary: " << this->data.toBinary() << std::endl;
        std::cout << "Decimal: " << this->toDouble() << std::endl;
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

} // namespace QuBLAS