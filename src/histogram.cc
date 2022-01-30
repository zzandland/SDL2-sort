#include "histogram.h"

#include <iostream>

Histogram::Histogram(size_t size, Uint32 screen_width, Uint32 screen_height) {
  const Sint32 rect_width = screen_width / size;
  Sint32 rect_height;
  rects_.resize(size);

  for (size_t i = 0; i < size; ++i) {
    rect_height = (screen_height / size) * (i + 1);
    SDL_Rect rect = {rect_width * (Sint32)i,
                     (Sint32)screen_height - rect_height, rect_width,
                     rect_height};
    rects_[i] = rect;
  }
}

void Histogram::Draw(SDL_Renderer* renderer) {
  // reset screen
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  // draw all rectangles first
  SDL_SetRenderDrawColor(renderer, 170, 183, 184, 0);
  SDL_RenderDrawRects(renderer, &rects_[0], rects_.size());

  SDL_RenderPresent(renderer);
}
