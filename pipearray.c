#include "pipe.h"
#include "pipearray.h"
#include <vram.h>
#include "patterns.h"
#include "bird.h"

pipe_t pipearray[PIPEARRAY_SIZE];

void pipearray_init(void) {
    uint8_t i, j;
    uint8_t k = BIRD_OBMAS_SIZE;

    for (i = 0; i < PIPEARRAY_SIZE; i++) {
        pipearray[i].hole.x = i * 64;
        pipe_newy(pipearray + i);
        for (j = 0; j < PIPE_OBMAS_SIZE; j++) {
            pipearray[i].obmas[j] = k;
            OBM[k].pattern_config = white_pattern;
            OBM[k].x = pipearray[i].hole.x;
            OBM[k].y = pipearray[i].hole.y; // to fix
            OBM[k].color = WHITE_C_MASK;
            k++;
        }
    }

}
