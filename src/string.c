#include "string.h"
#include "class.h"
#include "common.h"
#include "priv_class.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

struct String {
  const void *class;
  char *text;
};

static void *String_ctor(void *self, va_list *args) {
  NULLCHK(self);

  // Convert pointer into String
  struct String *self_str = self;

  // Grab text passed in from variadic argument list
  const char *text = va_arg(*args, const char *);

  // Allocate space on heap for the string
  self_str->text = allocFn(1, strlen(text) + 1);
  NULLCHK(self_str->text);

  // Copy passed in text to the String
  strcpy(self_str->text, text);

  return self_str;
}

static void *String_dtor(void *self) {
  NULLCHK(self);

  // Convert pointer into String
  struct String *self_str = self;

  freeFn(self_str->text);
  self_str->text = NULL;

  return self_str;
}

static void *String_clone(const void *self) {
  // Convert pointer into String
  const struct String *self_str = self;

  return sol_new(sol_String, self_str->text);
}

static ssize_t String_compare(const void *self, const void *other) {
  NULLCHK(self);
  NULLCHK(other);

  // Convert pointers into String
  const struct String *self_str = self;
  const struct String *other_str = other;

  // Return 0 if they are the same
  if (self == other) {
    return 0;
  }

  return strcmp(self_str->text, other_str->text);
}

const struct sol_Class String_class = {.size = sizeof(struct String),
                                       .ctor = String_ctor,
                                       .dtor = String_dtor,
                                       .clone = String_clone,
                                       .compare = String_compare};

const void *sol_String = &String_class;
