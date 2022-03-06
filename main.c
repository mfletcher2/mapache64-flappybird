
// ==================== main.c ==================== //
// Follow this file template to implement your game //
// ================================================ //

#define SIM 1 // change value depending if running simulation or not

// ================================ //
#pragma code-name ("CODE")
#pragma bss-name ("BSS")

#include <int.h>
#include <vram.h>
#include <stop.h>
#include <Q9_6.h>
#include <mapache64_zero_page.h>
#include <controller.h>
#include <screen.h>

#include "pipe.h"
#include "pipearray.h"
#include "patterns.h"
#include "bird.h"

bird_t bird;

uint16_t CONTROLLER_1_PEDGE;
uint16_t CONTROLLER_1_PREV;

void fill_vram(void);

// run once on startup
void reset(void) { 
    pipearray_init();
    bird_init(&bird);
    load_patterns();  
    //fill_vram();
    //stop();
}

// run 60 times a second
void do_logic(void) {
    // calculate positive edge of all controller buttons
    CONTROLLER_1_PEDGE = (~CONTROLLER_1_PREV) & CONTROLLER_1;
    CONTROLLER_1_PREV = CONTROLLER_1;

    pipearray_move();

    if (CONTROLLER_1_PEDGE & CONTROLLER_A_MASK) bird_flap(&bird);

    bird_move(&bird);

    pipearray_draw();
    bird_draw(&bird);
}

// run after do_logic and once gpu is idle
void fill_vram(void) { 


}
