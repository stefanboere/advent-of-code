// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day17.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <tuple>
#include <vector>

struct Rectangle {
  int x0;
  int y0;
  int x1; // Should be >= x0
  int y1; // Should be >= y0
};

// The sum 1 + 2 + ... + n
int ex17_euler(int n) {
  return n * (n+1) / 2;
}

bool hitsTarget(std::pair<int, int> velocity, Rectangle target) {
  int x = 0;
  int y = 0;

  while (y >= target.y0 && x <= target.x1) {

    if (x >= target.x0 && y <= target.y1)
      return true;

    x += velocity.first;
    y += velocity.second;
    if (velocity.first > 0) velocity.first -= 1;
    else if (velocity.first < 0) velocity.first += 1;
    velocity.second -= 1;
  }
  return false;
}

int MinimumXVelocity(int x0) {
  // The maximum x position is
  // sum ( v_x + ... + 3 + 2 + 1) = v_x (v_x + 1) / 2
  // The maximum number of steps is also v_x
  // The minimum x velocity is therefore
  // v_x^2 + v_x - 2 x0 = 0
  // v_x = -1/2 + sqrt(1 + 8 x0)/2
  int v_x_min = -0.5 + 0.5 * std::sqrt(1 + 8 * x0);
  return v_x_min;
}

int ex17a_work(Rectangle target) {
  // Assume x0 > 0 and y1 < 0
  if (target.x0 <= 0 || target.y1 >= 0 || target.y0 > target.y1 || target.x0 > target.x1)
    return 0;

  int v_x_min = MinimumXVelocity(target.x0);

  // After 2*v_y steps, the probe will be at y=0 with speed -v_y
  // So if v_y is greater than target.y0, then it will always overshoot

  int max_v_y = 0;
  for (int v_x = v_x_min; v_x <= target.x1; v_x++) {
    for (int v_y = 0 ; v_y <= std::abs(target.y0); v_y++) {
      if (hitsTarget(std::make_pair(v_x, v_y), target)) {
        max_v_y = std::max(v_y, max_v_y);
      }
    }
  }

  return ex17_euler(max_v_y);
}

int ex17b_work(Rectangle target) {
  if (target.x0 <= 0 || target.y1 >= 0 || target.y0 > target.y1 || target.x0 > target.x1)
    return 0;

  int v_x_min = MinimumXVelocity(target.x0);

  int counter = 0;
  for (int v_x = v_x_min; v_x <= target.x1; v_x++) {
    for (int v_y = target.y0; v_y <= std::abs(target.y0); v_y++) {
      if (hitsTarget(std::make_pair(v_x, v_y), target)) {
        counter++;
      }
    }
  }

  return counter;
}

std::tuple<int, int> ex17() {
  std::ifstream ex17_file("../input/17");
  Rectangle ex17_input;

  std::string line;
  std::getline(ex17_file, line);
  int x_is = line.find("x=");
  int x_dots = line.find("..", x_is);
  int y_is = line.find(", y=");
  int y_dots  = line.find("..", y_is);

  int x0 = stoi(line.substr(x_is + 2, x_dots));
  int x1 = stoi(line.substr(x_dots + 2, y_is));
  int y0 = stoi(line.substr(y_is + 4, y_dots));
  int y1 = stoi(line.substr(y_dots + 2));
  ex17_input = Rectangle{x0, y0, x1, y1};

  int ex17a = ex17a_work(ex17_input);
  int ex17b = ex17b_work(ex17_input);

  std::tuple<int, int> result(ex17a, ex17b);

  return result;
}
