#include "QuBLAS.h"
#include <bitset>
#include <iostream>
#include <utility>
#include <chrono>

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

    using mat_t = Qu<dim<32, 32>, type1>;
    mat_t mat1;
    mat_t mat2;

    using vec_t = Qu<dim<32>, type2>;
    vec_t vec1;
    vec_t vec2;



    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            mat1[i, j] = 1 + randomGaussian();
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            mat2[i, j] = 1 + randomGaussian();
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < 32; i++)
    {
        vec2[i] = 1 + randomGaussian();
    }



    for (int i = 0; i < 32; i++)
    {
        vec1[i] = 1 + randomGaussian_divSqrt2();
    }

    auto start = std::chrono::high_resolution_clock::now();
    Qgramul(mat2, mat1);

    // mat2.display();

    // Qgemv(vec2, mat1, vec1);

    // vec2.display();

    // Qpotrf(mat2);

    // mat2.display();

    // Qpotrs(mat2, vec2);

    // vec2.display();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Execution time: " << duration << " microseconds" << std::endl;
}