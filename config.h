#pragma once
#include "QuBLAS.h"
#include <cmath>
namespace fxp {
using QU_IN_1 = Qu<intBits<-2>, fracBits<5>, isSigned<true>, QuMode<TRN::TCPL>, OfMode<SAT::ZERO>>;
using QU_OUT = Qu<intBits<-2>, fracBits<4>, isSigned<true>, QuMode<TRN::TCPL>, OfMode<SAT::ZERO>>;
using QU_IN = Qu<dim<4>, QU_IN_1>;

template <int intAugBits, typename QuType>
using AugQu = Qu<intBits<QuType::intB + intAugBits>, fracBits<QuType::fracB>, isSigned<QuType::isS>, QuMode<typename QuType::QuM>, OfMode<typename QuType::OfM>>;

template <typename QuT1, typename QuT2>
using MulQu = Qu<intBits<QuT1::intB + QuT2::intB>, fracBits<QuT1::fracB + QuT2::fracB>, isSigned<QuT1::isS>, QuMode<typename QuT1::QuM>, OfMode<typename QuT1::OfM>>;

constexpr int ceil_log2(int x)
{
    if (x <= 0)
        return -1;
    int result = 0;
    --x;
    while (x > 0)
    {
        x >>= 1;
        ++result;
    }
    return result;
}
template <size_t N, typename QuType>
using TreeQu = AugQu<ceil_log2(N), QuType>;
} // namespace fxp