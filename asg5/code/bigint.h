// $Id: bigint.h,v 1.2 2012-03-05 20:19:38-08 - - $

#ifndef __BIGINT_H__
#define __BIGINT_H__

#include <stdbool.h>

typedef struct bigint *bigint_ref;

typedef bigint_ref (*bigint_binop) (bigint_ref, bigint_ref);

bigint_ref new_bigint (size_t length);

bigint_ref new_bigint_string (char *string);

void free_bigint (bigint_ref);

void print_bigint (bigint_ref);

bigint_ref add_bigint (bigint_ref left, bigint_ref right);

bigint_ref sub_bigint (bigint_ref left, bigint_ref right);

bigint_ref mul_bigint (bigint_ref left, bigint_ref right);

bool is_bigint (bigint_ref);

#endif

