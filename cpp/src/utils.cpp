// Copyright 2021 Stefan Boere <s.boere@hotmail.com>
#include "include/utils.h"
#include <sstream>
#include <string>
#include <vector>

template <typename Out, typename T>
void split(const std::string &s, char delim, Out result) {
  std::istringstream iss(s);
  std::string item;
  while (std::getline(iss, item, delim)) {
    if (!item.empty()) {
      T a;
      std::istringstream iss2(item);
      iss2 >> a;
      *result++ = a;
    }
  }
}

template <typename T> std::vector<T> split(const std::string &s, char delim) {
  using Out = std::back_insert_iterator<std::vector<T>>;
  std::vector<T> elems;
  split<Out, T>(s, delim, std::back_inserter(elems));
  return elems;
}

template std::vector<int> split<int>(const std::string &s, char delim);
template std::vector<std::string> split<std::string>(const std::string &s,
                                                     char delim);
