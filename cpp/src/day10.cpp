// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day10.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <tuple>
#include <vector>

enum Bracket {
  Round,
  Square,
  Curly,
  Angle,
};

struct Token {
  Bracket bracket;
  bool open;
};

int bracket_value(Bracket bracket) {
  switch (bracket) {
  case Bracket::Round:
    return 3;
  case Bracket::Square:
    return 57;
  case Bracket::Curly:
    return 1197;
  case Bracket::Angle:
    return 25137;
  }
  return 0;
}

int64_t autocomplete_score(Bracket bracket) {
  switch (bracket) {
  case Bracket::Round:
    return 1;
  case Bracket::Square:
    return 2;
  case Bracket::Curly:
    return 3;
  case Bracket::Angle:
    return 4;
  }
  return 0;
}

int ex10a_work(const std::vector<std::vector<Token>> &xs) {
  int score = 0;
  for (auto &line : xs) {
    std::vector<Bracket> openings;
    for (auto &t : line) {
      if (t.open) {
        openings.push_back(t.bracket);
      } else {
        Bracket b = openings.back();
        openings.pop_back();

        if (b != t.bracket) {
          // Corrupted
          score += bracket_value(t.bracket);
        }
      }
    }
  }
  return score;
}

int64_t ex10b_work(const std::vector<std::vector<Token>> &xs) {
  std::vector<int64_t> scores;
  for (auto &line : xs) {
    std::vector<Bracket> openings;
    bool corrupted = false;
    for (auto &t : line) {
      if (t.open) {
        openings.push_back(t.bracket);
      } else {
        Bracket b = openings.back();
        openings.pop_back();

        if (b != t.bracket) {
          // Corrupted, skip in score calculation
          openings.clear();
          break;
        }
      }
    }

    int64_t score = 0;
    while (!openings.empty()) {
      score *= 5;
      auto b = openings.back();
      score += autocomplete_score(b);
      openings.pop_back();
    }
    if (score > 0) {
      scores.push_back(score);
    }
  }

  sort(scores.begin(), scores.end());

  return scores[scores.size() / 2];
}

std::tuple<int, int64_t> ex10() {
  std::ifstream ex10_file("../input/10");
  std::vector<std::vector<Token>> ex10_input;

  std::string line;
  while (std::getline(ex10_file, line)) {
    std::vector<Token> tokens;
    for (auto &c : line) {
      Token token;
      switch (c) {
      case '[':
        token = Token{Bracket::Square, true};
        break;
      case ']':
        token = Token{Bracket::Square, false};
        break;
      case '{':
        token = Token{Bracket::Curly, true};
        break;
      case '}':
        token = Token{Bracket::Curly, false};
        break;
      case '(':
        token = Token{Bracket::Round, true};
        break;
      case ')':
        token = Token{Bracket::Round, false};
        break;
      case '<':
        token = Token{Bracket::Angle, true};
        break;
      case '>':
        token = Token{Bracket::Angle, false};
        break;
      }
      tokens.push_back(token);
    }
    ex10_input.push_back(tokens);
  }

  int ex10a = ex10a_work(ex10_input);
  int64_t ex10b = ex10b_work(ex10_input);

  std::tuple<int, int64_t> result(ex10a, ex10b);

  return result;
}
