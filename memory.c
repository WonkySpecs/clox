#include <stdlib.h>
#include <stdio.h>

#include "memory.h"
#include "vm.h"

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

void freeObject(Obj* obj) {
    switch (obj->type) {
        case OBJ_STRING: {
            ObjString* s = (ObjString*)(obj);
            FREE_ARRAY(char, s->chars, s->length + 1);
            FREE(ObjString, s);
            break;
        }
    }
}

void freeObjects() {
    Obj* obj = vm.objects;
    while (obj != NULL) {
        Obj* next = obj->next;
        freeObject(obj);
        obj = next;
    }
}
