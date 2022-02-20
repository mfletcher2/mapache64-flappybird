#include "pipearray.h"

#include "bird.h"
#include "pipe.h"

pipe_t pipearray[PIPEARRAY_SIZE];

void pipearray_init(void) {
    uint8_t i, j;
    uint8_t k = BIRD_OBMAS_SIZE;

    for (i = 0; i < PIPEARRAY_SIZE; i++) {
        pipearray[i].hole.x = i * 64;
        pipe_newy(pipearray + i);
        for (j = 0; j < PIPE_OBMAS_SIZE; j++) {
            pipearray[i].obmas[j] = k;
            k++;
        }
    }
}

void pipearray_move(void) {
    uint8_t i;
    for (i = 0; i < PIPEARRAY_SIZE; i++) pipe_move(pipearray + i);
}

void pipearray_draw(void) {
    uint8_t i;
    for (i = 0; i < PIPEARRAY_SIZE; i++) pipe_draw(pipearray + i);
}