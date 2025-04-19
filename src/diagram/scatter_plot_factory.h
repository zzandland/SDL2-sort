#pragma once

#include "diagram_factory.h"
#include "scatter_plot.h"

class ScatterPlotFactory : public DiagramFactory {
 public:
  std::unique_ptr<Diagram> CreateDiagram(SDL_Renderer* renderer, size_t size,
                                         Uint32 screen_width,
                                         Uint32 screen_height) override;
};
