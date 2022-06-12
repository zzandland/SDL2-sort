#pragma once

#include <SDL.h>

#include <memory>
#include <thread>

#include "helper.h"
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
  std::thread t;
  SDL_Window* window_;
  SDL_GLContext context_;
  std::shared_ptr<Sorter> sorter_;

  void PollAndHandleSDLEvent();
};
