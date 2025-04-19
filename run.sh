#!/bin/bash

# Exit immediately if a command exits with a non-zero status.
set -e

# Define the project root and build directory
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${PROJECT_ROOT}/build"
EXECUTABLE_NAME="SDL2-sort" # Match the project name in CMakeLists.txt
EXECUTABLE_PATH="${BUILD_DIR}/Debug/${EXECUTABLE_NAME}" # Assuming Debug build

echo "--- Checking for SDL2 installation ---"
if ! brew list sdl2 &>/dev/null; then
  echo "SDL2 not found. Attempting to install via Homebrew..."
  if brew install sdl2; then
    echo "SDL2 installed successfully."
  else
    echo "Failed to install SDL2. Please install it manually and try again."
    exit 1
  fi
else
  echo "SDL2 is already installed."
fi

echo "--- Configuring CMake ---"
# Create build directory if it doesn't exist
mkdir -p "${BUILD_DIR}"

# Configure CMake from the build directory
# Homebrew should make SDL2 findable by CMake automatically
# Specify the build type as Debug
cmake -S "${PROJECT_ROOT}" -B "${BUILD_DIR}" -DCMAKE_BUILD_TYPE=Debug

echo "--- Building project ---"
# Build the project from the build directory
cmake --build "${BUILD_DIR}"

echo "--- Running application ---"
# Check if the executable exists
if [ -f "${EXECUTABLE_PATH}" ]; then
  # Run the executable
  "${EXECUTABLE_PATH}"
else
  echo "Error: Executable not found at ${EXECUTABLE_PATH}"
  # Try the default output path if Debug wasn't explicitly set or used
  ALT_EXECUTABLE_PATH="${BUILD_DIR}/${EXECUTABLE_NAME}"
  if [ -f "${ALT_EXECUTABLE_PATH}" ]; then
     echo "Trying alternative path: ${ALT_EXECUTABLE_PATH}"
    "${ALT_EXECUTABLE_PATH}"
  else
     echo "Error: Executable not found at ${ALT_EXECUTABLE_PATH} either."
     exit 1
  fi
fi


echo "--- Script finished ---"
