#pragma once

#include "../sorter.h"

class MergeSort {
 public:
  static void Sort(Sorter &sorter);

 private:
  static void Recurse(size_t l, size_t r, Sorter &sorter);
  static void InPlaceSort(size_t l, size_t r, size_t m, Sorter &sorter);
};
