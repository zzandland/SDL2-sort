#pragma once

#include "diagram.h"

class ScatterPlot : public Diagram {
 private:
  // Private constructor to prevent instantiation
  ScatterPlot() = default;

  // Delete copy constructor and assignment operator
  ScatterPlot(const ScatterPlot&) = delete;
  ScatterPlot& operator=(const ScatterPlot&) = delete;

 public:
  static ScatterPlot& GetInstance();

  void Render(SDL_Renderer* renderer, std::vector<Uint32>& data,
              std::vector<size_t>& indexes, std::vector<ColorState>& colors,
              Uint32 screen_width, Uint32 screen_height) override;
};
