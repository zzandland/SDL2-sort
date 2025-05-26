#include "screen.h"

Screen::Screen(SDL_Renderer* renderer, const Uint32 width, const Uint32 height)
    : renderer_(renderer), width_(width), height_(height) {
  // Initialize with a default diagram using its factory
  diagram_ = &Histogram::GetInstance();
}

Screen::~Screen() { renderer_ = nullptr; }

void Screen::Update(SortEvent e) {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
  SDL_RenderClear(renderer_);
  diagram_->Render(renderer_, e.data, e.indices, e.colors, width_, height_);
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
      diagram_ = &Histogram::GetInstance();
      break;
    }
    case DiagramType::kScatterPlot: {
      diagram_ = &ScatterPlot::GetInstance();
      break;
    }
    default:
      // Optionally handle default case, maybe log an error or do nothing
      break;
  }
  // Re-initialize after changing the diagram
}

Uint32 Screen::width() { return width_; }
