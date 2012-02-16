// $Id: sizeofsizes.c,v 1.12 2012-02-09 19:00:37-08 - - $

#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define PRINTSIZE(TYPE) \
        printf ("%4ld = sizeof (%s)\n", sizeof (TYPE), #TYPE);

struct node {
   char *string;
   struct node *link;
};

int main (int argc, char **argv) {
   printf ("argc = %d, argv = %p\n", argc, argv);
   printf ("argv[0] = %p = \"%s\"\n", argv[0], argv[0]);
   PRINTSIZE (char);
   PRINTSIZE (short);
   PRINTSIZE (int);
   PRINTSIZE (long);
   PRINTSIZE (long long);
   PRINTSIZE (float);
   PRINTSIZE (double);
   PRINTSIZE (long double);
   PRINTSIZE (void *);
   PRINTSIZE (struct node);
   PRINTSIZE (struct node *);
   PRINTSIZE (size_t);
   PRINTSIZE (uintptr_t);
   return EXIT_SUCCESS;
}

//TEST// ./sizeofsizes >sizeofsizes.lis
//TEST// mkpspdf sizeofsizes.ps sizeofsizes.c* sizeofsizes.lis

