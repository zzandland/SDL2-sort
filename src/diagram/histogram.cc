#include <windows.h>

#include "diagram/histogram.h"

#include <algorithm>
#include <iostream>

Histogram::Histogram(SDL_Renderer* renderer, size_t size, Uint32 screen_width,
                     Uint32 screen_height) {
  const Sint32 rect_width = screen_width / size;
  Sint32 rect_height;
  rects_.resize(size);
  SDL_SetRenderDrawColor(renderer, 170, 183, 184, SDL_ALPHA_OPAQUE);

  for (size_t i = 0; i < size; ++i) {
    rect_height = (screen_height / size) * (i + 1);
    SDL_Rect rect = {rect_width * (Sint32)i,
                     (Sint32)screen_height - rect_height, rect_width,
                     rect_height};
    rects_[i] = rect;
  }

  SDL_RenderDrawRects(renderer, &rects_[0], rects_.size());
}

void Histogram::Update(SDL_Renderer* renderer, size_t a, size_t b, bool isSwap) {
  char buff[100];
  if (isSwap) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
    SDL_RenderDrawRect(renderer, &rects_[a]);
    SDL_RenderDrawRect(renderer, &rects_[b]);
    Swap(a, b);
  }

  if (isSwap) {
    SDL_SetRenderDrawColor(renderer, 165, 105, 189, SDL_ALPHA_OPAQUE);
  } else {
    SDL_SetRenderDrawColor(renderer, 100, 180, 100, SDL_ALPHA_OPAQUE);
  }

  // fill rectangles of interest with provided color
  SDL_RenderFillRect(renderer, &rects_[a]);
  SDL_RenderFillRect(renderer, &rects_[b]);

  SDL_RenderPresent(renderer);

  Histogram::ResetRect(renderer, a);
  Histogram::ResetRect(renderer, b);
}

void Histogram::Swap(size_t a, size_t b) {
  Sint32 h = rects_[a].h;
  Sint32 y = rects_[a].y;
  rects_[a].h = rects_[b].h;
  rects_[a].y = rects_[b].y;
  rects_[b].h = h;
  rects_[b].y = y;
}

void Histogram::ResetRect(SDL_Renderer* renderer, size_t rect_index) {
  // After rendering remove colors in the current rectangles
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
  SDL_RenderFillRect(renderer, &rects_[rect_index]);

  // Draw the outline of the rectangles again
  SDL_SetRenderDrawColor(renderer, 170, 183, 184, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawRect(renderer, &rects_[rect_index]);
}
