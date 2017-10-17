#include "mytrit.h"

namespace trit_set {

    TritSet::TritSet(size_t set_size) : size(set_size), new_pos(0), last_chahged_trit(0) {
        uint real_size = ceil((double)(set_size + 1) * 2 / 8 / sizeof(uint));
        begin = (uint *) malloc(sizeof(uint) * real_size);
        if (begin == NULL) {
            throw my_exception("Not enough memory for storage TritSet of this length");
        }
        for (size_t i = 0; i < real_size; i++) {
            begin[i] = 0;
        }
    }

    TritSet::TritSet(const TritSet &A) : size(A.size), new_pos(A.new_pos), last_chahged_trit(A.last_chahged_trit) {
        uint real_size = ceil((double)A.size * 2 / 8 / sizeof(uint))  + 1;
        begin = (uint *) malloc(sizeof(uint) * real_size);
        if (begin == NULL) {
            throw my_exception("Not enough memory for storage TritSet of this length");
        }
        for (size_t i = 0; i < real_size; i++) {
            begin[i] = A.begin[i];
        }
    }

    TritSet::~TritSet() {
        free(begin);
        begin = 0;
    }

    TritSet& TritSet::operator=(const TritSet& tset) {
        if (this != &tset) {
            free(begin);
            uint real_size = ceil((double)(tset.size + 1) * 2 / 8 / sizeof(uint));
            begin = (uint *) malloc(sizeof(uint) * real_size);
            if (begin == NULL) {
                throw my_exception("Not enough memory for storage TritSet of this length");
            }
            for (size_t i = 0; i < real_size; i++) {
                begin[i] = tset.begin[i];
            }
            size = tset.size;
            new_pos = tset.new_pos;
            last_chahged_trit = tset.last_chahged_trit;
        }
        return *this;
    }

    Trit TritSet::operator[](size_t position) const {
        if (position < 0 || position > size) {
            throw my_exception("Error: trit index is outside tritset");
        }
        uint *trit_ptr = begin + (position + 1) * 2 / 8 / sizeof(uint);
        int trit_index = position - (position * 2 / 8 / sizeof(uint))*sizeof(uint) * 8 / 2;
        int t = (*trit_ptr >> trit_index * 2) & (uint)3;
        if (t == 0) {return Unknown;}
        if (t == 1) {return True;} else {return False;}
    }

    TritSet::reference TritSet::operator[](size_t position) {
        if (position <= size) {
            this->last_chahged_trit = position;
            uint *trit_ptr = begin + (position + 1) * 2 / 8 / sizeof(uint);
            int trit_index = position - (position * 2 / 8 / sizeof(uint))*sizeof(uint) * 8 / 2;
            TritSet::reference ref(trit_ptr, trit_index, this);
            return ref;
        } else {
            new_pos = position;
            TritSet::reference ref(NULL, 0, this);
            return ref;
        }
    }

    TritSet::reference::reference(uint *trit_ptr, int trit_index, TritSet *trit_set) :
            ptr(trit_ptr), index(trit_index), tset(trit_set) {}

    TritSet::reference& TritSet::reference::operator=(Trit t) {
        if (this->tset->new_pos > this->tset->size && t == Unknown) {
            return *this;
        }
        if (this->tset->new_pos > this->tset->size) {
            uint new_real_size = ceil((double)(this->tset->new_pos + 1) * 2 / 8 / sizeof(uint));
            uint *tmp = (uint *) malloc(sizeof(uint) * new_real_size);
            if (tmp == NULL) {
                throw my_exception("Not enough memory for storage TritSet of length including a new element");
            }
            for (size_t  i = 0; i < new_real_size; i++) {
                tmp[i] = 0;
            }
            for (size_t i = 0; i <= this->tset->new_pos; i++) {
                size_t ptr_number = i * 2 / sizeof(uint) / 8;
                size_t trit_pos = i - ptr_number * sizeof(uint) * 8 / 2;
                if (i < this->tset->size) {
                    uint t = (this->tset->begin[ptr_number] >> 2 * trit_pos) & (uint)3;
                    tmp[ptr_number] = tmp[ptr_number] & ~((uint)3 << 2 * trit_pos);
                    tmp[ptr_number] = tmp[ptr_number] | (t << 2 * trit_pos);
                } else {
                    tmp[ptr_number] = tmp[ptr_number] & ~((uint)3 << 2 * trit_pos);
                    std::cout << tmp[ptr_number] << ' ';
                }
            }
            free(this->tset->begin);
            this->tset->begin = tmp;
            this->tset->size = this->tset->new_pos;
            this->tset->last_chahged_trit = this->tset->new_pos;
            this->ptr = this->tset->begin + (this->tset->size * 2 / 8 / sizeof(uint)) * sizeof(uint) ;
            this->index = this->tset->size - (this->tset->size * 2/ 8 / sizeof(uint)) * sizeof(uint) * 8 /2;
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
            uint new_real_size = ceil((double)(this->tset->new_pos + 1) * 2 / 8 / sizeof(uint));
            uint *tmp = (uint *) malloc(sizeof(uint) * new_real_size);
            if (tmp == NULL) {
                throw my_exception("Not enough memory for storage TritSet of length including a new element");
            }
            for (size_t i = 0; i < this->tset->new_pos; i++) {
                size_t ptr_number = i * 2 / sizeof(uint) / 8;
                size_t trit_pos = i - ptr_number * sizeof(uint) * 8 / 2;
                if (i < this->tset->size) {
                    uint t = (this->tset->begin[ptr_number] >> 2 * trit_pos) & ((uint) 3);
                    this->tset->begin[ptr_number] = this->tset->begin[ptr_number] | (t << 2 * trit_pos);
                } else {
                    this->tset->begin[ptr_number] = this->tset->begin[ptr_number] | (0 << 2 * trit_pos);
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
        this->tset->last_chahged_trit = this->tset->new_pos;
        return *this;
    }

    void TritSet::shrink() {
        uint real_size = ceil((double)(this->last_chahged_trit + 1) * 2 / 8 / sizeof(uint));
        uint *new_begin = (uint*) malloc(real_size * sizeof(uint));
        if (new_begin == NULL) {
            throw my_exception("Not enough memory for storage shrinked TritSet");
        }
        for (size_t i = 0; i < last_chahged_trit; i++) {
            size_t ptr_number = i * 2 / sizeof(uint) / 8;
            size_t trit_pos = i - ptr_number * sizeof(uint) * 8 / 2;
            uint t = (begin[ptr_number] >> 2 * trit_pos) & (uint)3;
            new_begin[ptr_number] = new_begin[ptr_number] | (t << 2 * trit_pos);
        }
        free(begin);
        begin = new_begin;
        size = last_chahged_trit;
    }

    void TritSet::trim(size_t last_index) {
        uint real_size = ceil((double)(last_index + 1) * 2 / 8 / sizeof(uint));
        uint *new_begin = (uint*) malloc(real_size * sizeof(uint));
        if (new_begin == NULL) {
            throw my_exception("Not enough memory for storage trimed TritSet");
        }
        for (size_t i = 0; i < last_index; i++) {
            size_t ptr_number = i * 2 / sizeof(uint) / 8;
            size_t trit_pos = i - ptr_number * sizeof(uint) * 8 / 2;
            uint t = (begin[ptr_number] >> 2 * trit_pos) & (uint)3;
            new_begin[ptr_number] = new_begin[ptr_number] | (t << 2 * trit_pos);
        }
        free(begin);
        begin = new_begin;
        size = last_index;
    }

    size_t TritSet::length() {
        for (size_t i = this->size - 1; i >= 0; i--) {
            size_t ptr_number = i * 2 / sizeof(uint) / 8;
            size_t trit_pos = i - ptr_number * sizeof(uint) * 8 / 2;
            uint t = (begin[ptr_number] >> 2 * trit_pos) & (uint)3;
            if (t != 0) {
                return i + 1;
            }
        }
        return 0;
    }

    size_t TritSet::cardinality(Trit value) {
        size_t trit_counter = 0;
        for (size_t i = 0; i < this->size; i++) {
            size_t ptr_number = i * 2 / sizeof(uint) / 8;
            size_t trit_pos = i - ptr_number * sizeof(uint) * 8 / 2;
            uint t = (begin[ptr_number] >> 2 * trit_pos) & (uint)3;
            if (t == value) {
                trit_counter++;
            }
        }
        return trit_counter;
    }

    std::unordered_map< Trit, size_t, std::hash<int> > TritSet::cardinality() {
        std::unordered_map< Trit, size_t, std::hash<int> > m;
        size_t trits_true = this->cardinality(True);
        size_t trits_false = this->cardinality(False);
        size_t trits_unknown = this->cardinality(Unknown);
        m[True] = trits_true;
        m[False] = trits_false;
        m[Unknown] = trits_unknown;
        return m;
    };

    TritSet operator&(const TritSet A, const TritSet B) {
        if (A.size >= B.size) {
            TritSet C(A.size);
            for (size_t i = 0; i < A.size; i++) {
                size_t ptr_number = i * 2 / sizeof(uint) / 8;
                size_t trit_pos = i - ptr_number * sizeof(uint) * 8 / 2;
                if (i < B.size) {
                    uint t_A = (A.begin[ptr_number] >> 2 * trit_pos) & ((uint) 3);
                    uint t_B = (B.begin[ptr_number] >> 2 * trit_pos) & ((uint) 3);
                    if (t_A == 2 || t_B == 2) {
                        C.begin[ptr_number] = C.begin[ptr_number] | ((uint)2 << 2 * trit_pos);
                    } else if (t_A == t_B && t_A == 1) {
                        C.begin[ptr_number] = C.begin[ptr_number] | ((uint)1 << 2 * trit_pos);
                    }
                } else {
                    uint t = (A.begin[ptr_number] >> 2 * trit_pos) & (uint)3;
                    C.begin[ptr_number] = C.begin[ptr_number] | (t << 2 * trit_pos);
                }
            }
            C.last_chahged_trit = B.size;
            return C;
        } else {
            TritSet C(B.size);
            for (size_t i = 0; i < A.size; i++) {
                size_t ptr_number = i * 2 / sizeof(uint) / 8;
                size_t trit_pos = i - ptr_number * sizeof(uint) * 8 / 2;
                if (i < A.size) {
                    uint t_A = (A.begin[ptr_number] >> 2 * trit_pos) & ((uint) 3);
                    uint t_B = (B.begin[ptr_number] >> 2 * trit_pos) & ((uint) 3);
                    if (t_A == 2 || t_B == 2) {
                        C.begin[ptr_number] = C.begin[ptr_number] | ((uint)2 << 2 * trit_pos);
                    } else if (t_A == t_B == 1) {
                        C.begin[ptr_number] = C.begin[ptr_number] | ((uint)1 << 2 * trit_pos);
                    }
                } else {
                    uint t = (A.begin[ptr_number] >> 2 * trit_pos) & (uint)3;
                    C.begin[ptr_number] = C.begin[ptr_number] | (t << 2 * trit_pos);
                }
            }
            C.last_chahged_trit = B.size;
            return C;
        }
    }
    TritSet operator|(const TritSet A, const TritSet B) {
        if (A.size >= B.size) {
            TritSet C(A.size);
            for (size_t i = 0; i < A.size; i++) {
                size_t ptr_number = i * 2 / sizeof(uint) / 8;
                size_t trit_pos = i - ptr_number * sizeof(uint) * 8 / 2;
                if (i < B.size) {
                    uint t_A = (A.begin[ptr_number] >> 2 * trit_pos) & ((uint) 3);
                    uint t_B = (B.begin[ptr_number] >> 2 * trit_pos) & ((uint) 3);
                    if (t_A == 1 || t_B == 1) {
                        C.begin[ptr_number] = C.begin[ptr_number] | ((uint)1 << 2 * trit_pos);
                    } else if (t_A == t_B && t_A == 2) {
                        C.begin[ptr_number] = C.begin[ptr_number] | ((uint)2 << 2 * trit_pos);
                    }
                } else {
                    uint t = (A.begin[ptr_number] >> 2 * trit_pos) & (uint)3;
                    C.begin[ptr_number] = C.begin[ptr_number] | (t << 2 * trit_pos);
                }
            }
            C.last_chahged_trit = B.size;
            return C;
        } else {
            TritSet C(B.size);
            for (size_t i = 0; i < A.size; i++) {
                size_t ptr_number = i * 2 / sizeof(uint) / 8;
                size_t trit_pos = i - ptr_number * sizeof(uint) * 8 / 2;
                if (i < A.size) {
                    uint t_A = (A.begin[ptr_number] >> 2 * trit_pos) & ((uint) 3);
                    uint t_B = (B.begin[ptr_number] >> 2 * trit_pos) & ((uint) 3);
                    if (t_A == 1 || t_B == 1) {
                        C.begin[ptr_number] = C.begin[ptr_number] | ((uint)1 << 2 * trit_pos);
                    } else if (t_A == t_B && t_A == 2) {
                        C.begin[ptr_number] = C.begin[ptr_number] | ((uint)2 << 2 * trit_pos);
                    }
                } else {
                    uint t = (A.begin[ptr_number] >> 2 * trit_pos) & (uint)3;
                    C.begin[ptr_number] = C.begin[ptr_number] | (t << 2 * trit_pos);
                }
            }
            C.last_chahged_trit = B.size;
            return C;
        }
    }

    TritSet operator~(const TritSet A) {
        TritSet C(A.size);
        for (size_t i = 0; i < A.size; i++) {
            size_t ptr_number = i * 2 / sizeof(uint) / 8;
            size_t trit_pos = i - ptr_number * sizeof(uint) * 8 / 2;
            uint t = (~A.begin[ptr_number] >> 2 * trit_pos) & ((uint)3);
            if (t != 3) { // 3 - инвертированный 0 (Unknown)
                C.begin[ptr_number] = C.begin[ptr_number] & ~((uint) 3 << 2 * trit_pos);
                C.begin[ptr_number] = C.begin[ptr_number] | (t << 2 * trit_pos);
            }
        }
        C.last_chahged_trit = C.size;
        return C;
    }

    std::ostream& operator<<(std::ostream& os, const TritSet& tset) {
        std::string trit;
        std::string s = ", ";
        for (size_t i = 0; i < tset.size; i++)
        {
            size_t ptr_number = i * 2 / sizeof(uint) / 8;
            size_t trit_pos = i - ptr_number * sizeof(uint) * 8 / 2;
            uint t = (tset.begin[ptr_number] >> 2 * trit_pos) & ((uint) 3);
            if (t == 0) {
                trit = "Unknown";
            } else if (t == 1) {
                trit = "True";
            } else {
                trit = "False";
            }
            if (i != tset.size - 1) {
                os << trit << s;
            } else {
                os << trit;
            }
        }
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const TritSet::reference& ref) {
        std::string trit;
        std::string s = ", ";
        uint t = (*ref.ptr >> 2 * ref.index) & ((uint) 3);
        if (t == 0) {
            trit = "Unknown";
        } else if (t == 1) {
            trit = "True";
        } else {
            trit = "False";
        }
        os << trit;
        return os;
    }

    my_exception::my_exception(const std::string& msg) : message(msg) {}
}