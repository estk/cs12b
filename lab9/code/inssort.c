#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void insertion_sort(void *base, size_t nel, size_t width,
  int (*compar)(const void *, const void *)) {
  void *copy = malloc(width);
  for (int sorted=1 ; sorted < nel ; ++sorted) {
    int slot = sorted;
    memcpy(copy, base + (slot*width), width);
    for (; slot > 0; --slot) {
      int cmp = compar (base +(slot - 1)*width, copy);
      if (cmp > 0) break;
      void *p = (base + slot*width);
      p = base + (slot - 1)*width;
    }
    void *p = base + slot*width;
    p = copy;
  }
}
