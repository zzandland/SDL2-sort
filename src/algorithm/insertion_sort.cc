#include "insertion_sort.h"

void InsertionSort::Sort(Sorter &sorter) {
  for (size_t i = 0; i < sorter.size() - 1; ++i) {
    for (size_t j = i + 1; j > 0; --j) {
      if (!sorter.running()) return;
      if (sorter.Compare(j - 1, j) <= 0) {
        break;
      }
      if (!sorter.running()) return;
      sorter.Swap(j - 1, j);
    }
  }
}
