#include "heap_sort.h"

void HeapSort::Sort(Sorter &sorter) {
  // build max heap
  size_t len = sorter.size();
  for (int i = len / 2 - 1; i >= 0; --i) {
    if (!sorter.running()) return;
    Heapify(sorter, i, len);
  }

  for (int i = len - 1; i > 0; --i) {
    if (!sorter.running()) return;
    sorter.Swap(0, i);
    Heapify(sorter, 0, i);
  }
}

void HeapSort::Heapify(Sorter &sorter, size_t i, size_t len) {
  size_t k = i;
  size_t l = 2 * i + 1;
  size_t r = 2 * i + 2;

  // determine if the left child is the largest
  if (!sorter.running()) return;
  if (l < len && sorter.Compare(l, k) > 0) {
    k = l;
  }

  // determine if the right child is the largest
  if (!sorter.running()) return;
  if (r < len && sorter.Compare(r, k) > 0) {
    k = r;
  }

  if (k != i) {
    if (!sorter.running()) return;
    sorter.Swap(i, k);
    Heapify(sorter, k, len);
  }
}
