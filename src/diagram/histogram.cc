#include "diagram/histogram.h"

#if defined(_WIN32)
#include <windows.h>
#endif

#include <algorithm>
#include <iostream>

Histogram& Histogram::GetInstance() {
  static Histogram instance;
  return instance;
}

void Histogram::Render(SDL_Renderer* renderer, std::vector<Uint32>& data,
                       std::vector<size_t>& indexes,
                       std::vector<ColorState>& colors, Uint32 screen_width,
                       Uint32 screen_height) {
  size_t size = data.size();
  // Use floating-point for precise division
  const double rect_width = static_cast<double>(screen_width) / size;
  Sint32 height;

  for (size_t i = 0, j = 0; i < size; ++i) {
    SDL_Rect rect = CalculateRect(screen_height, size, data[i], rect_width, i);
    if (j < indexes.size() && i == indexes[j]) {
      // Set color for the current index
      SDL_Color color = GetColor(colors[j]);
      SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b,
                             (color.a + SDL_ALPHA_TRANSPARENT) / 2);
      SDL_RenderFillRect(renderer, &rect);
      ++j;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &rect);
  }
}

SDL_Rect Histogram::CalculateRect(Uint32 screen_h, size_t total_elements,
                                  Uint32 element_value,
                                  double column_width_exact,
                                  size_t element_index) {
  Sint32 height_val = static_cast<Sint32>(
      (static_cast<double>(screen_h) / total_elements) * element_value);
  Sint32 x_val = static_cast<Sint32>(column_width_exact * element_index);
  Sint32 width_val = static_cast<Sint32>(column_width_exact);

  return {x_val, static_cast<Sint32>(screen_h) - height_val, width_val,
          height_val};
}
