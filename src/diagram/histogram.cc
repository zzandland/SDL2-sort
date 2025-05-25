#include "diagram/histogram.h"

#if defined(_WIN32)
#include <windows.h>
#endif

#include <algorithm>
#include <iostream>

void Histogram::Render(SDL_Renderer* renderer, std::vector<Uint32>& data,
                       std::vector<size_t>& indexes, Uint32 screen_width,
                       Uint32 screen_height) {
  SDL_SetRenderDrawColor(renderer, 170, 183, 184, SDL_ALPHA_OPAQUE);
  size_t size = data.size();
  const double rect_width = static_cast<double>(screen_width) /
                            size;  // Use floating-point for precise division
  Sint32 height;

  for (size_t i = 0; i < size; ++i) {
    height = static_cast<Sint32>((static_cast<double>(screen_height) / size) *
                                 data[i]);
    Sint32 x = static_cast<Sint32>(
        rect_width * i);  // Calculate x position as a float and cast to integer
    SDL_Rect rect = {x, static_cast<Sint32>(screen_height) - height,
                     static_cast<Sint32>(rect_width),
                     height};  // Use rect_width as float, cast to integer
    SDL_RenderDrawRect(renderer, &rect);
  }
}
