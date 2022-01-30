#pragma once

#include <SDL.h>

#include <vector>

class Diagram {
 public:
  virtual void Draw(SDL_Renderer* renderer) = 0;
};
