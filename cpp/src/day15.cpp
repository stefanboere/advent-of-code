// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day15.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <tuple>
#include <vector>


int pathlength(const std::vector<std::vector<int>> &xs) {
  int dx = xs[0].size();
  int dy = xs.size();
  std::vector<std::vector<int>> distances(dy, std::vector<int>(dx, std::numeric_limits<int>().max()/2));

  distances[0][0] = 0;

  std::pair<int, int> neighbors[4] = {
    std::make_pair(-1, 0),
    std::make_pair(1, 0),
    std::make_pair(0, -1),
    std::make_pair(0, 1)
  };

  bool dirty = true;
  while (dirty) {
    dirty = false;
    for (int x = 0; x < dx; x++) {
      for (int y = 0; y < dy; y++) {

        int d = xs[y][x];
        for (auto &n: neighbors) {
          if (x + n.first < 0
              || x + n.first >= dx
              || y + n.second < 0
              || y + n.second >= dy)
            continue;

          int curd = distances[y][x];
          int newd = distances[y+n.second][x+n.first] + d;

          if (newd < curd) {
            distances[y][x] = newd;
            dirty = true;
          }
        }
      }
    }
  }
  return distances[dy -1][dx-1];
}

int ex15a_work(const std::vector<std::vector<int>> &xs) {
  return pathlength(xs);
}

int ex15b_work(const std::vector<std::vector<int>> &xs) {
  int dx = xs[0].size();
  int dy = xs.size();
  std::vector<std::vector<int>> ys(5*dy, std::vector<int>(5*dx));

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      int weight = i + j;

      for (int x = 0; x < dx; x++) {
        for (int y = 0; y < dy; y++) {
          int risklevel = xs[y][x] + weight;
          if (risklevel > 9)
            risklevel -= 9;
          ys[j*dy + y][i*dx + x] = risklevel;
        }
      }
    }
  }

  return pathlength(ys);
}

std::tuple<int, int> ex15() {
  std::ifstream ex15_file("../input/15");
  std::vector<std::vector<int>> grid;

  std::string line;
  std::string start = line;
  while (std::getline(ex15_file, line)) {
    std::vector<int> ln;
    for (auto &c : line) {
      ln.push_back(c - '0');
    }
    grid.push_back(ln);
  }

  int ex15a = ex15a_work(grid);
  int ex15b = ex15b_work(grid);

  std::tuple<int, int64_t> result(ex15a, ex15b);

  return result;
}
