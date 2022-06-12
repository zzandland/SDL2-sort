#if defined(_WIN32)
#include <windows.h>
#endif
#include <iostream>
#include <memory>
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

  sorter_ = std::make_unique<Sorter>(
      std::make_unique<Screen>(renderer, width, height, size), size);
}

Engine::~Engine() {
  SDL_DestroyWindow(window_);
  window_ = nullptr;

  SDL_Quit();
}

void Engine::Run() {
  while (true) {
    PollAndHandleSDLEvent();
  }
}

void Engine::PollAndHandleSDLEvent() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (SDL_QUIT == event.type) {
      throw sdl_exception::EarlyQuit();
    }
    if (SDL_KEYDOWN == event.type) {
      switch (event.key.keysym.sym) {
        case SDLK_SPACE:
          sorter_->StartAndStop();
          break;
        case SDLK_1:
          sorter_->set_selected(Algorithm::kBubbleSort);
          break;
        case SDLK_2:
          sorter_->set_selected(Algorithm::kInsertionSort);
          break;
        case SDLK_3:
          sorter_->set_selected(Algorithm::kSelectionSort);
          break;
        case SDLK_4:
          sorter_->set_selected(Algorithm::kQuickSort);
          break;
        case SDLK_5:
          sorter_->set_selected(Algorithm::kMergeSort);
          break;
        case SDLK_6:
          sorter_->set_selected(Algorithm::kHeapSort);
          break;
        default:
          break;
      }
    }
  }
}
