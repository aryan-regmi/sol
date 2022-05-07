#include "vector.h"
#include "class.h"
#include "common.h"
#include "iterator.h"
#include "priv_class.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct Vector {
  const void *class;

  const struct sol_Iter *iter;

  size_t len;

  size_t capacity;

  void **data;
};

// CLASS FUNCTIONS

static void *Vector_ctor(void *self, va_list *args) {
  NULLCHK(self);

  // Convert pointer into Vector
  struct Vector *self_vec = self;

  // Initalize vector
  self_vec->len = 0;
  self_vec->capacity = 0;
  self_vec->data = NULL;

  // Grab capacity from variadic argument list and update vector capacity and
  // data pointer
  size_t capacity = va_arg(*args, size_t);
  if (capacity > 0) {
    self_vec->len = 0;
    self_vec->capacity = capacity;

    // Allocate space on heap for the vector elements
    self_vec->data = allocFn(capacity, sizeof(self_vec->data[0]));
    NULLCHK(self_vec->data);
  }

  return self_vec;
}

static void *Vector_dtor(void *self) {
  NULLCHK(self);

  // Convert pointer into String
  struct Vector *self_vec = self;

  freeFn(self_vec->data);
  self_vec->len = 0;
  self_vec->capacity = 0;
  self_vec->data = NULL;

  return self_vec;
}

static void *Vector_clone(const void *self) {
  NULLCHK(self);

  // Convert pointer into Vector
  const struct Vector *self_vec = self;

  // Create new Vector with the same capacity
  struct Vector *cloned_vec = sol_new(sol_Vec, self_vec->capacity);

  // Set cloned vector's length
  cloned_vec->len = self_vec->len;

  // Copy old data
  struct Vector *cloned_vec_ =
      memcpy(cloned_vec->data, self_vec->data, self_vec->len);
  NULLCHK(cloned_vec_);

  return cloned_vec_;
}

static ssize_t Vector_compare(const void *self, const void *other) {
  NULLCHK(self);
  NULLCHK(other);

  // Convert pointers into Vector
  const struct Vector *self_vec = self;
  const struct Vector *other_vec = other;

  // Return 0 if they are the same pointer
  if (self == other) {
    return 0;
  }

  // If lengths or capacities don't match, they can't be the same
  if (self_vec->len != other_vec->len ||
      self_vec->capacity != other_vec->capacity) {
    return -1;
  }

  // Compare each element and return -1 if they don't match
  for (size_t i = 0; i < self_vec->len; i++) {
    if (self_vec->data[i] != other_vec->data[i]) {
      return -1;
    }
  }

  return 0;
}

const struct sol_Class Vector_class = {.size = sizeof(struct Vector),
                                       .ctor = Vector_ctor,
                                       .dtor = Vector_dtor,
                                       .clone = Vector_clone,
                                       .compare = Vector_compare};

const void *sol_Vec = &Vector_class;

// VECTOR FUNCTIONS/METHODS

static void Vec_resize(void *vector) {
  NULLCHK(vector);

  // Convert pointer to Vector
  struct Vector *vec = vector;

  vec->capacity *= 2;

  void *resized_vec = resizeFn(vec->data, vec->capacity * sizeof(vec->data[0]));
  NULLCHK(resized_vec);
  vec->data = resized_vec;
}

void sol_Vec_push(void *vector, const void *value) {
  NULLCHK(vector);

  // Convert pointer to Vector
  struct Vector *vec = vector;

  // Allocate on first push if capacity is 0
  if (vec->capacity == 0) {
    vec->data = allocFn(1, sizeof(vec->data[0]));
    vec->capacity++;
    NULLCHK(vec->data);
  }

  // Resize if necessary
  if (vec->capacity < vec->len + 1) {
    Vec_resize(vec);
  }

  vec->data[vec->len] = (void *)value;

  vec->len++;
}

void *sol_Vec_pop(void *vector) {
  NULLCHK(vector);

  // Convert pointer to Vector
  struct Vector *vec = vector;

  void *popped_val = vec->data[vec->len - 1];

  // Delete popped value from vec
  vec->data[vec->len - 1] = NULL;

  vec->len--;

  return popped_val;
}

size_t sol_Vec_len(const void *vector) {
  NULLCHK(vector);

  // Convert pointer to Vector
  const struct Vector *vec = vector;

  return vec->len;
}

size_t sol_Vec_capacity(const void *vector) {
  NULLCHK(vector);

  // Convert pointer to Vector
  const struct Vector *vec = vector;

  return vec->capacity;
}

void sol_Vec_setIndex(void *vector, size_t idx, const void *value) {
  NULLCHK(vector);

  // Convert pointer to Vector
  const struct Vector *vec = vector;

  if (vec->len - 1 < idx) {
    err_panic("[ERROR] IndexOutOfBoundsError: The specified index is outside "
              "the bounds of the vector");
  }

  vec->data[idx] = (void *)value;
}

void *sol_Vec_getIndex(const void *vector, size_t idx) {
  NULLCHK(vector);

  // Convert pointer to Vector
  const struct Vector *vec = vector;

  if (vec->len - 1 < idx) {
    err_panic("[ERROR] IndexOutOfBoundsError: The specified index is outside "
              "the bounds of the vector");
  }

  return vec->data[idx];
}
