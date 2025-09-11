#ifndef MACROS_H_
#define MACROS_H_

#include <stdio.h>

/* Helper macro to print Log Messages */
#define LOG_ERROR(...)                                                         \
do {                                                                           \
  fprintf(stderr, "error: ");                                                  \
  fprintf(stderr, __VA_ARGS__);                                                \
  fprintf(stderr, "\n");                                                       \
} while(0)                                                                     \

#define MAX(a, b) ((a > b) ? (a) : (b))
#define MIN(a, b) ((a < b) ? (a) : (b))

/* Helper macro to mark unused function args
*  and silent warnings */
#define ARG_UNUSED(x) ((void)(x))

#endif

