#pragma once

#include <SDL.h>

#include <vector>

struct SortEvent {
  std::vector<Uint32> data;
  std::vector<size_t> indices;

  inline SortEvent(std::vector<Uint32> &d, std::vector<size_t> &i)
      : data(d), indices(i) {}
};
