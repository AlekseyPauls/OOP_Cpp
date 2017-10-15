#include <cstdlib>
#include <cmath>
#include <cstdint>
#include <unordered_map>
#define uint unsigned int

namespace trit_set {
    enum Trit {Unknown, True, False};

    class TritSet {
    private:
        uint *begin; // Указатель на начало
        size_t size; // Размер
        size_t new_pos; // Для выделения памяти
        size_t last_chahged_trit; // Последний измененный трит
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
        TritSet(const TritSet&); // Конструктор копии
        ~TritSet(); // Деструктор
        TritSet& operator=(const TritSet&);
        Trit operator[](size_t) const;
        reference operator[](size_t);
        void shrink();
        void trim(size_t);
        size_t length();
        size_t cardinality(Trit);
        std::unordered_map< Trit, size_t, std::hash<int> > cardinality();
        friend TritSet operator&(const TritSet, const TritSet);
        friend TritSet operator|(const TritSet, const TritSet);
        friend TritSet operator~(const TritSet);
    };
    TritSet operator&(const TritSet, const TritSet);
    TritSet operator|(const TritSet, const TritSet);
    TritSet operator~(const TritSet);

    class my_exception {
    public:
        std::string message;
        my_exception(const std::string& msg);
    };
}