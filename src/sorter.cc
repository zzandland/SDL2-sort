#include "sorter.h"

#include "algorithm/bubble_sort.h"
#include "algorithm/insertion_sort.h"
#include "algorithm/quick_sort.h"
#include "algorithm/selection_sort.h"
#include "helper.h"

Sorter::Sorter(Screen *screen, size_t size)
    : screen_(screen), running_(false), size_(size), selected_(1) {
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
            Sort();
          } else {
            screen_->Init();
            Init();
          }
          break;
        case SDLK_1:
          selected_ = 1;
          break;
        case SDLK_2:
          selected_ = 2;
          break;
        case SDLK_3:
          selected_ = 3;
          break;
        case SDLK_4:
          selected_ = 4;
          break;
        default:
          break;
      }
    }
  }
}

void Sorter::Sort() {
  Randomize();
  switch (selected_) {
    case 1:
      BubbleSort::Sort(*this);
      break;
    case 2:
      InsertionSort::Sort(*this);
      break;
    case 3:
      SelectionSort::Sort(*this);
    case 4:
      QuickSort::Sort(*this);
    default:
      break;
  }
  running_ = false;
}

void Sorter::set_size(const Uint32 size) {
  size_ = size;
  Init();
  screen_->set_size(size);
}

void Sorter::Randomize() {
  size_t len = data_.size();
  size_t seed = (unsigned)time(NULL);
  srand(seed);
  for (size_t i = data_.size() - 1; i > 0; --i) {
    PollAndHandleSDLEvent();
    if (!running_) return;
    size_t j = rand() % (i + 1);
    screen_->Update(i, j, true);
    std::swap(data_[i], data_[j]);
  }
}
