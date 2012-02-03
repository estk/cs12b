// $Id: structopts.c,v 1.1 2012-01-31 18:13:32-08 - - $

//
// NAME
//    structopts - checks and prints out some option values
//
// SYNOPSIS
//    structopts [-cmnstv]
//
// DESCRIPTION
//    Uses getopt(3) to scan options.  Prints out the values of the
//    resulting option structure.
//

#include <libgen.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef enum {FALSE = 0, TRUE = 1} bool;

struct options {
   bool moretitles;    // -m print file titles à la `more'
   bool numberlines;   // -n print line numbers in left column
   bool squeeze;       // -s squeeze multiple blank lines into one
};

//
// Function to print out the options.  Note that the inline struct
// from the main program is passed by reference.
//
void printoptions (struct options *options_ref) {
   printf ("moretitles   = %d\n", options_ref->moretitles  );
   printf ("numberlines  = %d\n", options_ref->numberlines );
   printf ("squeeze      = %d\n", options_ref->squeeze     );
}


//
// Main function to analyze options and print them.
//

int main (int argc, char **argv) {
   char *progname = basename (argv[0]);
   int exit_status = EXIT_SUCCESS;
   struct options options;
   int argi;
   memset (&options, 0, sizeof options); // set all opts FALSE

   //
   // Scan arguments and set flags.
   //
   opterr = FALSE;
   for (;;) {
      int option = getopt (argc, argv, "mns");
      if (option == EOF) break;
      switch (option) {
         case 'm': options.moretitles   = TRUE; break;
         case 'n': options.numberlines  = TRUE; break;
         case 's': options.squeeze      = TRUE; break;
         default : fflush (NULL);
                   fprintf (stderr, "%s: -%c: invalid option\n",
                            progname, optopt);
                   fflush (NULL);
                   exit_status = EXIT_FAILURE;
      };
   };

   //
   // Print options and operands.
   //
   printoptions (&options);

   for (argi = optind; argi < argc; ++argi) {
      printf ("argv[%d] operand = \"%s\"\n", argi, argv[argi]);
   };

   return exit_status;
}

//TEST// runprog -x structopts.lis structopts -m -n foo bar
//TEST// mkpspdf Listing.structopts.ps structopts.c* structopts.lis*

