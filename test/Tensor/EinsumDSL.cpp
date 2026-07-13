#include <gtest/gtest.h>

#include <type_traits>

#include "QuBLAS.h"

namespace {

using Scalar = Qu<intBits<4>, fracBits<0>>;
using Left = Qu<dim<2, 3>, Scalar>;
using Right = Qu<dim<3, 2>, Scalar>;

template <typename>
inline constexpr bool isLazyTensor = false;

template <typename Size, typename Compute>
inline constexpr bool isLazyTensor<LazyTensor<Size, Compute>> = true;

constexpr bool contractsAtCompileTime()
{
    using Vector = Qu<dim<2>, Scalar>;
    Vector left{1, 2};
    Vector right{3, 4};
    return einsum<"i,i->">(left, right).eval() == Scalar{11};
}

static_assert(contractsAtCompileTime());

TEST(EinsumDSL, BuildsALazyCompileTimePlannedMatrixProduct)
{
    Left lhs;
    Right rhs;

    lhs[0, 0] = 1;
    lhs[0, 1] = 2;
    lhs[0, 2] = 3;
    lhs[1, 0] = 4;
    lhs[1, 1] = 5;
    lhs[1, 2] = 6;

    rhs[0, 0] = 7;
    rhs[0, 1] = 8;
    rhs[1, 0] = 9;
    rhs[1, 1] = 10;
    rhs[2, 0] = 11;
    rhs[2, 1] = 12;

    auto expression = einsum<"ij,jk->ik">(lhs, rhs);
    static_assert(isLazyTensor<decltype(expression)>);
    static_assert(std::is_same_v<typename decltype(expression)::size, dim<2, 2>>);

    EXPECT_DOUBLE_EQ((expression[0, 0].toDouble()), 58.0);
    EXPECT_DOUBLE_EQ((expression[1, 0].toDouble()), 139.0);
    EXPECT_DOUBLE_EQ((expression[0, 1].toDouble()), 64.0);
    EXPECT_DOUBLE_EQ((expression[1, 1].toDouble()), 154.0);
    EXPECT_THROW((void)expression[4], std::out_of_range);
    EXPECT_THROW((static_cast<void>(expression[2, 0])), std::out_of_range);
}

TEST(EinsumDSL, MaterializesAndAcceptsRenamedIndices)
{
    Left lhs;
    Right rhs;
    lhs.fill(1);
    rhs.fill(2);

    auto result = einsum<"ab,bc->ac">(lhs, rhs).eval();

    static_assert(std::is_same_v<typename decltype(result)::size, dim<2, 2>>);
    EXPECT_DOUBLE_EQ((result[0, 0].toDouble()), 6.0);
    EXPECT_DOUBLE_EQ((result[1, 1].toDouble()), 6.0);
}

} // namespace
