// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day08.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <tuple>
#include <vector>
#include "include/utils.h"

struct Display {
  std::vector<std::string> patterns;
  std::vector<std::string> digits;

  Display(std::vector<std::string> patterns, std::vector<std::string> digits)
    : patterns(std::move(patterns))
    , digits(std::move(digits)) {
  }
};

int ex08a_work(std::vector<Display> &xs) {
  int result = 0;
  for (auto &x : xs) {
    for (auto &d : x.digits) {
      int len = d.size();
      if (len == 2 || len == 3 || len == 4 || len == 7) {
        result++;
      }
    }
  }
  return result;
}

bool contained_in(std::string needle, std::string haystack) {
  for (auto &x : needle) {
    if (haystack.find(x) == std::string::npos) {
      return false;
    }
  }
  return true;
}

int read_display(Display &display) {
  std::string digits[10];

  for (auto &x : display.patterns) {
    sort(x.begin(), x.end());
    switch (x.size()) {
    case 2:
      digits[1] = x;
      break;
    case 3:
      digits[7] = x;
      break;
    case 4:
      digits[4] = x;
      break;
    case 7:
      digits[8] = x;
      break;
    }
  }

  // a nine is four union 7
  std::string nine = digits[4] + digits[7];
  sort(nine.begin(), nine.end());

  for (auto &x : display.patterns) {
    if (x.size() == 6) {
      if (!contained_in(digits[1], x)) {
        digits[6] = x;
      } else if (contained_in(nine, x)) {
        digits[9] = x;
      } else {
        digits[0] = x;
      }
    }
  }
  for (auto &x : display.patterns) {
    if (x.size() == 5) {
      if (contained_in(digits[1], x)) {
        digits[3] = x;
      } else if (contained_in(x, digits[9])) {
        digits[5] = x;
      } else {
        digits[2] = x;
      }
    }
  }

  int order = std::pow(10, display.digits.size() - 1);
  int result = 0;
  for (auto &x : display.digits) {
    sort(x.begin(), x.end());
    auto *it = std::find(std::begin(digits), std::end(digits), x);
    size_t i = std::distance(digits, it);

    result += i * order;
    order /= 10;
  }

  return result;
}

int ex08b_work(std::vector<Display> &xs) {
  int result = 0;
  for (auto &x : xs) {
    result += read_display(x);
  }
  return result;
}

std::tuple<int, int> ex08() {
  std::ifstream ex08_file("../input/08");
  std::vector<Display> ex08_input;

  std::string line;
  while (std::getline(ex08_file, line)) {
    size_t pipe = line.find(" | ");
    auto patterns = line.substr(0, pipe);
    auto digits = line.substr(pipe + 3, line.length());

    auto pat = split<std::string>(patterns, ' ');
    auto dig = split<std::string>(digits, ' ');
    ex08_input.emplace_back(pat, dig);
  }

  int ex08a = ex08a_work(ex08_input);
  int ex08b = ex08b_work(ex08_input);

  std::tuple<int, int> result(ex08a, ex08b);

  return result;
}
