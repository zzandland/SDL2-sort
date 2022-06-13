#pragma once

#include <SDL.h>

#include <memory>

#include "diagram/diagram.h"

enum class DiagramType { kLine, kScatterPlot };

class Screen {
 public:
  Screen(SDL_Renderer* renderer, const Uint32 width, const Uint32 height,
         const Uint32 size);
  ~Screen();
  void set_size(const Uint32 size);
  void Init();
  void Render();
  void Update(std::vector<Uint32>& data, std::vector<size_t>& indexes,
              SDL_Color color);
  void Update(std::vector<Uint32>& data, size_t index, SDL_Color color);
  void set_diagram(DiagramType diagram);

 private:
  Uint32 width_;
  Uint32 height_;
  Uint32 size_;
  SDL_Renderer* renderer_;
  std::unique_ptr<Diagram> diagram_;
};
