#include "csvparser.h"


template <class ... Args>
CSVParser<Args...>::Iter::Iter(std::tuple< Args... > *ptr, int pos, std::vector< std::tuple< Args... > > *text) :
        ptr(ptr), pos(pos), text(text) {}

template <class ... Args>
bool CSVParser<Args...>::Iter::operator!=(const CSVParser::Iter & other) const {
    return pos != other.pos;
}

template <class ... Args>
const CSVParser<Args...>::Iter& CSVParser<Args...>::Iter::operator++ () {
    pos++;
    ptr = &text[pos];
    return *this;
}

template <class ... Args>
std::tuple< Args... >& CSVParser<Args...>::Iter::operator*(){
    return *ptr;
}

template <class ... Args>
CSVParser<Args...>::CSVParser() : delimiter(','), row_delimiter('\n'), quotechar('"') {}

template <class ... Args>
CSVParser<Args...>::CSVParser(std::ifstream *s, int skiped_lines) : delimiter(','), row_delimiter('\n'), quotechar('"') {
    std::string str;
    std::tuple< Args... > t;
    for (int i = 0; ; i++) {
        if (str == "") {
            break;
        }
        if (i > skiped_lines - 1) {
            getline(*s, str, row_delimiter);
            parseLine(str, *t);
            text.push_back(t);
        }
    }
}

template <class ... Args>
CSVParser<Args...>::CSVParser(std::ifstream *s, int skiped_lines, char delimiter, char row_delimiter, char quotechar)
        : delimiter(','), row_delimiter('\n'), quotechar('"') {
    std::string str;
    std::tuple< Args... > t;
    for (int i = 0; ; i++) {
        if (str == "") {
            break;
        }
        if (i > skiped_lines - 1) {
            getline(*s, str, row_delimiter);
            parseLine(str, *t);
            text.push_back(t);
        }
    }
}

template <class ... Args>
CSVParser<Args...>::~CSVParser() {

}

template <class ... Args>
void CSVParser<Args...>::parseLine(std::string s, std::tuple< Args... > * t) {
    std::string arg;
    for (int i = 0; ; i++) {
        if (s == "") {
            break;
        }
        arg = s.substr(0, s.find(delimiter));
        if (arg.size() == 1) {
            std::get<i>(t) = arg[0];
        } else if (strtoint(arg) != -1) {
            std::get<i>(t) = strtoint(arg);
        } else if (strtodouble(arg) != -1) {
            std::get<i>(t) = strtodouble(arg);
        } else {
            std::get<i>(t) = arg;
        }
        s = s.substr(s.find(delimiter) + 1, s.size()); // ?
    }
}

template <class ... Args>
int CSVParser<Args...>::strtoint(std::string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] < 48 || s[i] > 57) {
            return -1;
        }
    }
    return atoi(s.c_str());
}

template <class ... Args>
double CSVParser<Args...>::strtodouble(std::string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] < 48 || (s[i] > 57 && s[i] != 78)) {
            return -1;
        }
    }
    return atof(s.c_str());
}

template <class ... Args>
void CSVParser<Args...>::change_config(char delim = ',', char row_delim = '\n', char quotech = '"') {
    delimiter = delim;
    row_delimiter = row_delim;
    quotechar = quotech;
}

template <class ... Args>
CSVParser<Args...>::Iter CSVParser<Args...>::begin() const {
    return Iter(&text[0], 0, &text);
}

template <class ... Args>
CSVParser<Args...>::Iter CSVParser<Args...>::end() const {
    return Iter(&text[text.size() - 1], text.size() - 1, &text);
}
