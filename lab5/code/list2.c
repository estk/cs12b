// $Id: list1.c,v 1.1 2011-02-01 18:51:19-08 - - $

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

typedef struct node *node_ref;
struct node {
   char *word;
   node_ref link;
};

int main (int argc, char **argv) {
   node_ref head;
   for (int argi = 0; argi < 5; ++argi) {
      node_ref node = malloc (sizeof (node_ref));
      assert (node != NULL);
      node->word = argv[argi];
      node->link = head;
      head = node;
   }
   for (node_ref curr = head; curr->link != NULL; curr = curr->link) {
      printf ("%p->node {word=%p->[%s], link=%p}\n",
              curr, curr->word, curr->word, curr->link);
   }
   return 9;
}
