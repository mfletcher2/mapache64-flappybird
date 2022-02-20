#include "pipe.h"

#include <stdlib.h>

#include "bird.h"

void pipe_move(pipe_t* p) {
    p->hole.x -= PIPE_SPEED;
    if (p->hole.x < -8) {
        p->hole.x = SCREEN_WIDTH;
        pipe_newy(p);
    }
}

bool pipe_collision(pipe_t* p, coordinate_t* bird) {
    if (bird->x < p->hole.x - BIRD_WIDTH || bird->x > p->hole.x + PIPE_WIDTH)
        return false;

    if (p->hole.y > bird->y ||
        bird->y + BIRD_HEIGHT > p->hole.y + PIPE_HOLE_HEIGHT)
        return true;

    return false;
}

void pipe_newy(pipe_t* p) {
    // replace 16 with rand()
    p->hole.y = SCREEN_START + 16 % (SCREEN_HEIGHT - PIPE_HOLE_HEIGHT);
}
