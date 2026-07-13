#include "QuBLAS.h"

#include <gtest/gtest.h>

#include <array>
#include <numeric>
#include <type_traits>

using namespace QuBLAS;

namespace {

using Scalar =
    Qu<intBits<8>, fracBits<0>, isSigned<true>, OfMode<SAT::TCPL>>;

using CompatibleLeft = Qu<dim<2, 3>, Scalar>;
using CompatibleRight = Qu<dim<3, 4>, Scalar>;
using MismatchedRight = Qu<dim<4, 4>, Scalar>;
using WrongRank = Qu<dim<3>, Scalar>;

static_assert(
    EinsumCompatible<"ij,jk->ik", CompatibleLeft, CompatibleRight>);
static_assert(
    !EinsumCompatible<"ij,jk->ik", CompatibleLeft, MismatchedRight>);
static_assert(
    !EinsumCompatible<"ij,jk->iz", CompatibleLeft, CompatibleRight>);
static_assert(!EinsumCompatible<"ij,jk->ik", WrongRank, CompatibleRight>);
static_assert(!EinsumCompatible<"ii->i", CompatibleLeft>);

TEST(GeneralEinsum, InfersOutputAxesInFirstAppearanceOrder)
{
    CompatibleLeft left;
    CompatibleRight right;
    left.fill(1);
    right.fill(2);

    auto result = einsum<"ij,jk">(left, right).eval();
    static_assert(std::is_same_v<typename decltype(result)::size, dim<2, 4>>);

    EXPECT_DOUBLE_EQ((result[0, 0].toDouble()), 6.0);
    EXPECT_DOUBLE_EQ((result[1, 3].toDouble()), 6.0);
}

TEST(GeneralEinsum, ContractsAThreeOperandChain)
{
    using A = Qu<dim<2, 2>, Scalar>;
    using B = Qu<dim<2, 3>, Scalar>;
    using C = Qu<dim<3, 2>, Scalar>;

    A a;
    a[0, 0] = 1;
    a[0, 1] = 2;
    a[1, 0] = 3;
    a[1, 1] = 4;

    B b;
    b[0, 0] = 1;
    b[0, 1] = 0;
    b[0, 2] = 2;
    b[1, 0] = 0;
    b[1, 1] = 1;
    b[1, 2] = 3;

    C c;
    c[0, 0] = 1;
    c[0, 1] = 2;
    c[1, 0] = 3;
    c[1, 1] = 4;
    c[2, 0] = 5;
    c[2, 1] = 6;

    auto result = einsum<"ij,jk,kl->il">(a, b, c).eval();
    static_assert(std::is_same_v<typename decltype(result)::size, dim<2, 2>>);

    EXPECT_DOUBLE_EQ((result[0, 0].toDouble()), 47.0);
    EXPECT_DOUBLE_EQ((result[0, 1].toDouble()), 58.0);
    EXPECT_DOUBLE_EQ((result[1, 0].toDouble()), 105.0);
    EXPECT_DOUBLE_EQ((result[1, 1].toDouble()), 130.0);
}

TEST(GeneralEinsum, PreservesUncontractedAxesOfAHigherRankOperand)
{
    using Left = Qu<dim<2, 2, 3>, Scalar>;
    using Right = Qu<dim<3, 2>, Scalar>;

    Left left;
    int value = 1;
    for (size_t a = 0; a < 2; ++a)
        for (size_t b = 0; b < 2; ++b)
            for (size_t c = 0; c < 3; ++c)
                left[a, b, c] = value++;

    Right right;
    right[0, 0] = 1;
    right[1, 0] = 0;
    right[2, 0] = 1;
    right[0, 1] = 0;
    right[1, 1] = 1;
    right[2, 1] = 1;

    auto result = einsum<"abc,cd->abd">(left, right).eval();
    static_assert(
        std::is_same_v<typename decltype(result)::size, dim<2, 2, 2>>);

    EXPECT_DOUBLE_EQ((result[0, 0, 0].toDouble()), 4.0);
    EXPECT_DOUBLE_EQ((result[0, 0, 1].toDouble()), 5.0);
    EXPECT_DOUBLE_EQ((result[0, 1, 0].toDouble()), 10.0);
    EXPECT_DOUBLE_EQ((result[0, 1, 1].toDouble()), 11.0);
    EXPECT_DOUBLE_EQ((result[1, 0, 0].toDouble()), 16.0);
    EXPECT_DOUBLE_EQ((result[1, 0, 1].toDouble()), 17.0);
    EXPECT_DOUBLE_EQ((result[1, 1, 0].toDouble()), 22.0);
    EXPECT_DOUBLE_EQ((result[1, 1, 1].toDouble()), 23.0);
}

TEST(GeneralEinsum, ExtractsADiagonal)
{
    using Matrix = Qu<dim<3, 3>, Scalar>;

    Matrix matrix;
    int value = 1;
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            matrix[i, j] = value++;

    auto result = einsum<"ii->i">(matrix).eval();
    static_assert(std::is_same_v<typename decltype(result)::size, dim<3>>);

    EXPECT_DOUBLE_EQ(result[0].toDouble(), 1.0);
    EXPECT_DOUBLE_EQ(result[1].toDouble(), 5.0);
    EXPECT_DOUBLE_EQ(result[2].toDouble(), 9.0);
}

TEST(GeneralEinsum, FullyContractsToAScalar)
{
    using Matrix = Qu<dim<2, 3>, Scalar>;

    Matrix left;
    Matrix right;
    int value = 1;
    for (size_t i = 0; i < 2; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            left[i, j] = value;
            right[i, j] = 7 - value;
            ++value;
        }
    }

    auto result = einsum<"ij,ij->">(left, right).eval();
    static_assert(isScalar<std::remove_cvref_t<decltype(result)>>);
    EXPECT_DOUBLE_EQ(result.toDouble(), 56.0);
}

TEST(GeneralEinsum, BuildsAnOuterProductWithoutContractedAxes)
{
    using Left = Qu<dim<2>, Scalar>;
    using Right = Qu<dim<3>, Scalar>;

    Left left{2, 3};
    Right right{4, 5, 6};

    auto result = einsum<"i,j->ij">(left, right).eval();
    static_assert(std::is_same_v<typename decltype(result)::size, dim<2, 3>>);

    EXPECT_DOUBLE_EQ((result[0, 0].toDouble()), 8.0);
    EXPECT_DOUBLE_EQ((result[0, 1].toDouble()), 10.0);
    EXPECT_DOUBLE_EQ((result[0, 2].toDouble()), 12.0);
    EXPECT_DOUBLE_EQ((result[1, 0].toDouble()), 12.0);
    EXPECT_DOUBLE_EQ((result[1, 1].toDouble()), 15.0);
    EXPECT_DOUBLE_EQ((result[1, 2].toDouble()), 18.0);
}

auto temporaryLeft()
{
    using Matrix = Qu<dim<2, 2>, Scalar>;
    Matrix value;
    value[0, 0] = 1;
    value[0, 1] = 2;
    value[1, 0] = 3;
    value[1, 1] = 4;
    return value;
}

auto temporaryRight()
{
    using Matrix = Qu<dim<2, 2>, Scalar>;
    Matrix value;
    value[0, 0] = 5;
    value[0, 1] = 6;
    value[1, 0] = 7;
    value[1, 1] = 8;
    return value;
}

TEST(GeneralEinsum, OwnsTemporaryOperandsUntilLazyEvaluation)
{
    auto expression =
        einsum<"ij,jk->ik">(temporaryLeft(), temporaryRight());

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
