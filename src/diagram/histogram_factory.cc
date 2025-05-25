#include "histogram_factory.h"

std::unique_ptr<Diagram> HistogramFactory::CreateDiagram() {
  return std::make_unique<Histogram>();
}