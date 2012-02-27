/* $Id: main.c,v 1.4 2012-02-14 20:49:59-08 - - $ */

/*
* Silly main program which just creates an intx box, puts a
* number in it, gets it back out, and deletes the box.
* Run with bcheck to verify no memory leaks.
*/

#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "intx.h"

char *execname = NULL;

void say_when (char *when) {
   struct timeval timeval;
   int retcode = gettimeofday (&timeval, NULL);
   if (retcode != 0) {
      fprintf (stderr, "%s: gettimeofday: %s\n",
               execname, strerror (errno));
   }
   struct tm *tm_buffer = localtime (&timeval.tv_sec);
   char buffer1[64];
   char buffer2[64];
   strftime (buffer1, sizeof buffer1, "%a %b %e %T", tm_buffer);
   strftime (buffer2, sizeof buffer2, " %Z %Y", tm_buffer);
   printf ("%s: %s: %s.%06ld %s\n", execname, when,
           buffer1, timeval.tv_usec, buffer2);
}

int main (int argc, char **argv) {
   argc = argc; // Avoid:16: warning: unused parameter 'argc'
   execname = basename (argv[0]);
   say_when ("starting");

   /* Declare the box and initialize it.  */
   intx_ref box = new_intx();
   printf ("box = %p\n", box);

   /* Perform a couple of operations on it.  */
   put_intx (box, 1024);
   printf ("box value is %d\n", get_intx (box));

   /* Free up the box and set the handle to NULL to avoid a dangle. */
   free_intx (box);
   box = NULL;

   /* OK! */
   say_when ("finished");
   return EXIT_SUCCESS;
}

