#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <tuple>
#include <iads.h>
#include "parser_exceptions.h"

template<std::size_t> struct int_{};

template <class... Args>
class CSVParser {
private:
    char delimiter;
    char row_delimiter;
    char quotechar;
    std::vector< std::tuple< Args... > > text;

    template <class Tuple, size_t Pos>
    void tuple_app(Tuple& t, int_<Pos>, std::string s) {
        std::string arg;
        if (s == "") {
            //throw tmg;
        }
        arg = s.substr(0, s.find(delimiter));
        if (strtoint(arg) != -1 && typeid(std::get< std::tuple_size<Tuple>::value-Pos >(t)).name() == typeid(int).name()) {
            std::get< std::tuple_size<Tuple>::value-Pos >(t) = strtoint(arg);
        } else if (arg.size() == 1 && typeid(std::get< std::tuple_size<Tuple>::value-Pos >(t)).name() == typeid(char).name()) {
            std::get< std::tuple_size<Tuple>::value-Pos >(t) = arg[0];
        } else if (typeid(std::get< std::tuple_size<Tuple>::value-Pos >(t)).name() == typeid(double).name()) {
            double d = strtod(&arg[0], nullptr);
            std::get< std::tuple_size<Tuple>::value-1 >(t) = d;
        } //else {
        //    std::get< std::tuple_size<Tuple>::value-Pos >(t) = arg;
        //}
        s = s.substr(s.find(delimiter) + 1, s.size());
        return tuple_app(t, int_<Pos-1>(), s);
    }

    template <class Tuple>
    void tuple_app(Tuple& t, int_<1>, std::string s) {
        std::string arg;
        if (s == "") {
            //throw tmg;
        }
        arg = s.substr(0, s.find(delimiter));
        if (strtoint(arg) != -1 && typeid(std::get< std::tuple_size<Tuple>::value-1 >(t)).name() == typeid(int).name()) {
            std::get< std::tuple_size<Tuple>::value-1 >(t) = strtoint(arg);
        } else if (arg.size() == 1 && typeid(std::get< std::tuple_size<Tuple>::value-1 >(t)).name() == typeid(char).name()) {
            std::get< std::tuple_size<Tuple>::value-1 >(t) = arg[0];
        } else if (typeid(std::get< std::tuple_size<Tuple>::value-1 >(t)).name() == typeid(double).name()) {
            double d = strtod(&arg[0], nullptr);
            std::get< std::tuple_size<Tuple>::value-1 >(t) = d;
        } //else {
        //    std::get< std::tuple_size<Tuple>::value-1 >(t) = arg;
        //}
        s = s.substr(s.find(delimiter) + 1, s.size());
        return;
    }

    int strtoint(std::string s) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] < 48 || s[i] > 57) {
                return -1;
            }
        }
        return atoi(s.c_str());
    }
    double strtodouble(std::string s) {
        for (int i = 0; i < s.size(); i++) {
            if (s[i] < 48 || (s[i] > 57 && s[i] != 78)) {
                return -1;
            }
        }
        return atof(s.c_str());
    }
public:
    class Iter {
    private:
        int pos;
        std::tuple< Args... > * ptr;
        std::vector< std::tuple< Args... > > *text;
    public:
        Iter(std::tuple< Args... > * ptr, int pos, std::vector< std::tuple< Args... > > *text) :
                ptr(ptr), pos(pos), text(text) {}
        bool operator!=(const Iter & other) const {
            return pos != other.pos;
        }
        const Iter& operator++ () {
            pos++;
            if (pos != (*text).size()) {
                ptr = &(*text)[pos];
            }
            return *this;
        }
        std::tuple< Args... >& operator*() {
            return *ptr;
        }
    };

    CSVParser() : delimiter(','), row_delimiter('\n'), quotechar('"') {}
    CSVParser(std::ifstream *s, int skiped_lines) : delimiter(','), row_delimiter('\n'), quotechar('"') {
        std::string str;
        std::tuple< Args... > t;
        int i = 0;
        while (getline(*s, str, row_delimiter)) {
            i++;
            if (i > skiped_lines && str == "") {
                break;
            }
            if (i > skiped_lines - 1) {
                tuple_app(t, int_<sizeof...(Args)>(), str);
                text.push_back(t);
            }
        }
    }
    CSVParser(std::ifstream *s, int skiped_lines, char delimiter, char row_delimiter, char quotechar) : delimiter(','), row_delimiter('\n'), quotechar('"') {
        std::string str;
        std::tuple< Args... > t;
        for (int i = 0; ; i++) {
            getline(*s, str, row_delimiter);
            if (i > skiped_lines && str == "") {
                break;
            }
            if (i > skiped_lines - 1) {
                tuple_app(t, int_<sizeof...(Args)>(), str);
                text.push_back(t);
            }
        }
    }

    ~CSVParser() {}

    void change_config(char delim = ',', char row_delim = '\n', char quotech = '"') {
        delimiter = delim;
        row_delimiter = row_delim;
        quotechar = quotech;
    }

    Iter begin() {
        return Iter(&text[0], 0, &text);
    }
    Iter end() {
        return Iter(&text[text.size() - 1], text.size(), &text);
    }
};

template <class Tuple, size_t Pos>
std::ostream& print_tuple(std::ostream& out, const Tuple& t, int_<Pos> ) {
    out << std::get< std::tuple_size<Tuple>::value-Pos >(t) << ',';
    return print_tuple(out, t, int_<Pos-1>());
}

template <class Tuple>
std::ostream& print_tuple(std::ostream& out, const Tuple& t, int_<1> ) {
    return out << std::get<std::tuple_size<Tuple>::value-1>(t);
}

template <class... Args>
std::ostream& operator<<(std::ostream& out, const std::tuple<Args...>& t) {
    out << '(';
    print_tuple(out, t, int_<sizeof...(Args)>());
    return out << ')';
}
