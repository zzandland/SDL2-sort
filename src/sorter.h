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
  void Highlight(std::vector<size_t> &indexes);
  void Highlight(size_t index);
  void Color(std::vector<size_t> &indexes, SDL_Color color);
  void Color(size_t index, SDL_Color color);
  void Swap(size_t a, size_t b);
  void Swap(size_t a, size_t b, SDL_Color color);
  void Delete(std::vector<size_t> &indexes);
  void Delete(size_t index);

 private:
  Uint8 selected_;

  void Init();
  void Sort();
  void set_size(const Uint32 size);
};
