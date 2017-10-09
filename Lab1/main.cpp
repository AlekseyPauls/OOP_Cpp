#include <iostream>
#include "mytrit.h"

int main() {
    trit_set::TritSet A(10);
    trit_set::TritSet B(10);
    A[5] = trit_set::False;

    A = A & B;

    return 0;
}