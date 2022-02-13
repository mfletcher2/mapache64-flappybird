#include "pipe.h"

#include <stdlib.h>

#include "bird.h"

void pipe_move(pipe_t* p) { p->hole.x -= PIPE_SPEED; }

bool pipe_collision(pipe_t* p, coordinate_t* bird) {
    if (bird->x < p->hole.x - BIRD_WIDTH || bird->x > p->hole.x + PIPE_WIDTH)
        return false;

    if (p->hole.y > bird->y ||
        bird->y + BIRD_HEIGHT > p->hole.y + PIPE_HOLE_HEIGHT)
        return true;

    return false;
}

void pipe_draw(pipe_t* p) {}

void pipe_newy(pipe_t* p) { 
    p->hole.y =  SCREEN_START + rand() % SCREEN_HEIGHT;    
}
