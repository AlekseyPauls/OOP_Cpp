#include <fstream>
#include <iostream>
#include <vector>
#include <tuple>
#include "tuple_print.h"
#include "parser_exceptions.h"

template <class... Args>
class CSVParser {
private:
    char delimiter;
    char row_delimiter;
    char quotechar;
    std::vector< std::tuple< Args... > > text;

    void parseLine(std::string s, std::tuple< Args... > * t);
    int strtoint(std::string s);
    double strtodouble(std::string s);
public:
    class Iter {
    private:
        int pos;
        const std::tuple< Args... > *ptr;
        std::vector< std::tuple< Args... > > *text;
    public:
        Iter(std::tuple< Args... > *ptr, int pos, std::vector< std::tuple< Args... > > *text);
        bool operator!=(const Iter & other) const;
        const Iter& operator++ ();
        std::tuple< Args... >& operator*();
    };

    CSVParser();
    CSVParser(std::ifstream *s, int skiped_lines);
    CSVParser(std::ifstream *s, int skiped_lines, char delimiter, char row_delimiter, char quotechar);
    ~CSVParser();

    void change_config(char delimiter = ',', char row_delimiter = '\n', char quotechar = '"');

    Iter begin() const;
    Iter end() const;
};
