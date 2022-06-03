#pragma once

#include "../sorter.h"

class QuickSort {
 public:
  static void Sort(Sorter &sorter);

 private:
  static void Recurse(int l, int r, Sorter &sorter);
  static size_t Partition(int l, int r, Sorter &sorter);
};
