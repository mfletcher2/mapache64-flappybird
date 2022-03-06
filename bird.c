#include "bird.h"
#include "pipe.h"
#include "patterns.h"
#include <vram.h>

void bird_init(bird_t *bird) {
    uint8_t i;
    bird->pos.x = 48;
    bird->pos.y = SCREEN_START + (SCREEN_HEIGHT / 2);
    bird->y_velocity = 0;

    for(i = 0; i < BIRD_OBMAS_SIZE; i++) {
        bird->obmas[i] = i;
        OBM[i].pattern_config = white_pattern;
        OBM[i].color = YELLOW_C_MASK;
        OBM[i].x = bird->pos.x;
    }
    
}

void bird_flap(bird_t *bird) {
    bird->y_velocity = BIRD_FLAP_STRENGTH;
}

void bird_move(bird_t *bird) {
    bird->y_velocity = Q9_6_clamp(SINT_TO_Q9_6(-15), bird->y_velocity + BIRD_GRAVITY, SINT_TO_Q9_6(15));
    bird->pos.y += Q9_6_to_sint8(bird->y_velocity);
}

void bird_draw(bird_t *bird) {
    uint8_t i;
    for(i = 0; i < BIRD_OBMAS_SIZE; i++) {
        OBM[i].y = bird->pos.y;
    }
}