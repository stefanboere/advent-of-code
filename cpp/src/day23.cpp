// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day23.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <tuple>
#include <vector>

enum AmphiType { Empty = 0, Amber = 1, Bronze = 2, Copper = 3, Desert = 4 };

/*
#############
#0123456789A#
###B#C#D#E###
  #F#G#H#I#
  #########
*/
using burrow = std::vector<AmphiType>;

int get_x(int index) {
  if (index <= 10)
    return index;

  return ((index - 11) % 4) * 2 + 2;
}

int get_y(int index) {
  if (index <= 10)
    return 0;
  return (index - 11) / 4 + 1;
}

AmphiType room_type(int index) { return (AmphiType)(((index - 11) % 4) + 1); }

AmphiType read_amphitype(char c) {
  switch (c) {
  case 'A':
    return AmphiType::Amber;
  case 'B':
    return AmphiType::Bronze;
  case 'C':
    return AmphiType::Copper;
  case 'D':
    return AmphiType::Desert;
  default:
    return AmphiType::Empty;
  }
}

int energy_per_step(AmphiType t) {
  switch (t) {
  case AmphiType::Amber:
    return 1;
  case AmphiType::Bronze:
    return 10;
  case AmphiType::Copper:
    return 100;
  case AmphiType::Desert:
    return 1000;
  default:
    return 0;
  }
}

bool is_valid(burrow xs) {
  for (int i = 11; i < xs.size(); i++) {
    if (xs[i] != room_type(i))
      return false;
  }
  return true;
}

std::vector<std::pair<burrow, int>> next(burrow input) {
  std::vector<std::pair<burrow, int>> result;
  if (is_valid(input))
    return result; // no next moves

  std::vector<int> maxYpos(4, 0);
  std::vector<bool> allSameType(4, true);
  for (int i = 11; i < input.size(); i++) {
    int y = get_y(i);
    int roomIndex = room_type(i) - 1;

    if (input[i] != AmphiType::Empty && input[i] != room_type(i)) {
      allSameType[roomIndex] = false;
    }

    if (input[i] == AmphiType::Empty) {
      maxYpos[roomIndex] = std::max(y, maxYpos[roomIndex]);
    }
  }

  // Move to room
  for (int i = 0; i <= 10; i++) {
    if (input[i] == AmphiType::Empty)
      continue;

    int roomIndex = input[i] - 1;
    if (!allSameType[roomIndex])
      continue;

    int roomX = roomIndex * 2 + 2;
    int sign = roomX - i > 0 ? 1 : -1;
    bool free = true;

    for (int j = i + sign; j != roomX; j += sign) {
      free &= input[j] == AmphiType::Empty;
    }
    if (!free)
      continue;

    int d = std::abs(roomX - i);
    int y = maxYpos[roomIndex];
    std::vector<AmphiType> b = input;
    b[i] = AmphiType::Empty;
    int yInd = 11 + roomIndex + (y - 1) * 4;
    b[yInd] = input[i];
    int energy = energy_per_step(input[i]) * (d + y);
    result.push_back(std::make_pair(b, energy));
  }

  // Move out
  for (int roomIndex = 0; roomIndex < 4; roomIndex++) {
    if (allSameType[roomIndex])
      continue;

    int y = maxYpos[roomIndex];
    int yInd = 11 + roomIndex + y * 4;
    int roomX = roomIndex * 2 + 2;

    for (int dir = -1; dir <= 1; dir += 2) {
      for (int x_pls = roomX + dir; x_pls <= 10 && x_pls >= 0; x_pls += dir) {
        if (x_pls == 2 || x_pls == 4 || x_pls == 6 || x_pls == 8)
          continue;

        if (input[x_pls] != AmphiType::Empty)
          break;

        std::vector<AmphiType> b = input;
        b[x_pls] = input[yInd];
        b[yInd] = AmphiType::Empty;
        int energy =
            energy_per_step(input[yInd]) * (std::abs(x_pls - roomX) + y + 1);
        result.push_back(std::make_pair(b, energy));
      }
    }
  }
  return result;
}

char amphytype_char(AmphiType t) {
  char c = ' ';
  switch (t) {
  case AmphiType::Amber:
    c = 'A';
    break;
  case AmphiType::Bronze:
    c = 'B';
    break;
  case AmphiType::Copper:
    c = 'C';
    break;
  case AmphiType::Desert:
    c = 'D';
    break;
  case AmphiType::Empty:
    c = ' ';
    break;
  }
  return c;
}

void print_burrow(burrow xs) {
  for (int i = 0; i <= 10; i++) {
    std::cout << amphytype_char(xs[i]);
  }
  std::cout << '\n';
  for (int i = 11; i < xs.size(); i += 4) {
    std::cout << "  ";
    for (int j = i; j < i + 4; j++) {
      std::cout << amphytype_char(xs[j]) << ' ';
    }
    std::cout << '\n';
  }
  std::cout << std::endl;
}

int ex23a_work(burrow xs) {
  std::map<burrow, int> energies;
  energies[xs] = 0;

  int min = std::numeric_limits<int>().max();
  do {
    std::map<burrow, int> new_energies;

    for (auto &x : energies) {
      for (auto &x_next : next(x.first)) {
        int energy = x.second + x_next.second;

        if (is_valid(x_next.first)) {
          min = std::min(energy, min);
          continue;
        }
        if (new_energies.find(x_next.first) != new_energies.end()) {
          energy = std::min(new_energies[x_next.first], energy);
        }

        new_energies[x_next.first] = energy;
      }
    }

    energies = new_energies;
  } while (energies.size() > 0);

  return min;
}

int ex23b_work(burrow xs) {

  for (int j = 0; j < 2; j++) {
    for (int i = 0; i < 4; i++) {
      xs.push_back(xs[15 + i]);
    }
  }
  xs[15] = AmphiType::Desert;
  xs[16] = AmphiType::Copper;
  xs[17] = AmphiType::Bronze;
  xs[18] = AmphiType::Amber;
  xs[19] = AmphiType::Desert;
  xs[20] = AmphiType::Bronze;
  xs[21] = AmphiType::Amber;
  xs[22] = AmphiType::Copper;

  return ex23a_work(xs);
}

std::tuple<int, int> ex23() {
  std::ifstream ex23_file("../input/23");
  std::vector<std::vector<AmphiType>> ex23_input;

  std::string line;
  std::getline(ex23_file, line);
  while (std::getline(ex23_file, line)) {
    std::vector<AmphiType> ln;
    for (int i = 2; i < 10; i += 2) {
      ln.push_back(read_amphitype(line[i + 1]));
    }
    ex23_input.push_back(ln);
  }
  ex23_input.pop_back();

  std::vector<AmphiType> flattened;
  for (int i = 0; i <= 10; i++) {
    flattened.push_back(AmphiType::Empty);
  }
  for (auto &r : ex23_input) {
    for (auto &c : r) {
      if (c != AmphiType::Empty) {
        flattened.push_back(c);
      }
    }
  }

  int ex23a = ex23a_work(flattened);
  int ex23b = ex23b_work(flattened);

  std::tuple<int, int> result(ex23a, ex23b);

  return result;
}
