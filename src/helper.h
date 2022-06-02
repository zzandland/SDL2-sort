#pragma once

#include <SDL.h>

#include <exception>

namespace sdl_exception {
class EarlyQuit : public std::exception {
  using std::exception::exception;
};
}  // namespace sdl_exception
