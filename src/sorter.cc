#include "sorter.h"

Sorter::Sorter(size_t size) {
  data_.resize(size);
  for (size_t i = 0; i < size; ++i) {
    data_[i] = i + 1;
  }
}
