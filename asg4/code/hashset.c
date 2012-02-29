// $Id: hashset.c,v 1.1 2012-02-21 20:36:10-08 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugf.h"
#include "hashset.h"
#include "strhash.h"

#define HASH_NEW_SIZE 15

struct hashset {
   size_t length;
   int load;
   char **array;
};

hashset_ref new_hashset (void) {
   hashset_ref new = malloc (sizeof (struct hashset));
   assert (new != NULL);
   new->length = HASH_NEW_SIZE;
   new->load = 0;
   new->array = malloc (new->length * sizeof (char*));
   for (size_t index = 0; index < new->length; ++index) {
      new->array[index] = NULL;
   }
   assert (new->array != NULL);
   DEBUGF ('h', "%p -> struct hashset {length = %d, array=%p}\n",
                new, new->length, new->array);
   return new;
}

void free_hashset (hashset_ref hashset) {
   DEBUGF ('h', "free (%p), free (%p)\n", hashset->array, hashset);
   memset (hashset->array, 0, hashset->length * sizeof (char*));
   free (hashset->array);
   memset (hashset, 0, sizeof (struct hashset));
   free (hashset);
}

void put_hashset (hashset_ref hashset, char *item) {
   STUBPRINTF ("hashset=%p, item=%s\n", hashset, item);
}

bool has_hashset (hashset_ref hashset, char *item) {
   STUBPRINTF ("hashset=%p, item=%s\n", hashset, item);
   return true;
}

