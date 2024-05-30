#include "QuBLAS.h"
#include <bitset>
#include <chrono>
#include <iostream>
#include <utility>
#include <vector>



int main() {

  // 10 types
  using type1 = Qu<intBits<9>, fracBits<9>>;
  using type2 = Qu<intBits<5>, fracBits<9>>;
  using type3 = Qu<intBits<6>, fracBits<9>>;
  using type4 = Qu<intBits<7>, fracBits<9>>;
  using type5 = Qu<intBits<8>, fracBits<9>>;
  using type6 = Qu<intBits<9>, fracBits<9>>;
  using type7 = Qu<intBits<10>, fracBits<9>>;
  using type8 = Qu<intBits<11>, fracBits<9>>;
  using type9 = Qu<intBits<12>, fracBits<9>>;
  using type10 = Qu<intBits<13>, fracBits<9>>;


  using typeX = Qu<intBits<5>, fracBits<11>>;

  constexpr type1 a = 0.5;
  constexpr type2 b = 0.4;
  constexpr type3 c = 0.3;
  constexpr type4 d = 0.2;
  constexpr type5 e = 0.1;
  constexpr type6 f = 0.6;
  constexpr type7 g = 0.7;
  constexpr type8 h = 0.8;
  constexpr type9 i = 0.9;
  constexpr type10 j = 1.0;

  typeX x = 0.5;

  // get the function

  auto res = ANUS::Poly<a,b,c,d,e,f,g,h,i,j>::execute(x);

  res.display();

  using seg = ANUS::segments<0.1,0.5,0.7>;

  using poly1= ANUS::Poly<a,b,c>;
  using poly2= ANUS::Poly<d,e,f>;
  using poly3= ANUS::Poly<g,h,i>;
  using poly4= ANUS::Poly<a,j>;

  using polys = ANUS::polys<poly1,poly2,poly3,poly4>;

  using approx = ANUS::Approx<seg,polys>;


  auto res2 = approx::execute(x);

  res2.display();

  auto min = type1::minVal;
  auto max = type1::maxVal;

  std::cout << "min: " << min << std::endl;
  std::cout << "max: " << max << std::endl;

  // print the binary representation of the min and max values
  std::cout << "min: " << std::bitset<32>(min) << std::endl;
  std::cout << "max: " << std::bitset<32>(max) << std::endl;

  


 



 

 
 



}