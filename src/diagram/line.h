#pragma once

#include <vector>

#include "diagram.h"

class Line : public Diagram {
 public:
  Line(SDL_Renderer* renderer, size_t size, Uint32 screen_width,
       Uint32 screen_height);
  void Init(SDL_Renderer* renderer, size_t size, Uint32 screen_width,
            Uint32 screen_height);
  void Update(SDL_Renderer* renderer, size_t a, size_t b, bool isSwap);

 private:
  Uint32 screen_height_;
  std::vector<Uint32> lines_;

  void Swap(size_t a, size_t b);
};
