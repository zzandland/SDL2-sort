#pragma once

#include "diagram_factory.h"
#include "histogram.h"

class HistogramFactory : public DiagramFactory {
 public:
  std::unique_ptr<Diagram> CreateDiagram(SDL_Renderer* renderer, size_t size,
                                         Uint32 screen_width,
                                         Uint32 screen_height) override;
};