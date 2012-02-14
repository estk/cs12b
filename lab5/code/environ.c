#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

extern char **environ;

int
main (int argc, char **argv) {
  for (int i=0 ; environ[i] != NULL ; i++) {
    printf("%s\n", environ[i]);
  }
}
