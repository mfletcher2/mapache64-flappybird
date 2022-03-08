
// ==================== main.c ==================== //
// Follow this file template to implement your game //
// ================================================ //

#define SIM 1  // change value depending if running simulation or not

// ================================ //
#pragma code - name("CODE")
#pragma bss - name("BSS")

#include <Q9_6.h>
#include <controller.h>
#include <int.h>
#include <mapache64_zero_page.h>
#include <screen.h>
#include <stop.h>
#include <vram.h>

#include "bird.h"
#include "patterns.h"
#include "pipe.h"
#include "pipearray.h"

bird_t bird;
bool game_running = false;
uint8_t score;
bool vram_initialized = false;

uint16_t CONTROLLER_1_PEDGE;
uint16_t CONTROLLER_1_PREV;

void fill_vram(void);

void draw_score(void) {
    if (score < 10)
        TXBL[4][16] = score + '0';
    else if (score < 100) {
        TXBL[4][16] = score % 10 + '0';
        TXBL[4][15] = score / 10 + '0';
    } else {
        TXBL[4][16] = score % 10 + '0';
        TXBL[4][15] = (score / 10) % 10 + '0';
        TXBL[4][14] = score % 100 + '0';
    }
}

void reset_TXBL(void) {
    uint8_t i, j;
    for (i = 0; i < 30; i++)
        for (j = 0; j < 32; j++) TXBL[i][j] = 0;
}

void init_vram(void) {
    uint8_t i, j;
    // clear vram
    for (i = 0; i < 64; i++) {
        OBM[i].y = 0xff;
    }

    load_patterns();

    // load background
    background_palette = WHITE_C0_MASK | CYAN_C1_MASK;
    for (i = 0; i < 7; i++)
        for (j = 0; j < 32; j++) NTBL[i][j] = white_pattern_pmba;

    for (i = 7; i < 22; i++)
        for (j = 0; j < 32; j++)
            NTBL[i][j] = white_pattern_pmba | COLOR_SELECT_MASK;

    for (i = 22; i < 30; i++)
        for (j = 0; j < 32; j++) NTBL[i][j] = black_pattern_pmba;

    vram_initialized = true;
}

// run once on startup
void reset(void) {
    if (!vram_initialized) init_vram();

    reset_TXBL();
    pipearray_init();
    bird_init(&bird);
    score = 0;
    draw_score();

    // fill_vram();
    // stop();
}

// run 60 times a second
void do_logic(void) {
    // calculate positive edge of all controller buttons
    CONTROLLER_1_PEDGE = (~CONTROLLER_1_PREV) & CONTROLLER_1;
    CONTROLLER_1_PREV = CONTROLLER_1;

    if (game_running) {
        if (pipearray_move()) {
            score++;
            draw_score();
        }

        if ((CONTROLLER_1_PEDGE & CONTROLLER_A_MASK) &&
            bird.pos.y > SCREEN_START)
            bird_flap(&bird);

        bird_move(&bird);

        if (pipearray_collision(&(bird.pos)) ||
            bird.pos.y > SCREEN_END - BIRD_HEIGHT)
            game_running = false;

        pipearray_draw();
        bird_draw(&bird);
    } else if (CONTROLLER_1_PEDGE & CONTROLLER_A_MASK) {
        reset();
        game_running = true;
    }
}

// run after do_logic and once gpu is idle
void fill_vram(void) {}
