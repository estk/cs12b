#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "inssort.h"

#define ARYLEN 1000
#define BUFLEN 1000

char **array;
char *buf;

int scmp(const void *a, const void *b) {
  const char **a1 = (const char **)a;
  const char **b1 = (const char **)b;

  return strcmp(*a1, *b1);
}

int main(int argc, const char *argv[])
{
	array = malloc (sizeof(char*) * ARYLEN);
	buf = malloc (sizeof(char) * BUFLEN);
  // read lines
  int lines = 0;
  for (int i=0 ; i<ARYLEN ; i++) {
    int res = scanf("%s\n", buf);
    if (res != 1) break;
    lines++;
    array[i] = strdup(buf);
  }

  /*for (int i=0 ; i<lines ; i++)*/
    /*printf("%s\n", array[i]);*/

  // sort zem
  qsort(array, lines, sizeof(char *), scmp);

  // print zem
  for (int i=0 ; i<lines ; i++)
    printf("%s\n", array[i]);

  return 0;
}
