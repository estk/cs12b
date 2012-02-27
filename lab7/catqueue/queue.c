/* $Id: queue.c,v 1.2 2012-02-21 14:57:52-08 - - $ */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define STUBPRINTF(...) fprintf (stderr, __VA_ARGS__);

static char *queue_tag = "struct queue";
static char *queuenode_tag = "struct queuenode";

typedef struct queuenode *queuenode_ref;

struct queuenode {
   char *tag;
   queue_item_t item;
   queuenode_ref link;
};

struct queue {
   char *tag;
   queuenode_ref front;
   queuenode_ref rear;
};

queue_ref new_queue (void) {
   STUBPRINTF ("return NULL\n");
   return NULL;
}

void free_queue (queue_ref queue) {
   assert (is_queue (queue));
   assert (isempty_queue (queue));
   memset (queue, 0, sizeof (struct queue));
   free (queue);
}

void insert_queue (queue_ref queue, queue_item_t item) {
   assert (is_queue (queue));
   STUBPRINTF ("item =\n\t\"%s\"\n", item);
}

queue_item_t remove_queue (queue_ref queue) {
   assert (is_queue (queue));
   assert (! isempty_queue (queue));
   STUBPRINTF ("return NULL\n");
   return NULL;
}

bool isempty_queue (queue_ref queue) {
   assert (is_queue (queue));
   // LINTED (assignment of 32-bit integer to 8-bit integer)
   return queue->front == NULL;
}

bool is_queue (queue_ref queue) {
   // LINTED (assignment of 32-bit integer to 8-bit integer)
   return queue != NULL && queue->tag == queue_tag;
}

