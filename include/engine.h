#include <SDL.h>

class Engine {
 public:
  bool init_success_;

  Engine();
  ~Engine();
  bool Run();

 private:
  SDL_Window* window_;
  SDL_Renderer* renderer_;
  SDL_GLContext context_;
};
