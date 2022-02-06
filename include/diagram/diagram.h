#pragma once

#include <SDL.h>

#include <vector>

class Diagram {
 public:
  virtual void Update(SDL_Renderer* renderer, size_t a, size_t b,
                    bool isSwap) = 0;

 private:
  virtual void Swap(size_t a, size_t b) = 0;
};
