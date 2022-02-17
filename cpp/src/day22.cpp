// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day22.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <tuple>
#include <vector>
#include "include/utils.h"

class Interval {
  int64_t p0;
  int64_t p1;
 public:
  bool on = true;
  Interval() : Interval(0, 0) { }
  Interval(int64_t p0, int64_t p1, bool on = true) : p0(p0), p1(p1), on(on) { }
  int64_t Length() const { return std::max(p1 - p0 + 1l, 0l); }
  static Interval Parse(const std::string &str);
  void Print() const;
  void ClipTo(const Interval &c);
  std::vector<Interval> SplitAt(const Interval &other) const;
};

Interval Interval::Parse(const std::string& str) {
  int eq = str.find('=');
  int dots = str.find("..");
  return Interval {
    stoi(str.substr(eq+1, dots)),
    stoi(str.substr(dots+2))
  };
}

void Interval::Print() const {
  std::cout << p0 << ".." << p1;
}

std::vector<Interval> Interval::SplitAt(const Interval &other) const {
  Interval i0 = Interval(p0, std::min(other.p0 - 1, p1));
  Interval i1 = Interval(std::max(other.p0, p0), std::min(other.p1, p1), false);
  Interval i2 = Interval(std::max(other.p1 +1, p0), p1);

  std::vector<Interval> result;
  if (i0.Length() > 0) result.push_back(i0);
  if (i1.Length() > 0) result.push_back(i1);
  if (i2.Length() > 0) result.push_back(i2);
  return result;
}

void Interval::ClipTo(const Interval &bounds) {
  p0 = std::max(p0, bounds.p0);
  p1 = std::min(p1, bounds.p1);
}

class Cuboid {
  Interval x;
  Interval y;
  Interval z;
  bool on = true;
 public:
  Cuboid() : Cuboid(Interval(), Interval(), Interval()) { }
  explicit Cuboid(Interval xyz) : Cuboid(xyz, xyz, xyz) { }
  Cuboid(Interval x, Interval y, Interval z, bool on = true) : x(x), y(y), z(z), on(on) { }
  int64_t Volume() const { return x.Length() * y.Length() * z.Length(); }
  bool IsOn() const { return on; }
  void Print() const;
  std::vector<Cuboid> Except(const Cuboid& other) const;
  void ClipTo(const Cuboid &c);
};

void Cuboid::Print() const {
  std::cout << (on ? "on " : "off ");
  std::cout << "x=";
  x.Print();
  std::cout << ",y=";
  y.Print();
  std::cout << ",z=";
  z.Print();
  std::cout << std::endl;
}

// Returns up to 26 cuboids describing the remaining cubs after subtracting a cube
std::vector<Cuboid> Cuboid::Except(const Cuboid &other) const {
  auto intervals_x = x.SplitAt(other.x);
  auto intervals_y = y.SplitAt(other.y);
  auto intervals_z = z.SplitAt(other.z);

  std::vector<Cuboid> result;
  for (auto &i_x: intervals_x) {
    if (i_x.on) {
      result.push_back(Cuboid(i_x, y, z));
      continue;
    }

    for (auto &i_y: intervals_y) {
      if (i_y.on) {
        result.push_back(Cuboid(i_x, i_y, z));
        continue;
      }

      for (auto &i_z: intervals_z) {
        if (i_z.on) {
          result.push_back(Cuboid(i_x, i_y, i_z));
        }
      }
    }
  }
  return result;
}

void Cuboid::ClipTo(const Cuboid& bounds) {
  x.ClipTo(bounds.x);
  y.ClipTo(bounds.y);
  z.ClipTo(bounds.z);
}

int64_t ex22_work(std::vector<Cuboid> xs, bool clip) {
  std::vector<Cuboid> on;
  Cuboid bounds = Cuboid(Interval(-50, 50));
  for (auto &c : xs) {
    if (clip) c.ClipTo(bounds);
    std::vector<Cuboid> new_on;
    // Remove c from the current lit cubes
    for (auto &cur: on) {
      for (auto &new_cur: cur.Except(c)) {
        new_on.push_back(new_cur);
      }
    }
    // If it is lit, add it too
    if (c.IsOn()) {
      new_on.push_back(c);
    }
    // Then save these new cubes
    on.clear();
    for (auto & c2: new_on) {
      on.push_back(c2);
    }
  }

  int64_t result = 0;
  for (auto &c: on) {
    result += c.Volume();
  }

  return result;
}

int ex22a_work(const std::vector<Cuboid> &xs) {
  return ex22_work(xs, true);
}

int64_t ex22b_work(const std::vector<Cuboid> &xs) {
  return ex22_work(xs, false);
}

std::tuple<int, int64_t> ex22() {
  std::ifstream ex22_file("../input/22");
  std::vector<Cuboid> ex22_input;

  std::string line;
  while (std::getline(ex22_file, line)) {
    int space = line.find(' ');
    auto onoff = line.substr(0, space);
    bool on = onoff == "on";

    std::vector<std::string> intervals = split<std::string>(line.substr(space +1), ',');
    Interval x = Interval::Parse(intervals[0]);
    Interval y = Interval::Parse(intervals[1]);
    Interval z = Interval::Parse(intervals[2]);
    ex22_input.push_back(Cuboid(x, y, z, on));
  }

  int ex22a = ex22a_work(ex22_input);
  int64_t ex22b = ex22b_work(ex22_input);

  std::tuple<int, int64_t> result(ex22a, ex22b);

  return result;
}
