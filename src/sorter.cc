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

Sorter::~Sorter() {
  // Ensure the thread is stopped and joined when the Sorter is destroyed
  if (running_) {
    running_ = false;
  }
  if (t_.joinable()) {
    t_.join();
  }
}

void Sorter::Init() {
  data_.resize(size_);
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = i + 1;
  }
  Notify(SortEvent(SortEvent::Type::Init));
}

void Sorter::StartAndStop() {
  if (running_) {
    // Request the thread to stop
    running_ = false;
    // Wait for the thread to finish cleanly
    if (t_.joinable()) {
      t_.join();
    }
  } else {
    // Ensure any previous thread is joined before starting a new one
    // This handles cases where the thread finished but wasn't joined yet
    if (t_.joinable()) {
      t_.join();
    }
    // Start the new sorting thread
    running_ = true;
    t_ = std::thread(&Sorter::Sort, this);
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

void Sorter::Update(size_t index, Uint32 val) {
  data_[index] = val;
  std::vector<size_t> indexes{index};
  Notify(SortEvent(SortEvent::Type::Update, data_, indexes));
}

void Sorter::Swap(size_t a, size_t b) {
  std::vector<size_t> indexes{a, b};
  std::swap(data_[a], data_[b]);

  Notify(SortEvent(SortEvent::Type::Update, data_, indexes));
}
