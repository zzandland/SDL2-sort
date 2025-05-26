#include "diagram/scatter_plot.h"

#if defined(_WIN32)
#include <windows.h>
#endif

#include <algorithm>  // Required for std::max
#include <iostream>

ScatterPlot& ScatterPlot::GetInstance() {
  static ScatterPlot instance;
  return instance;
}

void ScatterPlot::Render(SDL_Renderer* renderer, std::vector<Uint32>& data,
                         std::vector<size_t>& indexes, Uint32 screen_width,
                         Uint32 screen_height) {
  SDL_SetRenderDrawColor(renderer, 170, 183, 184, SDL_ALPHA_OPAQUE);
  size_t size = data.size();
  Sint32 height;
  const double width_scale = (double)screen_width / size;
  // Calculate point size based on height and number of items, ensure minimum
  // size of 1
  const int point_size = std::max(1, static_cast<int>(screen_height / size));

  for (size_t i = 0; i < size; ++i) {
    height = ((double)screen_height / size) * data[i];
    const Sint32 x = i * width_scale;
    const Sint32 y = screen_height - height;
    // Draw a small rectangle instead of a point
    SDL_Rect rect = {x - point_size / 2, y - point_size / 2, point_size,
                     point_size};
    SDL_RenderFillRect(renderer, &rect);
  }
}
