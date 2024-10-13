
#include "QuBLAS.h"
#include <algorithm>
#include <bitset>
#include <iostream>
#include <sys/types.h>

using namespace QuBLAS;

 

template <size_t shift, size_t val>
bool check(const std::string &shifted, const std::string &raw)
{
    for (size_t i = 0; i < val - shift; i++)
    {
        if (shifted[shifted.size() - 1 - i] != raw[raw.size() - 1 - i - shift])
        {
            return false;
        }
    }

    return true;
}

int main()
{

    ArbiInt<70> a;

    a.fill();

    auto raw = a.toBinary();

    auto shifted = staticShiftRight<10>(a).toBinary();

    bool result = check<10, 70>(shifted, raw);

    std::cout << raw  << std::endl;
    std::cout << shifted << std::endl;
    std::cout << result << std::endl;

}
