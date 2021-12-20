// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day09.h"
#include <algorithm>
#include <fstream>
#include <iterator>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool is_low_point(std::vector<std::vector<int>> xs, size_t i, size_t j) {
    std::vector<int> &row = xs[i];
    int &self = row[j];
    // A low point is lower than all four neighbors
    bool isLowPoint = true;
    isLowPoint &= j == 0 || row[j - 1] > self;
    isLowPoint &= j == row.size() - 1 || row[j + 1] > self;
    isLowPoint &= i == 0 || xs[i - 1][j] > self;
    isLowPoint &= i == xs.size() - 1 || xs[i + 1][j] > self;
    return isLowPoint;
}

int ex09a_work(std::vector<std::vector<int>> xs) {
  int riskLevel = 0;
  for (size_t i = 0; i < xs.size(); ++i) {
    std::vector<int> &row = xs[i];
    for (size_t j = 0; j < row.size(); ++j) {
      bool isLowPoint = is_low_point(xs, i, j);

      if (isLowPoint) {
        riskLevel += row[j] + 1;
      }
    }
  }
  return riskLevel;
}

int ex09b_work(std::vector<std::vector<int>> xs) {
  // Give each low point a unique number
  int lowPointIndex = 1;
  std::vector<std::vector<int>> basins;
  for (size_t i = 0; i < xs.size(); ++i) {
    std::vector<int> &row = xs[i];
    std::vector<int> basinrow;
    for (size_t j = 0; j < row.size(); ++j) {
      if (is_low_point(xs, i, j)) {
        basinrow.push_back(lowPointIndex++);
      } else {
        basinrow.push_back(-1);
      }
    }
    basins.push_back(basinrow);
  }

  // Grow the basins
  bool done = false;
  do {
    done = true;
    for (size_t i = 0; i < xs.size(); ++i) {
      std::vector<int> &row = xs[i];
      for (size_t j = 0; j < row.size(); ++j) {
        int height = row[j];
        int basinno = basins[i][j];

        if (basinno >= 0)
          continue;

        done = false;

        if (height == 9) {
          basins[i][j] = 0;
          continue;
        }

        if (i > 0 && height > xs[i-1][j] && basins[i-1][j] > 0) {
          basins[i][j] = basins[i-1][j];
          continue;
        }
        if (i < xs.size() - 1 && height > xs[i+1][j] && basins[i+1][j] > 0) {
          basins[i][j] = basins[i+1][j];
          continue;
        }
        if (j > 0 && height > xs[i][j-1] && basins[i][j-1] > 0) {
          basins[i][j] = basins[i][j-1];
          continue;
        }
        if (j < row.size() - 1 && height > xs[i][j+1] && basins[i][j+1] > 0) {
          basins[i][j] = basins[i][j+1];
          continue;
        }
      }
    }
  } while (!done);

  std::vector<int> basins_sizes(lowPointIndex + 1, 0);

  for (auto &b : basins) {
    for (auto &c : b) {
      if (c == 0) continue;
      basins_sizes[c]++;
    }
  }
  sort(basins_sizes.begin(), basins_sizes.end(), std::greater<>());
  return basins_sizes[0] * basins_sizes[1] * basins_sizes[2];
}

std::tuple<int, int> ex09() {
  std::ifstream ex09_file("../input/09");
  std::vector<std::vector<int>> ex09_input;

  std::string line;
  while (std::getline(ex09_file, line)) {
    std::vector<int> iline;
    for (auto &c : line) {
      iline.push_back(c - '0');
    }
    ex09_input.push_back(iline);
  }

  int ex09a = ex09a_work(ex09_input);
  int ex09b = ex09b_work(ex09_input);

  std::tuple<int, int> result(ex09a, ex09b);

  return result;
}
