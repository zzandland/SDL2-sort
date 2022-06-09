#include "quick_sort.h"

void QuickSort::Sort(Sorter &sorter) { Recurse(0, sorter.size_ - 1, sorter); }

void QuickSort::Recurse(int l, int r, Sorter &sorter) {
  if (l < r) {
    size_t m = Partition(l, r, sorter);
    if (!sorter.running_) return;

    Recurse(l, m - 1, sorter);
    Recurse(m + 1, r, sorter);
  }
}

size_t QuickSort::Partition(int l, int r, Sorter &sorter) {
  Uint32 pivot = sorter.data_[r];
  int i = l - 1;
  std::vector<size_t> indexes;
  for (size_t j = l; j <= r; ++j) {
    indexes.push_back(j);
  }
  sorter.Color(indexes, {100, 180, 100, SDL_ALPHA_OPAQUE});
  for (size_t j = l; j < r; ++j) {
    if (!sorter.running_) return 0;
    if (sorter.data_[j] < pivot) {
      ++i;
      sorter.Swap(i, j, {100, 180, 100, SDL_ALPHA_OPAQUE});
    }
  }
  if (i + 1 != r) {
    sorter.Swap(i + 1, r, {100, 180, 100, SDL_ALPHA_OPAQUE});
  }
  sorter.Color(indexes, {170, 183, 184, SDL_ALPHA_OPAQUE});
  return i + 1;
}
