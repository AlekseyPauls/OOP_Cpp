#include <cstdlib>
#include <cmath>
#include <cstdint>
#define uint unsigned int

class TritSet {
private:
    uint *begin; // Указатель на начало
    int size; // Размер
    uint *last; // Последний элемент
public:
    TritSet(int); // Конструктор
    ~TritSet(); // Деструктор

};