#ifndef PRIV_CLASS_H
#define PRIV_CLASS_H

#include <stdarg.h>
#include <stddef.h>
#include <sys/types.h>

struct sol_Class {
  // Size of the class object in memory
  size_t size;

  // Constructor for class
  void *(*ctor)(void *self, va_list *app);

  // Destructor for class
  void *(*dtor)(void *self);

  // Function to clone/copy class object
  void *(*clone)(const void *self);

  // Function to compare two objects of a class
  ssize_t (*compare)(const void *self, const void *other);
};

#endif
