#include <SDL.h>
#include "screen.h"

class Engine {
 public:
  bool init_success_;
  Screen* screen_;

  Engine(const Uint32 width, const Uint32 height);
  ~Engine();
  bool Run();

 private:
  SDL_Window* window_;
  SDL_GLContext context_;
};
