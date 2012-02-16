// $Id: strlist.c,v 1.3 2012-02-15 20:45:26-08 - - $

// Reads in a sequence of lines and then prints them out in debug
// format.  strdup(3) copies these lines onto the heap.  Read the
// comments in the file `numlist.c' first.

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Declaration for linked list of nodes.
//
typedef struct node *node_ref;
struct node {
   char *string;
   node_ref link;
};

// LINTED (argument unused in function)
int main (int argc, char **argv) {
   char *progname = basename (argv[0]);
   node_ref head = NULL;
   char buffer[256];
   int linenr;
   for (linenr = 1; ; ++linenr) {

      // Read a line of input and check to see if it ends with
      // a newline character.  Print a message if not.

      char *gotline = fgets (buffer, sizeof buffer, stdin);
      if (gotline == NULL) break;

      char *nlpos = strchr (buffer, '\n');
      if (nlpos != NULL) {
         *nlpos = '\0';
      }else {
         fprintf (stderr, "%s: %d: unterminated line: %s\n",
                  progname, linenr, buffer);
      };

      // Allocate a node and initialize it to point a a heap copy
      // of the input line.  Note that strdup(3) contains a call
      // to malloc(3), so we need the NULL check there as well.

      node_ref new = malloc (sizeof (struct node));
      assert (new != NULL);
      new->string = strdup (buffer);
      assert (new->string != NULL);
      new->link = head;
      head = new;
   };

   // Print the results in debug mode.

   printf ("%s: head= %p\n", argv[0], (void*) head);
   while (head != NULL) {
      node_ref old = head;
      head = head->link;
      printf ("%s: %p-> node {\n"
              "    string= %p->\"%s\",\n"
              "    link= %p}\n",
              progname, (void*) old, (void*) old->string,
              old->string, (void*) old->link);
   };

   return EXIT_SUCCESS;
}

/*
//TEST// (echo "this is line 1" \
//TEST// ;echo "" \
//TEST// ;echo "the previous line has length 0." \
//TEST// ;echo "fit the buffer." \
//TEST// ;echo "Last Line." \
//TEST// ) | valgrind --leak-check=full --log-file=strlist.lisval \
//TEST// ./strlist >strlist.lisout 2>&1
//TEST// mkpspdf strlist.ps strlist.c* strlist.lis*
*/

