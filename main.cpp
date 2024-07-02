#include "QuBLAS.h"
#include <bitset>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>

using namespace QuBLAS;

// QuT mu0
using mu0_QuT = Qu<intBits<3>, fracBits<5>>;

// QuT mu
using mu_QuT = Qu<intBits<4>, fracBits<8>>;

constexpr int TxAntNum = 4;

int main()
{

    Qu<dim<2 * TxAntNum>, mu_QuT> vec1;
    Qu<dim<2 * TxAntNum>, mu_QuT> vec2;

    vec1 = vec2;

    return 0;
}


