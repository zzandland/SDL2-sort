#include "sorter.h"

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
        case SDLK_z:
          set_size(128);
          break;
        case SDLK_x:
          set_size(256);
          break;
        case SDLK_c:
          set_size(512);
          break;
        default:
          break;
      }
    }
  }
}

void Sorter::Sort() {
  switch (selected_) {
    case 1:
      BubbleSort();
      break;
    case 2:
      InsertionSort();
      break;
    case 3:
      SelectionSort();
    case 4:
      QuickSort();
    default:
      break;
  }
}

void Sorter::set_size(const Uint32 size) {
  size_ = size;
  Init();
  screen_->set_size(size);
}

void Sorter::QuickSortHelper(int l, int r) {
  if (l < r) {
    size_t m = QuickSortPartition(l, r);
    if (!running_) return;

    QuickSortHelper(l, m - 1);
    QuickSortHelper(m + 1, r);
  }
}

size_t Sorter::QuickSortPartition(int l, int r) {
  Uint32 pivot = data_[r];
  int i = l - 1;
  for (size_t j = l; j < r; ++j) {
    PollAndHandleSDLEvent();
    if (!running_) return 0;
    screen_->Update(j, j);
    if (data_[j] < pivot) {
      ++i;
      screen_->Update(i, j, true);
      std::swap(data_[i], data_[j]);
    }
  }
  if (i + 1 != r) {
    screen_->Update(i + 1, r, true);
    std::swap(data_[i + 1], data_[r]);
  }
  return i + 1;
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

void Sorter::BubbleSort() {
  Randomize();

  for (size_t i = size_ - 1; i > 0; --i) {
    for (size_t j = 0; j < i; ++j) {
      PollAndHandleSDLEvent();
      if (!running_) return;
      screen_->Update(j, j + 1);
      // swap if left element is greater than the right element
      if (data_[j] > data_[j + 1]) {
        screen_->Update(j, j + 1, true);
        std::swap(data_[j], data_[j + 1]);
      }
    }
  }

  running_ = false;
}

void Sorter::InsertionSort() {
  Randomize();

  for (size_t i = 0; i < size_ - 1; ++i) {
    for (size_t j = i + 1; j > 0 && data_[j - 1] > data_[j]; --j) {
      PollAndHandleSDLEvent();
      if (!running_) return;
      // swap
      screen_->Update(j - 1, j, true);
      std::swap(data_[j - 1], data_[j]);
    }
  }

  running_ = false;
}

void Sorter::SelectionSort() {
  Randomize();

  for (size_t i = 0; i < size_; ++i) {
    // find the smallest
    Uint32 min = data_[i];
    Uint32 k = i;
    for (size_t j = i + 1; j < size_; ++j) {
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

void Sorter::QuickSort() {
  Randomize();
  QuickSortHelper(0, size_ - 1);
  running_ = false;
}
