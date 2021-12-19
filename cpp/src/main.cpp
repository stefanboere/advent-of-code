// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include <iomanip>
#include <iostream>
#include <tuple>
#include "include/day01.h"
#include "include/day02.h"
#include "include/day03.h"
#include "include/day04.h"
#include "include/day05.h"
#include "include/day06.h"
#include "include/day07.h"
#include "include/day08.h"
#include "include/day09.h"
using std::cout;
using std::endl;

template <typename T, typename S> void day(int day, std::tuple<T, S> result) {
  printf("Day %02d: ", day);
  cout << std::get<0>(result) << " " << std::get<1>(result) << endl;
}

int main() {
  day(1, ex01());
  day(2, ex02());
  day(3, ex03());
  day(4, ex04());
  day(5, ex05());
  day(6, ex06());
  day(7, ex07());
  day(8, ex08());
  day(9, ex09());
  return 0;
}
