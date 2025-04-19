#pragma once

#include "scatter_plot_factory.h"

std::unique_ptr<Diagram> ScatterPlotFactory::CreateDiagram(
    SDL_Renderer* renderer, size_t size, Uint32 screen_width,
    Uint32 screen_height) {
  return std::make_unique<ScatterPlot>(renderer, size, screen_width,
                                       screen_height);
}
