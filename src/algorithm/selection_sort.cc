#include "selection_sort.h"

void SelectionSort::Sort(Sorter &sorter) {
  for (size_t i = 0; i < sorter.size_; ++i) {
    // find the smallest
    Uint32 min = sorter.data_[i];
    Uint32 k = i;
    for (size_t j = i + 1; j < sorter.size_; ++j) {
      if (sorter.data_[j] < min) {
        min = sorter.data_[j];
        k = j;
      }
      sorter.PollAndHandleSDLEvent();
      if (!sorter.running_) return;
      std::vector<size_t> tmp{i, j};
      sorter.Color(tmp);
    }
    sorter.PollAndHandleSDLEvent();
    if (!sorter.running_) return;
    sorter.Swap(i, k);
  }
}
