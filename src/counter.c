#include "counter.h"
#include "system_state.h"
#include "leds.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "COUNTER";

void vTaskCounter(void *pvParameters) {
    (void)pvParameters;

    ESP_LOGI(TAG, "Tarea contador iniciada");

    for (;;) {
        uint8_t value = system_get_counter();

        if (system_get_direction_up()) {
            value++;

            if (value > 9) {
                value = 0;
            }
        } else {
            if (value == 0) {
                value = 9;
            } else {
                value--;
            }
        }

        system_set_counter(value);

        ESP_LOGI(TAG,
                 "[COUNT] valor=%d direccion=%s velocidad=%lums",
                 value,
                 system_get_direction_up() ? "UP" : "DOWN",
                 (unsigned long)system_get_speed_ms());

        vTaskDelay(pdMS_TO_TICKS(system_get_speed_ms()));
    }
}

void vTaskLedBit(void *pvParameters) {
    const led_task_params_t *cfg = (const led_task_params_t *)pvParameters;

    ESP_LOGI(TAG, "[%s] Tarea LED BCD iniciada", cfg->name);

    for (;;) {
        uint8_t value = system_get_counter();
        uint8_t bit_value = (value >> cfg->bit_index) & 0x01;

        leds_write_bit(cfg->bit_index, bit_value);

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}
