#ifndef CONFIGS_H_
#define CONFIGS_H_

#define WIDTH               (300)                                       /* Window Width */
#define HEIGHT              (601)                                       /* Pipe Area Height */
#define PIPES               (3)                                         /* Number of Pipes */
#define HGAP                (150)                                       /* Horizontal gap between Pipes */
#define VGAP                (100)                                       /* Vertical gap between Pipes */
#define PIPE_HEIGHT         (320)                                       /* Pipe Height */
#define PIPE_WIDTH          (52)                                        /* Pipe Width */
#define PIPE_MAX_OFFSET     (((PIPE_HEIGHT << 1) + VGAP - HEIGHT) >> 1) /* Max offset for yPos */
#define BASES               (2)                                         /* Number of Bases */
#define BASE_HEIGHT         (112)                                       /* Base Height */
#define BASE_WIDTH          (336)                                       /* Base Width */
#define BIRD_JUMP_OFFSET    (40)                                        /* Max jump offset */
#define BIRD_ACCELERATION   (5)                                         /* Bird Acceleration 5px/10ms */
#define BIRD_DEACCELERATION (1)                                         /* Bird Deacceleration 1px/10ms */
#define WINDOW_WIDTH        WIDTH                                       /* Final Window Width */
#define WINDOW_HEIGHT       (HEIGHT + BASE_HEIGHT)                      /* Final Window Height */

#endif

