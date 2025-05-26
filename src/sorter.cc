#include "sorter.h"

#include "algorithm/bubble_sort.h"
#include "algorithm/heap_sort.h"
#include "algorithm/insertion_sort.h"
#include "algorithm/merge_sort.h"
#include "algorithm/quick_sort.h"
#include "algorithm/selection_sort.h"

Sorter::Sorter(size_t size)
    : running_(false), size_(size), selected_(Algorithm::kBubbleSort) {
  event_sem_ = SDL_CreateSemaphore(10);
  Init();
}

Sorter::~Sorter() {
  SDL_DestroySemaphore(event_sem_);
  Stop();
}

void Sorter::Init() {
  data_.resize(size_);
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = i + 1;
  }
  Publish(std::make_unique<SortEvent>(data_));
}

void Sorter::Start() {
  // Ensure any previous thread is joined before starting a new one
  // This handles cases where the thread finished but wasn't joined yet
  if (t_.joinable()) {
    t_.join();
  }
  // Start the new sorting thread
  running_ = true;
  Init();
  t_ = std::thread(&Sorter::Sort, this);
}

void Sorter::Stop() {
  running_ = false;
  // Wait for the thread to finish cleanly
  if (t_.joinable()) {
    t_.join();
  }
}

void Sorter::Sort() {
  Randomize();
  std::cout << "Starting sorting with algorithm: "
            << static_cast<int>(selected_) << std::endl;
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
      std::cout << "Unknown sorting algorithm selected" << std::endl;
      break;
  }
  std::cout << "Sorting completed" << std::endl;
  running_ = false;
}

void Sorter::set_selected(Algorithm algorithm) {
  Stop();
  selected_ = algorithm;
}

Uint32 Sorter::data(size_t index) { return data_[index]; }

void Sorter::set_data(size_t index, Uint32 val) { data_[index] = val; }

size_t Sorter::size() { return size_; }

bool Sorter::running() { return running_; }

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
  std::vector<ColorState> colors{ColorState::UPDATING};
  Publish(std::make_unique<SortEvent>(data_, indexes, colors));
}

void Sorter::Swap(size_t a, size_t b) {
  if (a > b) {
    std::swap(a, b);
  }
  std::vector<size_t> indexes{a, b};
  std::vector<ColorState> colors{ColorState::UPDATING, ColorState::UPDATING};
  std::swap(data_[a], data_[b]);

  Publish(std::make_unique<SortEvent>(data_, indexes, colors));
}

int Sorter::Compare(size_t a, size_t b) {
  int compare = 0;
  if (data_[a] < data_[b]) {
    compare = -1;  // a is less than b
  } else if (data_[a] > data_[b]) {
    compare = 1;  // a is greater than b
  }

  if (a > b) {
    std::swap(a, b);
  }
  std::vector<size_t> indexes{a, b};
  std::vector<ColorState> colors{ColorState::SCANNING, ColorState::SCANNING};
  Publish(std::make_unique<SortEvent>(data_, indexes, colors));

  return compare;  // return comparison result
}

void Sorter::Color(size_t a, ColorState color) {
  if (a >= data_.size()) {
    return;  // Prevent out-of-bounds access
  }
  std::vector<size_t> indexes{a};
  std::vector<ColorState> colors{color};
  Publish(std::make_unique<SortEvent>(data_, indexes, colors));
}

void Sorter::Publish(std::unique_ptr<SortEvent> event) {
  SDL_SemWait(event_sem_);

  SDL_Event sdl_event;
  sdl_event.type = SDL_USEREVENT;
  sdl_event.user.data1 = static_cast<void *>(event.release());
  sdl_event.user.data2 = nullptr;

  if (SDL_PushEvent(&sdl_event) < 0) {
    SDL_Log("Failed to push event: %s", SDL_GetError());
    Release();
    return;
  }
}

void Sorter::Release() { SDL_SemPost(event_sem_); }
