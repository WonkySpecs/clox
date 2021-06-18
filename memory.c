#include <stdlib.h>
#include <stdio.h>

#include "memory.h"

/*
oldSize = 0, newSize > 0: Allocate new block
oldSize > 0, newSize = 0: Free block
oldSize > 0, newSize < oldSize: Shrink block
oldSize > 0, newSize > oldSize: Grow block
*/
void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
    if (newSize == 0) {
        free(pointer);
        return NULL;
    }

    void* result = realloc(pointer, newSize);
    if (result == NULL) {
        printf("Out of memory");
        exit(1);
    }
    return result;
}
