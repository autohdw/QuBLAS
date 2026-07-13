#include <gtest/gtest.h>

#include <string_view>
#include <utility>

#include "QuBLAS.h"

namespace {

using namespace QuBLAS;

using Scalar = Qu<intBits<8>, fracBits<0>>;
using Vector = Qu<dim<3>, Scalar>;
using AddExpression =
    decltype(std::declval<Vector &>() + std::declval<Scalar>());
using Expression =
    decltype(std::declval<AddExpression>() * std::declval<Scalar>());
using SliceExpression =
    decltype(std::declval<AddExpression>()[all] + std::declval<Scalar>());

constexpr auto expressionTree = Expression::expression_tree();
constexpr std::string_view expressionTreeView(expressionTree.value,
                                              expressionTree.size());
constexpr auto sliceExpressionTree = SliceExpression::expression_tree();
constexpr std::string_view sliceExpressionTreeView(
    sliceExpressionTree.value, sliceExpressionTree.size());

static_assert(expressionTreeView == "Qmul(Qadd(Tensor, Scalar), Scalar)");
static_assert(
    sliceExpressionTreeView ==
    "Qadd(Slice(Qadd(Tensor, Scalar)), Scalar)");

TEST(NamedAST, ExposesTheCompileTimeTreeAtRuntime)
{
    Vector values{Scalar(1), Scalar(2), Scalar(3)};
    const auto expression = (values + Scalar(4)) * Scalar(2);

    EXPECT_EQ(expression.ast(), expressionTreeView);
    EXPECT_EQ(expression.ast(), "Qmul(Qadd(Tensor, Scalar), Scalar)");
}

TEST(NamedAST, SliceRemainsAVisibleNode)
{
    Vector values{Scalar(1), Scalar(2), Scalar(3)};
    const auto expression = (values + Scalar(4))[all] + Scalar(2);

    EXPECT_EQ(expression.ast(), sliceExpressionTreeView);
}

} // namespace
