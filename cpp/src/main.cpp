// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include <iostream>
#include <tuple>
#include "include/day01.h"
#include "include/day02.h"
#include "include/day03.h"
#include "include/day04.h"
#include "include/day05.h"
#include "include/day06.h"
using std::cout;
using std::endl;


int main() {
  auto day01 = ex01();
  cout << "Day 01: " << std::get<0>(day01) << " " << std::get<1>(day01) << endl;
  auto day02 = ex02();
  cout << "Day 02: " << std::get<0>(day02) << " " << std::get<1>(day02) << endl;
  auto day03 = ex03();
  cout << "Day 03: " << std::get<0>(day03) << " " << std::get<1>(day03) << endl;
  auto day04 = ex04();
  cout << "Day 04: " << std::get<0>(day04) << " " << std::get<1>(day04) << endl;
  auto day05 = ex05();
  cout << "Day 05: " << std::get<0>(day05) << " " << std::get<1>(day05) << endl;
  auto day06 = ex06();
  cout << "Day 06: " << std::get<0>(day06) << " " << std::get<1>(day06) << endl;
  return 0;
}
