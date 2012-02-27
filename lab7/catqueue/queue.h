/* $Id: queue.h,v 1.2 2012-02-14 20:43:22-08 - - $ */

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>

typedef struct queue *queue_ref;
typedef char *queue_item_t;

queue_ref new_queue (void);

void free_queue (queue_ref);

void insert_queue (queue_ref, queue_item_t);

queue_item_t remove_queue (queue_ref);

bool isempty_queue (queue_ref);

bool is_queue (queue_ref);

#endif

