#pragma once
#include <cstdlib>
#include <string>
#include <iostream>

namespace wf {
    class my_exception {
    public:
        std::string message;
        my_exception();
        my_exception(const std::string& msg);
        void get_message();
    };
}