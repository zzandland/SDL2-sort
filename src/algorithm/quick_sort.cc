#include "quick_sort.h"

void QuickSort::Sort(Sorter &sorter) { Recurse(0, sorter.size() - 1, sorter); }

void QuickSort::Recurse(int l, int r, Sorter &sorter) {
  if (l < r) {
    size_t m = Partition(l, r, sorter);
    if (!sorter.running()) return;

    Recurse(l, m - 1, sorter);
    Recurse(m + 1, r, sorter);
  }
}

size_t QuickSort::Partition(int l, int r, Sorter &sorter) {
  size_t pivot = r;
  size_t i = l - 1;
  for (size_t j = l; j < r; ++j) {
    if (!sorter.running()) return 0;
    if (sorter.Compare(j, pivot) < 0) {
      ++i;
      if (!sorter.running()) return 0;
      sorter.Swap(i, j);
    }
  }
  if (i + 1 != r) {
    if (!sorter.running()) return 0;
    sorter.Swap(i + 1, r);
  }
  return i + 1;
}
