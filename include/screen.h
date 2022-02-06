#pragma once

#include <SDL.h>

#include "diagram/diagram.h"

class Screen {
 public:
  Screen(SDL_Renderer* renderer, const Uint32 width, const Uint32 height, const Uint32 size);
  ~Screen();
  void Update(size_t a, size_t b, bool isSwap = false);

 private:
  Uint32 width_;
  Uint32 height_;
  SDL_Renderer* renderer_;
  Diagram* diagram_;
};
