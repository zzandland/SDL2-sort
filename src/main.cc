#include <SDL.h>

#if defined(_WIN32)
#include <windows.h>
#endif
#include <iostream>
#include <memory>
#include <string>

#include "engine.h"
#include "helper.h"
#include "options.h"

const Uint32 winWidth = 600;
const Uint32 winHeight = 400;

int main(int argc, char **argv) {
  ProgramOptions options = ParseCommandLine(argc, argv);

  std::unique_ptr<Engine> engine;
  try {
    engine = std::make_unique<Engine>(winWidth, winHeight, options);
    engine->Run();
    return EXIT_SUCCESS;
  } catch (const sdl_exception::EarlyQuit &) {
    return EXIT_SUCCESS;
  } catch (const std::runtime_error &error) {
    std::string error_msg =
        std::string("Caught a fatal error: ") + std::string(error.what());
#if defined(_WIN32)
    MessageBoxA(nullptr, error_msg.c_str(), NULL, MB_ICONERROR | MB_OK);
#else
    std::cerr << error_msg << std::endl;
#endif
    return EXIT_FAILURE;
  }
}
