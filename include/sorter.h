#pragma once

#include <iostream>
#include <vector>

struct Change {
  int a, b;
  bool isSwap;
};

class Sorter {
 public:
  std::vector<unsigned int> data_;

  Sorter(size_t size);
  Change Step();
};
