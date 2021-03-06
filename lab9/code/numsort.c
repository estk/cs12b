#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "inssort.h"

#define ARYLEN 1000

int lgcmp(const void *a, const void *b)
{
  const double *a1 = a;
  const double *b1 = b;

  if (*a1 > *b1) return 1;
  if (*b1 > *a1) return -1;
  return 0;
}

int main(void)
{
  double *array = malloc (sizeof (double) * ARYLEN);
  // read nums
  int nums = 0;
  double tmp;
  for (int i=0 ; i<ARYLEN; i++) {
    int res = scanf("%lg\n", &tmp);
    if (res != 1) break;
    array[i] = tmp;
    nums++;
  }
  // sort zem
  // LINTED
  insertion_sort(array, (size_t)nums, sizeof(double), lgcmp);

  // print zem
  for (int i=0 ; i<nums ; i++)
    printf("%20.15g\n", array[i]);

  return 0;
}
