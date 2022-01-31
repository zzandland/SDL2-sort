#pragma once

#include <SDL.h>

#include "screen.h"
#include "sorter.h"

class Engine {
 public:
  bool init_success_;

  Engine(const Uint32 width, const Uint32 height);
  ~Engine();
  bool InitCheck();
  bool Run();

 private:
  SDL_Window* window_;
  SDL_GLContext context_;
  Screen* screen_;
  Sorter* sorter_;
};
