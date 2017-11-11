#include "Game.h"

namespace gol {

    void Game::start() {
        system("cls");
        printf("\n Current step: %d \n", steps_counter);
        field.get_picture();
        printf("________________________\n\n");
        printf(" Input the next command: ");
    }

    void Game::step() {
        steps_counter++;
        std::string res = field.next_step();
        if (res == "") {
            system("cls");
            printf("\n Current step: %d \n", steps_counter);
            field.get_picture();
            printf("________________________\n\n");
            printf(" Input the next command: ");
        } else {
            system("cls");
            printf("\n Game is ended on %d step: %s\n\n", steps_counter, res.c_str());
            printf(" Load saving game or reset field \n\n");
            printf("________________________\n\n");
            printf(" Input the next command: ");
        }
    }

    void Game::step(int N) {
        std::string res;
        for (int i = 0; i < N; i++) {
            steps_counter++;
            res = field.next_step();
            if (res != "") {
                break;
            }
        }
        if (res == "") {
            system("cls");
            printf("\n Current step: %d \n", steps_counter);
            field.get_picture();
            printf("________________________\n\n");
            printf(" Input the next command: ");
        } else {
            system("cls");
            printf("\n Game is ended on %d step: %s\n\n", steps_counter, res.c_str());
            printf(" Load saving game or reset field \n\n");
            printf("________________________\n\n");
            printf(" Input the next command: ");
        }
    }

    void Game::reset() {
        field.clear_all_cages();
        steps_counter = 0;
        system("cls");
        printf("\n Current step: %d \n", steps_counter);
        field.get_picture();
        printf("________________________\n\n");
        printf(" Input the next command: ");
    }

    void Game::back() {
        if (steps_counter <= 0) {
            throw my_exception("Can't do step back");
        }
        field.step_back();
        steps_counter--;
        system("cls");
        printf("\n Current step: %d \n", steps_counter);
        field.get_picture();
        printf("________________________\n\n");
        printf(" Input the next command: ");
    }

    void Game::clear(int i, int j) {
        field.clear_cage(i, j);
        system("cls");
        printf("\n Current step: %d \n", steps_counter);
        field.get_picture();
        printf("________________________\n\n");
        printf(" Input the next command: ");
    }

    void Game::set(int i, int j) {
        field.populate_cage(i, j);
        system("cls");
        printf("\n Current step: %d \n", steps_counter);
        field.get_picture();
        printf("________________________\n\n");
        printf(" Input the next command: ");
    }

    void Game::random_set(int number) {
        if (number > field.get_cages_number() || number < 0) {
            printf("");
            return;
        }
        for (int i = 0; i < number; i++) {
            field.random_populate();
        }
        system("cls");
        printf("\n Current step: %d \n", steps_counter);
        field.get_picture();
        printf("________________________\n\n");
        printf(" Input the next command: ");
    }

    void Game::save(std::string filename) {
        std::ofstream fout;
        fout.open(filename);
        if (!fout.is_open()) {
            throw my_invalid_argument("save");
        }
        field.save_to_file(&fout);
        fout.close();
        system("cls");
        printf("\n Game has been saving\n\n");
        printf("________________________\n\n");
        printf(" Input the next command: ");
    }

    void Game::load(std::string filename) {
        std::ifstream fin;
        fin.open(filename);
        if (!fin.is_open()) {
            throw my_invalid_argument("save");
        }
        field.load_from_file(&fin);
        fin.close();
        steps_counter = 0;
        system("cls");
        printf("\n Current step: %d \n", steps_counter);
        field.get_picture();
        printf("________________________\n\n");
        printf(" Input the next command: ");
    }

    void Game::auto_game(int delay) {
        for (;;) {
            steps_counter++;
            std::ofstream fout;
            fout.open("prev_step.txt");
            field.save_to_file(&fout);
            fout.close();
            std::string res = field.next_step();
            if (res == "") {
                system("cls");
                printf("\n Current step: %d \n", steps_counter);
                field.get_picture();
            } else {
                system("cls");
                printf("\n Game is ended on %d step: %s\n\n", steps_counter, res.c_str());
                printf(" Load saving game or reset field \n\n");
                printf("________________________\n\n");
                printf(" Input the next command: ");
                break;
            }
            Sleep(delay);
            if (steps_counter % 50 == 0) {
                printf(" If you want to stop auto game press 'Esc'. If not press another key\n");
                char c = getch();
                if (c == 27) {
                    system("cls");
                    printf("\n Current step: %d \n", steps_counter);
                    field.get_picture();
                    printf("________________________\n\n");
                    printf(" Input the next command: ");
                    break;
                }
            }
        }

    }

    void Game::help() {
        system("cls");
        printf("\n There is list of names and descriptions of commands in this game: \n\n");
        printf(" 'start' - show current steps number and live configuration. In the begin of game all cages "
                       "are void\n\n");
        printf(" 'step' - go to the next life configuration (if live cage has less then 2 or more then 3 "
                       "living neighbors it dies, if void cage has 3 living neighbors it becomes alive)\n\n");
        printf(" 'step N' - go to the life configuration which will be through N (integer, N > 0) steps\n\n");
        printf(" 'back' - return to previous life configuration\n\n");
        printf(" 'set XY' - make cage by coordinates X (string, latin letter) and Y (string, integer number)"
                       " live\n\n");
        printf(" 'random_set N' - make N (integer, number of cages) random cages live\n\n");
        printf(" 'clear XY' - make cage by coordinates X (string, latin letter) and Y (string, integer number)"
                       " void\n\n");
        printf(" 'save filename' - save current life configuration to file with name 'filename' \n\n");
        printf(" 'load filename' - load life configuration from file with name 'filename' \n\n");
        printf(" 'help' - get list of commands and their descriptions\n\n");
        printf(" 'auto_game N' - steps are done automatically with N (integer, delay) delay\n\n");
        printf("________________________\n\n");
        printf(" Input the next command: ");
    }

    Game::Game(int length, int height) : field(Field(length, height)), steps_counter(0) {
        system("cls");
        printf("\n                                 #   #   #");
        printf("\n                               #   #   #   #\n\n");
        printf("                 Hello! This is the Conway's 'Game of life'\n\n");
        printf(" To see the fool command list write 'help', to start the game write 'start' \n\n");
        printf("                              Have a good game!\n\n");
        printf("                               #   #   #   #\n");
        printf("                                 #   #   #\n\n");
        printf("________________________\n\n");
        printf(" Input the next command: ");
    }

    Game::~Game() {}

    void Game::exec_command(std::string command) {
        if (command.empty()) {
            throw my_command_error();
        }
        // Command parsing
        int error_flag = 0;
        std::string args[3];
        for (int i = 0; i < command.size(); i++) {
            if (command[i] == ' ') {
                args[0] = command.substr(0, i);
                if (args[0] == "set" || args[0] == "clear") {
                    args[1] = command[i + 1];
                    args[2] = command.substr(i + 2, 100);
                    if (args[1][0] < 65 || args[1][0] > 90) {
                        error_flag = 1;
                    }
                    for (int i = 0; i < args[2].size(); i++) {
                        if (args[2][i] < 48 || args[2][i] > 57 || i > 1) {
                            error_flag = 1;
                            break;
                        }
                    }
                } else if (args[0] == "step" || args[0] == "random_set" || args[0] == "auto_game") {
                    args[1] = command.substr(i + 1, 100);
                    for (int i = 0; i < args[1].size(); i++) {
                        if (args[1][i] < 48 || args[1][i] > 57 || i > 9) {
                            error_flag = 1;
                            break;
                        }
                    }
                } else if (args[0] == "save" || args[0] == "load") {
                    args[1] = command.substr(i + 1, 100);
                } else if (args[0] == "help" || args[0] == "start" || args[0] == "back" || args[0] == "reset"){
                    throw my_invalid_argument(args[0]);
                }
                break;
            }
        }
        if (error_flag == 1) {
            throw my_invalid_argument(args[0]);
        }
        // Command choosing
        if (command == "step") {
            step();
        } else if (command == "help") {
            help();
        } else if (command == "start") {
            start();
        } else if (command == "back") {
            back();
        } else if (command == "reset") {
            reset();
        } else if (args[0] == "step") {
            step(atoi(args[1].c_str()));
        } else if (args[0] == "random_set") {
            random_set(atoi(args[1].c_str()));
        } else if (args[0] == "auto_game") {
            auto_game(atoi(args[1].c_str()));
        } else if (args[0] == "set") {
            set(args[1][0] - 65, atoi(args[2].c_str()));
        } else if (args[0] == "clear") {
            clear(args[1][0] - 65, atoi(args[2].c_str()));
        } else if (args[0] == "save") {
            save(args[1]);
        } else if (args[0] == "load") {
            load(args[1]);
        } else {
            throw my_command_error(command);
        }
    }
}