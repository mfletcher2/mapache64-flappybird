#ifndef BIRD_H
#define BIRD_H

#include "coordinate.h"

#define BIRD_WIDTH 8
#define BIRD_HEIGHT 8
#define BIRD_OBMAS_SIZE 1


typedef struct bird_s {
    coordinate_t pos;
    uint8_t obmas[BIRD_OBMAS_SIZE];
} bird_t;

#endif