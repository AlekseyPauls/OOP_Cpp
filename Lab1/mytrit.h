#include <cstdlib>
#include <cmath>
#include <cstdint>
#include <unordered_map>
#include <iostream>

#define uint unsigned int

namespace trit_set {
    enum Trit {Unknown, True, False};

    class TritSet {
    private:
        uint *start; // Указатель на начало
        size_t size; // Размер
        size_t new_pos; // Для выделения памяти
        size_t last_chahged_trit; // Последний измененный трит
    public:
        class reference {
        private:
            friend class TritSet;
            //friend bool operator==(TritSet::reference& one, TritSet::reference& two);
            uint *ptr;
            int index;
            TritSet *tset;
        public:
            reference(uint *trit_ptr, int trit_index, TritSet * trit_set);
            reference& operator=(Trit t);
            reference& operator=(const reference& other);
            bool operator==(const TritSet::reference& one);
            friend std::ostream& operator<<(std::ostream& os, const reference& ref);
        };
        class TritIterator {
        private:
            friend class reference;
            friend bool operator!=(TritIterator const& one, TritIterator const& two);
            reference ref;
        public:
            TritIterator(reference& r);
            TritIterator(const TritIterator& it);
            //bool operator!=(TritIterator const& other) const;
            bool operator==(TritIterator const& other) const;
            TritIterator& operator=(const TritIterator& other);
            reference operator*() const;
            TritIterator& operator++();
            friend std::ostream& operator<<(std::ostream& os, const TritIterator& it);
        };
        TritSet();
        TritSet(size_t set_size); // Конструктор
        TritSet(const TritSet& tset); // Конструктор копии
        ~TritSet(); // Деструктор
        TritSet& operator=(const TritSet& tset);
        Trit operator[](size_t position) const;
        reference operator[](size_t position);
        void shrink();
        void trim(size_t last_index);
        size_t length();
        size_t cardinality(Trit value);
        std::unordered_map< Trit, size_t, std::hash<int> > cardinality();
        TritIterator begin();
        TritIterator end();
        friend TritSet operator&(const TritSet A, const TritSet B);
        friend TritSet operator|(const TritSet A, const TritSet B);
        friend TritSet operator~(const TritSet A);
        friend std::ostream& operator<<(std::ostream& os, const TritSet& tset);
    };
    TritSet operator&(const TritSet A, const TritSet B);
    TritSet operator|(const TritSet A, const TritSet B);
    TritSet operator~(const TritSet A);

    bool operator!=(TritSet::TritIterator const& one, TritSet::TritIterator const& two);
    std::ostream& operator<<(std::ostream& os, const TritSet& tset);
    std::ostream& operator<<(std::ostream& os, const TritSet::reference& ref);
    std::ostream& operator<<(std::ostream& os, const TritSet::TritIterator& it);

    class my_exception {
    public:
        std::string message;
        my_exception(const std::string& msg);
    };
}