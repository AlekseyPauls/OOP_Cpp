#include <iostream>
#include "mytrit.h"

int main() {
    trit_set::TritSet A(10);
    trit_set::TritSet B(10);
    A[1] = trit_set::True;
    std::cout << A.length() << "   " << A.cardinality(trit_set::True);
    std::unordered_map< trit_set::Trit, size_t, std::hash<int> > m = A.cardinality();

    return 0;
}