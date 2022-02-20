#include "pipe.h"

#include <stdlib.h>
#include <vram.h>

#include "bird.h"
#include "patterns.h"

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

void pipe_draw(pipe_t* p) {
    uint8_t j;

    for (j = 0; j < PIPE_OBMAS_SIZE; j++) {
        OBM[p->obmas[j]].x = p->hole.x;
    }

    if (OBM[p->obmas[0]].y != p->hole.y - 8 &&
        OBM[p->obmas[0]].y !=
            p->hole.y - 8 + SCREEN_HEIGHT) {  // if y value has changed
        uint8_t newy = p->hole.y;
        for (j = 0; j < PIPE_OBMAS_SIZE; j++) {
            newy -= 8;
            if (newy > p->hole.y && newy < p->hole.y + PIPE_HOLE_HEIGHT)
                newy = p->hole.y + PIPE_HOLE_HEIGHT;
            OBM[p->obmas[j]].y = newy;
            if (newy < SCREEN_START) newy += SCREEN_HEIGHT;
        }
    }
}

void pipe_newy(pipe_t* p) {
    // replace 16 with rand()
    p->hole.y = SCREEN_START + 16 % (SCREEN_HEIGHT - PIPE_HOLE_HEIGHT);
}
