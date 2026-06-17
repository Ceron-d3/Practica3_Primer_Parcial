#include "leds.h"
#include "app_config.h"
#include "driver/gpio.h"

static const uint8_t led_gpios[4] = {
    LED_BIT0_GPIO,
    LED_BIT1_GPIO,
    LED_BIT2_GPIO,
    LED_BIT3_GPIO
};

void leds_init(void) {
    for (int i = 0; i < 4; i++) {
        gpio_config_t io_conf = {
            .pin_bit_mask = (1ULL << led_gpios[i]),
            .mode = GPIO_MODE_OUTPUT,
            .pull_up_en = GPIO_PULLUP_DISABLE,
            .pull_down_en = GPIO_PULLDOWN_DISABLE,
            .intr_type = GPIO_INTR_DISABLE
        };

        gpio_config(&io_conf);
        gpio_set_level(led_gpios[i], 0);
    }
}

void leds_write_bit(uint8_t bit_index, uint8_t value) {
    if (bit_index > 3) {
        return;
    }

    gpio_set_level(led_gpios[bit_index], value ? 1 : 0);
}