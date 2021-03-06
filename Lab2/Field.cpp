#include "Field.h"

namespace gol {

    Field::Field(int length, int height) : length(length), height(height) {
        cages = new Cage* [length];
        for (int i = 0; i < length; i++) {
            cages[i] = (Cage*)operator new(sizeof(Cage) * height);
            for (int j = 0; j < height; j++) {
                new( &cages[i][j]) Cage('.');
            }
        }
        prev_step = nullptr;
    }

    Field::~Field() {
        for (int i = 0; i < length; i++) {
            operator delete(cages[i]);
        }
        operator delete(cages);
        if (prev_step != nullptr) {
            for (int i = 0; i < length; i++) {
                operator delete(prev_step[i]);
            }
        }
    }

    void Field::save_to_file(std::ofstream* fout) {
        *fout << length << std::endl;
        *fout << height << std::endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < length; j++) {
                char state = cages[j][i].get_state();
                *fout << state;
            }
            *fout << std::endl;
        }
    }

    void Field::load_from_file(std::ifstream* fin) {
        std::string s;
        getline(*fin, s);
        int new_length = atoi(s.c_str());
        getline(*fin, s);
        int new_height = atoi(s.c_str());
        if (new_length == length, new_height == height) {
            for (int i = 0; i < height; i++) {
                getline(*fin, s);
                for (int j = 0; j < length; j++) {
                    cages[j][i].set_state(s[j]);
                }
            }
        } else {
            for (int i = 0; i < length; i++) {
                operator delete(cages[i]);
            }
            operator delete(cages);
            length = new_length;
            height = new_height;
            cages = new Cage* [length];
            for (int i = 0; i < length; i++) {
                cages[i] = (Cage*)operator new(sizeof(Cage) * height);
                for (int j = 0; j < height; j++) {
                    new( &cages[i][j]) Cage('.');
                }
            }
            for (int i = 0; i < height; i++) {
                getline(*fin, s);
                for (int j = 0; j < length; j++) {
                    cages[j][i].set_state(s[j]);
                }
            }
        }
    }

    void Field::step_back() {
        if (prev_step != nullptr) {
            for (int i = 0; i < length; i++) {
                operator delete(cages[i]);
            }
            operator delete(cages);
            cages = prev_step;
            prev_step = nullptr;
        } else {

        }
    }

    void Field::get_picture() {

        printf("\n   |");
        for (int i = 0; i < length; i++) {
            printf("%3c", 65 + i);
        }
        printf(" |");
        for (int i = 0; i < length; i++) {
            printf("   ");
        }
        printf("\n___|");
        for (int i = 0; i < length; i++) {
            printf("___");
        }
        printf("_|\n   |");
        for (int i = 0; i < length; i++) {
            printf("   ");
        }
        printf(" |\n");
        for (int i = 0; i < height; i++) {
            printf("%2d |", i);
            for (int j = 0; j < length; j++) {
                char state = cages[j][i].get_state();
                printf("%3c", state);
            }
            if (i != length - 1) {
                printf(" |\n   |");
                for (int i = 0; i < length; i++) {
                    printf("   ");
                }
                printf(" |\n");
            } else {
                printf(" |\n___|");
                for (int i = 0; i < length; i++) {
                    printf("___");
                }
                printf("_|\n");
            }
        }
        printf("\n");
    }

    int Field::get_cages_number() {
        return length * height;
    }

    void Field::clear_cage(int i, int j) {
        cages[i][j].set_state('.');
    }

    void Field::clear_all_cages() {
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < height; j++) {
                cages[i][j].set_state('.');
            }
        }
    }

    void Field::populate_cage(int i, int j) {
        cages[i][j].set_state('o');
    }

    void Field::random_populate() {
        for(;;) {
            int i = rand() % length;
            int j = rand() % height;
            if (cages[i][j].get_state() == '.') {
                //cages[i][j].set_state('*');
                cages[i][j].set_state('o');
                return;
            }
        }
    }

    std::string Field::next_step() {
        if (prev_step != nullptr) {
            for (int i = 0; i < length; i++) {
                operator delete(prev_step[i]);
            }
            operator delete(prev_step);
        }
        prev_step = cages;
        Cage** new_cages = new Cage* [length];
        for (int i = 0; i < length; i++) {
            new_cages[i] = (Cage*)operator new(sizeof(Cage) * height);
            for (int j = 0; j < height; j++) {
                new( &new_cages[i][j]) Cage('.');
            }
        }
        int void_flag = 0;
        char new_state;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < length; j++) {
                new_state = state_prediction(i, j);
                new_cages[i][j].set_state(new_state);
                if (new_state == 'o') {
                    void_flag = 1;
                }
            }
        }
        int identity_flag = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < length; j++) {
                if (cages[i][j].get_state() != new_cages[i][j].get_state()) {
                    identity_flag = 1;
                    break;
                }
            }
        }
        if (identity_flag == 1 && void_flag == 1) {
            cages = new_cages;
            return "";
        } else if (void_flag == 0) {
                return "There are no living cages";
        } else {
            return "Life configuration has not changed";
        }
    }

    char Field::state_prediction(int i, int j) {
        int living_neighbors = 0;
        int real_n;
        int real_m;
        for (int n = i - 1; n <= i + 1; n ++) {
            for (int m = j - 1; m <= j + 1; m++) {
                if (n == i && m == j) {
                    continue;
                }
                real_n = n;
                real_m = m;
                if (n == -1) real_n = height - 1;
                if (n == height) real_n = 0;
                if (m == -1) real_m = length - 1;
                if (m == length) real_m = 0;

                if (cages[real_n][real_m].get_state() == 'o') {
                    living_neighbors++;
                }
            }
        }
        if (cages[i][j].get_state() == '.' && living_neighbors == 3) {
            //return '*';
            return 'o';
        }
        else if (cages[i][j].get_state() == 'o' && (living_neighbors < 2 || living_neighbors > 3)) {
                return '.';
        } else {
            return cages[i][j].get_state();
        }
    }

}