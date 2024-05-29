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

  auto res = ANUS::poly<a,b,c,d,e,f,g,h,i,j>(x);



  res.display();



}