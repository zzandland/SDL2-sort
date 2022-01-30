#include "screen.h"

#include "histogram.h"

Screen::Screen(SDL_Renderer* renderer, const Uint32 width, const Uint32 height)
    : renderer_(renderer), width_(width), height_(height) {
  diagram_ = new Histogram(128, width, height);
}

Screen::~Screen() {
  delete diagram_;
  SDL_DestroyRenderer(renderer_);
  renderer_ = nullptr;
}

void Screen::Draw() { diagram_->Draw(renderer_); }
