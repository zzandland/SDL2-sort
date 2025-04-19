#ifndef EVENT_H
#define EVENT_H

#include <SDL.h>  // For SDL_Color

#include <cstddef>  // For size_t
#include <vector>

struct SortEvent {
  enum class Type { Update, Render, Init };

  Type type;
  std::vector<Uint32> data;
  std::vector<size_t> indices;
  SDL_Color color;

  inline SortEvent(Type t, std::vector<Uint32> d, std::vector<size_t> i,
                   SDL_Color c)
      : type(t), data(std::move(d)), indices(std::move(i)), color(c) {}

  inline SortEvent(Type t) : type(t), data{}, indices{}, color{} {}
};

#endif  // EVENT_H
