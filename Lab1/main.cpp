#include <iostream>
#include "mytrit.h"

int main() {
    trit_set::TritSet A(10);
    trit_set::TritSet B(10);
    A = ~A;

    return 0;
}