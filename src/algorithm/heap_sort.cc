#include "heap_sort.h"

void HeapSort::Sort(Sorter &sorter) {
  // build max heap
  size_t len = sorter.size();
  for (int i = len / 2 - 1; i >= 0; --i) {
    Heapify(sorter, i, len);
    if (!sorter.running()) return;
  }

  for (int i = len - 1; i > 0; --i) {
    sorter.Swap(0, i);

    Heapify(sorter, 0, i);
    if (!sorter.running()) return;
  }
}

void HeapSort::Heapify(Sorter &sorter, size_t i, size_t len) {
  size_t largest = i;
  size_t l = 2 * i + 1;
  size_t r = 2 * i + 2;

  if (!sorter.running()) return;

  // determine if the left child is the largest
  if (l < len && sorter.data(l) > sorter.data(largest)) {
    largest = l;
  }

  // determine if the right child is the largest
  if (r < len && sorter.data(r) > sorter.data(largest)) {
    largest = r;
  }

  if (largest != i) {
    sorter.Swap(i, largest);
    Heapify(sorter, largest, len);
  }
}
