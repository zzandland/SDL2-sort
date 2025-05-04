#include "diagram/histogram.h"

#if defined(_WIN32)
#include <windows.h>
#endif

#include <algorithm>
#include <iostream>

Histogram::Histogram(SDL_Renderer* renderer, size_t size, Uint32 screen_width,
                     Uint32 screen_height)
    : screen_height_(screen_height), screen_width_(screen_width) {
  Init(renderer, size, screen_width, screen_height);
}

void Histogram::Init(SDL_Renderer* renderer, size_t size, Uint32 screen_width,
                     Uint32 screen_height) {
  const Sint32 rect_width = screen_width_ / size;
  Sint32 height;
  SDL_SetRenderDrawColor(renderer, 170, 183, 184, SDL_ALPHA_OPAQUE);

  for (size_t i = 0; i < size; ++i) {
    height = (screen_height / size) * (i + 1);
    SDL_Rect rect = {rect_width * (Sint32)i, (Sint32)screen_height_ - height,
                     rect_width, height};
    SDL_RenderDrawRect(renderer, &rect);
  }
}

void Histogram::Update(SDL_Renderer* renderer, std::vector<Uint32>& data,
                       std::vector<size_t>& indexes) {
  SDL_SetRenderDrawColor(renderer, 170, 183, 184, SDL_ALPHA_OPAQUE);
  size_t size = data.size();
  const Sint32 rect_width = screen_width_ / size;
  Sint32 height;

  for (size_t i = 0; i < size; ++i) {
    height = ((double)screen_height_ / size) * data[i];
    SDL_Rect rect = {rect_width * (Sint32)i, (Sint32)screen_height_ - height,
                     rect_width, height};
    SDL_RenderDrawRect(renderer, &rect);
  }
}
