#ifndef COUNTER_H
#define COUNTER_H

#include <stdint.h>

typedef struct {
    uint8_t bit_index;
    const char *name;
} led_task_params_t;

void vTaskCounter(void *pvParameters);
void vTaskLedBit(void *pvParameters);

#endif
