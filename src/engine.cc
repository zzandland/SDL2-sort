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

std::ostringstream err_msg;

// Global or static pointer to the engine instance for the Emscripten loop
Engine* g_engine_instance = nullptr;

// Wrapper function for Emscripten main loop
void emscripten_main_loop_wrapper() {
  if (g_engine_instance) {
    g_engine_instance->MainLoopIteration();
  }
}

Engine::Engine(const Uint32 width, const Uint32 height) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    err_msg << "Could not initialize SDL: " << SDL_GetError() << '\n';
    throw std::runtime_error(err_msg.str());
  }

  if (!(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))) {
    std::cout << "Warning: Linear Texture Filtering not enabled.\n";
  }

  window_ = SDL_CreateWindow("SDL2 Sort", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, width, height,
                             SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

  if (nullptr == window_) {
    err_msg << "Could not create window: " << SDL_GetError() << '\n';
    throw std::runtime_error(err_msg.str());
  }

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_SOFTWARE);
  if (nullptr == renderer_) {
    err_msg << "Could not create renderer: " << SDL_GetError() << '\n';
    throw std::runtime_error(err_msg.str());
  }

  // Get the actual drawable size which might differ due to High DPI
  int drawable_width, drawable_height;
  if (SDL_GetRendererOutputSize(renderer_, &drawable_width, &drawable_height) <
      0) {
    err_msg << "Could not get renderer output size: " << SDL_GetError() << '\n';
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    throw std::runtime_error(err_msg.str());
  }

  const Uint32 size = 256;

  screen_ =
      std::make_shared<Screen>(renderer_, static_cast<Uint32>(drawable_width),
                               static_cast<Uint32>(drawable_height), size);
  sorter_ = std::make_unique<Sorter>(size);
  sorter_->AddObserver(screen_);

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
#if defined(__EMSCRIPTEN__)
  // For Emscripten, set the main loop function
  // The -1 means use browser's requestAnimationFrame
  // 1 means simulate infinite loop
  emscripten_set_main_loop(emscripten_main_loop_wrapper, -1, 1);
#else
  // Native desktop loop
  while (true) {
    try {
      MainLoopIteration();
      // Add a small delay to prevent high CPU usage on native
      SDL_Delay(16);  // ~60 FPS
    } catch (const sdl_exception::EarlyQuit&) {
      break;  // Exit the loop if EarlyQuit is thrown
    }
  }
#endif
}

void Engine::MainLoopIteration() {
  // This function contains one iteration of the main loop
  PollAndHandleSDLEvent();
  // Add rendering logic here if it's not implicitly handled by observers
  // For example:
  // SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255); // Clear screen
  // SDL_RenderClear(renderer_);
  // screen_->Draw(); // Assuming Screen has a Draw method
  // SDL_RenderPresent(renderer_);
}

void Engine::PollAndHandleSDLEvent() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (SDL_QUIT == event.type) {
      // On Emscripten, throwing might not exit cleanly depending on flags.
      // Consider calling emscripten_cancel_main_loop() or similar.
#if defined(__EMSCRIPTEN__)
      emscripten_cancel_main_loop();
#else
      throw sdl_exception::EarlyQuit();
#endif
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
        case SDLK_z:
          screen_->set_diagram(DiagramType::kHistogram);
          break;
        case SDLK_x:
          screen_->set_diagram(DiagramType::kScatterPlot);
          break;
        default:
          break;
      }
    }
  }
}
