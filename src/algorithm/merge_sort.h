#pragma once

#include "../sorter.h"

class MergeSort {
 public:
  static void Sort(Sorter &sorter);

 private:
  static void Recurse(int l, int r, Sorter &sorter);
  static void InPlaceSort(int l, int r, int m, Sorter &sorter);
};
