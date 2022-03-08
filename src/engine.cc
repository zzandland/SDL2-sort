#if defined(_WIN32)
#include <windows.h>
#endif
#include <iostream>
#include <sstream>

#include "engine.h"

std::ostringstream err_msg;

Engine::Engine(const Uint32 width, const Uint32 height) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    err_msg << "Could not initialize SDL: " << SDL_GetError() << '\n';
    throw std::runtime_error(err_msg.str());
  }

  if (!(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))) {
    std::cout << "Warning: Linear Texture Filtering not enabled.\n";
  }

  window_ = SDL_CreateWindow(
      "SDL2Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
      height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

  if (nullptr == window_) {
    err_msg << "Could not create window: " << SDL_GetError() << '\n';
    throw std::runtime_error(err_msg.str());
  }

  SDL_Renderer* renderer =
      SDL_CreateRenderer(window_, -1, SDL_RENDERER_SOFTWARE);
  if (nullptr == renderer) {
    err_msg << "Could not create renderer: " << SDL_GetError() << '\n';
    throw std::runtime_error(err_msg.str());
  }

  context_ = SDL_GL_CreateContext(window_);

  const Uint32 size = width;

  Screen* screen = new Screen(renderer, width, height, size);
  sorter_ = new Sorter(screen, size);
}

Engine::~Engine() {
  delete sorter_;

  SDL_DestroyWindow(window_);
  window_ = nullptr;

  SDL_Quit();
}

void Engine::Run() {
  while (true) {
    sorter_->PollAndHandleSDLEvent();
  }
}
