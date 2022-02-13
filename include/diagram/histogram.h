#pragma once

#include <vector>

#include "diagram/diagram.h"

class Histogram : public Diagram {
 public:
  Histogram(SDL_Renderer* renderer, size_t size, Uint32 screen_width,
            Uint32 screen_height);
  void Init(SDL_Renderer* renderer, size_t size, Uint32 screen_width,
            Uint32 screen_height);
  void Update(SDL_Renderer* renderer, size_t a, size_t b, bool isSwap);

 private:
  std::vector<SDL_Rect> rects_;

  void Swap(size_t a, size_t b);
  void ResetRect(SDL_Renderer* renderer, size_t rect_index);
};
