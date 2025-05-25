#include "screen.h"

Screen::Screen(SDL_Renderer* renderer, const Uint32 width, const Uint32 height)
    : renderer_(renderer), width_(width), height_(height) {
  // Initialize with a default diagram using its factory
  HistogramFactory histogram_factory;
  diagram_ = histogram_factory.CreateDiagram();
}

Screen::~Screen() { renderer_ = nullptr; }

void Screen::Update(SortEvent e) {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
  SDL_RenderClear(renderer_);
  diagram_->Render(renderer_, e.data, e.indices, width_, height_);
  SDL_RenderPresent(renderer_);
}

void Screen::Resize(Uint32 width, Uint32 height) {
  width_ = width;
  height_ = height;
}

void Screen::set_diagram(DiagramType diagramType) {
  // Use factories to create diagrams
  switch (diagramType) {
    case DiagramType::kHistogram: {
      HistogramFactory histogram_factory;
      diagram_ = histogram_factory.CreateDiagram();
      break;
    }
    case DiagramType::kScatterPlot: {
      ScatterPlotFactory scatter_plot_factory;
      diagram_ = scatter_plot_factory.CreateDiagram();
      break;
    }
    default:
      // Optionally handle default case, maybe log an error or do nothing
      break;
  }
  // Re-initialize after changing the diagram
}

Uint32 Screen::width() { return width_; }
