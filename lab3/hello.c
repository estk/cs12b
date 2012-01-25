// $Id: hello.c,v 1.1 2012-01-24 19:58:03-08 - - $

//
// NAME
//    hello - the canonical hello world program
//
// SYNOPSIS
//    hello
//
// DESCRIPTION
//    Prints the message "Hello, world!"
//

#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
   if (argc != 1) {
      fprintf (stderr, "Usage: %s\n", basename (argv[0]));
      exit (EXIT_FAILURE);
   }
   printf ("Hello, World!\n");
   return EXIT_SUCCESS;
}

//TEST// runprogram.perl -x hello.lis1 ./hello 
//TEST// runprogram.perl -x hello.lis2 ./hello goodbye 
//TEST// mkpspdf hello.ps hello.c* hello.lis?

