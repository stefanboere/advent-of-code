// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day13.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <tuple>
#include <vector>

struct Point {
  int x;
  int y;

  bool operator <(Point j) {
    return x < j.x
      || (x == j.x && y < j.y);
  }

  int operator ==(Point j) {
    if (x ==j.x && y == j.y)
      return 1;
    else
      return 0;
  }
};

enum Axis { X, Y };

struct Fold {
  Axis axis;
  int position;
};


int ex13a_work(std::vector<Point> xs, std::vector<Fold> folds) {
  if (folds.empty())
    return 0;

  int dotsvisible = 0;
  auto fold = folds[0];

  for (auto &x : xs) {
    // Translate points to first page
    if (fold.axis == Axis::X
      && x.x > fold.position) {
      x.x = 2 * fold.position - x.x;
    } else if (fold.axis == Axis::Y
        && x.y > fold.position) {
      x.y = 2 * fold.position - x.y;
    }
  }

  sort(xs.begin(), xs.end());
  for (int i = 0; i < xs.size(); i++) {
    while (i < xs.size() - 1 && xs[i] == xs[i+1]) {
      i++;
    }
    dotsvisible++;
  }

  return dotsvisible;
}

int ex13b_work(std::vector<Point> xs, std::vector<Fold> folds) {

  for (auto &fold: folds) {
    for (auto &x : xs) {
      // Translate points to first page
      if (fold.axis == Axis::X
        && x.x > fold.position) {
        x.x = 2 * fold.position - x.x;
      } else if (fold.axis == Axis::Y
          && x.y > fold.position) {
        x.y = 2 * fold.position - x.y;
      }
    }
  }

  int max_x = 0;
  int max_y = 0;
  for (auto &x : xs) {
    max_x = std::max(x.x, max_x);
    max_y = std::max(x.y, max_y);
  }

  std::vector<std::vector<bool>> grid(max_y + 1);
  for (int i = 0; i <= max_y; i++) {
    std::vector<bool> row(max_x + 1, false);
    grid[i] = row;
  }
  for (auto &x: xs) {
    grid[x.y][x.x] = true;
  }
  std::cout << std::endl;

  for (auto &row : grid) {
    for (auto c : row) {
      std::cout << (c ? '#' : '.');
    }
    std::cout << '\n';
  }
  std::cout << std::endl;

  return 0;
}

std::tuple<int, int> ex13() {
  std::ifstream ex13_file("../input/13");
  std::vector<Point> ex13_input;
  std::vector<Fold> folds;

  std::string line;
  while (std::getline(ex13_file, line) && !line.empty()) {
    int comma = line.find(',');
    int x = stoi(line.substr(0, comma));
    int y = stoi(line.substr(comma + 1));
    ex13_input.push_back(Point{x, y});
  }

  while (std::getline(ex13_file, line)) {
    char axis = line[11];
    Axis a = axis == 'x' ? Axis::X : Axis::Y;
    int position = stoi(line.substr(13));
    folds.push_back(Fold { a, position});
  }

  int ex13a = ex13a_work(ex13_input, folds);
  int ex13b = ex13b_work(ex13_input, folds);

  std::tuple<int, int> result(ex13a, ex13b);

  return result;
}
