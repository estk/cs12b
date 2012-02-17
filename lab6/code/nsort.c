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

node_ref getNums() {

}

node_ref insert(node_ref head, node_ref curr, double num) {
  if (curr->link == NULL) {

  }
}

void print_list(node_ref node) {
	if (node == NULL) return;
	printf("%24.15g\n", node->item);
	print_list(node->link);
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
    node_ref nums = getNums();
    print_list(nums);
  }

	return exit_status;
}

