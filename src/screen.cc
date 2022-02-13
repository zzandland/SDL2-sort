#include "screen.h"

#include "diagram/histogram.h"

Screen::Screen(SDL_Renderer* renderer, const Uint32 width, const Uint32 height, const Uint32 size)
    : renderer_(renderer), width_(width), height_(height), size_(size) {
  diagram_ = new Histogram(renderer, size, width, height);
}

Screen::~Screen() {
  delete diagram_;
  SDL_DestroyRenderer(renderer_);
  renderer_ = nullptr;
}

void Screen::Init() {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_TRANSPARENT);
  SDL_RenderClear(renderer_);
  diagram_->Init(renderer_, size_, width_, height_);
}

void Screen::Update(size_t a, size_t b, bool isSwap) { 
  diagram_->Update(renderer_, a, b, isSwap);
}
