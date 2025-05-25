#pragma once

#include "diagram_factory.h"
#include "scatter_plot.h"

class ScatterPlotFactory : public DiagramFactory {
 public:
  std::unique_ptr<Diagram> CreateDiagram() override;
};
