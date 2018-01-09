#include <iostream>
#include "csvparser.h"

int main() {
    std::ifstream file("1.txt");
    CSVParser<char, int> parser(&file, 0);
    for (std::tuple<char, int> rs: parser) {
        std::cout << rs << std::endl;
    }
    return 0;
}