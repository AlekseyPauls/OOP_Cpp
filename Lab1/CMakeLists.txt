cmake_minimum_required(VERSION 3.8)
project(Lab1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
SET (CMAKE_CXX_FLAGS "-std=gnu++11" CACHE STRING "compile flags" FORCE)
add_compile_options(-std=gnu++11)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES main.cpp Tests/mytrit.cpp Tests/test.cpp)
add_executable(Lab1 ${SOURCE_FILES})
target_link_libraries(Lab1 gtest gtest_main)