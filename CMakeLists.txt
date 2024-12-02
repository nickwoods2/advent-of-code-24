cmake_minimum_required(VERSION 3.10)

project(AdventOfCodeCpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(day01 src/day01/main.cpp)
add_executable(day02 src/day02/main.cpp)

include_directories(include)