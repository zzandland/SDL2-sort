#include <SDL.h>

#if defined(_WIN32)
#include <windows.h>
#endif
#include <iostream>

#include "engine.h"

int main(int argc, char **argv) {
  Engine *engine = new Engine();

  // constructor indicated a failure, early exit the program
  if (!engine->init_success_) {
    delete engine;
    return EXIT_FAILURE;
  }

  try {
    bool success = engine->Run();
    delete engine;
    return EXIT_SUCCESS;
  } catch (const std::runtime_error &error) {
    std::string error_msg =
        std::string("Caught a fatal error: ") + std::string(error.what());
#if defined(_WIN32)
    MessageBoxA(nullptr, error_msg.c_str(), NULL, MB_ICONERROR | MB_OK);
#else
    std::cerr << error_msg << endl;
#endif
    delete engine;
    return EXIT_FAILURE;
  }
}
