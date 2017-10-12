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
            TritSet::reference ref(trit_ptr, trit_index, this);
            return ref;
        } else {
            new_pos = position;
            TritSet::reference ref(NULL, 0, this);
            return ref;
        }
    }

    TritSet::reference::reference(uint *trit_ptr, int trit_index, TritSet *trit_set) {
        ptr = trit_ptr;
        index = trit_index;
        tset = trit_set;
        return;
    }

    TritSet::reference& TritSet::reference::operator=(Trit t) { //!!!
        if (this->tset->new_pos > this->tset->size && t == Unknown) {
            return *this;
        }
        if (this->tset->new_pos > this->tset->size) {
            uint old_real_size = ceil((double) this->tset->size * 2 / 8 / sizeof(uint));
            uint new_real_size = ceil((double) (this->tset->size + 1) * 2 / 8 / sizeof(uint));
            uint *tmp = (uint *) malloc(sizeof(uint) * new_real_size);
            for (uint i = 0; i <= new_real_size; i++) {
                if (i < old_real_size) {
                    tmp[i] = this->tset->begin[i];
                } else {
                    tmp[i] = 0;
                }
            }
            free(this->tset->begin);
            this->tset->begin = tmp;
            this->tset->size = this->tset->new_pos;
            this->ptr = this->tset->begin + this->tset->size / sizeof(uint);
            this->index = this->tset->size - (this->tset->size / (sizeof(uint) * 8)) * sizeof(uint) * 8;
        }
        *ptr = *ptr & ~((uint)3 << 2 * index);
        *ptr = *ptr | ((uint)t << 2 * index);
        return *this;
    }

    TritSet::reference& TritSet::reference::operator=(const reference &other) { //!!!
        uint t = (*(this->ptr) >> 2 * this->index) & (~((uint)3));
        if (this->tset->new_pos > this->tset->size && t == Unknown) {
            return *this;
        }
        if (this->tset->new_pos > this->tset->size) {
            uint old_real_size = ceil((double) this->tset->size * 2 / 8 / sizeof(uint));
            uint new_real_size = ceil((double) (this->tset->size + 1) * 2 / 8 / sizeof(uint));
            uint *tmp = (uint *) malloc(sizeof(uint) * new_real_size);
            for (uint i = 0; i <= new_real_size; i++) {
                if (i < old_real_size) {
                    tmp[i] = this->tset->begin[i];
                } else {
                    tmp[i] = 0;
                }
            }
            free(this->tset->begin);
            this->tset->begin = tmp;
            this->tset->size = this->tset->new_pos;
            this->ptr = this->tset->begin + this->tset->size / sizeof(uint);
            this->index = this->tset->size - (this->tset->size / (sizeof(uint) * 8)) * sizeof(uint) * 8;
        }
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

    TritSet operator~(const TritSet A) {
        TritSet C(A.size);
        for (size_t i = 0; i < A.size; i++) {
            size_t ptr_number = i / sizeof(uint) / 2;
            size_t trit_pos = i - ptr_number * sizeof(uint) / 2;
            uint t = (A.begin[ptr_number] >> 2 * trit_pos) & (~((uint)3));
            C.begin[ptr_number] = C.begin[ptr_number] & ~((uint)3 << 2 * trit_pos);
            C.begin[ptr_number] = C.begin[ptr_number] | (t << 2 * trit_pos);
        }
        return C;
    }
}