// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day18.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <tuple>
#include <variant>
#include <vector>

struct Sf;

struct SfPair {
  Sf *left;
  Sf *right;
  ~SfPair() {}
};

enum SfType { Pair, Number };

struct Sf {
  SfType type;
  union {
    SfPair pair;
    int number;
  };
  ~Sf() {}
};

Sf* clone(Sf* x) {
  if (x->type == SfType::Number) {
    Sf *sf = new Sf;
    sf->type = SfType::Number;
    sf->number = x->number;
    return sf;
  } else {
    auto l = clone(x->pair.left);
    auto r = clone(x->pair.right);
    auto pair = SfPair {l, r};
    return new Sf{SfType::Pair, pair };
  }
}

Sf* parse(std::string::iterator begin, std::string::iterator end) {
  if (*begin == '[') {
    // Parse a pair
    int notClosedCount = 1;
    auto new_end = begin + 1;
    std::string::iterator comma;
    while (notClosedCount > 0 && new_end < end) {
      if (*new_end == '[') {
        notClosedCount++;
      } else if (*new_end == ']') {
        notClosedCount--;
      } else if (notClosedCount == 1 && *new_end == ',') {
        comma = new_end;
      }
      new_end++;
    }
    auto l = parse(begin + 1, comma);
    auto r = parse(comma + 1, new_end - 1);
    auto pair = SfPair{l, r};
    return new Sf{SfType::Pair, pair };
  } else {
    // Parse a number
    int num = stoi(std::string(begin, end));
    Sf *sf = new Sf;
    sf->type = SfType::Number;
    sf->number = num;
    return sf;
  }
}

void print(Sf *x) {
  if (x->type == SfType::Pair) {
    auto p = x->pair;
    std::cout << '[';
    print(p.left);
    std::cout << ',';
    print(p.right);
    std::cout << ']';
  } else {
    std::cout << x->number;
  }
}

void add_left_right(Sf* left, int num, bool isleft) {
  if (left == NULL)
    return;

  if (left->type == SfType::Number) {
    left->number += num;
  } else {
    // Right is the closest
    if (isleft) {
      add_left_right(left->pair.right, num, isleft);
    } else {
      add_left_right(left->pair.left, num, isleft);
    }
  }
}

void add_left(Sf* left, int num) {
  return add_left_right(left, num, true);
}

void add_right(Sf* right, int num) {
  return add_left_right(right, num, false);
}

bool explode(Sf *x, Sf* left = NULL, int indent = 0, Sf* right = NULL) {
  if (x-> type == SfType::Number) {
    return false;
  } else if (indent >= 4
      && x->pair.left->type == SfType::Number
      && x->pair.right->type == SfType::Number) {
    // Pair indented too much
    int l_num = x->pair.left->number;
    int r_num = x->pair.right->number;
    add_left(left, l_num);
    add_right(right, r_num);

    x->type = SfType::Number;
    x->number = 0;

    return true;
  } else {
    // Regular pair not to be exploded
    // Check left
    return explode(x->pair.left, left, indent+1, x->pair.right)
      || explode(x->pair.right, x->pair.left, indent+1, right);
  }
  return false;
}

bool split(Sf *x) {
  if (x->type == SfType::Number) {
    if (x->number >= 10) {
      int left_val = x->number / 2;
      int right_val = x->number - left_val;

      Sf *l = new Sf;
      l->type = SfType::Number;
      l->number = left_val;

      Sf *r = new Sf;
      r->type = SfType::Number;
      r->number = right_val;

      auto pair = SfPair{l, r};
      x->type = SfType::Pair;
      x->pair = pair;

      return true;
    } else {
      return false;
    }
  } else {
    return split(x->pair.left)
        || split(x->pair.right);
  }
}

Sf* reduce(Sf *x) {
  bool reduced;
  do {
    reduced = !explode(x)
           && !split(x);
  } while (!reduced);
  return x;
}

Sf* add(Sf * x, Sf * y) { return reduce(new Sf{SfType::Pair, SfPair{x, y}}); }

int magnitude(Sf * x) {
  if (x->type == SfType::Number) {
    return x->number;
  } else {
    return magnitude(x->pair.left) * 3 +
           magnitude(x->pair.right) * 2;
  }
}

int ex18a_work(std::vector<Sf*> xs) {
  auto result = xs[0];
  for (auto cur = xs.begin() + 1; cur < xs.end(); cur++) {
    result = add(result, *cur);
  }

  return magnitude(result);
}

int ex18b_work(std::vector<Sf*> xs) {

  int max_magnitude = 0;
  for (auto &x : xs) {
    for (auto &y : xs) {

      int x1 = magnitude(add(clone(x), clone(y)));
      int x2 = magnitude(add(clone(y), clone(x)));
      int x = std::max(x1, x2);
      max_magnitude = std::max(x, max_magnitude);
    }
  }
  return max_magnitude;
}

std::tuple<int, int> ex18() {
  std::ifstream ex18_file("../input/18");
  std::vector<Sf*> ex18_input;

  std::string line;
  while (std::getline(ex18_file, line)) {
    ex18_input.push_back(parse(line.begin(), line.end()));
  }

  std::vector<Sf*> x1;
  for (auto & x: ex18_input) {
    x1.push_back(clone(x));
  }

  int ex18a = ex18a_work(x1);
  int ex18b = ex18b_work(ex18_input);

  std::tuple<int, int> result(ex18a, ex18b);

  return result;
}
