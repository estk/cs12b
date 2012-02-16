// $Id: scanf.c,v 1.1 2012-02-09 18:53:09-08 - - $

// Demo usage of scanf(3c).
// Read in numbers and print them out one per line.

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
   char *progname = basename (argv[0]);
   char err_buffer [256];
   char err_buf_fmt[16];
   sprintf (err_buf_fmt, "%%%lds", sizeof err_buffer - 1);
   printf ("err_buf_fmt = \"%s\"\n", err_buf_fmt);

   for (;;) {

      // Try to read a double number.  Print an error message if a
      // word is not recognized as a number.  Stop at end of file.

      double number;
      int scancount = scanf ("%lg", &number);

      if (scancount == EOF) {
         printf ("%s: EOF\n", progname);
         break;
      }else if (scancount == 1) {
         printf ("%s: number = %.15g\n", progname, number);
      }else {
         scancount = scanf (err_buf_fmt, err_buffer);
         assert (scancount == 1);
         printf ("%s: bad number \"%s\"\n", progname, err_buffer);
      };
   };

   return EXIT_SUCCESS;
}

/*
//TEST// (echo 33 44 \
//TEST// ;echo 1e1000000 \
//TEST// ;echo 888888888888888888888888888888888888888888888888888888 \
//TEST// ;echo This-is-not a-number \
//TEST// ;echo .666666666666666666666666666666666 \
//TEST// ;echo -6.02e23 +Infinity -Infinity NaN \
//TEST// ) | runprog -x scanf.lis -0- ./scanf
//TEST// mkpspdf scanf.ps scanf.c* scanf.lis*
*/

