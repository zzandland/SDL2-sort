#pragma once

#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include "observer.h"

enum class Algorithm {
  kBubbleSort,
  kInsertionSort,
  kSelectionSort,
  kQuickSort,
  kMergeSort,
  kHeapSort
};

class Sorter : public Observable {
 public:
  Sorter(size_t size);
  ~Sorter();
  void PollAndHandleSDLEvent();
  void StartAndStop();
  void Update(size_t index, Uint32 val);
  void Swap(size_t a, size_t b);
  void set_selected(Algorithm algorithm);
  Uint32 data(size_t index);
  void set_data(size_t index, Uint32 val);
  size_t size();
  void set_size(const Uint32 size);
  bool running();
  void toggle_running();

 private:
  std::vector<Uint32> data_;
  size_t size_;
  bool running_;
  std::thread t_;
  Algorithm selected_;

  void Init();
  void Sort();
  void Randomize();
};
