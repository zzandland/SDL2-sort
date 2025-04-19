#include "sorter.h"

#include "algorithm/bubble_sort.h"
#include "algorithm/heap_sort.h"
#include "algorithm/insertion_sort.h"
#include "algorithm/merge_sort.h"
#include "algorithm/quick_sort.h"
#include "algorithm/selection_sort.h"

Sorter::Sorter(size_t size)
    : running_(false), size_(size), selected_(Algorithm::kBubbleSort) {
  Init();
}

void Sorter::Init() {
  data_.resize(size_);
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = i + 1;
  }
  Notify(SortEvent(SortEvent::Type::Init));
}

void Sorter::StartAndStop() {
  running_ = !running_;
  if (running_) {
    t_ = std::thread(&Sorter::Sort, this);
    t_.detach();
  } else {
    running_ = false;
    Init();
  }
}

void Sorter::Sort() {
  Randomize();
  switch (selected_) {
    case Algorithm::kBubbleSort:
      BubbleSort::Sort(*this);
      break;
    case Algorithm::kInsertionSort:
      InsertionSort::Sort(*this);
      break;
    case Algorithm::kSelectionSort:
      SelectionSort::Sort(*this);
      break;
    case Algorithm::kQuickSort:
      QuickSort::Sort(*this);
      break;
    case Algorithm::kMergeSort:
      MergeSort::Sort(*this);
      break;
    case Algorithm::kHeapSort:
      HeapSort::Sort(*this);
      break;
    default:
      break;
  }
  running_ = false;
}

void Sorter::set_selected(Algorithm algorithm) { selected_ = algorithm; }

Uint32 Sorter::data(size_t index) { return data_[index]; }

void Sorter::set_data(size_t index, Uint32 val) { data_[index] = val; }

size_t Sorter::size() { return size_; }

bool Sorter::running() { return running_; }

void Sorter::toggle_running() { running_ = !running_; }

void Sorter::Randomize() {
  size_t len = data_.size();
  size_t seed = (unsigned)time(NULL);
  srand(seed);
  for (size_t i = data_.size() - 1; i > 0; --i) {
    if (!running_) return;
    size_t j = rand() % (i + 1);
    Swap(i, j);
  }
}

void Sorter::Highlight(size_t index) {
  // highlight the element at index
  Notify(SortEvent(SortEvent::Type::Update, data_, {index},

                   {100, 180, 100, SDL_ALPHA_OPAQUE}));
  Notify(SortEvent(SortEvent::Type::Render));

  // change the color to be regular
  Notify(SortEvent(SortEvent::Type::Update, data_, {index},
                   {170, 183, 184, SDL_ALPHA_OPAQUE}));
}

void Sorter::Color(std::vector<size_t> &indexes, SDL_Color color) {
  Notify(SortEvent(SortEvent::Type::Update, data_, indexes, color));

  Notify(SortEvent(SortEvent::Type::Render));
}

void Sorter::Color(size_t index, SDL_Color color) {
  Notify(SortEvent(SortEvent::Type::Update, data_, {index}, color));

  Notify(SortEvent(SortEvent::Type::Render));
}

void Sorter::Swap(size_t a, size_t b) {
  std::vector<size_t> indexes{a, b};
  // first clear the original elements
  Delete(indexes);

  std::swap(data_[a], data_[b]);

  // color the two elements being swapped
  Color(indexes, {165, 105, 189, SDL_ALPHA_OPAQUE});

  // change the colors to be regular
  Notify(SortEvent(SortEvent::Type::Update, data_, indexes,
                   {170, 183, 184, SDL_ALPHA_OPAQUE}));
}

void Sorter::Swap(size_t a, size_t b, SDL_Color color) {
  std::vector<size_t> indexes{a, b};
  // first clear the original elements
  Delete(indexes);

  std::swap(data_[a], data_[b]);

  // color the two elements being swapped
  Color(indexes, {165, 105, 189, SDL_ALPHA_OPAQUE});

  // change the colors to be what's provided in the input param
  Notify(SortEvent(SortEvent::Type::Update, data_, indexes, color));
}

void Sorter::Delete(std::vector<size_t> &indexes) {
  Notify(SortEvent(SortEvent::Type::Update, data_, indexes,
                   {0, 0, 0, SDL_ALPHA_TRANSPARENT}));
}

void Sorter::Delete(size_t index) {
  Notify(SortEvent(SortEvent::Type::Update, data_, {index},
                   {0, 0, 0, SDL_ALPHA_TRANSPARENT}));
}
