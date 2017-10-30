#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}

//#include "mytrit.h"
//
//using namespace trit_set;
//
//int main() {
//    TritSet C;
//    TritSet A(5);
//    TritSet B(5);
//    A[1] = True;
//    A[3] = False;
//    B = A;
//    B[2] = False;
//    B[3] = True;
//    A[0] = True;
//    std::cout << "TritSet A: " << A << std::endl;
//    std::cout << "TritSet B: " << B << std::endl;
//    std::cout << "TritSet A logical length: " << A.length() << std::endl;
//    std::cout << "Number of trits 'True' in TritSet A: " << A.cardinality(True) << std::endl;
//    std::cout << "~A: " << ~A << std::endl;
//    std::cout << "A | B: " << (A | B) << std::endl;
//    std::cout << "A & B: " << (A & B) << std::endl;
//    A.trim(2);
//    std::cout << "TritSet A trim: " << A << std::endl;
//    B.shrink();
//    std::cout << "TritSet B shrink: " << B << std::endl;
//    //A[1000000] = True;
//    //std::cout << "TritSet A have 10000 trit: " << A << std::endl;
//
//    for(TritSet::reference t : B)
//    {
//        std::cout << t << std::endl;
//    }
//
//    TritSet::TritIterator tritIterator = A.begin();
//    while(tritIterator != A.end()) {
//       std::cout << tritIterator << std::endl;
//       ++tritIterator;
//    }
//
//    return 0;
//}