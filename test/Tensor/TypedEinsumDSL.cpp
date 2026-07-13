#include "QuBLAS.h"

#include <gtest/gtest.h>

#include <array>
#include <numeric>
#include <type_traits>

using namespace QuBLAS;
using namespace QuBLAS::indices;

namespace {

using Scalar = Qu<intBits<8>, fracBits<0>, isSigned<true>, OfMode<SAT::TCPL>>;
using Matrix = Qu<dim<2, 2>, Scalar>;

Matrix matrix(int a, int b, int c, int d)
{
    Matrix result;
    result[0, 0] = a;
    result[0, 1] = b;
    result[1, 0] = c;
    result[1, 1] = d;
    return result;
}

TEST(TypedEinsumDSL, ContractsMatricesWithoutTouchingTensorOperators)
{
    auto left = matrix(1, 2, 3, 4);
    auto right = matrix(5, 6, 7, 8);

    auto expression =
        ein[_i, _k] <<= ein[left, _i, _j] * ein[right, _j, _k];

    // Lvalues remain live references inside the lazy backend expression.
    left[0, 0] = 2;
    auto result = expression.eval();
    static_assert(std::is_same_v<typename decltype(result)::size, dim<2, 2>>);

    EXPECT_DOUBLE_EQ((result[0, 0].toDouble()), 24.0);
    EXPECT_DOUBLE_EQ((result[0, 1].toDouble()), 28.0);
    EXPECT_DOUBLE_EQ((result[1, 0].toDouble()), 43.0);
    EXPECT_DOUBLE_EQ((result[1, 1].toDouble()), 50.0);

    // The pre-existing element-wise tensor operator remains independently viable.
    auto elementwise = (left * right).eval();
    EXPECT_DOUBLE_EQ((elementwise[0, 0].toDouble()), 10.0);
}

TEST(TypedEinsumDSL, AppendsAnyNumberOfFactors)
{
    auto a = matrix(1, 2, 3, 4);
    auto b = matrix(5, 6, 7, 8);
    auto c = matrix(2, 0, 0, 3);

    auto result =
        (ein[_i, _l] <<=
         ein[a, _i, _j] * ein[b, _j, _k] * ein[c, _k, _l])
            .eval();

    EXPECT_DOUBLE_EQ((result[0, 0].toDouble()), 38.0);
    EXPECT_DOUBLE_EQ((result[0, 1].toDouble()), 66.0);
    EXPECT_DOUBLE_EQ((result[1, 0].toDouble()), 86.0);
    EXPECT_DOUBLE_EQ((result[1, 1].toDouble()), 150.0);
}

TEST(TypedEinsumDSL, ASingleFactorCanProduceATensorOrScalar)
{
    using Square = Qu<dim<3, 3>, Scalar>;
    Square value;
    int next = 1;
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            value[i, j] = next++;

    auto diagonal = (ein[_i] <<= ein[value, _i, _i]).eval();
    auto trace = (ein[] <<= ein[value, _i, _i]).eval();

    static_assert(std::is_same_v<typename decltype(diagonal)::size, dim<3>>);
    static_assert(isScalar<std::remove_cvref_t<decltype(trace)>>);
    EXPECT_DOUBLE_EQ(diagonal[0].toDouble(), 1.0);
    EXPECT_DOUBLE_EQ(diagonal[1].toDouble(), 5.0);
    EXPECT_DOUBLE_EQ(diagonal[2].toDouble(), 9.0);
    EXPECT_DOUBLE_EQ(trace.toDouble(), 15.0);
}

TEST(TypedEinsumDSL, TransfersTemporaryOwnershipToTheLazyBackend)
{
    auto expression =
        ein[_i, _k] <<=
        ein[matrix(1, 2, 3, 4), _i, _j] *
            ein[matrix(5, 6, 7, 8), _j, _k];

    std::array<int, 4096> stackNoise;
    std::iota(stackNoise.begin(), stackNoise.end(), 0);
    ASSERT_EQ(stackNoise.back(), 4095);

    auto result = expression.eval();
    EXPECT_DOUBLE_EQ((result[0, 0].toDouble()), 19.0);
    EXPECT_DOUBLE_EQ((result[0, 1].toDouble()), 22.0);
    EXPECT_DOUBLE_EQ((result[1, 0].toDouble()), 43.0);
    EXPECT_DOUBLE_EQ((result[1, 1].toDouble()), 50.0);
}

} // namespace
