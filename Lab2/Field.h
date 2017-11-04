#pragma once
#include "Cage.h"
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>

namespace gol {

    class Field {
    private:
        int height;
        int length;
        Cage **cages;
    public:
        Field(int height, int length);
        ~Field();
        void save_to_file(std::ofstream* fout);
        void load_from_file(std::ifstream* fin);
        void get_picture();
        int get_cages_number();
        void clear_cage(int i, int j);
        void clear_all_cages();
        void populate_cage(int i, int j);
        void random_populate();
        char state_prediction(int i, int j);
        std::string next_step();

//        struct indices // Двусвязный циклический список
//        {
//            int index; // поле данных
//            struct indices *next; // указатель на следующий элемент
//            struct indices *prev; // указатель на предыдущий элемент
//        };
//        indices* create_index(int size, int index);
//        indices* addelem(Field::indices* ind, int index);

    };
}