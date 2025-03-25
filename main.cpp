#include "QuBLAS.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>

using namespace QuBLAS;


int main()
{
    // constexpr int input_in = 0;
    // constexpr int input_fr = 1;
    // constexpr int output_in = 0;
    // constexpr int output_fr = 1;

    // using input_t = Qu<intBits<input_in>, fracBits<input_fr>,isSigned<false>>;
    // using output_t = Qu<intBits<output_in>, fracBits<output_fr>,isSigned<false>>;

    // input_t input;
    // output_t out;

    // std::ofstream myfile;
    // myfile.open("sin.txt");

    // for (int i = 0; i < (1<<(input_in+input_fr)); i++)
    // {
        
    //     double input_double = input.toDouble();
    //     double output_double = std::atan(input_double);
    //     out = output_double;


    //     myfile << input.toString() <<  ' ' << out.toString() << std::endl;
    //     input.data.data++;
 
    // }

    // myfile.close();
    // return 0;

    using type1 = Qu<intBits<-9>, fracBits<10>, isSigned<true>, QuMode<TRN::SMGN>, OfMode<WRP::TCPL>>; 
    using type2 = Qu<intBits<-8>, fracBits<9>, isSigned<true>, QuMode<TRN::SMGN>, OfMode<WRP::TCPL>>;

    type1 a;
    a.data.data = -2;
    type2 b;
    b.data.data = -1;

    a.display();
    b=a;
    b.display();

     

}