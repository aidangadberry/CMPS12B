#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "inssort.h"

void inssort (void *base, size_t nelem, size_t size, 
              int (*compar) (const void *, const void *)){

    void* element = malloc(size);
    for (size_t sorted = 1; sorted < nelem; sorted++){
        size_t slot = sorted;
        memcpy(element, base+slot*size, size);
        for (; slot > 0; --slot){
            int cmp = compar(element, base+(slot-1)*size);
            if (cmp > 0){
                break;
            }
            memcpy(base+slot*size, base+(slot-1)*size, size);
        }
        memcpy(base+slot*size, element, size);
    }
    free (element);
}