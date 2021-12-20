// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day04.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>
#include "include/utils.h"

int card_value(std::set<int> xs, std::array<int, 25> card) {
  int result = 0;
  for (auto &el : card) {
    if (xs.find(el) == xs.end()) {
      result += el;
    }
  }
  return result;
}

int check_card(std::set<int> xs, std::array<int, 25> card) {
  // Check rows
  for (int i = 0; i < 25; i += 5) {
    bool allDrawn = true;
    for (int j = i; j < i + 5; j++) {
      allDrawn &= xs.find(card[j]) != xs.end();
    }
    if (allDrawn)
      return card_value(xs, card);
  }

  for (int i = 0; i < 5; i++) {
    bool allDrawn = true;
    for (int j = i; j < 25; j += 5) {
      allDrawn &= xs.find(card[j]) != xs.end();
    }
    if (allDrawn)
      return card_value(xs, card);
  }

  return -1;
}

int ex04a_work(std::vector<int> xs, std::vector<std::array<int, 25>> cards) {
  std::set<int> drawn;

  for (auto &el : xs) {
    drawn.insert(el);
    for (auto &card : cards) {
      int result = check_card(drawn, card);
      if (result >= 0) {
        return result * el;
      }
    }
  }

  return -2;
}

int ex04b_work(std::vector<int> xs, std::vector<std::array<int, 25>> cards) {
  std::set<int> drawn;
  std::set<int> removed;

  for (auto &el : xs) {
    drawn.insert(el);
    int i = 0;
    for (auto &card : cards) {
      i++;
      if (removed.find(i) != removed.end())
        continue;

      int result = check_card(drawn, card);
      if (result >= 0) {
        removed.insert(i);
        if (removed.size() == cards.size())
          return result * el;
      }
    }
  }
  return 0;
}

std::tuple<int, int> ex04() {
  std::ifstream ex04_file("../input/04");
  std::vector<std::array<int, 25>> ex04_cards;
  std::string line;

  std::getline(ex04_file, line);
  std::vector<int> ex04_input = split<int>(line, ',');

  int row = 0;
  std::array<int, 25> card = {0};
  while (std::getline(ex04_file, line)) {
    if (line.empty())
      continue;

    int col = 0;
    for (auto &el : split<int>(line, ' ')) {
      card[row * 5 + col] = el;
      col++;
    }
    row++;

    if (row == 5) {
      std::array<int, 25> clone = card;
      ex04_cards.push_back(clone);
      row = 0;
    }
  }

  int ex04a = ex04a_work(ex04_input, ex04_cards);
  int ex04b = ex04b_work(ex04_input, ex04_cards);

  std::tuple<int, int> result(ex04a, ex04b);

  return result;
}
