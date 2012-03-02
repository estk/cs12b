// $Id: hashset.h,v 1.2 2012-02-21 20:37:06-08 - - $

#ifndef __HASHSET_H__
#define __HASHSET_H__

#include <stdbool.h>

typedef struct hashset *hashset_ref;

//
// Create a new hashset with a default number of elements.
//
hashset_ref new_hashset (void);

//
// Frees the hashset, and the words it points at.
//
void free_hashset (hashset_ref);

//
// Inserts a new string into the hashset.
//
void put_hashset (hashset_ref, char*);

//
// Looks up the string in the hashset and returns true if found,
// false if not found.
//
bool has_hashset (hashset_ref, char*);

void print_hashset_clusters(hashset_ref);

void print_hashset (hashset_ref);

#endif

