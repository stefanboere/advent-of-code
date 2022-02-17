// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day20.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <tuple>
#include <vector>

std::vector<std::vector<bool>>
enhance(const std::vector<bool> &algo, const std::vector<std::vector<bool>> &xs, bool bg) {
  int width = xs[0].size();
  int height = xs.size();
  std::vector<std::vector<bool>> image(xs.size() + 2,
                                       std::vector<bool>(width + 2, bg));

  std::array<std::pair<int, int>, 9> offsets = {
      std::make_pair(-1, -1), std::make_pair(0, -1), std::make_pair(1, -1),
      std::make_pair(-1, 0),  std::make_pair(0, 0),  std::make_pair(1, 0),
      std::make_pair(-1, 1),  std::make_pair(0, 1),  std::make_pair(1, 1),
  };

  for (int j = -1; j <= height; j++) {
    for (int i = -1; i <= width; i++) {
      int index = 0;
      for (int k = 0; k < 9; k++) {
        auto off = offsets[k];
        int x = i + off.first;
        int y = j + off.second;

        bool white = bg;
        if (x >= 0 && y >= 0 && x < width && y < width) {
          white = xs[y][x];
        }
        if (white) {
          index |= 1 << (8 - k);
        }
      }
      image[j + 1][i + 1] = algo[index];
    }
  }

  return image;
}

int ex20a_work(const std::vector<bool> &algo, const std::vector<std::vector<bool>> &xs) {
  auto xs1 = enhance(algo, xs, false);
  auto xs2 = enhance(algo, xs1, algo[0]);
  int lit = 0;
  for (auto &row : xs2) {
    for (auto c : row) {
      if (c)
        lit++;
    }
  }
  return lit;
}

int ex20b_work(const std::vector<bool> &algo, std::vector<std::vector<bool>> &xs) {
  bool bg = false;
  for (int i = 0; i < 50; i++) {
    xs = enhance(algo, xs, bg);

    if (bg) {
      bg = algo[511];
    } else {
      bg = algo[0];
    }
  }

  int lit = 0;
  for (auto &row : xs) {
    for (auto c : row) {
      if (c)
        lit++;
    }
  }
  return lit;
}

std::tuple<int, int> ex20() {
  std::ifstream ex20_file("../input/20");
  std::vector<bool> ex20_algo;
  std::vector<std::vector<bool>> ex20_input;

  std::string line;
  std::getline(ex20_file, line);
  for (auto &c : line) {
    ex20_algo.push_back(c == '#');
  }

  while (std::getline(ex20_file, line)) {
    if (line.empty())
      continue;

    std::vector<bool> pixels;
    for (auto &c : line) {
      pixels.push_back(c == '#');
    }
    ex20_input.push_back(pixels);
  }

  int ex20a = ex20a_work(ex20_algo, ex20_input);
  int ex20b = ex20b_work(ex20_algo, ex20_input);

  std::tuple<int, int> result(ex20a, ex20b);

  return result;
}
