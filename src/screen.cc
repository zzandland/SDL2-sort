#include "screen.h"

Screen::Screen(SDL_Renderer* renderer, const Uint32 width, const Uint32 height)
    : renderer_(renderer), width_(width), height_(height) {}

Screen::~Screen() {
  SDL_DestroyRenderer(renderer_);
  renderer_ = nullptr;
}

void Screen::Draw() {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer_);
  SDL_RenderPresent(renderer_);
}
