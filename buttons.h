#ifndef BUTTONS_H
#define BUTTONS_H
#include <stdint.h>
#include "system_state.h"

typedef struct {
    uint8_t gpio;
    app_event_t event;
    const char *name;
} button_params_t;

void buttons_init(void);
void vTaskButton(void *pvParameters);

#endif