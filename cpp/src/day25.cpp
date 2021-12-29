// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day25.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <tuple>
#include <vector>

enum Cucumber { None = 0, East, South };

void print_result(std::vector<std::vector<Cucumber>> xs) {
  for (auto & row : xs) {
    for (auto &col : row) {
      char c = '.';
      switch (col) {
        case Cucumber::East: c = '>'; break;
        case Cucumber::South: c = 'v'; break;
        default: c = '.';
      }
      std::cout << c;
    }
    std::cout << '\n';
  }
  std::cout << std::endl;
}

void clear(std::vector<std::vector<Cucumber>>::iterator start,
    std::vector<std::vector<Cucumber>>::iterator end) {
  for (auto cur = start; cur != end; cur++) {
    for (auto &x: *cur) {
      x = Cucumber::None;
    }
  }
}

int ex25a_work(std::vector<std::vector<Cucumber>> xs) {
  int height = xs.size();
  int width = xs[0].size();

  std::vector<std::vector<Cucumber>> new_state(height, std::vector<Cucumber>(width, Cucumber::None));

  int step = 0;
  bool moved = false;
  do {
    moved = false;
    step++;

    clear(new_state.begin(), new_state.end());

    // East facing
    for (int j = 0; j < height; j++) {
      auto row = xs[j];
      for (int i = 0; i < width; i++) {
        if (row[i] == Cucumber::None)
          continue;

        int newInd = i;
        if (row[i] == Cucumber::East) {
          newInd = (i + 1) % width;
          bool canMove = row[newInd] == Cucumber::None;
          if (!canMove) {
            newInd = i; // Stay here
          } else {
            moved = true;
          }
        }
        new_state[j][newInd] = xs[j][i];
      }
    }

    clear(xs.begin(), xs.end());

    // South facing. swap new_state with xs
    for (int j = 0; j < height; j++) {
      auto row = new_state[j];
      for (int i = 0; i < width; i++) {
        if (row[i] == Cucumber::None)
          continue;

        int newInd = j;
        if (row[i] == Cucumber::South) {

          newInd = (j + 1) % height;
          bool canMove = new_state[newInd][i] == Cucumber::None;
          if (!canMove) {
            newInd = j; // Stay here
          } else {
            moved = true;
          }
        }
        xs[newInd][i] = new_state[j][i];
      }
    }
  } while (moved);

  return step;
}

std::tuple<int, int> ex25() {
  std::ifstream ex25_file("../input/25");
  std::vector<std::vector<Cucumber>> ex25_input;

  std::string line;
  while (std::getline(ex25_file, line)) {
    std::vector<Cucumber> ln;
    for (auto &ch: line) {
      Cucumber c;
      switch (ch) {
        case '>': c = Cucumber::East; break;
        case 'v': c = Cucumber::South; break;
        default: c = Cucumber::None; break;
      }
      ln.push_back(c);
    }
    ex25_input.push_back(ln);
  }

  int ex25a = ex25a_work(ex25_input);

  std::tuple<int, int> result(ex25a, 0);

  return result;
}
