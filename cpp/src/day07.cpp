// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day07.h"
#include <fstream>
#include <limits>
#include <tuple>
#include <vector>

int ex07_work(std::vector<int> xs, int (*cost)(int)) {
  int min = std::numeric_limits<int>::max();
  int max = 0;
  for (auto &x : xs) {
    min = std::min(x, min);
    max = std::max(x, max);
  }

  int fuelcost = std::numeric_limits<int>::max();
  for (int mid = min; mid <= max; mid++) {
    int curfuelcost = 0;
    for (auto &x : xs) {
      curfuelcost += cost(mid - x);
    }
    fuelcost = std::min(fuelcost, curfuelcost);
  }

  return fuelcost;
}

int ex07a_work(std::vector<int> xs) { return ex07_work(xs, std::abs); }

// 1 + 2 + 3 + .. + n = n(n+1)/2
int euler(int y) {
  int x = std::abs(y);
  return x * (x + 1) / 2;
}

int ex07b_work(std::vector<int> xs) { return ex07_work(xs, euler); }

std::tuple<int, int> ex07() {
  std::ifstream ex07_file("../input/07");
  std::vector<int> ex07_input;

  std::string line;
  while (std::getline(ex07_file, line, ',')) {
    ex07_input.push_back(stoi(line));
  }
  ex07_file.close();

  int ex07a = ex07a_work(ex07_input);
  int ex07b = ex07b_work(ex07_input);

  std::tuple<int, int> result(ex07a, ex07b);

  return result;
}
