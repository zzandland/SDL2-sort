#pragma once

#include "../sorter.h"

class HeapSort {
 public:
  static void Sort(Sorter &sorter);

 private:
  static void Heapify(Sorter &sorter, size_t i, size_t len);
};
