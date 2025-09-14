#ifndef MACROS_H_
#define MACROS_H_

#include <stdio.h>
#include <SDL.h>

/* Helper macro to print Log Messages */
#define LOG_ERROR(...)                                                         \
do {                                                                           \
  fprintf(stderr, "error: ");                                                  \
  fprintf(stderr, __VA_ARGS__);                                                \
  fprintf(stderr, "\n");                                                       \
} while(0)                                                                     \

/* Helper macro to center a box */
#define SDL_RECT_FROM_CENTER(_x, _y, _w, _h)                                   \
(SDL_Rect){                                                                    \
  .x = ((_x) - ((_w)/2)),                                                      \
  .y = ((_y) - ((_h)/2)),                                                      \
  .w = (_w),                                                                   \
  .h = (_h)                                                                    \
}                                                                              \

#define LOOKUP(x, mx) (((x) + (mx) - 1) % (mx))

#define IS_KEYDOWN(e, k) \
      ((e)->key.type == SDL_KEYDOWN && (e)->key.keysym.sym == (k))

#define IS_BUTTONDOWN(e, k) \
      ((e)->button.type == SDL_MOUSEBUTTONUP && (e)->button.button == (k))

#define MAX(a, b) ((a > b) ? (a) : (b))
#define MIN(a, b) ((a < b) ? (a) : (b))

/* Helper macro to mark unused function args
*  and silent warnings */
#define ARG_UNUSED(x) ((void)(x))

#endif

