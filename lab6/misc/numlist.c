// $Id: numlist.c,v 1.1 2012-02-09 18:53:08-08 - - $

//
// Demo of how to use malloc and free.
//

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

//
// Declare the type of the handle, or pointer, to the struct.
// In Java, the same name is used for both the handle and the
// struct.
//
// Declare the type of the node.  This is much like Java, except
// that the word `struct' is used.  C does not allow functions
// to be declared inside structs, as does Java.
//
typedef struct node *node_ref;
struct node {
   double item;
   node_ref link;
};

//
// The main program allocates some nodes, pushes them onto a list,
// prints them out, and then frees up the nodes.
//
int main (int argc, char **argv) {
   char *progname = basename (argv[0]);

   //
   // Declare and set the head of the list to NULL.
   //

   node_ref head = NULL;

   //
   // Loop, pushing some random numbers onto the list.  Note that
   // `->' in C means `.' in Java.  Malloc(3c) is used to allocate
   // storage, like `new' in Java.  Always check with `assert' that
   // malloc has actually returned the address of new memory.
   // `sizeof' returns the number of bytes necessary for its 
   // argument.
   //
   int max = argc < 2 ? 10 : atoi (argv[1]);
   printf ("%s: looping %d times\n", progname, max);
   for (int count = 0; count < max; ++count) {
      node_ref new = malloc (sizeof (struct node));
      assert (new != NULL);
      new->item = drand48() * 1e6;
      new->link = head;
      head = new;
   }

   //
   // Loop down the list, printing out each entry in debug mode.
   //
   printf ("&head= %p\n", (void*) &head);
   printf ("head= %p\n", (void*) head);
   for (node_ref curr = head; curr != NULL; curr = curr->link) {
      printf ("%p -> struct node {item= %.15g, link= %p}\n",
              (void*) curr, curr->item, (void*) curr->link);
   }
   printf ("NULL= %p\n", (void*) NULL);

   //
   // Free up all of the nodes.
   //
   while (head != NULL) {
      node_ref old = head;
      head = head->link;
      free (old);
   }

   //
   // Deliberately cause some memory leaks and throw away result.
   //
   for (int leaks = 0; leaks < 4; ++leaks) malloc (256);
   malloc (4096);

   return EXIT_SUCCESS;
}

/*
//TEST// valgrind --leak-check=full --log-file=numlist.lisval \
//TEST//./numlist >numlist.lisout 2>&1
//TEST// mkpspdf numlist.ps numlist.c* numlist.lis*
*/

