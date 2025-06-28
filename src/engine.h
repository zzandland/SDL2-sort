#pragma once

#include <SDL.h>
#include <memory>

#include "screen.h"
#include "sorter.h"
#include "options.h"

enum class SDLEventType {
  kNoEvent = 0,
};

class Engine {
 public:
  Engine(const Uint32 width, const Uint32 height, const ProgramOptions& options);
  ~Engine();
  void Run();
  void MainLoopIteration();

 private:
  bool running_;
  SDL_Renderer* renderer_;
  SDL_Window* window_;
  SDL_GLContext context_;
  std::unique_ptr<Sorter> sorter_;
  std::shared_ptr<Screen> screen_;

  void PollAndHandleSDLEvent();
};
