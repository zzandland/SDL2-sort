#include "bubble_sort.h"

void BubbleSort::Sort(Sorter &sorter) {
  for (size_t i = sorter.size_ - 1; i > 0; --i) {
    for (size_t j = 0; j < i; ++j) {
      sorter.PollAndHandleSDLEvent();
      if (!sorter.running_) return;
      // swap if left element is greater than the right element
      if (sorter.data_[j] > sorter.data_[j + 1]) {
        sorter.Swap(j, j + 1);
      }
    }
  }
}