#include "sorter.h"

#include "algorithm/bubble_sort.h"
#include "algorithm/insertion_sort.h"
#include "algorithm/merge_sort.h"
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
        case SDLK_5:
          selected_ = 5;
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
      break;
    case 4:
      QuickSort::Sort(*this);
      break;
    case 5:
      MergeSort::Sort(*this);
      break;
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
    Swap(i, j);
  }
}

void Sorter::Color(std::vector<size_t> &indexes) {
  screen_->Update(data_, indexes, {100, 180, 100, SDL_ALPHA_OPAQUE});

  screen_->Render();

  // change the colors to be regular
  screen_->Update(data_, indexes, {170, 183, 184, SDL_ALPHA_OPAQUE});
}

void Sorter::Swap(size_t a, size_t b) {
  std::vector<size_t> indexes{a, b};
  // first clear the original elements
  Delete(indexes);

  std::swap(data_[a], data_[b]);

  // color the two elements being swapped
  screen_->Update(data_, indexes, {165, 105, 189, SDL_ALPHA_OPAQUE});

  screen_->Render();

  // change the colors to be regular
  screen_->Update(data_, indexes, {170, 183, 184, SDL_ALPHA_OPAQUE});
}

void Sorter::Delete(std::vector<size_t> &indexes) {
  screen_->Update(data_, indexes, {0, 0, 0, SDL_ALPHA_TRANSPARENT});
}
