// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day01.h"
#include <fstream>
#include <iterator>
#include <tuple>
#include <vector>

const std::vector<int> ex01_example = {199, 200, 208, 210, 200,
                                       207, 240, 269, 260, 263};

int ex01a_work(std::vector<int>::iterator first,
               std::vector<int>::iterator last) {
  int prev = *first;
  int c = 0;

  for (auto cur = first + 1; cur != last; ++cur) {
    if (prev < *cur) {
      c++;
    }

    prev = *cur;
  }

  return c;
}

int ex01b_work(std::vector<int> &xs) {

  if (xs.size() <= 2)
    return 0;

  int prev0 = xs[0];
  int prev1 = xs[1];

  for (std::vector<int>::iterator cur = xs.begin() + 2; cur != xs.end();
       ++cur) {
    int prev2 = *cur;

    *cur = prev0 + prev1 + prev2;
    prev0 = prev1;
    prev1 = prev2;
  }

  return ex01a_work(xs.begin() + 2, xs.end());
}

std::tuple<int, int> ex01() {
  std::ifstream ex01_file("../input/01");
  std::istream_iterator<int> start(ex01_file), end;
  std::vector<int> ex01_input(start, end);

  int ex01a = ex01a_work(ex01_input.begin(), ex01_input.end());
  int ex01b = ex01b_work(ex01_input);

  std::tuple<int, int> result(ex01a, ex01b);

  return result;
}
