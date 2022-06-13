#include "selection_sort.h"

void SelectionSort::Sort(Sorter &sorter) {
  for (size_t i = 0; i < sorter.size(); ++i) {
    // find the smallest
    Uint32 min = sorter.data(i);
    Uint32 k = i;
    sorter.Color(i, {100, 180, 100, SDL_ALPHA_OPAQUE});
    for (size_t j = i + 1; j < sorter.size(); ++j) {
      if (sorter.data(j) < min) {
        min = sorter.data(j);
        k = j;
      }
      if (!sorter.running()) return;
      sorter.Highlight(j);
    }
    sorter.Color(i, {170, 183, 184, SDL_ALPHA_OPAQUE});
    if (!sorter.running()) return;
    sorter.Swap(i, k);
  }
}
