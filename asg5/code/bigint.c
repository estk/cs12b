// $Id: bigint.c,v 1.3 2012-03-06 16:27:19-08 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bigint.h"

static char *bigint_tag = "struct bigint";

struct bigint {
   char *tag;
   bool is_negative;
   size_t length;
   size_t digits;
   char *buffer;
};

static void trim_zeros (bigint_ref bigint) {
   while (bigint->digits > 0) {
      size_t digitpos = bigint->digits - 1;
      if (bigint->buffer[digitpos] != 0) break;
      --bigint->digits;
   }
}

static bigint_ref do_add (bigint_ref left, bigint_ref right) {
}

static bigint_ref do_sub (bigint_ref left, bigint_ref right) {
}


bigint_ref new_bigint (size_t length) {
   bigint_ref bigint = malloc (sizeof (struct bigint));
   assert (bigint != NULL);
   bigint->tag = bigint_tag;
   bigint->is_negative = false;
   bigint->length = length;
   bigint->digits = 0;
   bigint->buffer = calloc (length, sizeof (char));
   assert (bigint->buffer != NULL);
   return bigint;
}

bigint_ref new_bigint_string (char *string) {
   assert (string != NULL);
   size_t length = strlen (string);
   bigint_ref bigint = new_bigint (length);
   if (*string == '_') {
      bigint->is_negative = true;
      ++string;
      --length;
   }
   int index = 0;
   while (--length > 0) {
      // LINTED (assignment of 32-bit integer to 8-bit integer)
      char digit = string[length] - '0';
      assert (0 <= digit && digit <= 9);
      bigint->buffer[index++] = digit;
   }
   trim_zeros (bigint);
   return NULL;
}


void free_bigint (bigint_ref bigint) {
   assert (is_bigint (bigint));
}

void print_bigint (bigint_ref bigint) {
   assert (is_bigint (bigint));
}

bigint_ref add_bigint (bigint_ref left, bigint_ref right) {
   assert (is_bigint (left));
   assert (is_bigint (right));
   return NULL;
}

bigint_ref sub_bigint (bigint_ref left, bigint_ref right) {
   assert (is_bigint (left));
   assert (is_bigint (right));
   return NULL;
}

bigint_ref mul_bigint (bigint_ref left, bigint_ref right) {
   assert (is_bigint (left));
   assert (is_bigint (right));
   return NULL;
}

bool is_bigint (bigint_ref bigint) {
   return false;
}

