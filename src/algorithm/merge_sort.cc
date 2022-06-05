#include "merge_sort.h"

#include <iostream>

void MergeSort::Sort(Sorter &sorter) { Recurse(0, sorter.size_ - 1, sorter); }

void MergeSort::Recurse(size_t l, size_t r, Sorter &sorter) {
  sorter.PollAndHandleSDLEvent();
  if (!sorter.running_) return;
  if (l < r) {
    size_t m = l + (r - l) / 2;
    Recurse(l, m, sorter);
    Recurse(m + 1, r, sorter);
    InPlaceSort(l, r, m, sorter);
  }
}

void MergeSort::InPlaceSort(size_t l, size_t r, size_t m, Sorter &sorter) {
  size_t i = l;      // start of first array
  size_t j = m + 1;  // start of second array
  int k = 0;         // running index within the tmp array
  Uint32 tmp[r - l + 1];
  while (i <= m || j <= r) {
    Uint32 lVal = (i <= m) ? sorter.data_[i] : INT_MAX;
    Uint32 rVal = (j <= r) ? sorter.data_[j] : INT_MAX;
    if (lVal < rVal) {
      tmp[k++] = sorter.data_[i];
      ++i;
    } else {
      tmp[k++] = sorter.data_[j];
      ++j;
    }
  }
  k = 0;
  while (l + k <= r) {
    sorter.PollAndHandleSDLEvent();
    if (!sorter.running_) return;
    if (tmp[k] == l + k) {
      ++k;
      continue;
    }
    std::vector<size_t> indexes{l + k};
    sorter.Delete(indexes);
    sorter.data_[l + k] = tmp[k];
    sorter.Color(indexes);
    ++k;
  }
}
