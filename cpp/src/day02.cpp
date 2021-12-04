// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day02.h"
#include <fstream>
#include <iterator>
#include <tuple>
#include <vector>

enum Direction { Forward = 1, Up = 2, Down = 3 };

int ex02a_work(std::vector<std::tuple<Direction, int>> xs) {
  int depth = 0;
  int hor = 0;

  for (auto &el : xs) {
    auto dir = std::get<0>(el);
    auto x = std::get<1>(el);
    switch (dir) {
    case Direction::Forward:
      hor += x;
      break;
    case Direction::Up:
      depth -= x;
      break;
    case Direction::Down:
      depth += x;
      break;
    }
  }
  return depth * hor;
}

int ex02b_work(std::vector<std::tuple<Direction, int>> xs) {
  int depth = 0;
  int hor = 0;
  int aim = 0;

  for (auto &el : xs) {
    auto dir = std::get<0>(el);
    auto x = std::get<1>(el);

    switch (dir) {
    case Direction::Forward:
      depth += x * aim;
      hor += x;
      break;
    case Direction::Up:
      aim -= x;
      break;
    case Direction::Down:
      aim += x;
      break;
    }
  }
  return depth * hor;
}

std::tuple<int, int> ex02() {
  std::ifstream ex02_file("../input/02");
  std::vector<std::tuple<Direction, int>> ex02_input;

  std::string line;
  while (std::getline(ex02_file, line)) {
    size_t pos = line.find(' ');
    auto dirstr = line.substr(0, pos);
    auto numstr = line.substr(pos + 1);
    int num = std::stoi(numstr);

    Direction dir;
    if (dirstr == "forward")
      dir = Direction::Forward;
    else if (dirstr == "up")
      dir = Direction::Up;
    else if (dirstr == "down")
      dir = Direction::Down;

    std::tuple<Direction, int> comb(dir, num);
    ex02_input.push_back(comb);
  }
  ex02_file.close();

  int ex02a = ex02a_work(ex02_input);
  int ex02b = ex02b_work(ex02_input);

  std::tuple<int, int> result(ex02a, ex02b);

  return result;
}
