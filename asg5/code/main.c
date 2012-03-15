// $Id: main.c,v 1.3 2012-03-06 16:27:19-08 - - $

#include <assert.h>
#include <ctype.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "bigint.h"
#include "debugf.h"
#include "stack.h"
#include "token.h"

char *execname = NULL;

#define DO_NOTHING(X) {DEBUGF ('s', ""); return X; }

bool not_enough (stack_ref stack, int enough) {
   if (length_stack (stack) >= enough) return false;
   fprintf (stdin, "%s: stack empty\n", execname);
   return true;
}

void do_push (stack_ref stack, char *yytext) {
   bigint_ref bigint = new_bigint_string (yytext);
   push_stack (stack, bigint);
}

void do_binop (stack_ref stack, bigint_binop binop) {
   if (not_enough (stack, 2)) return;
   bigint_ref right = pop_stack (stack);
   bigint_ref left = pop_stack (stack);
   bigint_ref answer = binop (left, right);
   push_stack (stack, answer);
   free_bigint (left);
   free_bigint (right);
}

void do_clear (stack_ref stack) {
   while (! is_empty_stack (stack)) {
      bigint_ref bigint = pop_stack (stack);
      free_bigint (bigint);
   }
}


void do_print (stack_ref stack) {
   assert (stack != NULL);
   if (not_enough (stack, 1)) return;
   print_bigint (peek_stack (stack, 0));
}

void do_print_all (stack_ref stack) {
   int length = length_stack (stack);
   for (int index = 0; index < length; ++index) {
      print_bigint (peek_stack (stack, index));
   }
}

void unimplemented (int oper) {
   printf ("%s: ", execname);
   if (isgraph (oper)) printf ("'%c' (0%o)", oper, oper);
                  else printf ("0%o", oper);
   printf (" unimplemented\n");
}

void scan_options (int argc, char **argv) {
   opterr = false;
   for (;;) {
      int option = getopt (argc, argv, "y@:");
      if (option == EOF) break;
      switch (option) {
         case '@': set_debugflags (optarg);
                   break;
         default : printf ("%s: -%c: invalid option\n",
                           execname, optopt);
                   break;
      }
   }
}

int main (int argc, char **argv) {
   execname = basename (argv[0]);
   set_execname (execname);
   scan_options (argc, argv);
   stack_ref stack = new_stack ();
   token_ref scanner = new_token (stdin);
   for (;;) {
      int token = scan_token (scanner);
      if (token == EOF) break;
      switch (token) {
         case NUMBER: do_push (stack, peek_token (scanner)); break;
         case '+': do_binop (stack, add_bigint); break;
         case '-': do_binop (stack, sub_bigint); break;
         case '*': do_binop (stack, mul_bigint); break;
         case 'c': do_clear (stack); break;
         case 'f': do_print_all (stack); break;
         case 'p': do_print (stack); break;
         default: unimplemented (token); break;
      }
   }
   free_token(scanner);
   do_clear(stack);
   free_stack(stack);
   return EXIT_SUCCESS;
}
