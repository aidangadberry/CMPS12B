//
// NAME
//    strhash - return an unsigned 32-bit hash code for a string
//
// SYNOPSIS
//    size_t strhash (const char *string);
//

#ifndef __STRHASH_H__
#define __STRHASH_H__

#include <inttypes.h>

size_t strhash (const char *string);

#endif