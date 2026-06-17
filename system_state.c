#include "system_state.h"
#include "app_config.h"

static volatile uint8_t g_counter = 0;
static volatile bool g_direction_up = true;
static volatile uint32_t g_speed_ms = SPEED_SLOW_MS;
static volatile bool g_running = false;

void system_state_init(void) {
    g_counter = 0;
    g_direction_up = true;
    g_speed_ms = SPEED_SLOW_MS;
    g_running = false;
}

uint8_t system_get_counter(void) {
    return g_counter;
}

void system_set_counter(uint8_t value) {
    g_counter = value % 10;
}

bool system_get_direction_up(void) {
    return g_direction_up;
}

void system_toggle_direction(void) {
    g_direction_up = !g_direction_up;
}

uint32_t system_get_speed_ms(void) {
    return g_speed_ms;
}

void system_toggle_speed(void) {
    if (g_speed_ms == SPEED_SLOW_MS) {
        g_speed_ms = SPEED_FAST_MS;
    } else {
        g_speed_ms = SPEED_SLOW_MS;
    }
}

bool system_get_running(void) {
    return g_running;
}

void system_set_running(bool running) {
    g_running = running;
}