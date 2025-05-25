#pragma once

#include "diagram.h"

class ScatterPlot : public Diagram {
 public:
  void Render(SDL_Renderer* renderer, std::vector<Uint32>& data,
              std::vector<size_t>& indexes, Uint32 screen_width,
              Uint32 screen_height) override;
};
