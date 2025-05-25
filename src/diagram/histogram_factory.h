#pragma once

#include "diagram_factory.h"
#include "histogram.h"

class HistogramFactory : public DiagramFactory {
 public:
  std::unique_ptr<Diagram> CreateDiagram() override;
};