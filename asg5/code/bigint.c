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

static size_t maxdigits (bigint_ref left, bigint_ref right) {
   return left->digits > right->digits ?
      left->digits : right->digits;
}

static int cmpdigits (bigint_ref left, bigint_ref right) {
   int res;
   if (left->digits > right->digits)
      res = 1;
   else if (right->digits > left->digits)
      res = -1;
   else
      res = 0;

   return res;
}

static char cmpbuffers (bigint_ref left, bigint_ref right) {
   char *lbuf = left->buffer;
   char *rbuf = right->buffer;
   size_t i = left->digits;
   do {
      i--;
      if (lbuf[i] > rbuf[i])
         return 1;
      else if (lbuf[i] < rbuf[i])
         return -1;
   } while (i != 0);

   return 0;
}

static bigint_ref do_add (bigint_ref left, bigint_ref right) {
   size_t size = 1 + maxdigits (left, right);
   bigint_ref res = new_bigint (size);

   char *lbuf = left->buffer;
   char *rbuf = right->buffer;

   char sum, carry;
   carry = 0;
   for (size_t i=0 ; i<size-1 ; i++) {
      sum = lbuf[i] + rbuf[i] + carry;
      res->buffer[i] = sum % 10;
      carry = sum / 10;
   }

   trim_zeros(res);
   return res;
}

static bigint_ref do_sub (bigint_ref left, bigint_ref right) {
   size_t size = left->digits;
   bigint_ref res = new_bigint (size);

   char *lbuf = left->buffer;
   char *rbuf = right->buffer;
   /*printf("size : %d", (int)size);*/

   char diff, carry;
   carry = 0;
   for (size_t i=0 ; i<size ; i++) {
      diff = lbuf[i] - rbuf[i] - carry;
      if (diff < 0) diff += 10;
      res->buffer[i] = diff;
      /*carry = diff / 10;*/
   }

   trim_zeros(res);
   return res;
}

char cmpbig(bigint_ref left, bigint_ref right) {
   char res;
   char cmp = cmpdigits(left, right);
   if (cmp > 0)
      res = 1;
   else if (cmp < 0)
      res = -1;
   else
      res = cmpbuffers(left, right);
   return res;
}


bigint_ref new_bigint (size_t length) {
   bigint_ref bigint = malloc (sizeof (struct bigint));
   assert (bigint != NULL);
   bigint->tag = bigint_tag;
   bigint->is_negative = false;
   bigint->length = length;
   bigint->digits = length;
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
   while (length-- > 0) {
      // LINTED (assignment of 32-bit integer to 8-bit integer)
      char digit = string[length] - '0';
      assert (0 <= digit && digit <= 9);
      bigint->buffer[index++] = digit;
   }
   trim_zeros (bigint);
   return bigint;
}


void free_bigint (bigint_ref bigint) {
   assert (is_bigint (bigint));
   free (bigint);
}

void print_bigint (bigint_ref bigint) {
   assert (is_bigint (bigint));
   size_t size = bigint->digits;
   if (bigint->is_negative)
      printf("_");
   for (int i=size-1 ; ; i--) {
      printf("%d", bigint->buffer[i]);
      if (i == 0) break;
   }
   printf("\n");
}

bigint_ref add_bigint (bigint_ref left, bigint_ref right) {
   assert (is_bigint (left));
   assert (is_bigint (right));
   bigint_ref res;
   if (left->is_negative == right->is_negative) {
      res = do_add(left, right);
      res->is_negative = left->is_negative;
   } else {
     char cmp = cmpbig (left, right);
      if (cmp >= 0) {
        res = do_sub(left, right);
        res->is_negative = left->is_negative;
      } else {
        res = do_sub(right, left);
        res->is_negative = right->is_negative;
      }
   }
   return res;
}

bigint_ref sub_bigint (bigint_ref left, bigint_ref right) {
   assert (is_bigint (left));
   assert (is_bigint (right));
   bigint_ref res;

   bool lneg, rneg;
   lneg = left->is_negative;
   rneg = right->is_negative;
   char cmp = cmpbig (left, right);
   if (lneg != rneg) {
      printf("signs neq\n");
      res = do_add(right, left);
      if (cmp > 0)
         res->is_negative = lneg;
      else
         res->is_negative = rneg;
   } else {
      if (cmp >= 0) {
         res = do_sub(left, right);
         res->is_negative = lneg ?
            lneg : !lneg;
      }else {
         res = do_sub(right, left);
         res->is_negative = rneg ?
            !rneg : rneg;
      }
   }
   /*printf("got:\n");*/
   /*print_bigint(res);*/
   return res;
}

bigint_ref mul_bigint (bigint_ref left, bigint_ref right) {
   assert (is_bigint (left));
   assert (is_bigint (right));

   size_t size = left->digits + right->digits;
   bigint_ref res = new_bigint (size);


   return res;
}

bool is_bigint (bigint_ref bigint) {
   assert (bigint != NULL);
   assert (bigint->tag != NULL);
   char cmp = strcmp(bigint->tag, bigint_tag);
   return cmp == 0 ? 1 : 0;
}

