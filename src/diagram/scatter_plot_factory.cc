#include "scatter_plot_factory.h"

std::unique_ptr<Diagram> ScatterPlotFactory::CreateDiagram() {
  return std::make_unique<ScatterPlot>();
}
