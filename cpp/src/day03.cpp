// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day03.h"
#include <fstream>
#include <iterator>
#include <tuple>
#include <vector>

const std::vector<int> ex03_example = {0b00100, 0b11110, 0b10110, 0b10111,
                                       0b10101, 0b01111, 0b00111, 0b11100,
                                       0b10000, 0b11001, 0b00010, 0b01010};

int ex03a_work(std::vector<int> xs) {

  int diffs[12] = {0};
  for (auto &x : xs) {
    for (int i = 0; i < 12; i++) {
      int xmask = x & (1 << i);
      if (xmask == 0) {
        diffs[i] -= 1;
      } else {
        diffs[i] += 1;
      }
    }
  }

  int gamma = 0;
  int epsilon = 0;
  for (int i = 0; i < 12; i++) {
    if (diffs[i] > 0) {
      // In this case 1 is most common
      gamma |= 1 << i;
    } else {
      epsilon |= 1 << i;
    }
  }
  return gamma * epsilon;
}

std::vector<int> ex03b_filter_crit(std::vector<int> xs, bool keep,
                                   int column = 11) {

  if (xs.size() <= 1 || column < 0) {
    return xs;
  }

  int diff = 0;
  for (auto &x : xs) {
    int xmask = x & (1 << column);
    if (xmask == 0) {
      diff -= 1;
    } else {
      diff += 1;
    }
  }

  int tokeep;
  if (diff >= 0) {
    // If 1 is most common, we keep a 1 for oxygen (keep =true),
    // and 0 otherwise since it is the least common then
    tokeep = keep;
  } else {
    tokeep = !keep;
  }

  std::vector<int> filteredXs;
  for (auto &x : xs) {
    int xcol = x >> column & 1;
    if (xcol == tokeep) {
      filteredXs.push_back(x);
    }
  }
  xs.clear();

  return ex03b_filter_crit(filteredXs, keep, column - 1);
}

int ex03b_work(std::vector<int> xs) {
  std::vector<int> xs1;
  std::vector<int> xs2;
  xs1 = xs;
  xs2 = xs;
  xs.clear();

  auto oxygen = ex03b_filter_crit(xs1, true);
  auto co2 = ex03b_filter_crit(xs2, false);
  int result = 0;
  if (oxygen.size() == 1 && co2.size() == 1) {
    result = oxygen[0] * co2[0];
  }
  oxygen.clear();
  co2.clear();

  return result;
}

std::tuple<int, int> ex03() {
  std::ifstream ex03_file("../input/03");
  std::vector<int> ex03_input;
  std::string line;

  while (std::getline(ex03_file, line)) {
    ex03_input.push_back(stoi(line, 0, 2));
  }
  ex03_file.close();

  int ex03a = ex03a_work(ex03_input);
  int ex03b = ex03b_work(ex03_input);

  std::tuple<int, int> result(ex03a, ex03b);

  return result;
}
