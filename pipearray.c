#include "pipe.h"
#include "pipearray.h"
#include <vram.h>
#include "patterns.h"
#include "bird.h"

pipe_t pipearray[PIPEARRAY_SIZE];

void pipearray_init(void) {
    uint8_t i, j;

    for (i = 0; i < PIPEARRAY_SIZE; i++) {
        pipearray[i].hole.x = i * 64;
        pipe_newy(pipearray + i);
    }

}

void pipearray_move(void) {
    uint8_t i;
    for(i = 0; i < PIPEARRAY_SIZE; i++) 
        pipe_move(pipearray + i);
}

void pipearray_draw(void) {
    uint8_t i, j;
    uint8_t k = BIRD_OBMAS_SIZE;
    uint8_t newy;

    for (i = 0; i < PIPEARRAY_SIZE; i++) {
        newy = pipearray[i].hole.y;
        for (j = 0; j < PIPE_OBMAS_SIZE; j++) {
            pipearray[i].obmas[j] = k;
            OBM[k].pattern_config = white_pattern;
            OBM[k].x = pipearray[i].hole.x;

            newy -= 8;
            if (newy > pipearray[i].hole.y &&
                newy < pipearray[i].hole.y + PIPE_HOLE_HEIGHT)
                newy = pipearray[i].hole.y + PIPE_HOLE_HEIGHT;
            OBM[k].y = newy;
            if (newy < SCREEN_START) newy += SCREEN_HEIGHT;

            OBM[k].color = WHITE_C_MASK;
            k++;
        }
    }
}