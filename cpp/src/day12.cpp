// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day12.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <tuple>
#include <vector>

struct Edge {
  std::string start;
  std::string end;
};

struct Path {
  std::vector<std::string> nodes;
  bool exceptionApplied;
};

int ex12_work(std::vector<Edge> xs, bool singleSmallException = false) {
  // Start in 'start'
  std::vector<Path> paths;
  std::vector<std::string> path;
  path.push_back("start");
  paths.push_back(Path{path, false});

  int pathcount = 0;
  bool hasUnfinishedPaths;
  do {
    hasUnfinishedPaths = false;
    std::vector<Path> newpaths;

    for (auto &p : paths) {
      auto last = p.nodes.back();
      for (auto &edge : xs) {
        std::string next;
        if (edge.end == last) {
          next = edge.start;
        } else if (edge.start == last) {
          next = edge.end;
        } else {
          continue;
        }

        if (next == "end") {
          pathcount++;
          continue;
        }

        if (next == "start") {
          continue;
        }

        // Lower case caves may only be accessed once, or one of them may be
        // visited twice
        bool visited = false;
        if (islower(next[0])) {
          visited =
              std::find(p.nodes.begin(), p.nodes.end(), next) != p.nodes.end();
          if (visited && (!singleSmallException || p.exceptionApplied)) {
            continue;
          }
        }

        std::vector<std::string> newpath = p.nodes;
        newpath.push_back(next);
        newpaths.push_back(Path{newpath, p.exceptionApplied || visited});
        hasUnfinishedPaths = true;
      }
    }

    paths = newpaths;
  } while (hasUnfinishedPaths);

  return pathcount;
}

int ex12a_work(std::vector<Edge> xs) { return ex12_work(xs, false); }

int ex12b_work(std::vector<Edge> xs) { return ex12_work(xs, true); }

std::tuple<int, int> ex12() {
  std::ifstream ex12_file("../input/12");
  std::vector<Edge> ex12_input;

  std::string line;
  while (std::getline(ex12_file, line)) {
    int dash = line.find('-');
    std::string start = line.substr(0, dash);
    std::string end = line.substr(dash + 1, line.size());
    ex12_input.push_back(Edge{start, end});
  }

  int ex12a = ex12a_work(ex12_input);
  int ex12b = ex12b_work(ex12_input);

  std::tuple<int, int> result(ex12a, ex12b);

  return result;
}
