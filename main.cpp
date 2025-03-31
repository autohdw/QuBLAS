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

    // using type1 = Qu<intBits<-3>, fracBits<7>, isSigned<true>, QuMode<TRN::SMGN>, OfMode<WRP::TCPL>>; 
    // using type2 = Qu<intBits<0>, fracBits<4>, isSigned<true>, QuMode<TRN::SMGN>, OfMode<WRP::TCPL>>; 

    // type1 a;
    // a.data.data = -7;
    // type2 b;
    // // b.data.data = -512;

    // a.display();
    // b=a;
    // b.display();

     
    using type1 = Qu<intBits<2>, fracBits<4>, isSigned<true>, QuMode<TRN::TCPL>, OfMode<SAT::ZERO>>; 
    using type2 = Qu<intBits<-3>, fracBits<7>, isSigned<true>, QuMode<TRN::TCPL>, OfMode<SAT::ZERO>>; 

    type1 a;
 
    type2 b;
    
    
     auto cmp = a==b;
     auto cmp2 = a!=b;

 

     

}