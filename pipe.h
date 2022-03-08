
#ifndef __PIPE_H
#define __PIPE_H

#include <int.h>

#include "coordinate.h"

#define PIPE_SPEED 1
#define PIPE_WIDTH 8
#define PIPE_HOLE_HEIGHT 24
#define PIPE_OBMAS_SIZE 15
#define SCREEN_START (8 * 7)
#define SCREEN_HEIGHT (8 * 16)
#define SCREEN_END (SCREEN_HEIGHT + SCREEN_START)
#define SCREEN_WIDTH 256

typedef struct pipe_s {
    coordinate_t hole;
    uint8_t obmas[PIPE_OBMAS_SIZE];
    bool passed;
} pipe_t;

bool pipe_move(pipe_t *);

void pipe_newy(pipe_t *);

void pipe_draw(pipe_t *);

bool pipe_collision(pipe_t *p, coordinate_t *bird);

#endif
