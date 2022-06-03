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
  for (size_t j = l; j < r; ++j) {
    sorter.PollAndHandleSDLEvent();
    if (!sorter.running_) return 0;
    sorter.screen_->Update(j, j);
    if (sorter.data_[j] < pivot) {
      ++i;
      sorter.screen_->Update(i, j, true);
      std::swap(sorter.data_[i], sorter.data_[j]);
    }
  }
  if (i + 1 != r) {
    sorter.screen_->Update(i + 1, r, true);
    std::swap(sorter.data_[i + 1], sorter.data_[r]);
  }
  return i + 1;
}
