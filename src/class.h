#ifndef CLASS_H
#define CLASS_H

#include <stdlib.h>
#include <sys/types.h>

#define allocFn calloc
#define freeFn free
#define resizeFn realloc

void *sol_new(const void *type, ...);

void sol_delete(void *object);

void *sol_clone(const void *object);

ssize_t sol_compare(const void *self, const void *other);

size_t sol_sizeOf(const void *object);

#endif
