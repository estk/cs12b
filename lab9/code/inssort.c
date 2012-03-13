#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void insertion_sort(void *base, size_t nel, size_t width,
  int (*compar)(const void *, const void *))
{
  void *copy = malloc(width);
  for (size_t sorted=1 ; sorted < nel ; ++sorted)
  {
    size_t slot = sorted;
    // LINTED
    memcpy(copy, base + (slot*width), width);
    for (; slot > 0; --slot)
    {
      // LINTED
      int cmp = compar (copy, base +(slot - 1)*width);
      if (cmp > 0) break;
      // LINTED
      memcpy(base+(slot*width), base+(slot-1)*width, width);
    }
    // LINTED
    memcpy(base+(slot*width), copy, width);
  }
  free(copy);
}
