#include "diagram/line.h"

#if defined(_WIN32)
#include <windows.h>
#endif

#include <algorithm>
#include <iostream>

Line::Line(SDL_Renderer* renderer, size_t size, Uint32 screen_width,
           Uint32 screen_height)
    : screen_height_(screen_height) {
  Init(renderer, size, screen_width, screen_height);
}

void Line::Init(SDL_Renderer* renderer, size_t size, Uint32 screen_width,
                Uint32 screen_height) {
  Sint32 height;
  SDL_SetRenderDrawColor(renderer, 170, 183, 184, SDL_ALPHA_OPAQUE);

  for (size_t i = 0; i < size; ++i) {
    height = ((double)screen_height / size) * (i + 1);
    SDL_RenderDrawLine(renderer, i, screen_height_, i, screen_height_ - height);
  }

  SDL_RenderPresent(renderer);
}

void Line::Render(SDL_Renderer* renderer) { SDL_RenderPresent(renderer); }

void Line::Update(SDL_Renderer* renderer, std::vector<Uint32>& data,
                  std::vector<size_t>& indexes, SDL_Color color) {
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  size_t size = data.size();
  Sint32 height;
  for (size_t index : indexes) {
    height = ((double)screen_height_ / size) * data[index];
    SDL_RenderDrawLine(renderer, index, screen_height_, index,
                       screen_height_ - height);
  }
}
