#ifndef EVENT_H
#define EVENT_H

#include <SDL.h>  // For SDL_Color

#include <cstddef>  // For size_t
#include <vector>

// Forward declaration if Sorter is needed within the event, though likely not
// class Sorter;

struct SortEvent {
  enum class Type {
    Swap,
    Highlight,
    Color,
    Delete,
    FullUpdate  // For Init, Randomize, or complete redraws
  };

  Type type;
  std::vector<size_t> indices;  // Indices affected by the operation
  SDL_Color
      color;  // Color used (relevant for Color, potentially Highlight/Swap)
  // Add other relevant data if needed in the future

  // Constructor examples (optional, but can be convenient)
  SortEvent(Type t, std::vector<size_t> idxs = {}, SDL_Color c = {0, 0, 0, 0})
      : type(t), indices(std::move(idxs)), color(c) {}

  SortEvent(Type t, size_t idx, SDL_Color c = {0, 0, 0, 0})
      : type(t), indices({idx}), color(c) {}
};

#endif  // EVENT_H
