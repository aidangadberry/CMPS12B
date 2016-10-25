#include <assert.h>
#include <stdio.h>
#include <sys/types.h>

#include "strhash.h"

size_t strhash (const char *string) {
   assert (string != NULL);
   size_t hash = 0;
   for (; *string != '\0'; ++string) {
      hash = *string + (hash << 6) + (hash << 16) - hash;
   }
   return hash;
}