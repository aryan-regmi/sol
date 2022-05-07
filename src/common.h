#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

// Easy function for panics
static inline void err_panic(const char error_msg[]) {
  fprintf(stderr, "\n%s\n", error_msg);
  exit(EXIT_FAILURE);
}

// Easy function for NULL_CHECK
static inline void null_check(const void *ptr, const char filename[],
                              size_t line_num) {
  if (!ptr) {
    fprintf(stderr,
            "\n[ERROR] NullCheckError: NULL pointer at unexpected position "
            "[%s:%zu]\n",
            filename, line_num);
    exit(EXIT_FAILURE);
  }
}

#define NULLCHK(ptr) null_check(ptr, __FILE__, __LINE__)

#endif
