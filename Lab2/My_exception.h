#pragma once
#include <cstdlib>
#include <string>

namespace gol {
    class my_exception {
    public:
        std::string message;
        my_exception(const std::string& msg);
    };
}