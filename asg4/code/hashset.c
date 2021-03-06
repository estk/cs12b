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
   hashset->array = malloc (new_length * sizeof (char*));
   hashset->length = new_length;
   hashset->load = 0;

   for (size_t index = 0; index < hashset->length; ++index) {
      hashset->array[index] = NULL;
   }
   
   for (size_t i=0 ; i < old_length ; i++) {
      char *item = old_ary[i];
      if (item != NULL) 
         put_hashset (hashset, item);
   }
   DEBUGF('h', "done doubleing ary\n");
   free(old_ary);
}

void free_hashset (hashset_ref hashset) {
   for (size_t index = 0; index < hashset->length; ++index) {
      free (hashset->array[index]);
   }

   DEBUGF ('h', "free (%p), free (%p)\n", hashset->array, hashset);
   memset (hashset->array, 0, hashset->length * sizeof (char*));
   free (hashset->array);
   memset (hashset, 0, sizeof (struct hashset));
   free (hashset);
}

void put_hashset (hashset_ref hashset, char *item) {
   assert (item != NULL);
   // need to double?
   // LINTED
   if ((4 * (size_t)hashset->load + 1) > hashset->length)
      double_hashset(hashset);
   
   //LINTED
   hashcode_t starting_index = strhash (item) % hashset->length;
   hashcode_t i;
   for (i = starting_index ; i < (size_t)hashset->length ; i++) {
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
   // LINTED
   hashcode_t starting_index = strhash (item) % hashset->length;
   hashcode_t i;
   // LINTED
   for (i=starting_index ; i < (hashcode_t)hashset->length ; i++) {
      if (hashset->array[i] != NULL)
         if (strcmp (item, hashset->array[i]) == 0) return true;
   }
   for (i=0 ; i < starting_index ; i++) {
      if (hashset->array[i] != NULL)
         if (strcmp (item, hashset->array[i]) == 0) return true;
   }
   return false;
}

int count_clusters(hashset_ref hashset, int n) {
   int count = 0;
   int since_null = 0;
   char **ary = hashset->array;
   for (size_t i=0 ; i < hashset->length ; i++) {
      if (ary[i] == NULL) {
         if (since_null == n) count++;
         since_null = 0;
         continue;
      } 
      else since_null++;
   }
   if (since_null == n) count++;
   return count;
}

void print_hashset_clusters(hashset_ref hashset) {
   
   printf("%10d words in the hashset\n", hashset->load);
   // LINTED
   printf("%10d length of the hash array\n", (int)hashset->length);
   printf("%10d clusters of size 1\n", count_clusters (hashset, 1));
   printf("%10d clusters of size 2\n", count_clusters (hashset, 2));
   printf("%10d clusters of size 3\n", count_clusters (hashset, 3));
   printf("%10d clusters of size 7\n", count_clusters (hashset, 7));
}

void print_hashset(hashset_ref hashset) {
   for (size_t i = 0 ; i < hashset->length; i++) {
      char * item = hashset->array[i];
      if (item != NULL)
         printf ("array[%10d] = %12u \"%s\"\n",
         // LINTED
            (int)i, strhash(item), item);
   }
   DEBUGF('m',"load = %d\n", hashset->load);
   DEBUGF('m', "length = %d\n", hashset->length);
}

