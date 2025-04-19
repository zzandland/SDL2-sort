cmake_minimum_required(VERSION 3.16)
project(SDL2-sort VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})

# Add the Homebrew SDL2 path to CMAKE_PREFIX_PATH
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew/Cellar/sdl2/2.32.4")

include(CTest)
enable_testing()

set(TARGET_SRC "")
list(APPEND TARGET_SRC
    src/helper.h
    src/diagram/histogram.cc
    src/diagram/histogram_factory.cc
    src/diagram/scatter_plot.cc
    src/diagram/scatter_plot_factory.cc
    src/algorithm/bubble_sort.cc
    src/algorithm/insertion_sort.cc
    src/algorithm/selection_sort.cc
    src/algorithm/quick_sort.cc
    src/algorithm/merge_sort.cc
    src/algorithm/heap_sort.cc
    src/screen.cc
    src/engine.cc
    src/sorter.cc
    src/main.cc
)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} ${TARGET_SRC})
target_include_directories(${PROJECT_NAME} PUBLIC src)

# Link against SDL2::SDL2 instead of SDL2::Main
target_link_libraries(${PROJECT_NAME} SDL2::SDL2)