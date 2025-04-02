#include "config.h"
#include <QuBLAS.h>
#include <fstream>
#include <iostream>
#include <random>

size_t randint(size_t N)
{
    std::random_device rd;                       // Obtain a random number from hardware
    std::mt19937 gen(rd());                      // Seed the generator
    std::uniform_int_distribution<> distr(1, N); // Define the range
    return distr(gen);                           // Generate a random number in the range [1, N]
}

int main()
{
    // verification params
    size_t N_FRAMES = 100;
    // fstreams
    std::ofstream f_i_data("../Input_Files/Adder_Tree_i_data.txt");
    std::ofstream f_o_data("../Comparison_Files/Adder_Tree_o_data.txt");
    for (size_t frame = 0; frame < N_FRAMES; frame++)
    {
        fxp::QU_IN i_data;
        fxp::QU_OUT o_data;
        i_data.fill();
        o_data = Qreduce<fxp::TreeQu<4, fxp::QU_IN_1>>(i_data);
        for (size_t input = 0; input < 4; input++)
        {
            f_i_data << i_data[input].toString();
        }
        f_i_data << std::endl;
        // write output data to Comparison_Files/add_o_data.txt
        f_o_data << o_data.toString() << std::endl;
    }
    return 0;

    using type = Qu_s<intBits<-2>, fracBits<5>, isSigned<true>, QuMode<TRN::TCPL>, OfMode<SAT::ZERO>>;
    TRN::TCPL::value;
}