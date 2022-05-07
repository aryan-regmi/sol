#pragma once

#include "../../external/acutest.h"
#include <assert.h>
#include <stdio.h>

#include "../class.h"
#include "../string.h"
#include "../vector.h"

void test_String(void) {
  void *a = sol_new(sol_String, "a");
  void *b = sol_new(sol_String, "b");
  void *aa = sol_clone(a);

  // printf("Size: %zu", sol_sizeOf(a));
  TEST_CHECK(sol_compare(a, b) < 0);
  TEST_CHECK(sol_compare(a, aa) == 0);
  TEST_CHECK(a != aa);

  sol_delete(a);
  sol_delete(aa);
  sol_delete(b);
}

void test_Vec(void) {
  void *vec = sol_new(sol_Vec, 0);
  TEST_CHECK(sol_Vec_capacity(vec) == 0);
  TEST_CHECK(sol_Vec_len(vec) == 0);

  void *vec2 = sol_new(sol_Vec, 5);
  TEST_CHECK(sol_Vec_capacity(vec2) == 5);
  TEST_CHECK(sol_Vec_len(vec2) == 0);

  TEST_CHECK(sol_compare(vec, vec) == 0);
  TEST_CHECK(sol_compare(vec, vec2) == -1);

  sol_Vec_push(vec, &(int){42});
  TEST_CHECK(sol_Vec_len(vec) == 1);
  TEST_CHECK(sol_Vec_capacity(vec) == 1);

  sol_Vec_push(vec, &(int){99});
  TEST_CHECK(sol_Vec_len(vec) == 2);
  TEST_CHECK(sol_Vec_capacity(vec) == 2);

  sol_Vec_push(vec, &(int){23});
  TEST_CHECK(sol_Vec_len(vec) == 3);
  TEST_CHECK(sol_Vec_capacity(vec) == 4);

  sol_Vec_setIndex(vec, 1, &(int){17});
  TEST_CHECK(*(int *)sol_Vec_getIndex(vec, 1) == 17);

  TEST_CHECK(*(int *)sol_Vec_pop(vec) == 23);
  TEST_CHECK(*(int *)sol_Vec_pop(vec) == 17);
  TEST_CHECK(*(int *)sol_Vec_pop(vec) == 42);
  TEST_CHECK(sol_Vec_len(vec) == 0);

  sol_delete(vec);
  sol_delete(vec2);
}
