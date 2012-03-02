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

void double_hashset(hashset_ref hashset) {
   size_t old_length = hashset->length;
   char **old_ary = hashset->array;
   size_t new_length = old_length * 2 + 1;
   hashset->array = malloc (sizeof (char[new_length]));
   hashset->length = new_length;
   hashset->load = 0;
   
   for (size_t i=0 ; i < old_length ; i++) {
      char *item = old_ary[i];
      put_hashset (hashset, item);
   }
   printf("done doubleing ary\n");
}

void free_hashset (hashset_ref hashset) {
   DEBUGF ('h', "free (%p), free (%p)\n", hashset->array, hashset);
   memset (hashset->array, 0, hashset->length * sizeof (char*));
   free (hashset->array);
   memset (hashset, 0, sizeof (struct hashset));
   free (hashset);
}

void put_hashset (hashset_ref hashset, char *item) {
   // need to double?
   if ((4 * hashset->load + 1) > (int)hashset->length) double_hashset(hashset);
   
   hashcode_t starting_index = strhash (item) % hashset->length;
   hashcode_t i;
   for (i = starting_index ; i < hashset->length ; i++) {
      if (hashset->array[i] == NULL) { 
         hashset->array[i] = item;
         hashset->load++;
         return;
      }
      if (strcmp (item, hashset->array[i]) == 0) return;
   }
   for (i = 0 ; i < starting_index ; i++) {
      if (hashset->array[i] == NULL) { 
         hashset->array[i] = item;
         hashset->load++;
         return;
      }
      if (strcmp (item, hashset->array[i]) == 0) return;
   }
}

bool has_hashset (hashset_ref hashset, char *item) {
   hashcode_t starting_index = strhash (item) % hashset->length;
   hashcode_t i;
   for (i=starting_index ; i < hashset->length ; i++) {
      if (hashset->array[i] == NULL) return false;
      if (strcmp (item, hashset->array[i]) == 0) return true;
   }
   for (i=0 ; i < starting_index ; i++) {
      if (hashset->array[i] == NULL) return false;
      if (strcmp (item, hashset->array[i]) == 0) return true;
   }
   return false;
}

