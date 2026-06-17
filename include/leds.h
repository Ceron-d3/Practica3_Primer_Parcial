#ifndef LEDS_H
#define LEDS_H
#include <stdint.h>

void leds_init(void);
void leds_write_bit(uint8_t bit_index, uint8_t value);

#endif
