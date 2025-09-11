#ifndef MACROS_H_
#define MACROS_H_

#include <stdio.h>

#define WIDTH           (300)
#define HEIGHT          (600)
#define PIPES           (3)
#define PIPE_MAX_OFFSET (70)
#define HGAP            (150)
#define VGAP            (100)
#define PIPE_HEIGHT     (320)
#define PIPE_WIDTH      (52)

#define LOG_ERROR(...)                                                         \
do {                                                                           \
  fprintf(stderr, "error: ");                                                  \
  fprintf(stderr, __VA_ARGS__);                                                \
  fprintf(stderr, "\n");                                                       \
} while(0)                                                                     \

#define MAX(a, b) ((a > b) ? (a) : (b))
#define MIN(a, b) ((a < b) ? (a) : (b))
#define ARG_UNUSED(x) ((void)(x))

#endif

