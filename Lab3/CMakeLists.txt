cmake_minimum_required(VERSION 3.8)
project(Lab3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp workflow.cpp workflow.h my_exception.cpp my_exception.h shared_pointer.cpp shared_pointer.h Tests/test.cpp)
add_executable(Lab3 ${SOURCE_FILES})