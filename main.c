#include "leds.h"
#include "buttons.h"
#include "system_state.h"
#include "app_tasks.h"
#include "esp_log.h"

static const char *TAG = "MAIN";

void app_main(void) {
    ESP_LOGI(TAG, "=== Practica 3: Contador BCD FreeRTOS ===");

    system_state_init();
    leds_init();
    buttons_init();
    app_tasks_create_all();

    ESP_LOGI(TAG, "Sistema iniciado. Presiona START/PAUSE para comenzar");
}