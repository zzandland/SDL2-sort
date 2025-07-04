#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
#endif

#if defined(_WIN32)
#include <windows.h>
#endif
#include <iostream>
#include <memory>
#include <sstream>

#include "engine.h"
#include "helper.h"

std::ostringstream err_msg;

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

// Global or static pointer to the engine instance for the Emscripten loop
Engine* g_engine_instance = nullptr;

// Wrapper function for Emscripten main loop
void emscripten_main_loop_wrapper() {
  if (g_engine_instance) {
    g_engine_instance->MainLoopIteration();
  }
}

Engine::Engine(const Uint32 width, const Uint32 height,
               const ProgramOptions& options) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    err_msg << "Could not initialize SDL: " << SDL_GetError() << '\n';
    throw std::runtime_error(err_msg.str());
  }

  if (!(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))) {
    std::cout << "Warning: Linear Texture Filtering not enabled.\n";
  }

  window_ =
      SDL_CreateWindow("SDL2 Sort", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                       SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN |
                           SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE);

  if (nullptr == window_) {
    err_msg << "Could not create window: " << SDL_GetError() << '\n';
    throw std::runtime_error(err_msg.str());
  }

  renderer_ = SDL_CreateRenderer(
      window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (nullptr == renderer_) {
    err_msg << "Could not create renderer: " << SDL_GetError() << '\n';
    throw std::runtime_error(err_msg.str());
  }

  // Get the actual drawable size which might differ due to High DPI
  if (SDL_GetRendererOutputSize(renderer_, &SCREEN_WIDTH, &SCREEN_HEIGHT) < 0) {
    err_msg << "Could not get renderer output size: " << SDL_GetError() << '\n';
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    throw std::runtime_error(err_msg.str());
  }

  const Uint32 size = 150;
  screen_ =
      std::make_shared<Screen>(renderer_, static_cast<Uint32>(SCREEN_WIDTH),
                               static_cast<Uint32>(SCREEN_HEIGHT));
  sorter_ = std::make_unique<Sorter>(size);

  sorter_->set_selected(options.algorithm);
  screen_->set_diagram(options.diagram);

  g_engine_instance = this;  // Set the global instance
}

Engine::~Engine() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
  window_ = nullptr;

  SDL_Quit();

  g_engine_instance = nullptr;
}

void Engine::Run() {
  running_ = true;
#if defined(__EMSCRIPTEN__)
  // For Emscripten, set the main loop function
  // The -1 means use browser's requestAnimationFrame
  // 1 means simulate infinite loop
  emscripten_set_main_loop(emscripten_main_loop_wrapper, 60, 1);
#else
  // Native desktop loop
  while (running_) {
    try {
      MainLoopIteration();
      // Add a small delay to prevent high CPU usage on native
      SDL_Delay(16);
    } catch (const sdl_exception::EarlyQuit&) {
      break;  // Exit the loop if EarlyQuit is thrown
    }
  }
#endif
}

void Engine::MainLoopIteration() {
  // This function contains one iteration of the main loop
  PollAndHandleSDLEvent();
}

void Engine::PollAndHandleSDLEvent() {
  SDL_Event event;
  while (running_ && SDL_PollEvent(&event)) {
    if (SDL_USEREVENT == event.type) {
      SortEvent* sort_event = static_cast<SortEvent*>(event.user.data1);
      if (sort_event) {
        screen_->Update(*sort_event);
        delete sort_event;
      } else {
        err_msg << "Received null SortEvent in SDL_USEREVENT.\n";
        throw std::runtime_error(err_msg.str());
      }
      sorter_->Release();
      continue;
    }

    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
      if (SDL_GetRendererOutputSize(renderer_, &SCREEN_WIDTH, &SCREEN_HEIGHT) <
          0) {
        err_msg << "Could not get renderer output size: " << SDL_GetError()
                << '\n';
        SDL_DestroyRenderer(renderer_);
        SDL_DestroyWindow(window_);
        throw std::runtime_error(err_msg.str());
      }

      // Update the renderer's viewport
      SDL_RenderSetLogicalSize(renderer_, SCREEN_WIDTH, SCREEN_HEIGHT);

      // Update the screen object dimensions if necessary
      screen_->Resize(SCREEN_WIDTH, SCREEN_HEIGHT);
      continue;
    }

    switch (event.type) {
      case SDL_QUIT:
#if defined(__EMSCRIPTEN__)
        emscripten_cancel_main_loop();
#endif
        running_ = false;
        break;

      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
#if defined(__EMSCRIPTEN__)
            emscripten_cancel_main_loop();
#endif
            running_ = false;
            break;
          case SDLK_SPACE:
            if (sorter_->running()) {
              sorter_->Stop();
            } else {
              sorter_->Start();
            }
            break;
          default:
            break;
        }
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (sorter_->running()) {
          sorter_->Stop();
        } else {
          sorter_->Start();
        }
        break;
    }
  }
}
