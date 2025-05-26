#include "bubble_sort.h"

void BubbleSort::Sort(Sorter &sorter) {
  for (size_t i = sorter.size() - 1; i > 0; --i) {
    for (size_t j = 0; j < i; ++j) {
      if (!sorter.running()) return;
      // swap if left element is greater than the right element
      if (sorter.Compare(j, j + 1) > 0) {
        if (!sorter.running()) return;
        sorter.Swap(j, j + 1);
      }
    }
  }
}
