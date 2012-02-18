#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int exit_status = 0;
int debug = 0;
char *progname;

typedef char *cstring;
typedef struct node *node_ref;
struct node {
  char *string;
  node_ref link;
};

void usage (void) {
  printf("nsort [-d]");
  printf("    -d : print output in debug format");
  exit_status = 1;
}

node_ref insert(node_ref head, cstring str) {
  node_ref prev = NULL;
  node_ref curr = head;

  while (curr != NULL) {
    if (strcmp (curr->string, str) > 0) break;
    prev = curr;
    curr = curr->link;
  }

  node_ref new = malloc (sizeof (struct node));
  assert (new != NULL);
  new->string = strdup (str);
  assert (new->string != NULL);
  new->link = curr;

  if (prev == NULL) head = new;
  else {
    prev->link = new;
  }
  return head;
}

node_ref getChars(void) {
  node_ref head = NULL;
  char buffer[256];

  int linenr;
  for (linenr = 1; ; ++linenr) {
    char *gotline = fgets (buffer, sizeof buffer, stdin);
    if (gotline == NULL) { printf("done\n"); break; }

    char *nlpos = strchr (buffer, '\n');
    if (nlpos != NULL) {
      *nlpos = '\0';
    }else {
      fprintf (stderr, "%s: %d: unterminated line: %s\n",
          progname, linenr, buffer);
			exit_status = 1;
    };

    head = insert(head, buffer);
  }
  return head;
}


void print_list(node_ref head) {
  while (head != NULL) {
    if (debug) {
      printf ("%s: head= %p\n", progname, (void*) head);
      while (head != NULL) {
        node_ref old = head;
        head = head->link;
        printf ("%s: %p-> node {\n"
            "    string= %p->\"%s\",\n"
            "    link= %p}\n",
            progname, (void*) old, (void*) old->string,
            old->string, (void*) old->link);
        free (old);
      };
    }
    else {
      printf("%s\n", head->string);
      head = head->link;
    }
  }
}

int main (int argc, char **argv) {
  int ch;
  progname = basename (argv[0]);

  if (argc > 2)  usage();
  else if (argc == 2) {
    ch = getopt(argc, argv, "d");
    if (ch != 'd') usage();
    else debug = 1;
  }

  if (!exit_status) {
    node_ref node = getChars();
    print_list(node);

    // free
    while (node != NULL) {
      node_ref tmp = node->link;
      free (node->string);
      free (node);
      node = tmp;
    }
  }

  return exit_status;
}

