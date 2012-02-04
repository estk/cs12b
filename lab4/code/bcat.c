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
#include <libc.h>
#include <errno.h>
#include <libgen.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mflag, nflag, sflag;

//
// cat -
// Copy the contents of an already-opened file to stdout.
//

void catfile (char *filename, FILE *input) {
   int newlines=0;

   if (mflag) {
      char head[65] = "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::";
      printf("\n%s\n", head);
      printf("%s", filename);
      printf("\n%s\n\n", head);
   }

   if (nflag) {
      
   }

   if (sflag) {
      
   }

   for (;;) {
      int byte = getc (input);
      if (byte == EOF) break;
      if (sflag) {
         if (byte == '\n') newlines++;
         else newlines = 0;
         if (newlines <= 2) putchar (byte);
      }else {
         putchar (byte);
      }
   };
}

void usage() {
   printf("%s", "bcat [-mns] [filename...]");
   exit(1);
}

//
// main -
// Loop over files, if any, and cat each of them to stdout.
// Print error messages if appropriate.
//

int main (int argc, char **argv) {
   int exit_status = EXIT_SUCCESS;
   char *progname = basename (argv[0]);
   // add "-" to argv if no args
    if (argc != 1){
      char ch;
      int optind = 0;
      mflag = nflag = sflag = 0;
      // check for flags, then remove from argv
      while ((ch = getopt(argc, argv, "mns")) != -1) {
         switch (ch) {
         case 'm':
            mflag = 1; optind++; break;
         case 'n':
            nflag = 1; optind++; break;
         case 's':
            sflag = 1; optind++; break;
         default:
            usage();
         }
      }
      argc -= optind;
      argv += optind;
   }

   if (argc == 1) {
      catfile ("-", stdin);
   }

   for (int argi = 1; argi < argc; ++argi) {
      if (strcmp (argv[argi], "-") == 0) {
         catfile ("-", stdin);
      }else {
         FILE *input = fopen (argv[argi], "r");
         if (input == NULL) {
            fflush (NULL);
            fprintf (stderr, "%s: %s: %s\n", progname,
                     argv[argi], strerror (errno));
            fflush (NULL);
            exit_status = EXIT_FAILURE;
         }else{
            catfile (argv[argi], input);
            fclose (input);
         };
      };
   };
   return exit_status;
}

