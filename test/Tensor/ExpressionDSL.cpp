#include <gtest/gtest.h>

#include <type_traits>

#include "QuBLAS.h"

namespace {

using Scalar = Qu<intBits<8>, fracBits<0>>;
using Vector = Qu<dim<3>, Scalar>;

constexpr auto composeNamedIntermediate(Vector &values)
{
    auto inner = values + Scalar(1);
    return inner + Scalar(2);
}

constexpr auto sliceNamedIntermediate(Vector &values)
{
    auto inner = values + Scalar(1);
    return inner[all];
}

constexpr auto composeNamedSlice(Vector &values)
{
    auto inner = values + Scalar(1);
    auto view = inner[all];
    return view + Scalar(2);
}

constexpr auto composeNamedOwner(Vector &values)
{
    auto snapshot = own(values);
    return snapshot + Scalar(1);
}

constexpr auto sliceNamedOwner(Vector &values)
{
    auto snapshot = own(values);
    return snapshot[all];
}

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

TEST(ExpressionDSL, ReturnedExpressionOwnsNamedIntermediateNodes)
{
    Vector values{Scalar(1), Scalar(2), Scalar(3)};
    auto expression = composeNamedIntermediate(values);

    values[0] = Scalar(10);

    EXPECT_DOUBLE_EQ(expression[0].toDouble(), 13.0);
    EXPECT_DOUBLE_EQ(expression[2].toDouble(), 6.0);
}

TEST(ExpressionDSL, ReturnedSlicesOwnNamedIntermediateNodes)
{
    Vector values{Scalar(1), Scalar(2), Scalar(3)};
    auto slice = sliceNamedIntermediate(values);
    auto expression = composeNamedSlice(values);

    values[0] = Scalar(10);
    values[2] = Scalar(30);

    EXPECT_DOUBLE_EQ(slice[0].toDouble(), 11.0);
    EXPECT_DOUBLE_EQ(slice[2].toDouble(), 31.0);
    EXPECT_DOUBLE_EQ(expression[0].toDouble(), 13.0);
    EXPECT_DOUBLE_EQ(expression[2].toDouble(), 33.0);
}

TEST(ExpressionDSL, OwnCanSnapshotATerminalLvalue)
{
    Vector values{Scalar(1), Scalar(2), Scalar(3)};
    auto expression = own(values) + Scalar(1);

    values[0] = Scalar(20);

    EXPECT_DOUBLE_EQ(expression[0].toDouble(), 2.0);
    EXPECT_DOUBLE_EQ(expression[2].toDouble(), 4.0);
}

TEST(ExpressionDSL, RefCanBorrowANamedIntermediateExplicitly)
{
    Vector values{Scalar(1), Scalar(2), Scalar(3)};
    auto inner = values + Scalar(1);
    auto ownedNode = inner + Scalar(2);
    auto borrowedNode = ref(inner) + Scalar(2);

    inner = values + Scalar(5);
    values[0] = Scalar(10);

    EXPECT_DOUBLE_EQ(ownedNode[0].toDouble(), 13.0);
    EXPECT_DOUBLE_EQ(borrowedNode[0].toDouble(), 17.0);
}

TEST(ExpressionDSL, NamedOwnPolicyPersistsAcrossCompositionAndSlicing)
{
    Vector values{Scalar(1), Scalar(2), Scalar(3)};
    auto expression = composeNamedOwner(values);
    auto view = sliceNamedOwner(values);

    values[0] = Scalar(20);

    EXPECT_DOUBLE_EQ(expression[0].toDouble(), 2.0);
    EXPECT_DOUBLE_EQ(expression[2].toDouble(), 4.0);
    EXPECT_DOUBLE_EQ(view[0].toDouble(), 1.0);
    EXPECT_DOUBLE_EQ(view[2].toDouble(), 3.0);
}

TEST(ExpressionDSL, ScalarPoliciesAreTransparentTensorOperands)
{
    Vector values{Scalar(1), Scalar(2), Scalar(3)};
    Scalar offset(1);
    auto ownedOffset = own(offset);
    auto borrowedOffset = ref(offset);
    auto ownedExpression = values + ownedOffset;
    auto borrowedExpression = values + borrowedOffset;

    offset = Scalar(5);

    EXPECT_DOUBLE_EQ(ownedExpression[0].toDouble(), 2.0);
    EXPECT_DOUBLE_EQ(borrowedExpression[0].toDouble(), 6.0);
    EXPECT_DOUBLE_EQ(Qadd(ownedOffset, Scalar(2)).toDouble(), 3.0);
    EXPECT_DOUBLE_EQ(Qadd(borrowedOffset, Scalar(2)).toDouble(), 7.0);
}

} // namespace
