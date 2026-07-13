#include "QuBLAS.h"

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

using namespace QuBLAS;

namespace {

using OrderedScalar =
    Qu<intBits<5>, fracBits<3>, isSigned<false>, QuMode<RND::CONV>,
       OfMode<SAT::ZERO>>;
using ShuffledScalar =
    Qu<OfMode<SAT::ZERO>, QuMode<RND::CONV>, fracBits<3>, intBits<5>,
       isSigned<false>>;
using ExpectedScalar =
    Qu_s<intBits<5>, fracBits<3>, isSigned<false>, QuMode<RND::CONV>,
         OfMode<SAT::ZERO>>;

struct IgnoredCompatibilityTag
{};

static_assert(std::is_same_v<OrderedScalar, ExpectedScalar>);
static_assert(std::is_same_v<ShuffledScalar, ExpectedScalar>);
static_assert(std::is_same_v<Qu<OrderedScalar>, OrderedScalar>);
static_assert(std::is_same_v<
              Qu<IgnoredCompatibilityTag, intBits<5>, fracBits<3>,
                 isSigned<false>, QuMode<RND::CONV>, OfMode<SAT::ZERO>>,
              ExpectedScalar>);

using FirstDuplicateWins =
    Qu<intBits<5>, intBits<9>, fracBits<3>, fracBits<7>, isSigned<false>,
       isSigned<true>, QuMode<RND::CONV>, QuMode<TRN::SMGN>,
       OfMode<SAT::ZERO>, OfMode<SAT::TCPL>>;
static_assert(std::is_same_v<FirstDuplicateWins, OrderedScalar>);

using DefaultScalar = Qu<>;
static_assert(DefaultScalar::intB == defaultIntBits);
static_assert(DefaultScalar::fracB == defaultFracBits);
static_assert(DefaultScalar::isS == defaultIsSigned);

static_assert(sizeof(Qu<QuMode<RND::POS_INF>>) > 0);
static_assert(sizeof(Qu<QuMode<RND::NEG_INF>>) > 0);
static_assert(sizeof(Qu<QuMode<RND::ZERO>>) > 0);
static_assert(sizeof(Qu<QuMode<RND::INF>>) > 0);
static_assert(sizeof(Qu<QuMode<RND::CONV>>) > 0);
static_assert(sizeof(Qu<QuMode<TRN::TCPL>>) > 0);
static_assert(sizeof(Qu<QuMode<TRN::SMGN>>) > 0);
static_assert(sizeof(Qu<OfMode<SAT::TCPL>>) > 0);
static_assert(sizeof(Qu<OfMode<SAT::ZERO>>) > 0);
static_assert(sizeof(Qu<OfMode<SAT::SMGN>>) > 0);
static_assert(sizeof(Qu<OfMode<WRP::TCPL>>) > 0);

using NegativeFrac = Qu<fracBits<-3>, intBits<6>>;
static_assert(NegativeFrac::intB == 6);
static_assert(NegativeFrac::fracB == -3);

using WrapWithSaturation =
    Qu<OfMode<WRP::TCPL_SAT<2>>, fracBits<1>, isSigned<true>, intBits<4>,
       QuMode<TRN::TCPL>>;
static_assert(std::is_same_v<typename WrapWithSaturation::OfM_t,
                             WRP::TCPL_SAT<2>>);

enum class SaturationBits : unsigned
{
    one = 1
};

struct StructuralSaturationBits
{
    size_t value;
    constexpr explicit operator size_t() const { return value; }
    constexpr auto operator<=>(const StructuralSaturationBits &) const =
        default;
};

// TCPL_SAT has historically been template<auto>; keep all of these NTTP
// spellings viable. N == 0 retains AP_WRAP's ordinary two's-complement wrap.
using WrapZero = Qu<intBits<4>, fracBits<0>,
                    OfMode<WRP::TCPL_SAT<0>>>;
using WrapEnum = Qu<intBits<4>, fracBits<0>,
                    OfMode<WRP::TCPL_SAT<SaturationBits::one>>>;
using WrapFloating = Qu<intBits<4>, fracBits<0>,
                        OfMode<WRP::TCPL_SAT<2.0>>>;
using WrapOversized = Qu<intBits<4>, fracBits<0>,
                        OfMode<WRP::TCPL_SAT<100>>>;
using WrapStructural =
    Qu<intBits<4>, fracBits<0>,
       OfMode<WRP::TCPL_SAT<StructuralSaturationBits{2}>>>;

using TensorFromTags =
    Qu<dim<2, 3>, OfMode<SAT::ZERO>, fracBits<3>, intBits<5>,
       isSigned<false>, QuMode<RND::CONV>>;
using TensorFromScalar = Qu<dim<2, 3>, OrderedScalar>;
using ExpectedTensor = Qu_s<dim<2, 3>, OrderedScalar>;
static_assert(std::is_same_v<TensorFromTags, ExpectedTensor>);
static_assert(std::is_same_v<TensorFromScalar, ExpectedTensor>);

using RawTensorTypeList =
    TypeList<intBits<5>, fracBits<3>, isSigned<false>, QuMode<RND::CONV>,
             OfMode<SAT::ZERO>>;
using TensorFromTypeList = Qu<dim<2, 3>, RawTensorTypeList>;
static_assert(std::is_same_v<
              TensorFromTypeList,
              Qu_s<dim<2, 3>, RawTensorTypeList>>);

using TypeListElementTensor =
    Qu<dim<2>, TypeList<OrderedScalar, OrderedScalar>>;
using TypeListTensorExpression = decltype(Qadd(
    std::declval<const TypeListElementTensor &>(),
    std::declval<const TypeListElementTensor &>()));
static_assert(
    std::is_same_v<typename TypeListTensorExpression::size, dim<2>>);

using OtherScalar =
    Qu<fracBits<2>, OfMode<SAT::TCPL>, intBits<4>, QuMode<TRN::SMGN>,
       isSigned<true>>;
using ComplexViaQu = Qu<OrderedScalar, OtherScalar>;
using ComplexViaAlias = Qcomplex<OrderedScalar, OtherScalar>;
using WrappedComplex = Qu<ComplexViaQu>;
static_assert(std::is_same_v<ComplexViaQu, ComplexViaAlias>);
static_assert(std::is_same_v<WrappedComplex, ComplexViaQu>);

using OutputReal =
    Qu<intBits<7>, fracBits<4>, isSigned<true>, QuMode<RND::POS_INF>,
       OfMode<SAT::TCPL>>;
using OutputImag =
    Qu<intBits<6>, fracBits<2>, isSigned<true>, QuMode<TRN::SMGN>,
       OfMode<SAT::ZERO>>;
using OutputTags =
    TypeList<OfMode<SAT::TCPL>, fracBits<4>, QuMode<RND::POS_INF>,
             intBits<7>, isSigned<true>>;
using CanonicalOutputTags =
    TypeList<intBits<7>, fracBits<4>, isSigned<true>,
             QuMode<RND::POS_INF>, OfMode<SAT::TCPL>>;

static_assert(std::is_same_v<MergerArgsWrapper<OutputReal>,
                             CanonicalOutputTags>);
static_assert(std::is_same_v<MergerArgsWrapper<OutputTags>, OutputTags>);
static_assert(std::is_same_v<
              MergerArgsWrapper<MergerArgsWrapper_s<
                  intBits<7>, fracBits<4>, isSigned<true>,
                  QuMode<RND::POS_INF>, OfMode<SAT::TCPL>>>,
              CanonicalOutputTags>);

static_assert(std::is_same_v<TypeAt<0, TypeList<OrderedScalar, OtherScalar>>,
                             OrderedScalar>);
static_assert(std::is_same_v<TypeAt<1, TypeList<OrderedScalar, OtherScalar>>,
                             OtherScalar>);
static_assert(TypeList<OrderedScalar, OtherScalar>::size == 2);

// These declarations deliberately instantiate every legacy output-tag wrapper.
using AddFromIndividualTags = decltype(Qadd<
    OfMode<SAT::TCPL>, fracBits<4>, QuMode<RND::POS_INF>, intBits<7>,
    isSigned<true>>(std::declval<OrderedScalar>(),
                    std::declval<OtherScalar>()));
using AddFromTypeList = decltype(Qadd<OutputTags>(
    std::declval<OrderedScalar>(), std::declval<OtherScalar>()));
using AddFromQuType = decltype(Qadd<OutputReal>(
    std::declval<OrderedScalar>(), std::declval<OtherScalar>()));
static_assert(std::is_same_v<AddFromIndividualTags, OutputReal>);
static_assert(std::is_same_v<AddFromTypeList, OutputReal>);
static_assert(std::is_same_v<AddFromQuType, OutputReal>);

using MulFromIndividualTags = decltype(Qmul<
    isSigned<true>, intBits<7>, OfMode<SAT::TCPL>,
    QuMode<RND::POS_INF>, fracBits<4>>(
    std::declval<OrderedScalar>(), std::declval<OtherScalar>()));
using MulFromTypeList = decltype(Qmul<OutputTags>(
    std::declval<OrderedScalar>(), std::declval<OtherScalar>()));
using MulFromQuType = decltype(Qmul<OutputReal>(
    std::declval<OrderedScalar>(), std::declval<OtherScalar>()));
using MulFullPrecision = decltype(Qmul<FullPrec>(
    std::declval<OrderedScalar>(), std::declval<OtherScalar>()));
static_assert(std::is_same_v<MulFromIndividualTags, OutputReal>);
static_assert(std::is_same_v<MulFromTypeList, OutputReal>);
static_assert(std::is_same_v<MulFromQuType, OutputReal>);
static_assert(MulFullPrecision::intB == OrderedScalar::intB +
                                            OtherScalar::intB);
static_assert(MulFullPrecision::fracB == OrderedScalar::fracB +
                                             OtherScalar::fracB);

using SubFromTypeList = decltype(Qsub<OutputTags>(
    std::declval<OrderedScalar>(), std::declval<OtherScalar>()));
using DivFromQuType = decltype(Qdiv<OutputReal>(
    std::declval<OrderedScalar>(), std::declval<OtherScalar>()));
static_assert(std::is_same_v<SubFromTypeList, OutputReal>);
static_assert(std::is_same_v<DivFromQuType, OutputReal>);

using ComplexAddTagged = decltype(Qadd<realT<OutputReal>, imagT<OutputImag>>(
    std::declval<ComplexViaQu>(), std::declval<ComplexViaQu>()));
using ComplexAddPair = decltype(Qadd<OutputReal, OutputImag>(
    std::declval<ComplexViaQu>(), std::declval<ComplexViaQu>()));
using ComplexAddDirectTags = decltype(Qadd<
    realT<OfMode<SAT::TCPL>, fracBits<4>, QuMode<RND::POS_INF>,
          intBits<7>, isSigned<true>>,
    imagT<isSigned<true>, OfMode<SAT::ZERO>, intBits<6>,
          QuMode<TRN::SMGN>, fracBits<2>>>(
    std::declval<ComplexViaQu>(), std::declval<ComplexViaQu>()));
using ComplexAddNestedTypeLists = decltype(Qadd<
    realT<CanonicalOutputTags>,
    imagT<TypeList<intBits<6>, fracBits<2>, isSigned<true>,
                   QuMode<TRN::SMGN>, OfMode<SAT::ZERO>>>>(
    std::declval<ComplexViaQu>(), std::declval<ComplexViaQu>()));
using ComplexSubTagged = decltype(Qsub<imagT<OutputImag>, realT<OutputReal>>(
    std::declval<ComplexViaQu>(), std::declval<ComplexViaQu>()));
using ComplexSubPair = decltype(Qsub<OutputReal, OutputImag>(
    std::declval<ComplexViaQu>(), std::declval<ComplexViaQu>()));
using ExpectedOutputComplex = Qcomplex<OutputReal, OutputImag>;
static_assert(std::is_same_v<ComplexAddTagged, ExpectedOutputComplex>);
static_assert(std::is_same_v<ComplexAddPair, ExpectedOutputComplex>);
static_assert(std::is_same_v<ComplexAddDirectTags, ExpectedOutputComplex>);
static_assert(
    std::is_same_v<ComplexAddNestedTypeLists, ExpectedOutputComplex>);
static_assert(std::is_same_v<ComplexSubTagged, ExpectedOutputComplex>);
static_assert(std::is_same_v<ComplexSubPair, ExpectedOutputComplex>);

using ComplexBasicMul = decltype(Qmul<BasicComplexMul<
    adbcT<OutputImag>, acT<OutputReal>, bcT<OutputImag>,
    acbdT<OutputReal>, adT<OutputImag>, bdT<OutputReal>>>(
    std::declval<ComplexViaQu>(), std::declval<ComplexViaQu>()));
using ComplexThreeMul = decltype(Qmul<TFComplexMul<
    BCT<OutputImag>, abT<OutputReal>, badT<OutputImag>,
    cdT<OutputReal>, ABT<OutputReal>, baT<OutputImag>,
    abcT<OutputReal>, cdbT<OutputImag>>>(
    std::declval<ComplexViaQu>(), std::declval<ComplexViaQu>()));
static_assert(isScalar<ComplexBasicMul>);
static_assert(isScalar<ComplexThreeMul>);

using RealComplexMulTagged = decltype(Qmul<
    imagT<OutputImag>, realT<OutputReal>>(
    std::declval<OrderedScalar>(), std::declval<ComplexViaQu>()));
using ComplexRealMulPair = decltype(Qmul<OutputReal, OutputImag>(
    std::declval<ComplexViaQu>(), std::declval<OrderedScalar>()));
using ComplexRealDivPair = decltype(Qdiv<OutputReal, OutputImag>(
    std::declval<ComplexViaQu>(), std::declval<OrderedScalar>()));
static_assert(std::is_same_v<RealComplexMulTagged, ExpectedOutputComplex>);
static_assert(std::is_same_v<ComplexRealMulPair, ExpectedOutputComplex>);
static_assert(std::is_same_v<ComplexRealDivPair, ExpectedOutputComplex>);

using TensorAddTagged = decltype(Qadd<OutputTags>(
    std::declval<const TensorFromScalar &>(),
    std::declval<const TensorFromScalar &>()));
using TensorAddQu = decltype(Qadd<OutputReal>(
    std::declval<const TensorFromScalar &>(),
    std::declval<const TensorFromScalar &>()));
using TensorScalarMul = decltype(Qmul<OutputReal>(
    std::declval<const TensorFromScalar &>(),
    std::declval<OrderedScalar>()));
#ifndef QUBLAS_COMPARE_PRE_FIX_BASELINE
using NestedTensorExpression = decltype(Qadd<OutputReal>(
    std::declval<TensorAddTagged>(), std::declval<TensorScalarMul>()));
#endif
static_assert(std::is_same_v<typename TensorAddTagged::size, dim<2, 3>>);
static_assert(std::is_same_v<typename TensorAddQu::size, dim<2, 3>>);
static_assert(std::is_same_v<typename TensorScalarMul::size, dim<2, 3>>);
#ifndef QUBLAS_COMPARE_PRE_FIX_BASELINE
static_assert(std::is_same_v<typename NestedTensorExpression::size, dim<2, 3>>);
#endif

TEST(LegacyTemplateSyntax, AllEstablishedFormsRemainUsable)
{
    OrderedScalar a = 1.25;
    OtherScalar b = 0.5;
    ComplexViaQu complexA{a, b};
    ComplexViaAlias complexB{b, a};

    [[maybe_unused]] auto scalarAdd = Qadd<OutputTags>(a, b);
    [[maybe_unused]] auto scalarMul = Qmul<OutputReal>(a, b);
    [[maybe_unused]] auto scalarSub = Qsub<
        fracBits<4>, isSigned<true>, OfMode<SAT::TCPL>, intBits<7>,
        QuMode<RND::POS_INF>>(a, b);
    [[maybe_unused]] auto scalarDiv = Qdiv<OutputReal>(a, b);

    WrapZero wrapZero = 17;
    WrapEnum wrapEnum = 17;
    WrapFloating wrapFloating = 17;
    WrapOversized wrapOversized = 17;
    WrapStructural wrapStructural = 17;
    EXPECT_DOUBLE_EQ(wrapZero.toDouble(), -15.0);
    EXPECT_DOUBLE_EQ(wrapEnum.toDouble(), 1.0);
    EXPECT_DOUBLE_EQ(wrapFloating.toDouble(), 9.0);
    EXPECT_DOUBLE_EQ(wrapOversized.toDouble(), 15.0);
    EXPECT_DOUBLE_EQ(wrapStructural.toDouble(), 9.0);

    [[maybe_unused]] auto complexAdd =
        Qadd<imagT<OutputImag>, realT<OutputReal>>(complexA, complexB);
    [[maybe_unused]] auto complexPairAdd =
        Qadd<OutputReal, OutputImag>(complexA, complexB);
    [[maybe_unused]] auto complexMul = Qmul<BasicComplexMul<
        bdT<OutputReal>, adbcT<OutputImag>, acT<OutputReal>,
        acbdT<OutputReal>, bcT<OutputImag>, adT<OutputImag>>>(complexA,
                                                             complexB);
    [[maybe_unused]] auto realComplexMul =
        Qmul<realT<OutputReal>, imagT<OutputImag>>(a, complexA);

    using ComplexVector = Qu<dim<3>, ComplexViaQu>;
    ComplexVector complexVector{complexA, complexB, complexA};
    auto complexVectorMul = Qmul<TFComplexMul<
        abT<OutputReal>, cdT<OutputReal>, baT<OutputImag>,
        abcT<OutputReal>, cdbT<OutputImag>, badT<OutputImag>,
        ABT<OutputReal>, BCT<OutputImag>>>(complexVector, complexVector);
    [[maybe_unused]] const auto complexVectorElement = complexVectorMul[0];

    TensorFromScalar tensor;
    TensorFromScalar tensorResult = Qadd<OutputTags>(tensor, tensor);
#ifndef QUBLAS_COMPARE_PRE_FIX_BASELINE
    tensorResult = Qadd<OutputReal>(Qmul<OutputReal>(tensor, a), tensor);
#endif

    Qu<dim<5>, OrderedScalar> oddVector{a, b, a, b, a};
    [[maybe_unused]] auto reduceDefault = Qreduce<>(a, b, a, b);
    [[maybe_unused]] auto reduceOneType = Qreduce<OutputReal>(oddVector);
    [[maybe_unused]] auto reduceTypeList =
        Qreduce<TypeList<OutputReal, OutputImag>>(oddVector);
    [[maybe_unused]] auto reduceTypePack =
        Qreduce<OutputReal, OutputImag>(a, b, a, b, a);

    SUCCEED();
}

} // namespace
