#include "selection_sort.h"

void SelectionSort::Sort(Sorter &sorter) {
  for (size_t i = 0; i < sorter.size(); ++i) {
    // find the smallest
    Uint32 k = i;
    for (size_t j = i + 1; j < sorter.size(); ++j) {
      if (!sorter.running()) return;
      if (sorter.Compare(j, k) < 0) {
        k = j;
      }
    }
    if (!sorter.running()) return;
    sorter.Swap(i, k);
  }
}
