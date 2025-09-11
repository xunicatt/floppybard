#ifndef MACROS_H_
#define MACROS_H_

#include <stdio.h>

#define WIDTH           (300) /* Window Width */
#define HEIGHT          (600) /* Window Height */
#define PIPES           (3)   /* Number of Pipes */
#define PIPE_MAX_OFFSET (70)  /* Max offset for yPos */
#define HGAP            (150) /* Horizontal gap between Pipes */
#define VGAP            (100) /* Vertical gap between Pipes */
#define PIPE_HEIGHT     (320) /* Pipe Height */
#define PIPE_WIDTH      (52)  /* Pipe Width */

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

