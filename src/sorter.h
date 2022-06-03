#pragma once

#include <iostream>
#include <vector>

#include "screen.h"

class Sorter {
 public:
  bool running_;
  size_t size_;
  std::vector<Uint32> data_;
  Screen *screen_;
  Sorter(Screen *screen, size_t size);
  ~Sorter();
  void PollAndHandleSDLEvent();
  void Randomize();
  void BubbleSort();
  void InsertionSort();
  void SelectionSort();
  void QuickSort();

 private:
  Uint8 selected_;

  void Init();
  void Sort();
  void set_size(const Uint32 size);
  void QuickSortHelper(int l, int r);
  size_t QuickSortPartition(int l, int r);
};
