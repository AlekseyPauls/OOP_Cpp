cmake_minimum_required(VERSION 3.8)
project(Lab1)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES main.cpp mytrit.cpp Tests/test.cpp)
add_executable(Lab1 ${SOURCE_FILES} Tests/test.cpp)
target_link_libraries(Lab1 gtest gtest_main)