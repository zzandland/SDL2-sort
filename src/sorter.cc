#include "sorter.h"

#include "helper.h"

Sorter::Sorter(Screen *screen, size_t size) : screen_(screen), running_(false), size_(size) {
  Init();
}

Sorter::~Sorter() { delete screen_; }

void Sorter::Init() {
  data_.resize(size_);
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = i + 1;
  }
}

void Sorter::PollAndHandleSDLEvent() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (SDL_QUIT == event.type) {
      throw sdl_exception::EarlyQuit();
    }
    if (SDL_KEYDOWN == event.type) {
      switch (event.key.keysym.sym) {
        case SDLK_SPACE:
          running_ = !running_;
          if (running_) {
            InsertionSort();
          } else {
            screen_->Init();
            Init();
          }
          break;
        default:
          break;
      }
    }
  }
}

void Sorter::Randomize() {
  size_t len = data_.size();
  size_t seed = (unsigned)time(NULL);
  srand(seed);
  for (size_t i = data_.size() - 1; i > 0; --i) {
    size_t j = rand() % (i + 1);
    screen_->Update(i, j, true);
    std::swap(data_[i], data_[j]);
  }
}

void Sorter::InsertionSort() {
  Randomize();

  size_t len = data_.size();
  for (size_t i = 0; i < len; ++i) {
    // find the smallest
    Uint32 min = data_[i];
    Uint32 k = i;
    for (size_t j = i + 1; j < len; ++j) {
      if (data_[j] < min) {
        min = data_[j];
        k = j;
      }
      PollAndHandleSDLEvent();
      if (!running_) return;
      screen_->Update(i, j);
    }
    PollAndHandleSDLEvent();
    if (!running_) return;
    screen_->Update(i, k, true);
    std::swap(data_[i], data_[k]);
  }

  running_ = false;
}
