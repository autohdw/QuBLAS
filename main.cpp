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
  using type3 = Qu<intBits<2>, fracBits<2>>;
  using type4 = Qu<intBits<7>, fracBits<9>>;
  using type5 = Qu<intBits<8>, fracBits<9>>;
  using type6 = Qu<intBits<9>, fracBits<9>>;
  using type7 = Qu<intBits<10>, fracBits<9>>;
  using type8 = Qu<intBits<11>, fracBits<9>>;
  using type9 = Qu<intBits<12>, fracBits<9>>;
  using type10 = Qu<intBits<13>, fracBits<9>>;


  using vec_t_1 = Qu<dim<3>, type1>;
  using vec_t_2 = Qu<dim<3>, type2>;

  vec_t_1 vec1 = {1, 2, 3};
  vec_t_2 vec2 = {1, 2, 3};

  auto vec3 = Qadd<type3>(vec1, vec2);

  vec3.display();
 

}