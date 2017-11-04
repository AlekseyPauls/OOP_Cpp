#include "Game.h"

int main() {
    std::string str;
    try {
        gol::Game gm(10, 10);
        for (int i = 0; i < 10; i++) {
            std::getline(std::cin, str);
            gm.exec_command(str);
        }
    } catch (gol::my_exception &e) {
        printf("%s", e.message.c_str());
    }
    return 0;
}