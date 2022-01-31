#if defined(_WIN32)
#include <windows.h>
#endif
#include <iostream>

#include "engine.h"
#include "helper.h"

Engine::Engine(const Uint32 width, const Uint32 height) : init_success_(true) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cout << "Could not initialize SDL: " << SDL_GetError();
    init_success_ = false;
    return;
  }

  if (!(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))) {
    std::cout << "Warning: Linear Texture Filtering not enabled.\n";
  }

  window_ = SDL_CreateWindow(
      "SDL2Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
      height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

  if (nullptr == window_) {
    std::cerr << "Could not create window: " << SDL_GetError() << '\n';
    init_success_ = false;
    return;
  }

  SDL_Renderer* renderer =
      SDL_CreateRenderer(window_, -1, SDL_RENDERER_SOFTWARE);
  if (nullptr == renderer) {
    std::cerr << "Could not create renderer: " << SDL_GetError() << '\n';
    init_success_ = false;
    return;
  }

  context_ = SDL_GL_CreateContext(window_);

  Screen* screen = new Screen(renderer, width, height);
  sorter_ = new Sorter(screen, 128);
}

Engine::~Engine() {
  delete sorter_;

  SDL_DestroyWindow(window_);
  window_ = nullptr;

  SDL_Quit();
}

bool Engine::InitCheck() { return init_success_; }

int Engine::Run() {
  if (EXIT_FAILURE == helper::HandleSDLEvent()) {
    return EXIT_FAILURE;
  }

  if (EXIT_FAILURE == sorter_->InsertionSort()) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
