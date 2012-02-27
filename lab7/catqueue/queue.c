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
   queue_ref tmp = malloc (sizeof (struct queue));
   tmp->tag = queue_tag;
   return tmp;
}

void free_queue (queue_ref queue) {
   assert (is_queue (queue));
   assert (isempty_queue (queue));
   memset (queue, 0, sizeof (struct queue));
   free (queue);
}

void insert_queue (queue_ref queue, queue_item_t item) {
   assert (is_queue (queue));
   queuenode_ref tmp = malloc (sizeof (struct queue));
   tmp->tag = queuenode_tag;
   tmp->item = item;

   if (queue->rear != NULL) {
     queue->rear->link = tmp;
     queue->rear = tmp;
   }else {
     queue->front = tmp;
     queue->rear = tmp;
   }
}

queue_item_t remove_queue (queue_ref queue) {
   assert (is_queue (queue));
   assert (! isempty_queue (queue));
   queuenode_ref newfront = queue->front->link;
   queue_item_t res = queue->front->item;
   free (queue->front->item);
   free (queue->front);
   queue->front = newfront;

   return res;
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

