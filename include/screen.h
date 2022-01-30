#include <SDL.h>

class Screen {
 public:
  Screen(SDL_Renderer* renderer, const Uint32 width, const Uint32 height);
  ~Screen();
  void Draw();

 private:
  Uint32 width_;
  Uint32 height_;
  SDL_Renderer* renderer_;
};
