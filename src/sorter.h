#pragma once

#include <iostream>
#include <memory>
#include <thread>
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
  Uint32 data(size_t index);
  void set_data(size_t index, Uint32 val);
  size_t size();
  void set_size(const Uint32 size);
  bool running();
  void toggle_running();
  void set_diagram(DiagramType diagram);

 private:
  std::vector<Uint32> data_;
  size_t size_;
  bool running_;
  std::thread t_;
  Algorithm selected_;
  std::unique_ptr<Screen> screen_;

  void Init();
  void Sort();
  void Randomize();
};
