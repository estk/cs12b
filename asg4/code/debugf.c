// $Id: debugf.c,v 1.4 2012-02-22 19:50:19-08 - - $

#include <errno.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "debugf.h"

static char *debugflags = "";
static bool alldebugflags = false;
static char *execname = NULL;

void set_execname (char *name) {
   execname = name;
}

void print_execname (FILE *out) {
   if (execname != NULL) fprintf (out, "%s: ", execname);
}

void __stubprintf (char *filename, int line, const char *func,
                   char *format, ...) {
   va_list args;
   fflush (NULL);
   print_execname (stdout);
   fprintf (stdout, "STUB: %s[%d] %s:\n", filename, line, func);
   va_start (args, format);
   vfprintf (stdout, format, args);
   va_end (args);
   fflush (NULL);
}

void set_debugflags (char *flags) {
   debugflags = flags;
   if (strchr (debugflags, '@') != NULL) alldebugflags = true;
   DEBUGF ('a', "Debugflags = \"%s\"\n", debugflags);
}

void __debugprintf (char flag, char *file, int line,
                    char *format, ...) {
   va_list args;
   if (alldebugflags || strchr (debugflags, flag) != NULL) {
      fflush (NULL);
      print_execname (stderr);
      fprintf (stderr, "DEBUGF(%c): %s[%d]:\n",
                flag, file, line);
      va_start (args, format);
      vfprintf (stderr, format, args);
      va_end (args);
      fflush (NULL);
   }
}

