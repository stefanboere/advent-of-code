cmake_minimum_required(VERSION 2.4)

project(advent_of_code)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(main src/main.cpp src/day01.cpp src/day02.cpp src/day03.cpp)
