// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include <iostream>
#include <tuple>
#include "include/day01.h"
#include "include/day02.h"
#include "include/day03.h"
using std::cout;
using std::endl;


int main() {
  auto day01 = ex01();
  cout << "Day 01: " << std::get<0>(day01) << " " << std::get<1>(day01) << endl;
  auto day02 = ex02();
  cout << "Day 02: " << std::get<0>(day02) << " " << std::get<1>(day02) << endl;
  auto day03 = ex03();
  cout << "Day 03: " << std::get<0>(day03) << " " << std::get<1>(day03) << endl;
  return 0;
}
