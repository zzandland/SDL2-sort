#include "screen.h"

#include "diagram/histogram_factory.h"     // Include factory
#include "diagram/scatter_plot_factory.h"  // Include factory

Screen::Screen(SDL_Renderer* renderer, const Uint32 width, const Uint32 height,
               const Uint32 size)
    : renderer_(renderer), width_(width), height_(height), size_(size) {
  // Initialize with a default diagram using its factory
  HistogramFactory histogram_factory;
  diagram_ = histogram_factory.CreateDiagram(renderer_, size_, width_, height_);
}

Screen::~Screen() { renderer_ = nullptr; }

void Screen::set_size(const Uint32 size) {
  size_ = size;
  Init();
}

void Screen::Init() {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
  SDL_RenderClear(renderer_);
  diagram_->Init(renderer_, size_, width_, height_);
}

void Screen::Render() { diagram_->Render(renderer_); }

void Screen::Update(SortEvent e) {
  switch (e.type) {
    case SortEvent::Type::Update:
      diagram_->Update(renderer_, e.data, e.indices, e.color);
      break;
    case SortEvent::Type::Render:
      diagram_->Render(renderer_);
      break;
    case SortEvent::Type::Init:
      Init();
      break;
    default:
      break;
  }
}

void Screen::set_diagram(DiagramType diagramType) {
  // Use factories to create diagrams
  switch (diagramType) {
    case DiagramType::kScatterPlot: {
      ScatterPlotFactory scatter_plot_factory;
      diagram_ =
          scatter_plot_factory.CreateDiagram(renderer_, size_, width_, height_);
      break;
    }
    case DiagramType::kHistogram: {
      HistogramFactory histogram_factory;
      diagram_ =
          histogram_factory.CreateDiagram(renderer_, size_, width_, height_);
      break;
    }
    default:
      // Optionally handle default case, maybe log an error or do nothing
      break;
  }
  // Re-initialize after changing the diagram
  Init();
}

Uint32 Screen::width() { return width_; }
