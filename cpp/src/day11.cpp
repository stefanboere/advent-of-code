// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day11.h"
#include <fstream>
#include <limits>
#include <iostream>
#include <iterator>
#include <tuple>
#include <vector>


int ex11a_work_onestep(std::vector<std::vector<int>> &xs) {
  int imax = xs.size() - 1;
  bool needsAnotherPass = false;
  do {
    needsAnotherPass = false;
    for (size_t i = 0; i <= imax; ++i) {
      std::vector<int> &row = xs[i];
      int jmax = row.size() - 1;
      for (size_t j = 0; j <= jmax ; ++j) {
        if (row[j] >= 9) {
          needsAnotherPass = true;
          // Bump everyone around
          if (j > 0 && i > 0) xs[i-1][j-1]++;
          if (j > 0) xs[i][j-1]++;
          if (j > 0 && i < imax) xs[i+1][j-1]++;

          if (j < jmax && i > 0) xs[i-1][j+1]++;
          if (j < jmax) xs[i][j+1]++;
          if (j < jmax && i < imax) xs[i+1][j+1]++;

          if (i > 0) xs[i-1][j]++;
          if (i < imax) xs[i+1][j]++;

          // Set handled
          row[j] = std::numeric_limits<int>().min();
        }
      }
    }
  } while (needsAnotherPass);

  int flashes = 0;
  for (auto & row: xs) {
    for (auto & el: row) {
      el++;
      if (el < 0) {
        flashes++;
        el = 0;
      }
    }
  }

  return flashes;
}

int ex11a_work(std::vector<std::vector<int>> xs) {
  int flashes = 0;
  for (int i = 0; i < 100; i++) {
    flashes += ex11a_work_onestep(xs);
  }
  return flashes;
}

int ex11b_work(std::vector<std::vector<int>> xs) {
  int sz = xs.size() * xs[0].size();
  int step = 0;
  int flashes;
  do {
    step++;
    flashes = ex11a_work_onestep(xs);
  } while (flashes < sz);
  return step;
}

std::tuple<int, int> ex11() {
  std::ifstream ex11_file("../input/11");
  std::vector<std::vector<int>> ex11_input;

  std::string line;
  while (std::getline(ex11_file, line)) {
    std::vector<int> iline;
    for (auto &c : line) {
      iline.push_back(c - '0');
    }
    ex11_input.push_back(iline);
  }

  int ex11a = ex11a_work(ex11_input);
  int ex11b = ex11b_work(ex11_input);

  std::tuple<int, int> result(ex11a, ex11b);

  return result;
}
