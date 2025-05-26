#pragma once

#include <SDL.h>

#include <unordered_map>

enum class ColorState { DEFAULT, SCANNING, UPDATING, SORTED };

static inline SDL_Color GetColor(ColorState state) {
  switch (state) {
    case ColorState::DEFAULT:
      return {255, 255, 255, 255};  // Default color
    case ColorState::SCANNING:
      return {255, 255, 0, 255};  // Yellow for scanning
    case ColorState::UPDATING:
      return {255, 0, 0, 255};  // Red for updating
    case ColorState::SORTED:
      return {0, 255, 0, 255};  // Green for sorted
    default:
      return {255, 255, 255, 255};  // Fallback to default color
  }
}
