#pragma once

#include <SDL.h>

#include <exception>

namespace sdl_exception {
class EarlyQuit : public std::exception {
  using std::exception::exception;
};
}  // namespace SDL_Event

namespace helper {
enum class SDLEventType {
  kNoEvent = 0,
};

inline SDLEventType HandleSDLEvent() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      throw sdl_exception::EarlyQuit();
    }
  }
  return SDLEventType::kNoEvent;
}
}  // namespace helper
