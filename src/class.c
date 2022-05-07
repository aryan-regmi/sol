#include "class.h"

#include "common.h"
#include "priv_class.h"
#include <assert.h>

void *sol_new(const void *_class, ...) {
  NULLCHK(_class);

  // The class interface/struct is expected to be the first member of the type
  // passed to this function
  const struct sol_Class *class = _class;

  // Allocate memory on heap with enough space to hold an object of the
  // specified class
  void *obj_ptr = allocFn(1, class->size);
  NULLCHK(obj_ptr);

  // Sets the same class interface passed to this function as the class for the
  // newly created/pointed to object
  *(const struct sol_Class **)obj_ptr = class;

  // Forward variadic arguments to the constructor
  if (class->ctor) {
    va_list args_ptr;

    va_start(args_ptr, _class);
    obj_ptr = class->ctor(obj_ptr, &args_ptr);
    va_end(args_ptr);
  }

  return obj_ptr;
}

void sol_delete(void *object) {
  NULLCHK(object);

  // Grab the class info from the passed object
  const struct sol_Class **class_ptr = object;
  NULLCHK(*class_ptr);

  // Call the underlying object's destructor
  if ((*class_ptr)->dtor) {
    object = (*class_ptr)->dtor(object);
  }

  // Free the pointer returned by the destructor
  freeFn(object);
}

ssize_t sol_compare(const void *self, const void *other) {
  NULLCHK(self);

  const struct sol_Class *const *class_ptr = self;
  NULLCHK(*class_ptr);
  assert((*class_ptr)->compare);

  return (*class_ptr)->compare(self, other);
}

size_t sol_sizeOf(const void *object) {
  NULLCHK(object);

  const struct sol_Class *const *class_ptr = object;
  NULLCHK(*class_ptr);

  return (*class_ptr)->size;
}

void *sol_clone(const void *object) {
  NULLCHK(object);

  const struct sol_Class *const *class_ptr = object;
  NULLCHK(*class_ptr);
  assert((*class_ptr)->clone);

  return (*class_ptr)->clone(object);
}
