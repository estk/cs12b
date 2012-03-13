// $Id: stack.c,v 1.3 2012-03-06 16:27:19-08 - - $

#include <stdio.h>
#include <assert.h>

#include "stack.h"

typedef struct stack_node *stack_node_ref;

static char *stack_tag = "struct stack";
static char *stack_node_tag = "struct stack_node";

struct stack {
   char *tag;
   stack_node_ref top;
};

struct stack_node {
   char *tag;
   stack_item item;
   stack_node_ref link;
};

stack_ref new_stack (void) {
   return NULL;
}

void free_stack (stack_ref stack) {
   assert (is_stack (stack));
   assert (is_empty_stack (stack));
}

void push_stack (stack_ref stack, stack_item item) {
   assert (is_stack (stack));
}

stack_item pop_stack (stack_ref stack) {
   assert (is_stack (stack));
   assert (! is_empty_stack (stack));
   return NULL;
}

stack_item peek_stack (stack_ref stack, int index) {
   assert (is_stack (stack));
   assert (index >= 0);
   assert (index < length_stack (stack));
   return NULL;
}

bool is_empty_stack (stack_ref stack) {
   assert (is_stack (stack));
   return false;
}

int length_stack (stack_ref stack) {
   assert (is_stack (stack));
   return 0;
}

bool is_stack (stack_ref stack) {
   return false;
}

