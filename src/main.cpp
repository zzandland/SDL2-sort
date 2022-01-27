#include <SDL.h>

#if defined(_WIN32)
#include <windows.h>
#endif
#include <iostream>

int main(int argc, char **argv) {
  SDL_Init(SDL_INIT_VIDEO);

  uint32_t winWidth = 1024;
  uint32_t winHeight = 768;
  SDL_Window *window = SDL_CreateWindow(
      "SDL2Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winWidth,
      winHeight,
      SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

  // Check that the window was successfully created
  if (window == NULL) {
    // In the case that the window could not be made...
    std::cout << "Could not create window: " << SDL_GetError() << '\n';
    SDL_Quit();
    return EXIT_FAILURE;
  }

  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  SDL_GLContext context = SDL_GL_CreateContext(window);

  // A basic main loop to prevent blocking
  bool quit = false;
  try {
    SDL_Event event;
    while (!quit) {
      while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          quit = true;
        }
      }
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderClear(renderer);
      SDL_RenderPresent(renderer);
    }
  } catch (const std::runtime_error &error) {
    std::string error_msg =
        std::string("Caught a fatal error: ") + std::string(error.what());
#if defined(_WIN32)
    MessageBoxA(nullptr, error_msg.c_str(), NULL, MB_ICONERROR | MB_OK);
#else
    std::cerr << error_msg << endl;
#endif
    return EXIT_FAILURE;
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
