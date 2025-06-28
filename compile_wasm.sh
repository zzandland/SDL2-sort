#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

# Set the EMSDK environment if it's not already set (for local builds)
if [ -z "$EMSDK" ]; then
  source ~/code/emsdk/emsdk_env.sh
fi

# Ensure the build_wasm directory exists
mkdir -p build_wasm

# Run CMake with Emscripten toolchain and enable WebGL and SDL2
# Added --use-port=sdl2 to ensure SDL2 is properly linked
emcmake cmake -S . -B build_wasm -DCMAKE_CXX_FLAGS="-s USE_SDL=2 --use-port=sdl2"

pushd build_wasm
# Compile the project
make -j

# Output success message
echo "Compilation for WebAssembly completed successfully. Output files are in the build_wasm directory."

popd