#include <cstdlib>
#include <cmath>
#include <cstdint>
#define uint unsigned int

namespace trit_set {
    enum Trit {Unknown, True, False};

    class TritSet {
    private:
        uint *begin; // Указатель на начало
        size_t size; // Размер
        size_t new_pos; // Для выделения памяти
    public:
        class reference {
        private:
            friend class TritSet;
            uint *ptr;
            int index;
            TritSet *tset;
            reference(uint *, int, TritSet *);
        public:
            reference& operator=(Trit);
            reference& operator=(const reference&);
        };
        TritSet(size_t); // Конструктор
        ~TritSet(); // Деструктор
        Trit operator[](size_t) const;
        reference operator[](size_t);
        friend TritSet operator&(const TritSet, const TritSet);
        friend TritSet operator|(const TritSet, const TritSet);
        friend TritSet operator~(const TritSet);
    };
    TritSet operator&(const TritSet, const TritSet);
    TritSet operator|(const TritSet, const TritSet);
    TritSet operator~(const TritSet);
}