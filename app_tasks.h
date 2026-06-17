#ifndef APP_TASKS_H
#define APP_TASKS_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

extern TaskHandle_t hCounterTask;

void app_tasks_create_all(void);
void vTaskManager(void *pvParameters);
void app_send_event_from_button(int event);

#endif