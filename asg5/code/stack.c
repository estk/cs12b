#include <stdlib.h>
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

static stack_node_ref new_stack_node (void) {
   stack_node_ref res = malloc (sizeof (struct stack_node));
   assert (res != NULL);
   res->tag = stack_node_tag;
   res->link = NULL;
   return res;
}

stack_ref new_stack (void) {
   stack_ref res = malloc (sizeof (struct stack));
   assert (res != NULL);
   res->tag = stack_tag;
   res->top = NULL;
   return res;
}


void free_stack (stack_ref stack) {
   assert (is_stack (stack));
   assert (is_empty_stack (stack));

   /*stack_node_ref top = stack->top;*/
   free (stack);
   /*while (top != NULL) {*/
      /*stack_node_ref next = top->link;*/
      /*free (top);*/
      /*top = next;*/
   /*}*/
}

void push_stack (stack_ref stack, stack_item item) {
   assert (is_stack (stack));
   assert (item != NULL);

   stack_node_ref newtop = new_stack_node();
   newtop->item = item;
   newtop->link = stack->top;
   stack->top = newtop;

   assert (stack->top != NULL);
   assert (stack->top->item == item);
}

stack_item pop_stack (stack_ref stack) {
   assert (is_stack (stack));
   assert (! is_empty_stack (stack));

   stack_node_ref tmp = stack->top;
   stack_item res = tmp->item;
   stack->top = stack->top->link;
   free (tmp);
   return res;
}

int length_stack (stack_ref stack) {
   assert (is_stack (stack));
   assert (stack != NULL);

   int count = 0;
   stack_node_ref tmp = stack->top;
   while (tmp != NULL) {
      count++;
      tmp = tmp->link;
   }
   return count;
}

stack_item peek_stack (stack_ref stack, int index) {
   assert (stack != NULL);
   assert (stack->top != NULL);
   assert (is_stack (stack));
   assert (index >= 0);
   assert (index < length_stack (stack));

   stack_node_ref res = stack->top;
   for (int i=0 ;; i++) {
      if (i == index) 
         break;
      res = res->link;
   }
   assert (res->item != NULL);
   return res->item;
}

bool is_empty_stack (stack_ref stack) {
   assert (is_stack (stack));
   // LINTED
   return stack->top == NULL;
}

bool is_stack (stack_ref stack) {
   // LINTED
   return stack->tag == stack_tag;
}

