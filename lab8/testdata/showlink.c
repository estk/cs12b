// $Id: showlink.c,v 1.1 2012-02-28 17:27:55-08 - - $

//
// Example of how to display a symbolic link.  This program is *NOT*
// called readlink, because one such already exists on Linux.
// Print a symlink or an error message.  PATH_MAX is the max length
// of a pathname.
//
// From man -s 2 readlink:
//
//    DESCRIPTION
//        readlink() places the contents of the symbolic link  path
//        in  the  buffer  buf,  which has size bufsiz.  readlink()
//        does not append a null byte to buf.  It will truncate the
//        contents  (to a length of bufsiz characters), in case the
//        buffer is too small to hold all of the contents.
//
// This looks like a bizarre design bug.
//

#include <errno.h>
#include <libgen.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char **argv) {
   int exit_status = EXIT_SUCCESS;
   for (int argi = 1; argi < argc; ++argi) {
      char *pathname = argv[argi];
      char linkname[PATH_MAX + 1];
      ssize_t retval = readlink (pathname, linkname, sizeof linkname);
      if (retval >= 0) {
         linkname[retval < PATH_MAX + 1 ? retval : PATH_MAX] = '\0';
         printf ("%s -> \"%s\"\n", pathname, linkname);
      }else {
         exit_status = EXIT_FAILURE;
         fflush (NULL);
         fprintf (stderr, "%s: %s: %s\n",
                  basename (argv[0]), pathname, strerror (errno));
         fflush (NULL);
      }
   }
   return exit_status;
}
