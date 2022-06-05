#include "merge_sort.h"

#include <iostream>

void MergeSort::Sort(Sorter &sorter) { Recurse(0, sorter.size_ - 1, sorter); }

void MergeSort::Recurse(int l, int r, Sorter &sorter) {
  sorter.PollAndHandleSDLEvent();
  if (!sorter.running_) return;
  if (l < r) {
    size_t m = l + (r - l) / 2;
    Recurse(l, m, sorter);
    Recurse(m + 1, r, sorter);
    InPlaceSort(l, r, m, sorter);
  }
}

void MergeSort::InPlaceSort(int l, int r, int m, Sorter &sorter) {
  int i = l;      // start of first array
  int j = m + 1;  // start of second array
  int tmp[r - l + 1];
  int k = 0;  // running index within the tmp array
  while (i <= m || j <= r) {
    int lVal = (i <= m) ? sorter.data_[i] : INT_MAX;
    int rVal = (j <= r) ? sorter.data_[j] : INT_MAX;
    if (lVal < rVal) {
      tmp[k++] = i;
      ++i;
    } else {
      tmp[k++] = j;
      ++j;
    }
  }
  std::cout << "*****" << l << ':' << r << ":" << m << std::endl;
  for (int h = 0; h < (r - l + 1); ++h) {
    std::cout << h << ':' << tmp[h] << std::endl;
  }
  k = 0;
  while (l + k <= r) {
    sorter.PollAndHandleSDLEvent();
    if (!sorter.running_) return;
    if (tmp[k] == l + k) {
      ++k;
      continue;
    }
    sorter.screen_->Update(tmp[k], l + k, true);
    std::swap(sorter.data_[tmp[k]], sorter.data_[l + k]);
    ++k;
  }
  for (int h = l; h <= r; ++h) {
    std::cout << h << ':' << sorter.data_[h] << std::endl;
  }
}
