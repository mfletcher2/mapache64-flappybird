#ifndef __BIRD_H
#define __BIRD_H

#include "coordinate.h"
#include <Q9_6.h>

#define BIRD_WIDTH 8
#define BIRD_HEIGHT 8
#define BIRD_OBMAS_SIZE 1
#define BIRD_FLAP_STRENGTH -(SINT_TO_Q9_6(3))
#define BIRD_GRAVITY ((Q9_6)0x000a) 

typedef struct bird_s {
    coordinate_t pos;
    Q9_6 y_velocity;
    uint8_t obmas[BIRD_OBMAS_SIZE];
} bird_t;

void bird_init(bird_t *);

void bird_flap(bird_t *);

void bird_move(bird_t *);

void bird_draw(bird_t *);

#endif