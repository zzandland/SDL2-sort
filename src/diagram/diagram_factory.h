#pragma once

#include "diagram.h"

class DiagramFactory {
 public:
  virtual ~DiagramFactory() = default;  // Add virtual destructor for base class
  virtual std::unique_ptr<Diagram> CreateDiagram(SDL_Renderer* renderer,
                                                 size_t size,
                                                 Uint32 screen_width,
                                                 Uint32 screen_height) = 0;
};