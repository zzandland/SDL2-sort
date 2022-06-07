#pragma once

#include <SDL.h>

#include <memory>

#include "screen.h"
#include "sorter.h"

enum class SDLEventType {
  kNoEvent = 0,
};

class Engine {
 public:
  Engine(const Uint32 width, const Uint32 height);
  ~Engine();
  void Run();

 private:
  SDL_Window* window_;
  SDL_GLContext context_;
  std::unique_ptr<Sorter> sorter_;
};
