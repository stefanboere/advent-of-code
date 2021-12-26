// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day16.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <tuple>
#include <vector>

int64_t readInt(std::vector<bool>::iterator first,
                std::vector<bool>::iterator last) {
  int64_t result = 0;
  for (auto i = first; i != last; ++i) {
    if (*i)
      result |= 1l << (last - i - 1);
  }
  return result;
}

struct ReadPacketResult {
  std::vector<bool>::iterator cur;
  int versions;
  std::vector<int64_t> values;
};

int64_t packetsValue(int typeId, std::vector<int64_t> values) {
  switch (typeId) {
  case 0: // Sum
    return std::accumulate(values.begin(), values.end(), 0l);
  case 1: // Produt
    return std::accumulate(values.begin(), values.end(), 1l,
                           std::multiplies<int64_t>());
  case 2: // Minimum
    return *std::min_element(values.begin(), values.end());
  case 3: // Maximum
    return *std::max_element(values.begin(), values.end());
  case 5: // Greater than
    return values[0] > values[1];
  case 6: // Less than
    return values[0] < values[1];
  case 7: // Equal
    return values[0] == values[1];
  }
  return 0;
}

ReadPacketResult
readPackets(std::vector<bool>::iterator first, std::vector<bool>::iterator last,
            int maxNumberOfPackets = std::numeric_limits<int>().max()) {

  int version = 0;
  int packagesRead = 0;
  std::vector<int64_t> values;

  while (last - first > 8 && packagesRead < maxNumberOfPackets) {

    version += readInt(first, first + 3);
    packagesRead++;
    first += 3;

    int typeId = readInt(first, first + 3);
    first += 3;

    if (typeId == 4) {
      std::vector<bool> literal_bits;
      for (; first <= last - 5; first += 5) {
        for (auto i = first + 1; i < first + 5; ++i) {
          literal_bits.push_back(*i);
        }

        if (*first == 0)
          break;
      }
      first += 5;
      int64_t literal = readInt(literal_bits.begin(), literal_bits.end());
      values.push_back(literal);
    } else {
      ReadPacketResult result;
      bool lengthType = *first;
      first += 1;
      if (lengthType) {
        size_t numberOfSubpackets = readInt(first, first + 11);
        first += 11;
        result = readPackets(first, last, numberOfSubpackets);

      } else {
        size_t totalLenghtOfSubpackets = readInt(first, first + 15);
        first += 15;

        result = readPackets(first, first + totalLenghtOfSubpackets);
      }

      version += result.versions;
      first = result.cur;
      values.push_back(packetsValue(typeId, result.values));
    }
  }

  return ReadPacketResult{first, version, values};
}

int ex16a_work(std::vector<bool> xs) {
  return readPackets(xs.begin(), xs.end()).versions;
}

int64_t ex16b_work(std::vector<bool> xs) {
  return readPackets(xs.begin(), xs.end()).values[0];
}

std::tuple<int, int64_t> ex16() {
  std::ifstream ex16_file("../input/16");

  std::string line;
  std::getline(ex16_file, line);

  std::vector<bool> input(line.size() * 4);

  int j = 0;
  for (auto &c : line) {
    int v = c - '0';
    if (v >= 10) {
      v -= 7;
    }
    for (int i = 0; i < 4; i++) {
      input[j] = (v >> (3 - i)) & 1;
      j++;
    }
  }

  int ex16a = ex16a_work(input);
  int64_t ex16b = ex16b_work(input);

  std::tuple<int, int64_t> result(ex16a, ex16b);

  return result;
}
