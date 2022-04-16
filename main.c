
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
bool movepipe;
uint8_t ground_phase;

uint16_t CONTROLLER_1_PEDGE;
uint16_t CONTROLLER_1_PREV;

void fill_vram(void);

void draw_score(void) {
    if (score < 10)
        TXBL[4][16] = score + '0' | COLOR_SELECT_MASK;
    else if (score < 100) {
        TXBL[4][16] = score % 10 + '0' | COLOR_SELECT_MASK;
        TXBL[4][15] = score / 10 + '0' | COLOR_SELECT_MASK;
    } else {
        TXBL[4][16] = score % 10 + '0' | COLOR_SELECT_MASK;
        TXBL[4][15] = (score / 10) % 10 + '0' | COLOR_SELECT_MASK;
        TXBL[4][14] = score % 100 + '0' | COLOR_SELECT_MASK;
    }
}

void reset_TXBL(void) {
    uint8_t i, j;
    for (i = 0; i < 30; i++)
        for (j = 0; j < 32; j++) TXBL[i][j] = 0;
}

void show_gameover(void) {
    uint8_t i;
    const char gameover[] = "Game Over!";
    for (i = 0; i < 10; i++) TXBL[2][i + 12] = gameover[i] | COLOR_SELECT_MASK;
}

void move_ground() {
    tile_t pmba;
    uint8_t j;

    if (ground_phase >= 0 && ground_phase <= 3)
        pmba = ground1_pattern_pmba + ground_phase;
    else
        pmba =
            (ground1_pattern_pmba + 6 - ground_phase) | HFLIP_MASK | VFLIP_MASK;

    for (j = 0; j < 32; j++) NTBL[SCREEN_END / 8][j] = pmba;

    ground_phase++;
    if (ground_phase > 6) ground_phase = 0;
}

void init_vram(void) {
    uint8_t i, j;
    // clear vram
    for (i = 0; i < 64; i++) {
        OBM[i].y = 0xff;
    }

    load_patterns();

    // load background
    background_palette = GREEN_C0_MASK | CYAN_C1_MASK;
    for (i = 0; i < SCREEN_START / 8; i++)
        for (j = 0; j < 32; j++) NTBL[i][j] = black_pattern_pmba;

    for (i = SCREEN_START / 8; i < SCREEN_END / 8; i++)
        for (j = 0; j < 32; j++)
            NTBL[i][j] = white_pattern_pmba | COLOR_SELECT_MASK;

    ground_phase = 0;
    move_ground();

    for (i = SCREEN_END / 8 + 1; i < GameHeight / 8; i++)
        for (j = 0; j < 32; j++) NTBL[i][j] = black_pattern_pmba;

    vram_initialized = true;
}

// run once on startup
void reset(void) {
    if (!vram_initialized) init_vram();
    reset_TXBL();
    score = 0;
    draw_score();
}

// run 60 times a second
void do_logic(void) {
    // calculate positive edge of all controller buttons
    CONTROLLER_1_PEDGE = (~CONTROLLER_1_PREV) & CONTROLLER_1;
    CONTROLLER_1_PREV = CONTROLLER_1;

    if (game_running) {
        
        if (movepipe) {
            move_ground();

            if (pipearray_move()) {
                score++;
                draw_score();
            }
        }

        if ((CONTROLLER_1_PEDGE & CONTROLLER_A_MASK) &&
            Q9_6_to_sint16(bird.y) > SCREEN_START)
            bird_flap(&bird);

        bird_move(&bird);

        if (pipearray_collision(&bird) ||
            Q9_6_to_sint16(bird.y) >= SCREEN_END - BIRD_HEIGHT) {
            game_running = false;
            show_gameover();
        }

        pipearray_draw();
        bird_draw(&bird);

        movepipe = !movepipe;
    } else if (CONTROLLER_1_PEDGE & CONTROLLER_A_MASK) {
        reset();
        pipearray_init();
        bird_init(&bird);
        game_running = true;
    } else {
        bird_move(&bird);
        bird_draw(&bird);
    }
}

// run after do_logic and once gpu is idle
void fill_vram(void) {}
