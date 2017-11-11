#include "Game.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//int main() {
//    std::string str;
//    gol::Game gm(10, 10);
//    for (int i = 0; i < 10; i++) {
//        std::getline(std::cin, str);
//        try {
//            gm.exec_command(str);
//        } catch (gol::my_constructor_error& ex) {
//            ex.get_message();
//        } catch (gol::my_invalid_argument& ex) {
//            ex.get_message();
//        } catch (gol::my_command_error& ex) {
//            ex.get_message();
//        } catch (gol::my_exception& ex) {
//            ex.get_message();
//        }
//    }
//    return 0;
//}