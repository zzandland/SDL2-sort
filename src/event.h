#pragma once

#include <SDL.h>

#include <vector>

#include "colors.h"

struct SortEvent {
  std::vector<Uint32> data;
  std::vector<size_t> indices;
  std::vector<ColorState> colors;

  inline SortEvent(std::vector<Uint32> &d) : data(d) {}

  inline SortEvent(std::vector<Uint32> &d, std::vector<size_t> &i,
                   std::vector<ColorState> &c)
      : data(d), indices(i), colors(c) {}
};
