#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>
#include <limits.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct stat *stat_ref;
typedef struct tm   *tm_ref;

char buf[PATH_MAX+1];
stat_ref filestat;
char *execname;

void print_err(void) {
  fprintf (stderr, "%s: %s\n",
      execname, strerror (errno));
}

void print_stat(stat_ref stat) {
  tm_ref tstamp = localtime (&stat->st_mtime);
  time_t timenow;
  time(&timenow);

  int old = (stat->st_mtime < timenow - 60*60*24*180) ? 1 : 0;

  // print size, and mode
  printf("%6o %9d ", stat->st_mode, (int)stat->st_size);

  // print datetime
  char timestr[50];
  if (old)
    strftime (timestr, 50, "%b %e %Y ", tstamp);
  else
    strftime (timestr, 50, "%b %e %R ", tstamp);

  printf("%s", timestr);
}

void print_link(ssize_t idx, char *link, char *name) {
  link[idx < PATH_MAX+1 ? idx : PATH_MAX] = '\0';
  printf ("%s -> \"%s\"\n", name, link);
}

void statfile(char *name) {
  ssize_t linkres = readlink (name, buf, sizeof buf);
  int statres = lstat (name, filestat);

  if (!statres) {
    print_stat (filestat);

    if (linkres >= 0)
      print_link(linkres, buf, name);
    else
      printf("%s\n", name);
  }else
    print_err();
}


int main(int argc, char *argv[])
{
  execname = basename (argv[0]);
  filestat = malloc (sizeof (struct stat));

  if (argc-1 == 0) {
    statfile("-");
  } else {
    for (int i=1 ; i < argc ; i++) {
      statfile (argv[i]);
    }
  }

  return 0;
}
