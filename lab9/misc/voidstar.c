// $Id: voidstar.c,v 1.21 2012-03-08 18:56:47-08 - - $

//
// Simple example of void* processing in C.
// The function process takes an array and a function and
// processes the array according to the rules given by a
// function.
//

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Process an array by applying a function to each element.
//
void process (void *base,   // of the array
              size_t nelem, // number of elements
              size_t size,  // size of one element
              void (*function) (void *)) {
   for (size_t index = 0; index < nelem; ++index) {
      void *element = (char *) base + index * size;
      function (element);
   }
}

//
// Array of strings with two processing functions.
//
char *strings[] = {
   "hello", "world", "foo", "bar", "baz", "qux",
   "this", "is", "a", "test", 
};

void strdupthem (void *string) {
   char **chars = (char **) string;
   *chars = strdup (*chars);
}

void capitalize (void *string) {
   for (char *chars = * (char **) string; *chars != '\0'; ++chars) {
      // LINTED (assignment of 32-bit integer to 8-bit integer)
      *chars = toupper (*chars);
   }
}

void printstr (void *string) {
   (void) printf (" %s", * (char **) string);
}


//
// Array of doubles with two processing functions.
//

double numbers[] = {6.02e23, 49, 287, -99, -472, 0, 6e-22, 10e1000};

void exponent (void *number) {
   double *value = (double *) number;
   *value = log10 (*value);
}

void printnum (void *number) {
   (void) printf (" %.5g", * (double *) number);
}

//
// Main function to exercise them.
//

int main (void) {

   size_t stringdim = sizeof strings / sizeof *strings;
   process (strings, stringdim, sizeof *strings, printstr);
   (void) printf ("\n");
   process (strings, stringdim, sizeof *strings, strdupthem);
   process (strings, stringdim, sizeof *strings, capitalize);
   process (strings, stringdim, sizeof *strings, printstr);
   (void) printf ("\n");

   size_t numberdim = sizeof numbers / sizeof *numbers;
   process (numbers, numberdim, sizeof *numbers, printnum);
   (void) printf ("\n");
   process (numbers, numberdim, sizeof *numbers, exponent);
   process (numbers, numberdim, sizeof *numbers, printnum);
   (void) printf ("\n");

   return EXIT_SUCCESS;
}

//TEST// runprog -x voidstar.lis voidstar
//TEST// mkpspdf Listing.ps voidstar.c voidstar.c.log voidstar.lis

