#pragma once

#include <SDL.h>

#include <vector>

class Diagram {
 public:
  virtual ~Diagram() = default;
  virtual void Init(SDL_Renderer* renderer, size_t size, Uint32 screen_width,
                    Uint32 screen_height) = 0;
  virtual void Render(SDL_Renderer* renderer) = 0;
  virtual void Update(SDL_Renderer* renderer, std::vector<Uint32>& data,
                      std::vector<size_t>& indexes, SDL_Color color) = 0;
};
