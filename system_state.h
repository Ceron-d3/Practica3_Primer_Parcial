#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H
#include <stdbool.h>
#include <stdint.h>

typedef enum {
    EVENT_BUTTON_DIR = 0,
    EVENT_BUTTON_SPEED,
    EVENT_BUTTON_START_PAUSE
} app_event_t;

void system_state_init(void);

uint8_t system_get_counter(void);
void system_set_counter(uint8_t value);

bool system_get_direction_up(void);
void system_toggle_direction(void);

uint32_t system_get_speed_ms(void);
void system_toggle_speed(void);

bool system_get_running(void);
void system_set_running(bool running);

#endif