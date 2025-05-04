#include "insertion_sort.h"

void InsertionSort::Sort(Sorter &sorter) {
  for (size_t i = 0; i < sorter.size() - 1; ++i) {
    for (size_t j = i + 1; j > 0 && sorter.data(j - 1) > sorter.data(j); --j) {
      if (!sorter.running()) return;
      sorter.Swap(j - 1, j);
    }
  }
}
