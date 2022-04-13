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
  lines_.resize(size);
  Sint32 height;
  SDL_SetRenderDrawColor(renderer, 170, 183, 184, SDL_ALPHA_OPAQUE);

  for (size_t i = 0; i < size; ++i) {
    height = ((double)screen_height / size) * (i + 1);
    lines_[i] = height;
    SDL_RenderDrawLine(renderer, i, screen_height_, i,
                       screen_height_ - lines_[i]);
  }

  SDL_RenderPresent(renderer);
}

void Line::Update(SDL_Renderer* renderer, size_t a, size_t b, bool isSwap) {
  if (isSwap) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
    SDL_RenderDrawLine(renderer, a, screen_height_, a,
                       screen_height_ - lines_[a]);
    SDL_RenderDrawLine(renderer, b, screen_height_, b,
                       screen_height_ - lines_[b]);
    Swap(a, b);
  }

  if (isSwap) {
    SDL_SetRenderDrawColor(renderer, 165, 105, 189, SDL_ALPHA_OPAQUE);
  } else {
    SDL_SetRenderDrawColor(renderer, 100, 180, 100, SDL_ALPHA_OPAQUE);
  }
  SDL_RenderDrawLine(renderer, a, screen_height_, a,
                     screen_height_ - lines_[a]);
  SDL_RenderDrawLine(renderer, b, screen_height_, b,
                     screen_height_ - lines_[b]);

  SDL_RenderPresent(renderer);

  SDL_SetRenderDrawColor(renderer, 170, 183, 184, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(renderer, a, screen_height_, a,
                     screen_height_ - lines_[a]);
  SDL_RenderDrawLine(renderer, b, screen_height_, b,
                     screen_height_ - lines_[b]);
}

void Line::Swap(size_t a, size_t b) { std::swap(lines_[a], lines_[b]); }
