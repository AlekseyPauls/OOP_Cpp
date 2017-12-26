#include <iostream>
#include "csvparser.h"

int main() {
    std::ifstream file("test.csv");
    CSVParser<int, int> parser(&file, 0);
    for (std::tuple<int, int> rs: parser) {
        std::cout << rs << std::endl;
    }
    return 0;
}