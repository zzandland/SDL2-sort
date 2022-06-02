cmake_minimum_required(VERSION 3.0.0)
project(SDL2-sort VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/sdl2")

include(CTest)
enable_testing()

include_directories(src)

set(TARGET_SRC "")
list(APPEND TARGET_SRC
    src/helper.h
    src/diagram/histogram.cc
    src/diagram/line.cc
    src/screen.cc
    src/engine.cc
    src/sorter.cc
    src/main.cc
)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} ${TARGET_SRC})
target_link_libraries(${PROJECT_NAME} SDL2::Main)