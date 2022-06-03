#include "insertion_sort.h"

void InsertionSort::Sort(Sorter &sorter) {
  for (size_t i = 0; i < sorter.size_ - 1; ++i) {
    for (size_t j = i + 1; j > 0 && sorter.data_[j - 1] > sorter.data_[j];
         --j) {
      sorter.PollAndHandleSDLEvent();
      if (!sorter.running_) return;
      // swap
      sorter.screen_->Update(j - 1, j, true);
      std::swap(sorter.data_[j - 1], sorter.data_[j]);
    }
  }
}
