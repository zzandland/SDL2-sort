#pragma once

#include "diagram/diagram.h"

class Histogram : public Diagram {
 public:
  Histogram(SDL_Renderer* renderer, size_t size, Uint32 screen_width,
            Uint32 screen_height);
  void Init(SDL_Renderer* renderer, size_t size, Uint32 screen_width,
            Uint32 screen_height);
  void Update(SDL_Renderer* renderer, std::vector<Uint32>& data,
              std::vector<size_t>& indexes);

 private:
  Uint32 screen_width_;
  Uint32 screen_height_;
};
