// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day05.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <tuple>
#include <vector>

struct Line {
  int x0;
  int y0;
  int x1;
  int y1;

  Line(int x0, int y0, int x1, int y1) : x0(x0), y0(y0), x1(x1), y1(y1) {
  }
};

int sign(int x) {
  return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

int ex05a_work(const std::vector<Line> &xs, bool noLimit = false) {
  std::vector<std::tuple<int, int>> points;

  for (auto &l : xs) {
    // If horizontal or vertical
    if (l.x0 == l.x1 || l.y0 == l.y1 || noLimit) {
      int steps = std::max(std::abs(l.x1 - l.x0), std::abs(l.y1 - l.y0));
      int dir_x = sign(l.x1 - l.x0);
      int dir_y = sign(l.y1 - l.y0);

      for (int off = 0; off <= steps; off++) {
        int x = l.x0 + dir_x * off;
        int y = l.y0 + dir_y * off;
        std::tuple<int, int> p(x, y);
        points.push_back(p);
      }
    }
  }
  std::sort(points.begin(), points.end());

  if (points.size() == 0)
    return 0;

  int counter = 0;
  std::tuple<int, int> prev = points[0];
  bool foundDuplicate = false;
  for (auto cur = points.begin() + 1; cur != points.end(); ++cur) {
    if (prev == *cur) {
      foundDuplicate = true;
    }

    if (prev != *cur) {
      if (foundDuplicate)
        counter++;
      foundDuplicate = false;
    }
    prev = *cur;
  }

  if (foundDuplicate) {
    counter++;
  }

  return counter;
}

int ex05b_work(const std::vector<Line> &xs) {
  return ex05a_work(xs, true);
}

std::tuple<int, int> ex05() {
  std::ifstream ex05_file("../input/05");
  std::vector<Line> ex05_input;

  std::string line;
  while (std::getline(ex05_file, line)) {
    size_t arrow = line.find("->");
    size_t comma0 = line.find(',');
    size_t comma1 = line.find(',', arrow);
    auto x0 = stoi(line.substr(0, comma0));
    auto y0 = stoi(line.substr(comma0 + 1, arrow));
    auto x1 = stoi(line.substr(arrow + 2, comma1));
    auto y1 = stoi(line.substr(comma1 + 1, line.length()));
    ex05_input.emplace_back(x0, y0, x1, y1);
  }

  int ex05a = ex05a_work(ex05_input);
  int ex05b = ex05b_work(ex05_input);

  std::tuple<int, int> result(ex05a, ex05b);

  return result;
}
