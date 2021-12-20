// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day14.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <tuple>
#include <vector>

template <typename T>
T resultValue(std::map<char, T> &counts) {
  T mostCommon = 0;
  T leastCommon = std::numeric_limits<T>().max();
  for (auto &c : counts) {
    if (c.second > mostCommon) {
      mostCommon = c.second;
    }
    if (c.second < leastCommon) {
      leastCommon = c.second;
    }
  }

  return mostCommon - leastCommon;
}

int ex14a_work(std::map<std::pair<char, char>, char> xs, std::string start) {
  std::vector<char> v(start.begin(), start.end());

  for (int j = 0; j < 10; j++) {

    int n = v.size();
    v.resize(2 * n - 1);
    for (int i = n - 1; i >= 0; i--) {
      v[2 * i] = v[i];
    }

    for (int i = 0; i < 2 * n; i += 2) {
      std::pair<char, char> m(v[i], v[i + 2]);
      v[i + 1] = xs[m];
    }
  }

  sort(v.begin(), v.end());
  std::map<char, int> counts;
  for (auto &c : v) {
    counts[c]++;
  }
  return resultValue(counts);
}

int64_t ex14b_work(std::map<std::pair<char, char>, char> xs, std::string start) {
  std::map<std::pair<char, char>, int64_t> counts;
  std::map<std::pair<char, char>, int64_t> extra;
  for (size_t i = 0; i < start.size() - 1; i++) {
    counts[std::make_pair(start[i], start[i+1])]++;
  }

  for (int j = 0; j < 40; j++) {
    for (auto &x : xs) {
      extra[x.first] = 0;
    }

    for (auto &c : counts) {
      char mid = xs[c.first];
      extra[std::make_pair(c.first.first, mid)] += c.second;
      extra[std::make_pair(mid, c.first.second)] += c.second;
      c.second = 0;
    }

    for (auto &c : extra) {
      counts[c.first] = c.second;
    }
  }

  std::map<char, int64_t> quantities;
  for (auto &c : counts) {
    quantities[c.first.second] += c.second;
  }
  quantities[start[0]]++;

  return resultValue(quantities);
}

std::tuple<int, int64_t> ex14() {
  std::ifstream ex14_file("../input/14");
  std::map<std::pair<char, char>, char> insertions;

  std::string line;
  std::getline(ex14_file, line);
  std::string start = line;
  while (std::getline(ex14_file, line)) {
    if (line.empty())
      continue;

    char insert = line[6];
    auto pair = std::make_pair(line[0], line[1]);
    insertions.insert(std::make_pair(pair, insert));
  }

  int ex14a = ex14a_work(insertions, start);
  int64_t ex14b = ex14b_work(insertions, start);

  std::tuple<int, int64_t> result(ex14a, ex14b);

  return result;
}
