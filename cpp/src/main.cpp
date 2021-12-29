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
#include "include/day10.h"
#include "include/day11.h"
#include "include/day12.h"
#include "include/day13.h"
#include "include/day14.h"
#include "include/day15.h"
#include "include/day16.h"
#include "include/day17.h"
#include "include/day18.h"
#include "include/day19.h"
#include "include/day20.h"
#include "include/day21.h"
#include "include/day22.h"
#include "include/day23.h"
#include "include/day24.h"
#include "include/day25.h"
using std::cout;
using std::endl;

template <typename T, typename S> void day(int day, std::tuple<T, S> result) {
  printf("Day %02d: ", day);
  cout << std::get<0>(result) << " " << std::get<1>(result) << endl;
}

int main() {
  day(25, ex25());
  day(24, ex24());
  day(23, ex23());
  day(22, ex22());
  day(21, ex21());
  day(20, ex20());
  day(19, ex19());
  day(18, ex18());
  day(17, ex17());
  day(16, ex16());
  day(15, ex15());
  day(14, ex14());
  day(13, ex13());
  day(12, ex12());
  day(11, ex11());
  day(10, ex10());
  day(9, ex09());
  day(8, ex08());
  day(7, ex07());
  day(6, ex06());
  day(5, ex05());
  day(4, ex04());
  day(3, ex03());
  day(2, ex02());
  day(1, ex01());
  return 0;
}
