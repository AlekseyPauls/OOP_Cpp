cmake_minimum_required(VERSION 3.8)
project(Lab2)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)


set(SOURCE_FILES main.cpp Cage.cpp Field.cpp Game.cpp My_exception.cpp Tests/test.cpp)
add_executable(Lab2 ${SOURCE_FILES})
target_link_libraries(Lab2 gtest gtest_main)