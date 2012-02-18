#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int exit_status = 0;

typedef struct node *node_ref;
struct node {
  double item;
  node_ref link;
};

void usage () {
  printf("nsort [−d]\n");
  printf("    −d Output is printed in debug format.\n");
  exit_status = 1;
}

node_ref insert(node_ref head, double num) {
  /*printf("inserting: %g\n\n", num);*/
  node_ref prev = NULL;
  node_ref curr = head;

  while (curr != NULL) {
    if (curr->item > num) break;
    prev = curr;
    curr = curr->link;
  }
  /*printf("prev=%p\n", prev);*/
  /*printf("curr=%p\n", curr);*/

  node_ref new = malloc (sizeof (struct node));
  assert (new != NULL);
  new->item = num;
  new->link = curr;

  /*printf("new->value: %g\n",new->item);*/
  /*printf("new->link: %p\n", new->link);*/

  if (prev == NULL) head = new;
  else {
    prev->link = new;
  }
  return head;
}

node_ref getNums() {
  node_ref list = NULL;

  while (1) {
    /*printf("list= %p", list);*/
    double num;
    int scancount = scanf("%lg", &num);

    if (scancount == EOF) {
      printf("done\n"); break;
    } else if (scancount == 1) {
      /*printf("inserting %g\n", num);*/
      list = insert(list, num);
    } else {
      printf("bad number\n");
    }
  }
  return list;
}


void print_list(node_ref list) {
  while (list != NULL) {
    printf("%24.15g\n", list->item);
    list = list->link;
  }
}

int main (int argc, char **argv) {
  char ch;
  int debug = 0;

  if (argc > 2)  usage();
  else if (argc == 2) {
    ch = getopt(argc, argv, "d");
    if (ch != 'd') usage();
    else debug = 1;
  }

  if (!exit_status) {
    node_ref numlist = getNums();
    print_list(numlist);
    /*printf("%g",numlist->item);*/
    /*printf("%g",numlist->link->item);*/
    /*printf("%g",numlist->link->link->item);*/
    while (numlist != NULL) {
      node_ref tmp = numlist->link;
      free (numlist);
      numlist = tmp;
    }
  }

  return exit_status;
}

