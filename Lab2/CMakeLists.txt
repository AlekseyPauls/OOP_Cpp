cmake_minimum_required(VERSION 3.8)
project(Lab2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Cage.cpp Field.cpp Game.cpp My_exception.cpp)
add_executable(Lab2 ${SOURCE_FILES})