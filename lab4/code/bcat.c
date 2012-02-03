// $Id: bcat.c,v 1.2 2012-02-01 13:40:11-08 - - $

//
// NAME
//    bcat - concatenate and display files
//
// SYNOPSIS
//    bcat [filename...]
//
// DESCRIPTION
//    The `bcat' utility reads each file in sequence and writes it
//    to stdout.  If any filename is given as the single character
//    `-', stdin is read at that point.  If no filenames are given
//    then stdin is read as the only file.
//

#include <errno.h>
#include <libgen.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// cat -
// Copy the contents of an already-opened file to stdout.
//

void catfile (FILE *input) {
   for (;;) {
      int byte = getc (input);
      if (byte == EOF) break;
      (void) putchar (byte);
   };
}


//
// main -
// Loop over files, if any, and cat each of them to stdout.
// Print error messages if appropriate.
//

int main (int argc, char **argv) {
   int exit_status = EXIT_SUCCESS;
   char *progname = basename (argv[0]);
   if (argc == 1) {
      catfile (stdin);
   }else{
      for (int argi = 1; argi < argc; ++argi) {
         if (strcmp (argv[argi], "-") == 0) {
            catfile (stdin);
         }else{
            FILE *input = fopen (argv[argi], "r");
            if (input == NULL) {
               fflush (NULL);
               fprintf (stderr, "%s: %s: %s\n", progname,
                        argv[argi], strerror (errno));
               fflush (NULL);
               exit_status = EXIT_FAILURE;
            }else{
               catfile (input);
               fclose (input);
            };
         };
      };
   };
   return exit_status;
}

