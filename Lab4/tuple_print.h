#include <iostream>
#include <tuple>

template<std::size_t> struct int_{};

template <class Tuple, size_t Pos>
std::ostream& print_tuple(std::ostream& out, const Tuple& t, int_<Pos> );

template <class Tuple>
std::ostream& print_tuple(std::ostream& out, const Tuple& t, int_<1> );

template <class... Args>
std::ostream& operator<<(std::ostream& out, const std::tuple<Args...>& t);