cmake_minimum_required(VERSION 2.4)

project(advent_of_code)

include_directories(${PROJECT_SOURCE_DIR})
add_executable(main
  src/main.cpp
  src/utils.cpp
  src/day01.cpp
  src/day02.cpp
  src/day03.cpp
  src/day04.cpp
  src/day05.cpp
  src/day06.cpp
  src/day07.cpp
  src/day08.cpp
  src/day09.cpp
  src/day10.cpp
  )
