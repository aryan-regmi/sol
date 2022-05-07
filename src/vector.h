#ifndef VECTOR_H
#define VECTOR_H

#include <sys/types.h>

extern const void *sol_Vec;

void sol_Vec_push(void *vector, const void *value);

void *sol_Vec_pop(void *vector);

size_t sol_Vec_len(const void *vector);

size_t sol_Vec_capacity(const void *vector);

void sol_Vec_setIndex(void *vector, size_t idx, const void *value);

void *sol_Vec_getIndex(const void *vector, size_t idx);

#endif
