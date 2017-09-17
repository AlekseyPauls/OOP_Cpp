cmake_minimum_required(VERSION 3.8)
project(A)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp module1.cpp module2.cpp module3.cpp)
add_executable(A ${SOURCE_FILES})