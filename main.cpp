#include "QuBLAS.h"
#include <bitset>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>



int main() {

  // 10 types



 

  using type1 = Qu<intBits<9>, fracBits<3>>;
  using type2 = Qu<intBits<8>, fracBits<2>>;
  using type3 = Qu<intBits<7>, fracBits<4>>;
  using type4 = Qu<intBits<6>, fracBits<5>>;
  using type5 = Qu<intBits<5>, fracBits<6>>;
  using type6 = Qu<intBits<4>, fracBits<7>>;


  using c_t_1 = Complex<type1, type2>;
  using c_t_2 = Complex<type3, type4>;

  
  c_t_1 a = {1, 2};
  c_t_1 b = {3, 4};

 
  
   auto c = a * b;

   c.display();



 
 

 

 
 

}