// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day24.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <tuple>
#include <vector>

enum Operation { Inp, Add, Mul, Div, Mod, Eql };

Operation read_operation(const std::string& str) {
  if (str == "inp")
    return Operation::Inp;
  else if (str == "add")
    return Operation::Add;
  else if (str == "mul")
    return Operation::Mul;
  else if (str == "div")
    return Operation::Div;
  else if (str == "mod")
    return Operation::Mod;
  else
    return Operation::Eql;
}

enum Variable { Constant, X = 1, Y, Z, W };

Variable read_variable(char c) {
  switch (c) {
  case 'x':
    return Variable::X;
  case 'y':
    return Variable::Y;
  case 'z':
    return Variable::Z;
  case 'w':
    return Variable::W;
  default:
    return Variable::Constant;
  }
}

struct Instruction {
  Operation op;
  Variable lvar;
  Variable rvar;
  int rval;
};

int64_t read_result(const std::vector<std::pair<int, int64_t>> &xs) {
  int64_t result = 0;
  int64_t sz = 1;
  for (auto x = xs.rbegin(); x != xs.rend(); ++x) {
    int64_t digit = x->first;
    result += digit * sz;
    sz *= 10;
  }
  return result;
}

class Section {
  int _4;
  int _5;
  int _15;

 public:
  Section(int _4, int _5, int _15) : _4(_4), _5(_5), _15(_15) {}
  int64_t Eval(int w, int64_t z);
  int64_t Get4() { return _4; }
};

// We see that z must be zero after each section,
int64_t Section::Eval(int w, int64_t z) {

  int64_t x = (z % 26 + _5) != w;
  return (z / _4) * (25 * x + 1) + (w + _15) * x;
}

int64_t ex24_work(const std::vector<Instruction>& xs, bool reverse = false) {
  std::vector<Section> sections;
  for (int i = 0; i < xs.size(); i += 18) {
    Section s = Section(xs[i + 4].rval, xs[i + 5].rval, xs[i + 15].rval);
    sections.push_back(s);
  }
  int dir = reverse ? 1 : -1;
  int startDigit = reverse ? 1 : 9;

  std::vector<std::pair<int, int64_t>> digits;
  int64_t z_before = 0;
  int curDigit = startDigit;

  do {
    if (curDigit <= 0 || curDigit >= 10) {
      if (digits.size() == 0) {
        return -1;
      }
      curDigit = digits[digits.size() - 1].first;
      curDigit += dir;
      digits.pop_back();

      if (digits.size() > 0) {
        z_before = digits[digits.size() - 1].second;
      } else {
        z_before = 0;
      }
      // Allow popping back twice
      continue;
    }

    Section s = sections[digits.size()];
    int64_t maxZ = 1;
    for (auto cur = sections.begin() + digits.size() + 1; cur != sections.end();
         cur++) {
      maxZ *= cur->Get4();
    }

    if (digits.size() == sections.size() - 1) {
      maxZ = 0;
    }

    int64_t z = s.Eval(curDigit, z_before);
    if (z <= maxZ) {
      digits.push_back(std::make_pair(curDigit, z));
      z_before = z;
      curDigit = startDigit;
    } else {
      curDigit += dir;
    }
  } while (digits.size() < 14);

  return read_result(digits);
}

int64_t ex24a_work(const std::vector<Instruction> &xs) { return ex24_work(xs); }

int64_t ex24b_work(const std::vector<Instruction> &xs) { return ex24_work(xs, true); }

std::tuple<int64_t, int64_t> ex24() {
  std::ifstream ex24_file("../input/24");
  std::vector<Instruction> ex24_input;

  std::string line;
  while (std::getline(ex24_file, line)) {
    Operation op = read_operation(line.substr(0, 3));
    Variable lvar = read_variable(line[4]);
    Instruction instr;
    if (op == Operation::Inp) {
      instr = Instruction{op, lvar, Variable::Constant, 0};
    } else {
      Variable rvar = read_variable(line[6]);
      if (rvar == Variable::Constant) {
        int rval = stoi(line.substr(6));
        instr = Instruction{op, lvar, rvar, rval};
      } else {
        instr = Instruction{op, lvar, rvar, 0};
      }
    }
    ex24_input.push_back(instr);
  }

  int64_t ex24a = ex24a_work(ex24_input);
  int64_t ex24b = ex24b_work(ex24_input);

  std::tuple<int64_t, int64_t> result(ex24a, ex24b);

  return result;
}
