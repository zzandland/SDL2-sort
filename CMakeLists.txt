cmake_minimum_required(VERSION 3.16)
project(SDL2-sort VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Emscripten specific setup ---
if(EMSCRIPTEN)
    # Add common warning flags for Emscripten buildsKE_CXX_FLAGS} -Wall -Wextra")
    # Define the shell file path relative to the source directory
    set(SHELL_FILE_PATH "${CMAKE_SOURCE_DIR}/shell.html") # Path to your custom shell file

    # Use SDL2, Freetype, pthreads
    set(USE_FLAGS "-s USE_SDL=2 -s USE_FREETYPE=1 -pthread")

    # Specify the custom shell file using the modern flag
    set(LINKER_FLAGS "--shell-file ${SHELL_FILE_PATH}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")

    # Add both USE_FLAGS and the shell file flag to the linker flags
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS} ${LINKER_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
endif()

# --- End Emscripten specific setup ---
include(CTest)
enable_testing()

set(TARGET_SRC "")
list(APPEND TARGET_SRC
    src/helper.h
    src/diagram/histogram.cc
    src/diagram/scatter_plot.cc
    src/algorithm/bubble_sort.cc
    src/algorithm/insertion_sort.cc
    src/algorithm/selection_sort.cc
    src/algorithm/quick_sort.cc
    src/algorithm/merge_sort.cc
    src/algorithm/heap_sort.cc
    src/screen.cc
    src/engine.cc
    src/sorter.cc
    src/options.cc
    src/main.cc
)

add_executable(${PROJECT_NAME} ${TARGET_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC src)

if(NOT EMSCRIPTEN)
    # Find and link SDL2 only for native builds
    find_package(SDL2 REQUIRED)
    target_link_libraries(${PROJECT_NAME} SDL2::SDL2)
endif()
