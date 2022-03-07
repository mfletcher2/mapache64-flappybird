#include "pipe.h"

#include <mapache64_zero_page.h>
#include <stdlib.h>
#include <stop.h>
#include <vram.h>

#include "bird.h"
#include "patterns.h"

void pipe_move(pipe_t* p) {
    p->hole.x -= PIPE_SPEED;
    if (p->hole.x < 0) {
        p->hole.x = SCREEN_WIDTH - 1;
        pipe_newy(p);
    }
}

bool pipe_collision(pipe_t* p, coordinate_t* bird) {
    if (bird->x < p->hole.x - BIRD_WIDTH || bird->x > p->hole.x + PIPE_WIDTH)
        return false;

    return p->hole.y > bird->y ||
           bird->y + BIRD_HEIGHT > p->hole.y + PIPE_HOLE_HEIGHT;
}

void pipe_draw(pipe_t* p) {
    uint8_t j;

    if (p->hole.x > SCREEN_WIDTH) {
        for (j = 0; j < PIPE_OBMAS_SIZE; j++) {
            OBM[p->obmas[j]].x = 0;
            OBM[p->obmas[j]].y = 256;
        }
    }

    else {
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
                if (newy < SCREEN_START) newy = SCREEN_END;
            }
        }
    }
}

void pipe_newy(pipe_t* p) {
    // replace 16 with rand()
    p->hole.y =
        SCREEN_START + 8 + rand() % (SCREEN_HEIGHT - PIPE_HOLE_HEIGHT - 16);
}
