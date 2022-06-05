#include "quick_sort.h"

void QuickSort::Sort(Sorter &sorter) { Recurse(0, sorter.size_ - 1, sorter); }

void QuickSort::Recurse(size_t l, size_t r, Sorter &sorter) {
  if (l < r) {
    size_t m = Partition(l, r, sorter);
    if (!sorter.running_) return;

    Recurse(l, m - 1, sorter);
    Recurse(m + 1, r, sorter);
  }
}

size_t QuickSort::Partition(size_t l, size_t r, Sorter &sorter) {
  Uint32 pivot = sorter.data_[r];
  Sint32 i = l - 1;
  for (size_t j = l; j < r; ++j) {
    sorter.PollAndHandleSDLEvent();
    if (!sorter.running_) return 0;
    if (sorter.data_[j] < pivot) {
      ++i;
      sorter.Swap(i, j);
    }
  }
  if (i + 1 != r) {
    sorter.Swap(i + 1, r);
  }
  return i + 1;
}
