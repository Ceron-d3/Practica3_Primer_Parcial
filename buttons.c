#include "buttons.h"
#include "app_config.h"
#include "app_tasks.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG = "BUTTONS";

void buttons_init(void) {
    const uint8_t button_gpios[3] = {
        BTN_DIR_GPIO,
        BTN_SPEED_GPIO,
        BTN_START_GPIO
    };

    for (int i = 0; i < 3; i++) {
        gpio_config_t io_conf = {
            .pin_bit_mask = (1ULL << button_gpios[i]),
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = GPIO_PULLUP_ENABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_DISABLE
        };

        gpio_config(&io_conf);
    }
}

void vTaskButton(void *pvParameters) {
    const button_params_t *cfg = (const button_params_t *)pvParameters;

    int last_state = 1;

    ESP_LOGI(TAG, "[%s] Tarea iniciada GPIO%d", cfg->name, cfg->gpio);

    for (;;) {
        int current_state = gpio_get_level(cfg->gpio);

        if (last_state == 1 && current_state == 0) {
            ESP_LOGI(TAG, "[%s] Boton presionado", cfg->name);
            app_send_event_from_button(cfg->event);
            vTaskDelay(pdMS_TO_TICKS(BUTTON_DEBOUNCE_MS));
        }

        last_state = current_state;
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}