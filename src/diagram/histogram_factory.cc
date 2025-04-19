#pragma once

#include "histogram_factory.h"

std::unique_ptr<Diagram> HistogramFactory::CreateDiagram(SDL_Renderer* renderer,
                                                         size_t size,
                                                         Uint32 screen_width,
                                                         Uint32 screen_height) {
  return std::make_unique<Histogram>(renderer, size, screen_width,
                                     screen_height);
}