#pragma once

#include <iostream>
#include <vector>

#include "screen.h"

class Sorter {
 public:
  Sorter(Screen *screen, size_t size);
  ~Sorter();
  void PollAndHandleSDLEvent();
  void Randomize();
  void BubbleSort();
  void InsertionSort();
  void SelectionSort();

 private:
  std::vector<unsigned int> data_;
  Screen *screen_;
  bool running_;
  size_t size_;
  Uint8 selected_;

  void Init();
  void Sort();
};
