cmake_minimum_required(VERSION 3.8)
project(Lab4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp csvparser.h parser_exceptions.cpp parser_exceptions.h)
add_executable(Lab4 ${SOURCE_FILES})