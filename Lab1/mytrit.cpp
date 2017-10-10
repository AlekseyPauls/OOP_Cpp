#include "mytrit.h"

namespace trit_set {

    TritSet::TritSet(size_t set_size) {
        uint real_size = ceil((double)set_size * 2 / 8 / sizeof(uint));
        begin = (uint *) malloc(sizeof(uint) * real_size);
        for (size_t i = 0; i < real_size; i++) {
            begin[i] = 0;
        }
        size = set_size;
        return;
    }

    TritSet::~TritSet() {
        free(begin);
        return;
    }

    Trit TritSet::operator[](size_t position) const {
        uint *trit_ptr = begin + position / sizeof(uint);
        int trit_index = position - (position / sizeof(uint))*sizeof(uint);
        int t = (*trit_ptr >> trit_index * 2) & (uint)3;
        if (t == 0) {return Unknown;}
        if (t == 1) {return True;} else {return False;}
    }

    TritSet::reference TritSet::operator[](size_t position) {
        if (position <= size) {
            uint *trit_ptr = begin + position / sizeof(uint);
            int trit_index = position - (position / (sizeof(uint) * 8)) * sizeof(uint) * 8;
            TritSet::reference ref(trit_ptr, trit_index);
            return ref;
        } else {
            new_pos = position;
            TritSet::reference ref(NULL, 0);
            return ref;
        }
    }

    TritSet::reference::reference(uint *trit_ptr, int trit_index) {
        ptr = trit_ptr;
        index = trit_index;
        return;
    }

    TritSet::reference& TritSet::reference::operator=(TritSet& tset, Trit t) { //!!!
        if (tset.new_pos > tset.size && t == Unknown) {
            return *this;
        }
        if (tset.new_pos > tset.size) {
            uint old_real_size = ceil((double) tset.size * 2 / 8 / sizeof(uint));
            uint new_real_size = ceil((double) (tset.size + 1) * 2 / 8 / sizeof(uint));
            uint *tmp = (uint *) malloc(sizeof(uint) * new_real_size);
            for (uint i = 0; i <= new_real_size; i++) {
                if (i < old_real_size) {
                    tmp[i] = tset.begin[i];
                } else {
                    tmp[i] = 0;
                }
            }
            free(tset.begin);
            tset.begin = tmp;
            tset.size = tset.new_pos;
            this->ptr = tset.begin + tset.size / sizeof(uint);
            this->index = tset.size - (tset.size / (sizeof(uint) * 8)) * sizeof(uint) * 8;
        }
        *ptr = *ptr & ~((uint)3 << 2 * index);
        *ptr = *ptr | ((uint)t << 2 * index);
        return *this;
    }

    TritSet::reference& TritSet::reference::operator=(TritSet& tset, const reference &other) { //!!!

        this->index = other.index;
        this->ptr = other.ptr;
        return *this;
    }

    TritSet operator&(const TritSet A, const TritSet B) { //!!!
        if (A.size >= B.size) {
            TritSet C(A.size);
            for (size_t i = 0; i < A.size; i++) {
                if (i < B.size) {
                    C.begin[i] = A.begin[i] & B.begin[i];
                } else {
                    C.begin[i] = A.begin[i];
                }
            }
            return C;
        } else {
            TritSet C(B.size);
            for (size_t i = 0; i < B.size; i++) {
                if (i < A.size) {
                    C.begin[i] = A.begin[i] & B.begin[i];
                } else {
                    C.begin[i] = B.begin[i];
                }
            }
            return C;
        }
    }
    TritSet operator|(const TritSet A, const TritSet B) {
        if (A.size >= B.size) {
            TritSet C(A.size);
            for (size_t i = 0; i < A.size; i++) {
                if (i < B.size) {
                    C.begin[i] = A.begin[i] | B.begin[i];
                } else {
                    C.begin[i] = A.begin[i];
                }
            }
            return C;
        } else {
            TritSet C(B.size);
            for (size_t i = 0; i < B.size; i++) {
                if (i < A.size) {
                    C.begin[i] = A.begin[i] | B.begin[i];
                } else {
                    C.begin[i] = B.begin[i];
                }
            }
            return C;
        }
    }

    TritSet TritSet::operator~() const {
        for (size_t i = 0; i < this->size; i++) {

        }
    }
}