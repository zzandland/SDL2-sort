#pragma once

#include <SDL.h>

#include <vector>

class Diagram {
 public:
  virtual void Init(SDL_Renderer* renderer, size_t size, Uint32 screen_width,
                    Uint32 screen_height) = 0;
  virtual void Update(SDL_Renderer* renderer, size_t a, size_t b,
                      bool isSwap) = 0;

 private:
  virtual void Swap(size_t a, size_t b) = 0;
};
