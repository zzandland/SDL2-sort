#include "sorter.h"

#include "helper.h"

Sorter::Sorter(Screen *screen, size_t size) : screen_(screen) {
  data_.resize(size);
  for (size_t i = 0; i < size; ++i) {
    data_[i] = i + 1;
  }
}

Sorter::~Sorter() { delete screen_; }

int Sorter::Randomize() {
  SDL_Event event;
  size_t len = data_.size();
  size_t seed = (unsigned)time(NULL);
  srand(seed);
  for (size_t i = data_.size() - 1; i > 0; --i) {
    size_t j = rand() % (i + 1);
    screen_->Draw(i, j, true);
    std::swap(data_[i], data_[j]);
    if (EXIT_FAILURE == helper::HandleSDLEvent()) {
      return EXIT_FAILURE;
    }
  }
  return 0;
}

int Sorter::InsertionSort() {
  if (Randomize() < 0) {
    return -1;
  }

  size_t len = data_.size();
  SDL_Event event;
  for (size_t i = 0; i < len; ++i) {
    // find the smallest
    Uint32 min = data_[i];
    Uint32 k = i;
    for (size_t j = i + 1; j < len; ++j) {
      if (data_[j] < min) {
        min = data_[j];
        k = j;
      }
      screen_->Draw(i, j);
      if (EXIT_FAILURE == helper::HandleSDLEvent()) {
        return EXIT_FAILURE;
      }
    }
    screen_->Draw(i, k, true);
    std::swap(data_[i], data_[k]);
    if (EXIT_FAILURE == helper::HandleSDLEvent()) {
      return EXIT_FAILURE;
    }
  }

  return 0;
}
