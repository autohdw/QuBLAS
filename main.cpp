#include "QuBLAS.h"
#include <bitset>
#include <iostream>
#include <utility>
#include <chrono>
#include <vector>

struct GaussianGenerator
{

    std::mt19937 rng;
    // 标准高斯分布
    std::normal_distribution<double> distribution;

    GaussianGenerator(double mean = 0.0, double stddev = 1.0) : distribution(mean, stddev)
    {
        auto seed = 1234;
        rng.seed(seed);
    }
    double operator()()
    {
        return distribution(rng);
    }
};

static GaussianGenerator gaussianGenerator;
static GaussianGenerator gaussianGenerator_divSqrt2(0.0, std::sqrt(0.5));

inline double randomGaussian()
{
    return gaussianGenerator();
}

inline double randomGaussian_divSqrt2()
{
    return gaussianGenerator_divSqrt2();
}




int main()
{
    using type1 = Qu<intBits<8>, fracBits<10>>;
    using type2 = Qu<intBits<5>, fracBits<10>>;

    using mat_t = Qu<dim<3, 3>, type1>;

    mat_t a = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};

    auto res = Qreduce(a);

    res.display();





 

}