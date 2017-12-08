#include "my_exeption.h"

namespace wf {
    my_exception::my_exception() : message("") {}

    my_exception::my_exception(const std::string &msg) : message(msg) {}

    void my_exception::get_message() {
        std::cout << message.c_str();
    }
}
