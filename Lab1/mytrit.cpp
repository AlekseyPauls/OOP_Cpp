#include "mytrit.h"

TritSet::TritSet(int set_size) {
    TritSet::begin = (uint*) malloc(sizeof(uint)*(ceil((double)set_size * 2 / 8 / sizeof(uint))));
    TritSet::size = set_size;
}