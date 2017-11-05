#include "Game.h"

int main() {
    std::string str;
    gol::Game gm(10, 10);
    for (int i = 0; i < 10; i++) {
        std::getline(std::cin, str);
        gm.exec_command(str);
    }
    return 0;
}