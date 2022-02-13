#pragma once

#include <iostream>
#include <vector>

#include "screen.h"

class Sorter {
 public:
  Sorter(Screen *screen, size_t size);
  ~Sorter();
  void Randomize();
  void InsertionSort();
  void PollAndHandleSDLEvent();

 private:
  std::vector<unsigned int> data_;
  Screen *screen_;
  bool running_;
  size_t size_;

  void Init();
};
