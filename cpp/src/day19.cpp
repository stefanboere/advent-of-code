// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day19.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <set>
#include <tuple>
#include <vector>

struct Point {
  int x;
  int y;
  int z;
  int sensor;
};

enum PermuteAxis {
  XYZ = 0, // The identity
  YZX = 1,
  ZXY = 2,
  YXZ = 3,
  XZY = 4,
  ZYX = 5
};

class Transform {
 public:
  virtual Transform *Inverse() = 0;
  virtual Point *Apply(Point *x) = 0;
};

// Actually this also includes mirroring (48 possibilities instead of 24)
class Rotation : public Transform {
  bool negateX;
  bool negateY;
  bool negateZ;
  PermuteAxis permuteAxis;

 public:
  Rotation();
  Rotation(PermuteAxis p, bool negateX, bool negateY, bool negateZ);
  ~Rotation() {}
  static std::vector<Rotation> All();
  Transform *Inverse();
  Point *Apply(Point *p);
};

Rotation::Rotation() : Rotation(PermuteAxis::XYZ, false, false, false) {}

Rotation::Rotation(PermuteAxis p, bool nx, bool ny, bool nz)
    : permuteAxis(p), negateX(nx), negateY(ny), negateZ(nz) {}

Transform *Rotation::Inverse() {
  PermuteAxis p = this->permuteAxis;
  bool negateX = this->negateX;
  bool negateY = this->negateY;
  bool negateZ = this->negateZ;
  switch (this->permuteAxis) {
  case PermuteAxis::XYZ:
    break;
  case PermuteAxis::YZX:
    p = PermuteAxis::ZXY;
    negateX = this->negateY;
    negateY = this->negateZ;
    negateZ = this->negateX;
    break;
  case PermuteAxis::ZXY:
    p = PermuteAxis::YZX;
    negateX = this->negateZ;
    negateY = this->negateX;
    negateZ = this->negateY;
    break;
  case PermuteAxis::YXZ:
    negateX = this->negateY;
    negateY = this->negateX;
    break;
  case PermuteAxis::XZY:
    negateY = this->negateZ;
    negateZ = this->negateY;
    break;
  case PermuteAxis::ZYX:
    negateX = this->negateZ;
    negateZ = this->negateX;
    break;
  }
  Rotation *r = new Rotation(p, negateX, negateY, negateZ);
  return r;
}

std::vector<Rotation> Rotation::All() {
  std::vector<Rotation> rotations(48);
  for (int i = 0; i < 6; i++) {
    PermuteAxis x = (PermuteAxis)i;
    rotations.push_back(Rotation(x, false, false, false));
    rotations.push_back(Rotation(x, false, false, true));
    rotations.push_back(Rotation(x, false, true, false));
    rotations.push_back(Rotation(x, false, true, true));
    rotations.push_back(Rotation(x, true, false, false));
    rotations.push_back(Rotation(x, true, false, true));
    rotations.push_back(Rotation(x, true, true, false));
    rotations.push_back(Rotation(x, true, true, true));
  }
  return rotations;
}

Point *Rotation::Apply(Point *p) {
  int x, y, z;
  switch (this->permuteAxis) {
  case PermuteAxis::XYZ:
    x = p->x;
    y = p->y;
    z = p->z;
    break;
  case PermuteAxis::YZX:
    y = p->x;
    z = p->y;
    x = p->z;
    break;
  case PermuteAxis::ZXY:
    z = p->x;
    x = p->y;
    y = p->z;
    break;
  case PermuteAxis::YXZ:
    y = p->x;
    x = p->y;
    z = p->z;
    break;
  case PermuteAxis::XZY:
    x = p->x;
    z = p->y;
    y = p->z;
    break;
  case PermuteAxis::ZYX:
    z = p->x;
    y = p->y;
    x = p->z;
    break;
  }

  if (this->negateX)
    x = -x;
  if (this->negateY)
    y = -y;
  if (this->negateZ)
    z = -z;
  p->x = x;
  p->y = y;
  p->z = z;
  return p;
}

class Translation : public Transform {
  int dx;
  int dy;
  int dz;

 public:
  Translation();
  Translation(int dx, int dy, int dz);
  ~Translation() {}
  Transform *Inverse();
  Point *Apply(Point *x);
};

Translation::Translation() : Translation(0, 0, 0) {}
Translation::Translation(int dx, int dy, int dz) : dx(dx), dy(dy), dz(dz) {}

Transform *Translation::Inverse() {
  Transform *p = new Translation(-dx, -dy, -dz);
  return p;
}

Point *Translation::Apply(Point *p) {
  p->x += dx;
  p->y += dy;
  p->z += dz;
  return p;
}

class Transforms : public Transform {
  std::vector<Transform *> transforms;

 public:
  Transforms();
  explicit Transforms(std::vector<Transform *> transforms);
  Transforms(Transform *x, Transform *y);
  ~Transforms() {}
  Transform *Inverse();
  Point *Apply(Point *x);
};

Transforms::Transforms() {}
Transforms::Transforms(std::vector<Transform *> ts) { transforms = ts; }
Transforms::Transforms(Transform *x, Transform *y) {
  transforms.push_back(x);
  transforms.push_back(y);
}
Point *Transforms::Apply(Point *p) {
  for (auto &t : transforms) {
    p = t->Apply(p);
  }
  return p;
}
Transform *Transforms::Inverse() {
  std::vector<Transform *> xs;
  for (auto cur = transforms.end() - 1; cur >= transforms.begin(); cur--) {
    xs.push_back((*cur)->Inverse());
  }
  Transforms *p = new Transforms(xs);
  return p;
}

int overlaps(std::map<int, int> ds0, std::map<int, int> ds1) {
  int count = 0;
  for (auto &d0 : ds0) {
    if (ds1.find(d0.first) != ds1.end()) {
      count += std::min(d0.second, ds1[d0.first]);
    }
  }
  return count;
}

int manhattan(Point *x, Point *y) {
  return std::abs(x->x - y->x) + std::abs(x->y - y->y) + std::abs(x->z - y->z);
}

// Points which have at least 12 connections in allowed distances set
std::vector<std::pair<Point *, std::vector<int>>>
relevantPoints(std::vector<Point *> xs, std::map<int, int> ds0) {
  std::vector<std::pair<Point *, std::vector<int>>> result;
  for (auto &x : xs) {
    std::vector<int> distances;
    for (auto &y : xs) {
      int d = manhattan(x, y);
      if (d == 0)
        continue;

      if (ds0.find(d) != ds0.end() && ds0[d] > 0) {
        distances.push_back(d);
      }
    }
    if (distances.size() >= 11) {
      std::sort(distances.begin(), distances.end());
      result.push_back(std::make_pair(x, distances));
    }
  }
  return result;
}

std::vector<std::pair<Point *, Point *>>
matchPoints(std::vector<std::pair<Point *, std::vector<int>>> rel_x,
            std::vector<std::pair<Point *, std::vector<int>>> rel_y) {

  std::vector<std::pair<Point *, Point *>> matches;
  for (auto &x : rel_x) {
    Point *match = NULL;
    bool unique = true;
    for (auto &y : rel_y) {

      int distancesMatch = 0;
      for (int i = 0; i < x.second.size(); i++) {
        if (std::find(y.second.begin(), y.second.end(), x.second[i]) !=
            y.second.end()) {
          distancesMatch++;
        }
      }

      if (distancesMatch >= 11 && unique) {
        match = y.first;
        unique = false;
      }
    }

    if (match != NULL) {
      matches.push_back(std::make_pair(x.first, match));
      match = NULL;
    }
  }
  return matches;
}

// The vector between two points is independent of translation, but depends on
// the rotation
Rotation *findRotation(std::vector<std::pair<Point *, Point *>> matches) {
  if (matches.size() < 2) {
    return new Rotation();
  }
  auto rotations = Rotation::All();
  std::vector<Rotation> possible;

  auto x0 = matches[0];
  for (auto x1 = matches.begin() + 1; x1 != matches.end(); x1++) {
    possible.clear();
    Point d_left = Point{x1->first->x - x0.first->x, x1->first->y - x0.first->y,
                         x1->first->z - x0.first->z};
    Point d_right =
        Point{x1->second->x - x0.second->x, x1->second->y - x0.second->y,
              x1->second->z - x0.second->z};
    for (auto &r : rotations) {
      Point d_right_clone = d_right;
      auto d = r.Apply(&d_right_clone);
      if (d->x == d_left.x && d->y == d_left.y && d->z == d_left.z) {
        possible.push_back(r);
      }
    }
    if (possible.size() <= 1) {
      break;
    }
  }
  if (possible.size() == 0) {
    return new Rotation();
  }

  return new Rotation(possible[0]);
}

// Points are assumed to be rotated first
Translation *findTranslation(Point *p0, Point *p1_noR, Rotation *r) {
  Point *p1 = r->Apply(new Point{p1_noR->x, p1_noR->y, p1_noR->z});

  return new Translation(p0->x - p1->x, p0->y - p1->y, p0->z - p1->z);
}

std::map<std::pair<int, int>, Transform *>
InsertMissing(std::map<std::pair<int, int>, Transform *> input, size_t n) {
  // Fill identities
  for (int i = 0; i < n; i++) {
    input[std::make_pair(i, i)] = new Transforms();
  }

  do {
    // Add inverses
    std::map<std::pair<int, int>, Transform *> newtransforms;
    for (auto &t : input) {
      auto back = std::make_pair(t.first.second, t.first.first);
      if (input.find(back) == input.end()) {
        newtransforms[back] = t.second->Inverse();
      }
    }

    // Add chains
    for (auto &t0 : input) {
      for (auto &t1 : input) {
        if (t0.first.second != t1.first.first)
          continue;

        auto path = std::make_pair(t0.first.first, t1.first.second);
        if (input.find(path) == input.end()) {
          newtransforms[path] = new Transforms(t1.second, t0.second);
        }
      }
    }

    for (auto &n : newtransforms) {
      input[n.first] = n.second;
    }
  } while (input.size() < n * n);
  return input;
}

std::map<std::pair<int, int>, Transform *>
coordinateMaps(std::vector<std::vector<Point *>> xs) {
  // The distances between any two points remains invariant under translations
  // and rotations. So if two sensors have 12 points in common, they also have
  // the 12 * 11 / 2 edges in common
  std::vector<std::map<int, int>> distances(xs.size());
  for (int i = 0; i < xs.size(); i++) {
    for (auto cur_x = xs[i].begin(); cur_x < xs[i].end(); cur_x++) {
      for (auto cur_y = cur_x + 1; cur_y < xs[i].end(); cur_y++) {
        auto x = *cur_x;
        auto y = *cur_y;
        int d = manhattan(x, y);
        distances[i][d]++;
      }
    }
  }

  std::map<std::pair<int, int>, Transform *> transforms;
  for (auto cur_x = distances.begin(); cur_x != distances.end(); cur_x++) {
    for (auto cur_y = cur_x + 1; cur_y != distances.end(); cur_y++) {
      int o = overlaps(*cur_x, *cur_y);
      if (o < 66)
        continue;

      int x = std::distance(distances.begin(), cur_x);
      int y = std::distance(distances.begin(), cur_y);

      auto rel_x = relevantPoints(xs[x], distances[y]);
      auto rel_y = relevantPoints(xs[y], distances[x]);
      auto matches = matchPoints(rel_x, rel_y);

      auto m0 = matches[0];
      Rotation *r = findRotation(matches);
      Translation *t = findTranslation(m0.first, m0.second, r);
      Transforms *rt = new Transforms(r, t);

      transforms[std::make_pair(x, y)] = rt;
    }
  }

  return InsertMissing(transforms, xs.size());
}

int ex19a_work(std::vector<std::vector<Point *>> xs,
               std::map<std::pair<int, int>, Transform *> transforms) {

  std::set<std::tuple<int, int, int>> uniquePoints;
  for (auto i = 0; i < xs.size(); i++) {
    auto transform = transforms[std::make_pair(0, i)];
    for (auto &p : xs[i]) {
      auto p1 = transform->Apply(p);
      auto tup = std::make_tuple(p1->x, p1->y, p1->z);
      if (uniquePoints.find(tup) == uniquePoints.end()) {
        uniquePoints.insert(tup);
      }
    }
  }

  return uniquePoints.size();
}

int ex19b_work(std::vector<std::vector<Point *>> xs,
               std::map<std::pair<int, int>, Transform *> transforms) {

  std::vector<Point *> sensors(xs.size());
  for (int i = 0; i < xs.size(); i++) {
    auto t = transforms[std::make_pair(0, i)];
    Point *p = t->Apply(new Point{0, 0, 0, 0});
    sensors[i] = p;
  }

  int maxDistance = 0;
  for (auto i = sensors.begin(); i != sensors.end(); i++) {
    for (auto j = i + 1; j != sensors.end(); j++) {
      maxDistance = std::max(maxDistance, manhattan(*i, *j));
    }
  }

  return maxDistance;
}

std::tuple<int, int> ex19() {
  std::ifstream ex19_file("../input/19");
  std::vector<std::vector<Point *>> ex19_input;

  std::string line;
  int i = -1;
  while (std::getline(ex19_file, line)) {
    if (line.rfind("---", 0) == 0) {
      std::vector<Point *> s0;
      ex19_input.push_back(s0);
      i++;
    } else if (!line.empty()) {

      auto comma0 = line.find(',');
      if (comma0 != std::string::npos) {
        auto comma1 = line.find(',', comma0 + 1);
        int x = stoi(line.substr(0, comma0));
        int y = stoi(line.substr(comma0 + 1, comma1));
        int z = stoi(line.substr(comma1 + 1));

        ex19_input[i].push_back(new Point{x, y, z, i});
      }
    }
  }

  auto transforms = coordinateMaps(ex19_input);
  int ex19a = ex19a_work(ex19_input, transforms);
  int ex19b = ex19b_work(ex19_input, transforms);

  std::tuple<int, int> result(ex19a, ex19b);

  return result;
}
