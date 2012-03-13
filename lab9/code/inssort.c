#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void insertion_sort(void *base, size_t nel, size_t width,
  int (*compar)(const void *, const void *)) {
  void *copy = malloc(width);
  for (int sorted=1 ; sorted < (int)nel ; ++sorted) {
    int slot = sorted;
    memcpy(copy, base + (slot*width), width);
    for (; slot > 0; --slot) {
      int cmp = compar (copy, base +(slot - 1)*width);
      if (cmp > 0) break;
      memcpy(base+(slot*width), base+(slot-1)*width, width);
    }
    memcpy(base+(slot*width), copy, width);
  }
  free(copy);
}
