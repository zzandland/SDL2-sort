#pragma once

#include <SDL.h>

#include <memory>

#include "diagram/diagram.h"
#include "observer.h"

enum class DiagramType { kScatterPlot, kHistogram };

class Screen : public Observer {
 public:
  Screen(SDL_Renderer* renderer, const Uint32 width, const Uint32 height,
         const Uint32 size);
  ~Screen();
  void set_size(const Uint32 size);
  void Init();
  void Render();
  void Update(SortEvent e);
  void set_diagram(DiagramType diagramType);
  Uint32 width();

 private:
  Uint32 width_;
  Uint32 height_;
  Uint32 size_;
  SDL_Renderer* renderer_;
  std::unique_ptr<Diagram> diagram_;
};
