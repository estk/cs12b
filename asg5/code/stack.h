// $Id: stack.h,v 1.1 2012-03-05 19:43:01-08 - - $

#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>

typedef struct stack *stack_ref;
typedef struct bigint *stack_item;

//
// Create a new empty stack.
//
stack_ref new_stack (void);

//
// Free up the stack.
// Precondition: stack must be empty.
//
void free_stack (stack_ref);

//
// Push a new stack_item onto the top of the stack.
//
void push_stack (stack_ref, stack_item);

//
// Pop the top stack_item from the stack and return it.
//
stack_item pop_stack (stack_ref);

//
// Peek into the stack and return a selected stack_item, with
// item 0 being the element at the top.
// and item length_stack - 1 being the element at the bottom.
// Precondition: 0 <= index && index < length_stack.
//
stack_item peek_stack (stack_ref, int index);

//
// Indicate whether the stack is empty or not.
//
bool is_empty_stack (stack_ref);

//
// Return a count of the number of items on the stack.
//
int length_stack (stack_ref);

//
// Indixate whether or not a pointer points at a stack.
//
bool is_stack (stack_ref);

#endif

