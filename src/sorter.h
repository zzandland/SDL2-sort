#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "screen.h"

enum class Algorithm {
  kBubbleSort,
  kInsertionSort,
  kSelectionSort,
  kQuickSort,
  kMergeSort,
  kHeapSort
};

class Sorter {
 public:
  bool running_;
  size_t size_;
  std::vector<Uint32> data_;
  std::unique_ptr<Screen> screen_;
  Sorter(std::unique_ptr<Screen> &&screen, size_t size);
  void PollAndHandleSDLEvent();
  void StartAndStop();
  void Highlight(std::vector<size_t> &indexes);
  void Highlight(size_t index);
  void Color(std::vector<size_t> &indexes, SDL_Color color);
  void Color(size_t index, SDL_Color color);
  void Swap(size_t a, size_t b);
  void Swap(size_t a, size_t b, SDL_Color color);
  void Delete(std::vector<size_t> &indexes);
  void Delete(size_t index);
  void set_selected(Algorithm algorithm);

 private:
  Algorithm selected_;

  void Init();
  void Sort();
  void Randomize();
  void set_size(const Uint32 size);
};
