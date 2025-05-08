/*
    Simple XORShift based random number generator for the atmega644p
    Authored by Willow Herring
*/
#include "xorrand.h"
#include <avr/io.h>

static struct xorshift32_state state = {.a = 0};

// Initialise the random number generator with noise from ADC
void rand_init() {
    // Initialise the ADC on channel 0
    ADMUX = 0x00;
    // Enable ADC and set prescaler to 64 for a 187.5KHz sample rate
    ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1);

    uint32_t seed = 0;

    for(uint8_t i=0; i<4; i++) {
        ADCSRA |= _BV(ADSC);
        while(ADCSRA & _BV(ADSC));
        seed |= ((ADC & 0x0F) << (i*4));
    }
    state.a = seed;

}

// Get a random uint32_t
uint32_t get_rand() {
    return xorshift32(&state);
}

// Taken from https://en.wikipedia.org/wiki/Xorshift#Example_implementation
// Internal function to feed and update xorshift state
uint32_t xorshift32(struct xorshift32_state *state)
{
	/* Algorithm "xor" from p. 4 of Marsaglia, "Xorshift RNGs" */
	uint32_t x = state->a;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	state->a = x;
    return x;
}