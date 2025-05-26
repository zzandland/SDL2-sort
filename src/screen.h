#pragma once

#include <SDL.h>

#include <memory>

#include "diagram/diagram.h"
#include "diagram/histogram_factory.h"
#include "diagram/scatter_plot_factory.h"
#include "event.h"

enum class DiagramType { kScatterPlot, kHistogram };

class Screen {
 public:
  Screen(SDL_Renderer* renderer, const Uint32 width, const Uint32 height);
  ~Screen();
  void Update(SortEvent e);
  void Resize(Uint32 width, Uint32 height);
  void set_diagram(DiagramType diagramType);
  Uint32 width();

 private:
  Uint32 width_;
  Uint32 height_;
  SDL_Renderer* renderer_;
  std::unique_ptr<Diagram> diagram_;
};
