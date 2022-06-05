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
  void Color(std::vector<size_t> &indexes);
  void Color(size_t index);
  void Swap(size_t a, size_t b);
  void Delete(std::vector<size_t> &indexes);
  void Delete(size_t index);

 private:
  Uint8 selected_;

  void Init();
  void Sort();
  void set_size(const Uint32 size);
};
