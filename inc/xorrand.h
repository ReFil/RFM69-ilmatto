/*
    Simple XORShift based random number generator for the atmega644p
    Authored by Willow Herring
*/

#pragma once

#include <stdint.h>

struct xorshift32_state {
    uint32_t a;
};

// Initialise the random number generator with noise from ADC
void rand_init();

// Get a random uint32_t
uint32_t get_rand();

// Internal function to feed and update xorshift state
uint32_t xorshift32(struct xorshift32_state *state);