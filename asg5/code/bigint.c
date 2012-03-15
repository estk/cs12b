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

static char cmpdigits (bigint_ref left, bigint_ref right) {
   char res;
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

static bigint_ref do_add (bigint_ref left, bigint_ref right) {
   char cmpd = cmpdigits (left, right);
   size_t size = 1 + maxdigits (left, right);
   size_t stop = cmpd < 0 ? left->digits : right->digits;
   bigint_ref res = new_bigint (size);

   char *lbuf = left->buffer;
   char *rbuf = right->buffer;

   char sum, carry;
   carry = 0;
   for (size_t i=0 ; i<stop ; i++) {
      assert (carry >= 0);
      assert (lbuf[i] >= 0);
      /*printf("%d\n", rbuf[i]);*/
      assert (rbuf[i] >= 0);

      // LINTED
      sum = lbuf[i] + rbuf[i] + carry;

      assert (sum >= 0);
      // LINTED
      res->buffer[i] = sum % 10;
      // LINTED
      carry = sum / 10;
   }
   if (size == stop) res->buffer[stop] = carry;

   for (size_t i=stop ; i<size-1 ; i++) {
      if (cmpd > 0)
         // LINTED
         sum = lbuf[i] + carry;
      else
         // LINTED
         sum = rbuf[i] + carry;

      // LINTED
      res->buffer[i] = sum % 10;
      // LINTED
      carry = sum / 10;
   }

   trim_zeros(res);
   return res;
}

static bigint_ref do_sub (bigint_ref left, bigint_ref right) {
   size_t size = left->digits;
   size_t stop = right->digits;
   bigint_ref res = new_bigint (size);

   char *lbuf = left->buffer;
   char *rbuf = right->buffer;

   char diff, carry;
   carry = 0;
   for (size_t i=0 ; i<stop ; i++) {
      // LINTED
      diff = lbuf[i] - rbuf[i] - carry;
      if (diff < 0) {
         // LINTED
         diff += 10;
         carry = 1;
      }
      else carry = 0;
      assert (diff >= 0);
      res->buffer[i] = diff;
   }

   char sum;
   for (size_t i=stop ; i<size ; i++) {
      // LINTED
      sum = lbuf[i] - carry;
      // LINTED
      res->buffer[i] = sum % 10;
      // LINTED
      carry = sum / 10;
   }

   trim_zeros(res);
   return res;
}

static bigint_ref do_mul (bigint_ref left, bigint_ref right) {
   assert (cmpbig(left, right) >= 0);

   size_t size = left->digits + right->digits;
   bigint_ref res = new_bigint (size);

   char *lbuf, *rbuf;
   lbuf = left->buffer;
   rbuf = right->buffer;
   bigint_ref tmpbig = new_bigint (size);
   char *tbuf = tmpbig->buffer;

   char mul, rem;
   rem = 0;
   for (size_t i=0 ; i<left->digits ; i++) {

      for (size_t j=0 ; j<right->digits ; j++) {
         // LINTED
         mul = lbuf[i] * rbuf[j] + rem;
         assert (mul >= 0);
         // LINTED
         tbuf[j+i] = mul % 10;
         // LINTED
         rem = mul / 10;
      }
      tbuf[right->digits+i] = rem;
      rem = 0;

      tmpbig->digits = right->digits+i+1;
      assert (tmpbig != NULL);
      /*printf("tmp= ");*/
      /*print_bigint(tmpbig);*/
      res = do_add (res, tmpbig);
      memset(tbuf, 0, size*sizeof (char));
      /*printf("tmpemp= ");*/
      /*print_bigint(tmpbig);*/
   }
   trim_zeros(res);
   return res;
}


bigint_ref add_bigint (bigint_ref left, bigint_ref right) {
   assert (is_bigint (left));
   assert (is_bigint (right));
   bigint_ref res;
   if (left->is_negative == right->is_negative) {
      assert ( !left->is_negative);
      res = do_add(left, right);
      res->is_negative = left->is_negative;
   } else {
      if (right->is_negative) {
         right->is_negative = false;
         res = sub_bigint(left, right);
      } else {
         left->is_negative = false;
         res = sub_bigint(right, left);
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
      res = do_add(right, left);
      if (cmp >= 0)
         res->is_negative = lneg;
      else
         res->is_negative = rneg;
   } else {
      if (cmp >= 0) {
         res = do_sub(left, right);
         res->is_negative = lneg;
      }else {
         res = do_sub(right, left);
         // LINTED
         res->is_negative = !rneg;
      }
   }
   return res;
}

bigint_ref mul_bigint (bigint_ref left, bigint_ref right) {
   assert (is_bigint (left));
   assert (is_bigint (right));

   bigint_ref res;
   char cmp = cmpbig (left, right);
   if (cmp > 0)
      res = do_mul (left, right);
   else
      res = do_mul (right, left);

   // LINTED
   res->is_negative = left->is_negative ^ right->is_negative;
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
      printf("-");
   size_t count = 1;
   for (size_t i=size-1 ; ; i--) {
      assert (bigint->buffer[i] >= 0);
      if (count % 70 == 0) printf("\\\n");
      printf("%d", bigint->buffer[i]);
      if (i == 0) break;
      count++;
   }
   printf("\n");
}

bool is_bigint (bigint_ref bigint) {
   assert (bigint != NULL);
   assert (bigint->tag != NULL);
   int cmp = strcmp(bigint->tag, bigint_tag);
   // LINTED
   return cmp == 0 ? 1 : 0;
}

