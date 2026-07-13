#include <gtest/gtest.h>

#include <type_traits>

#include "QuBLAS.h"

namespace {

using Scalar = Qu<intBits<8>, fracBits<0>>;
using Vector = Qu<dim<3>, Scalar>;

constexpr bool elementwiseClosuresAreConstantExpressions()
{
    Vector left{Scalar(1), Scalar(2), Scalar(3)};
    Vector right{Scalar(4), Scalar(5), Scalar(6)};
    const auto expression = (left + right) * Scalar(2);
    const auto result = expression.eval();
    return expression[0] == Scalar(10) && result[2] == Scalar(18);
}

static_assert(elementwiseClosuresAreConstantExpressions());

TEST(ExpressionDSL, EvalMaterializesTheWholeLazyTree)
{
    Vector left{Scalar(1), Scalar(2), Scalar(3)};
    Vector right{Scalar(4), Scalar(5), Scalar(6)};

    auto expression = Qabs((left + right) * Scalar(-2));
    auto result = expression.eval();

    static_assert(std::is_same_v<typename decltype(result)::size, dim<3>>);
    EXPECT_DOUBLE_EQ(result[0].toDouble(), 10.0);
    EXPECT_DOUBLE_EQ(result[1].toDouble(), 14.0);
    EXPECT_DOUBLE_EQ(result[2].toDouble(), 18.0);
}

TEST(ExpressionDSL, FreeEvalHasTheSameMaterializationSemantics)
{
    Vector values{Scalar(1), Scalar(2), Scalar(3)};
    auto result = eval(values + Scalar(7));

    EXPECT_DOUBLE_EQ(result[0].toDouble(), 8.0);
    EXPECT_DOUBLE_EQ(result[2].toDouble(), 10.0);
}

TEST(ExpressionDSL, MaterializedValueStopsFollowingNamedOperands)
{
    Vector values{Scalar(1), Scalar(2), Scalar(3)};
    auto expression = values + Scalar(1);
    auto snapshot = expression.eval();

    values[0] = Scalar(20);

    EXPECT_DOUBLE_EQ(expression[0].toDouble(), 21.0);
    EXPECT_DOUBLE_EQ(snapshot[0].toDouble(), 2.0);
}

} // namespace
