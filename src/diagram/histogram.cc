#include "diagram/histogram.h"

#include <algorithm>
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

void Histogram::Draw(SDL_Renderer* renderer, size_t a, size_t b, bool isSwap) {
  if (isSwap) {
    Swap(a, b);
  }

  // reset screen
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);

  // draw all rectangles first
  SDL_SetRenderDrawColor(renderer, 170, 183, 184, 0);
  SDL_RenderDrawRects(renderer, &rects_[0], rects_.size());

  if (isSwap) {
    SDL_SetRenderDrawColor(renderer, 165, 105, 189, SDL_ALPHA_OPAQUE);
  } else {
    SDL_SetRenderDrawColor(renderer, 100, 180, 100, SDL_ALPHA_OPAQUE);
  }

  // fill rectangles of interest with provided color
  SDL_RenderFillRect(renderer, &rects_[a]);
  SDL_RenderFillRect(renderer, &rects_[b]);

  SDL_RenderPresent(renderer);
}

void Histogram::Swap(size_t a, size_t b) {
  Sint32 h = rects_[a].h;
  Sint32 y = rects_[a].y;
  rects_[a].h = rects_[b].h;
  rects_[a].y = rects_[b].y;
  rects_[b].h = h;
  rects_[b].y = y;
}
