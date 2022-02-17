// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/day21.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <tuple>
#include <vector>

class Dice {
  int rollCount = 0;
  int prev = 0;
  int RollOnce();

 public:
  Dice() {}
  int Roll();
  int GetRollCount() const;
};

int Dice::RollOnce() {
  int val = ++prev;
  prev = prev % 10;
  rollCount++;
  return val;
}

int Dice::Roll() {
  int total = 0;
  total += RollOnce();
  total += RollOnce();
  total += RollOnce();
  return total;
}

int Dice::GetRollCount() const { return rollCount; }

class Player {
  int pos;
  int score = 0;

 public:
  explicit Player(int startPos);
  int GetScore() const;
  bool Play(int x);
};

Player::Player(int startPos) : pos(startPos) {}

bool Player::Play(int x) {
  pos += x;
  pos = (pos - 1) % 10 + 1; // Wrap around 10
  score += pos;
  return score >= 1000;
}

int Player::GetScore() const { return score; }

int ex21a_work(int pos_1, int pos_2) {
  Player p1(pos_1);
  Player p2(pos_2);
  Dice d = Dice();

  while (true) {
    bool p1_wins = p1.Play(d.Roll());
    if (p1_wins) {
      return p2.GetScore() * d.GetRollCount();
    }

    bool p2_wins = p2.Play(d.Roll());
    if (p2_wins) {
      return p1.GetScore() * d.GetRollCount();
    }
  }
  return 0;
}

struct Stats {
  int64_t playing;
  int64_t finished;
};

// How many of the total 3^n surpass 21 after n rolls
Stats statsOfRound(int pos_1, int rolls, int target = 21) {
  //  std::cout << pos_1 << "," << rolls << "," << target << std::endl;
  if (target <= 0 && rolls == 0)
    return Stats{0, 1}; // Rolling is stopped
  else if (rolls <= 0)
    return Stats{1, 0}; // Too little rolls left, but playing
  else if (target <= 0)
    return Stats{0, 0}; // Finished earlier

  std::array<std::pair<int, int64_t>, 7> weights = {
      std::make_pair(3, 1), std::make_pair(4, 3), std::make_pair(5, 6),
      std::make_pair(6, 7), std::make_pair(7, 6), std::make_pair(8, 3),
      std::make_pair(9, 1),
  };

  int64_t finished = 0;
  int64_t playing = 0;
  for (auto &w : weights) {
    int newPos = (pos_1 + w.first - 1) % 10 + 1;
    auto stats = statsOfRound(newPos, rolls - 1, target - newPos);
    finished += w.second * stats.finished;
    playing += w.second * stats.playing;
  }
  return Stats{playing, finished};
}

int64_t ex21b_work(int pos_1, int pos_2) {
  int64_t p1_wins = 0;
  int64_t p2_wins = 0;
  int64_t p2_playing = 1;
  for (int roll = 0; roll <= 21; roll++) {
    Stats p1 = statsOfRound(pos_1, roll);
    Stats p2 = statsOfRound(pos_2, roll);

    p1_wins += p1.finished * p2_playing;
    // P2 wins if p1 is playing
    p2_wins += p2.finished * p1.playing;
    p2_playing = p2.playing;

    if (p2.playing == 0 || p1.playing == 0) {
      break;
    }
  }
  return std::max(p1_wins, p2_wins);
}

std::tuple<int, int64_t> ex21() {
  std::ifstream ex21_file("../input/21");
  std::vector<int> ex21_input;

  std::string line;
  while (std::getline(ex21_file, line)) {
    int colon = line.find(": ");
    ex21_input.push_back(stoi(line.substr(colon + 2)));
  }

  int ex21a = ex21a_work(ex21_input[0], ex21_input[1]);
  int64_t ex21b = ex21b_work(ex21_input[0], ex21_input[1]);

  std::tuple<int, int64_t> result(ex21a, ex21b);

  return result;
}
