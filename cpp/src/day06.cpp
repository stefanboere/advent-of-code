// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day06.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <tuple>
#include <vector>

int ex06a_work(std::vector<int> xs) {
  for (int day = 0; day < 80; day++) {
    int newfish = 0;
    for (auto &x : xs) {
      x--;
      if (x < 0) {
        x = 6;
        newfish++;
      }
    }
    for (int fish = 0; fish < newfish; fish++) {
      xs.push_back(8);
    }
  }
  return xs.size();
}

int64_t ex06b_work(std::vector<int> xs) {
  int64_t bins[9] = {0};
  for (auto &x : xs) {
    bins[x]++;
  }

  for (int day = 0; day < 256; day++) {
    // Shift bins
    int64_t zeroes = bins[0];
    for (int i = 1; i < 9; i++) {
      bins[i-1] = bins[i];
    }
    bins[6] += zeroes; // Reset
    bins[8] = zeroes; // Birth
  }

  int64_t result;
  for (auto &x : bins) {
    result += x;
  }
  return result;
}

std::tuple<int, int64_t> ex06() {
  std::ifstream ex06_file("../input/06");
  std::vector<int> ex06_input;

  std::string line;
  while (std::getline(ex06_file, line, ',')) {
    ex06_input.push_back(stoi(line));
  }
  ex06_file.close();

  int ex06a = ex06a_work(ex06_input);
  int64_t ex06b = ex06b_work(ex06_input);

  std::tuple<int, int64_t> result(ex06a, ex06b);

  return result;
}
