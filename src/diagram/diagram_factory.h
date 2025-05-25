#pragma once

#include "diagram.h"

class DiagramFactory {
 public:
  virtual ~DiagramFactory() = default;  // Add virtual destructor for base class
  virtual std::unique_ptr<Diagram> CreateDiagram() = 0;
};