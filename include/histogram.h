#pragma once

#include <vector>

#include "diagram.h"

class Histogram : public Diagram {
 public:
  Histogram(size_t size, Uint32 screen_width, Uint32 screen_height);
  void Draw(SDL_Renderer* renderer);

 private:
  std::vector<SDL_Rect> rects_;
};
