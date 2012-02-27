/* $Id: intx.c,v 1.3 2012-02-15 20:47:04-08 - - $ */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "intx.h"

static char *intx_tag = "struct intx";

struct intx {
   char *tag;
   int value;
};

intx_ref new_intx (void) {
   return new1_intx (0);
}

intx_ref new1_intx (int initvalue) {
   intx_ref new = malloc (sizeof (struct intx));
   assert (new != NULL);
   new->tag = intx_tag;
   new->value = initvalue;
   return new;
}

void free_intx (intx_ref this) {
   assert (is_intx (this));
   memset(this, 0, sizeof (struct intx));
   free (this);
}

int get_intx (intx_ref this) {
   assert (is_intx (this));
   return this->value;
}

void put_intx (intx_ref this, int newvalue) {
   assert (is_intx (this));
   this->value = newvalue;
}

bool is_intx (intx_ref this) {
   // LINTED (warning: assignment of 32-bit integer to 8-bit integer)
   return this != NULL && this->tag == intx_tag;
}

/*
*****************************************************************

Notes that would normally not be put in the file:

A `.c' file always includes its own header.

The `struct' definition itself is specified in the
implementation file.  Everything declared in the implementation
file is `private'.  Never put field definitions in a header
file.

A tag string is defined so that each structure can be identified
at runtime similar to the way that `System.identityHashCode' in
Java can identify the type of the object.  It is also cleared
out when freed to permit checking of dangling pointers.

The tag is static so it can't be accessed outside of this file.
Static variables work as in Java if one considers the `.c' file
to be a class.

The function memset(3) is used before free(3C) in order to avoid
having pointers into the object remain live and also to prevent
a dangling pointer from verifying true for `is_intx'.  It also
can be used for checking up on types when using `void*' for
`Object'.

All functions assert is_intx as a precondition if appropriate.

*****************************************************************
*/
