#include <SDL.h>

#if defined(_WIN32)
#include <windows.h>
#endif
#include <iostream>

#include "engine.h"
#include "helper.h"

const Uint32 winWidth = 1536;
const Uint32 winHeight = 1024;

int main(int argc, char **argv) {
  Engine *engine = nullptr;
  try {
    engine = new Engine(winWidth, winHeight);
    engine->Run();
    delete engine;
    return EXIT_SUCCESS;
  } catch (const sdl_exception::EarlyQuit &) {
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
