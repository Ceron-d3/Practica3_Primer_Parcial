#include "app_tasks.h"
#include "buttons.h"
#include "counter.h"
#include "system_state.h"

#include "freertos/queue.h"
#include "esp_log.h"

static const char *TAG = "TASK_MANAGER";

TaskHandle_t hCounterTask = NULL;

static TaskHandle_t hButtonDir = NULL;
static TaskHandle_t hButtonSpeed = NULL;
static TaskHandle_t hButtonStart = NULL;

static TaskHandle_t hLed0 = NULL;
static TaskHandle_t hLed1 = NULL;
static TaskHandle_t hLed2 = NULL;
static TaskHandle_t hLed3 = NULL;

static TaskHandle_t hTaskManager = NULL;

static QueueHandle_t event_queue = NULL;

typedef struct {
    const char *name;
} manager_params_t;

void app_send_event_from_button(int event) {
    app_event_t app_event = (app_event_t)event;

    if (event_queue != NULL) {
        xQueueSend(event_queue, &app_event, 0);
    }
}

void vTaskManager(void *pvParameters) {
    const manager_params_t *cfg = (const manager_params_t *)pvParameters;
    app_event_t event;

    ESP_LOGI(TAG, "%s iniciado", cfg->name);

    system_set_running(false);

    if (hCounterTask != NULL) {
        vTaskSuspend(hCounterTask);
        ESP_LOGI(TAG, "Sistema iniciado en PAUSA. Contador suspendido");
    }

    for (;;) {
        if (xQueueReceive(event_queue, &event, portMAX_DELAY) == pdTRUE) {
            switch (event) {
                case EVENT_BUTTON_START_PAUSE:
                    if (system_get_running()) {
                        system_set_running(false);

                        if (hCounterTask != NULL) {
                            vTaskSuspend(hCounterTask);
                        }

                        ESP_LOGI(TAG, "[MANAGER] Sistema PAUSADO. Contador suspendido");
                    } else {
                        system_set_running(true);

                        if (hCounterTask != NULL) {
                            vTaskResume(hCounterTask);
                        }

                        ESP_LOGI(TAG,
                                 "[MANAGER] Sistema REANUDADO desde valor=%d",
                                 system_get_counter());
                    }
                    break;

                case EVENT_BUTTON_DIR:
                    if (system_get_running()) {
                        system_toggle_direction();

                        ESP_LOGI(TAG,
                                 "[MANAGER] Direccion cambiada a: %s",
                                 system_get_direction_up() ? "ASCENDENTE" : "DESCENDENTE");
                    } else {
                        ESP_LOGW(TAG,
                                 "[MANAGER] Ignorado: no se permite cambiar direccion en pausa");
                    }
                    break;

                case EVENT_BUTTON_SPEED:
                    if (system_get_running()) {
                        system_toggle_speed();

                        ESP_LOGI(TAG,
                                 "[MANAGER] Velocidad cambiada a: %lums",
                                 (unsigned long)system_get_speed_ms());
                    } else {
                        ESP_LOGW(TAG,
                                 "[MANAGER] Ignorado: no se permite cambiar velocidad en pausa");
                    }
                    break;

                default:
                    break;
            }

            if (hCounterTask != NULL) {
                ESP_LOGI(TAG,
                         "[MANAGER] Estado contador: %d",
                         (int)eTaskGetState(hCounterTask));
            }
        }
    }
}

void app_tasks_create_all(void) {
    static const button_params_t btn_dir = {
        .gpio = 18,
        .event = EVENT_BUTTON_DIR,
        .name = "BTN_DIR"
    };

    static const button_params_t btn_speed = {
        .gpio = 19,
        .event = EVENT_BUTTON_SPEED,
        .name = "BTN_SPEED"
    };

    static const button_params_t btn_start = {
        .gpio = 21,
        .event = EVENT_BUTTON_START_PAUSE,
        .name = "BTN_START_PAUSE"
    };

    static const led_task_params_t led0 = {
        .bit_index = 0,
        .name = "LED_BCD0"
    };

    static const led_task_params_t led1 = {
        .bit_index = 1,
        .name = "LED_BCD1"
    };

    static const led_task_params_t led2 = {
        .bit_index = 2,
        .name = "LED_BCD2"
    };

    static const led_task_params_t led3 = {
        .bit_index = 3,
        .name = "LED_BCD3"
    };

    static const manager_params_t manager_cfg = {
        .name = "TASK_MANAGER"
    };

    event_queue = xQueueCreate(10, sizeof(app_event_t));

    xTaskCreate(vTaskCounter, "Counter", 2048, NULL, 2, &hCounterTask);

    xTaskCreate(vTaskButton, "ButtonDir", 2048, (void *)&btn_dir, 3, &hButtonDir);
    xTaskCreate(vTaskButton, "ButtonSpeed", 2048, (void *)&btn_speed, 3, &hButtonSpeed);
    xTaskCreate(vTaskButton, "ButtonStart", 2048, (void *)&btn_start, 3, &hButtonStart);

    xTaskCreate(vTaskLedBit, "LedBCD0", 2048, (void *)&led0, 1, &hLed0);
    xTaskCreate(vTaskLedBit, "LedBCD1", 2048, (void *)&led1, 1, &hLed1);
    xTaskCreate(vTaskLedBit, "LedBCD2", 2048, (void *)&led2, 1, &hLed2);
    xTaskCreate(vTaskLedBit, "LedBCD3", 2048, (void *)&led3, 1, &hLed3);

    xTaskCreate(vTaskManager, "TaskManager", 4096, (void *)&manager_cfg, 4, &hTaskManager);

    ESP_LOGI(TAG, "Tareas creadas correctamente");
}