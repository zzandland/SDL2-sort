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
      sorter.screen_->Update(i, j);
    }
    sorter.PollAndHandleSDLEvent();
    if (!sorter.running_) return;
    sorter.screen_->Update(i, k, true);
    std::swap(sorter.data_[i], sorter.data_[k]);
  }
}
