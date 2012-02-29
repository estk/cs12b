#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
int main (int argc, char **argv) {
   ssize_t argcs = argc;
   for (size_t i = 0; i < argcs; ++i) printf ("%s\n", argv[i]);
   size_t st = 31;
   uint32_t ut = 123456789;
   size_t d = ut % st;
   printf ("%lu\n", d);
}
