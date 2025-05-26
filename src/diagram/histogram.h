#pragma once

#include "diagram/diagram.h"

class Histogram : public Diagram {
 private:
  // Private constructor to prevent instantiation
  Histogram() = default;

  // Delete copy constructor and assignment operator
  Histogram(const Histogram&) = delete;
  Histogram& operator=(const Histogram&) = delete;

 public:
  static Histogram& GetInstance();

  void Render(SDL_Renderer* renderer, std::vector<Uint32>& data,
              std::vector<size_t>& indexes, Uint32 screen_width,
              Uint32 screen_height) override;
};
