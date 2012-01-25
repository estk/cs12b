// $Id: scanner.c,v 1.19 2012-01-24 21:00:42-08 - - $

//
// Example use of scanf and strtod to read words and determine if
// they are numbers.  Print the number if it is numeric, the string
// that is not numeric if not.
//

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
   assert (argc == 1);
   printf ("%s:\n", argv[0]);

   for (;;) {
      char buffer[1024];

      // Read in a word and stop at EOF.
      int scanct = scanf ("%1023s", buffer);
      if (scanct == EOF) {
         printf ("EOF\n");
         break;
      }
      assert (scanct == 1);
      size_t length = strlen (buffer);

      // Tell whether or not it is a number.
      // If yes, print it and the string.
      // If not, print the endptr data.
      char *endptr;
      double number = strtod (buffer, &endptr);
      if (*endptr == '\0') {
         printf ("%22.15g %4ld \"%s\"\n", number, length, buffer);
      }else {
         printf ("%-22s %4ld \"%s\", endptr->\"%s\"\n",
                 "not numeric", length, buffer, endptr);
      }

   }
   return EXIT_SUCCESS;
}

/*
//TEST// echo 3.1415926535897932384626433832795029 \
//TEST//      2.7182818284590452353602874713526625 \
//TEST//      6.02e23 hello world '+' '-' '*' '/' ';' 1e1000000 \
//TEST//      +Infinity -Infinity NaN 1234foobar -5e-5000 \
//TEST//      .99999999999999999999999999999 -22e4 \
//TEST//      -3.33333333333333333333333333333333e-30 \
//TEST//      0xFFFF 0xFFFFFFFF 0x1p10 0x1p20 \
//TEST// | runprog -x scanner.lis -0- ./scanner
//TEST// mkpspdf scanner.ps scanner.c* scanner.lis*
*/
