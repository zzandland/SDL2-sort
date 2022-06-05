#pragma once

#include "../sorter.h"

class QuickSort {
 public:
  static void Sort(Sorter &sorter);

 private:
  static void Recurse(size_t l, size_t r, Sorter &sorter);
  static size_t Partition(size_t l, size_t r, Sorter &sorter);
};
