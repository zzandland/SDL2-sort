#ifndef EVENT_H
#define EVENT_H

#include <SDL.h>  // For SDL_Color

#include <cstddef>  // For size_t
#include <vector>

struct SortEvent {
  enum class Type { Update, Init };

  Type type;
  std::vector<Uint32> data;
  std::vector<size_t> indices;

  inline SortEvent(Type t, std::vector<Uint32> d, std::vector<size_t> i)
      : type(t), data(std::move(d)), indices(std::move(i)) {}

  inline SortEvent(Type t) : type(t), data{}, indices{} {}
};

#endif  // EVENT_H
