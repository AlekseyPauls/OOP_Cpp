#include "Field.h"
#include "My_exception.h"
#include <Windows.h>
#include <conio.h>


namespace gol {
    class Game {
    private:
        Field field;
        int steps_counter;

        void start();
        void step();
        void step(int N);
        void reset();
        void back();
        void clear(int i, int j);
        void set(int i, int j);
        void random_set(int number);
        void save(std::string filename);
        void load(std::string filename);
        void auto_game(int delay);
        void help();
    public:
        Game(int length, int height);
        ~Game();
        void exec_command(std::string command);
    };
}
