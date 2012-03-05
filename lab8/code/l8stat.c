#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

typedef struct stat stat_ref;

int fnum;
stat_ref *filestat;

void print_err(void) {
  strerror(errno);
  fprintf(stderr, "unable to stat node, errno: %d\n", errno);
}

void print_stat(char *name, stat_ref stat) {
  printf("%s is the fname\n", name);
  printf("%o is the mode\n", stat.st_mode);
  printf("%d is the size\n", (int)stat.st_size);
}

int main(int argc, char *argv[])
{
  fnum = argc-1;
  filestat = malloc (sizeof (struct stat));

  if (fnum == 0) {
    if (lstat ( "-", filestat)) print_err();
    else print_stat ("-", *filestat);
  } else {
    for (int i=1 ; i < argc ; i++) {
      char *fname = argv[i];
      if (lstat (fname, filestat)) print_err();
      else print_stat (fname, *filestat);
    }
  }

  return 0;
}
