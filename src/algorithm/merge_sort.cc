#include "merge_sort.h"

#include <iostream>

void MergeSort::Sort(Sorter &sorter) { Recurse(0, sorter.size() - 1, sorter); }

void MergeSort::Recurse(int l, int r, Sorter &sorter) {
  if (!sorter.running()) return;
  if (l < r) {
    size_t m = l + (r - l) / 2;
    Recurse(l, m, sorter);
    Recurse(m + 1, r, sorter);
    InPlaceSort(l, r, m, sorter);
  }
}

void MergeSort::InPlaceSort(int l, int r, int m, Sorter &sorter) {
  size_t i = l;      // start of first array
  size_t j = m + 1;  // start of second array
  size_t k = 0;      // running index within the tmp array
  std::vector<size_t> indexes;
  for (int h = l; h <= r; ++h) {
    indexes.push_back(h);
  }
  int tmp[r - l + 1];
  while (i <= m || j <= r) {
    Uint32 lVal = (i <= m) ? sorter.data(i) : UINT_MAX;
    Uint32 rVal = (j <= r) ? sorter.data(j) : UINT_MAX;
    if (lVal < rVal) {
      tmp[k++] = sorter.data(i);
      ++i;
    } else {
      tmp[k++] = sorter.data(j);
      ++j;
    }
  }
  k = 0;  // reuse the variable for updating the actual data
  while (l + k <= r) {
    if (!sorter.running()) return;
    sorter.Update(l + k, tmp[k]);
    k++;
  }
}
