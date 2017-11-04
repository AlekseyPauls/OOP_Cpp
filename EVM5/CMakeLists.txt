cmake_minimum_required(VERSION 3.8)
project(EVM5)

set(CMAKE_CXX_STANDARD 11)
include_directories("F:\\opencv\\build\\include\\")
link_directories("F:\\opencv\\")

set(SOURCE_FILES main.cpp)
add_executable(EVM5 ${SOURCE_FILES})