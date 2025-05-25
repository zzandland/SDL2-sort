#pragma once

#include <SDL.h>

#include <vector>

class Diagram {
 public:
  virtual ~Diagram() = default;
  virtual void Render(SDL_Renderer* renderer, std::vector<Uint32>& data,
                      std::vector<size_t>& indexes, Uint32 screen_width,
                      Uint32 screen_height) = 0;
};