// $Id: strhash.h,v 1.1 2012-02-21 20:36:10-08 - - $

//
// NAME
//    strhash - return an unsigned 32-bit hash code for a string
//
// SYNOPSIS
//    hashcode_t strhash (char *string);
//
// DESCRIPTION
//    Uses Horner's method to compute the hash code of a string
//    as is done by java.lang.String.hashCode:
//    .  s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1]
//    Using strength reduction, the multiplication is replaced by
//    a shift.  However, instead of returning a signed number,
//    this function returns an unsigned number.
//
// REFERENCE
//    http://java.sun.com/j2se/1.4.1/docs/api/java/lang/
//    String.html#hashCode()
// 
//

#ifndef __STRHASH_H__
#define __STRHASH_H__

#include <inttypes.h>

typedef uint32_t hashcode_t;

hashcode_t strhash (char *string);

#endif

