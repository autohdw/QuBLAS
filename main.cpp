#include "QuBLAS.h"

int main()
{

    using type1 = apFixed<intBits<8>, fracBits<10>>;
    using type2 = apFixed<intBits<7>, fracBits<6>>;
    using type3 = apFixed<intBits<6>, fracBits<7>>;
    using type4 = apFixed<intBits<5>, fracBits<8>>;

    using list1 = TypeList<type1, type2, type3, type4>;
    using getType = TypeAt<0, list1>;

    using listStack = TypeList<list1, list1, list1, list1>;
    using getTypeStack1 =  TypeAt<0,TypeAt<0, listStack>>;
 
    Qvec<5> a = {1, 2, 3, 4, 5};
    Qmat<3, 5> b = {1, 2.2, 3.1, 4.3, 5.5,
                           1.6, 1.7, 1.8, 1.9, 1.1,
                           1.1, 1.2, 1.3, 1.4, 1.5};

 
    Qvec<3,getTypeStack1> c;
    Qgemv(c, b, a);
    c.display();

    std::cout<<c[0].intB<<" "<<c[0].fracB<<std::endl;


    std::cout<<"====================="<<std::endl;

    Qvec<7,type1> d = {1, 2, 3, 4, 5, 6, 7};

    using shortList = TypeList<type1, type2, type3>;

    auto res = Qreduce(d);

    res.display();

}