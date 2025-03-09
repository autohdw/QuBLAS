#include "QuBLAS.h"
#include <iostream>
#include <string>
using namespace QuBLAS;


int main()
{

    // ArbiInt<80> a = -2565169217536;

    // a.display();

    // std::string str = "111111111111111110110011101101001100000010000000000000000000000000000000000000000";

    // // transform the last 64 bits of the string into a 64-bit integer
    // uint64_t b_low = std::bitset<64>(str.substr(16)).to_ullong() * 2;
 

    // ArbiInt<80> b;
    // b.data[0] = b_low;
    // b.data[1] = -1;

    // b.display();


    // std::cout << "a > b: " << (a > b) << std::endl;

    ArbiInt<80> a = -123;
    ArbiInt<150> b = -1233;

    a.display();
    b.display();

    std::cout << "a < b: " << (a < b) << std::endl;
    
}