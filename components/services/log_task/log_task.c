// components/services/log_task/log_task.c
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "osal.h"
#include "telemetry.h"

static const char* TAG = "log_task";
static osal_timer_t s_timer;

static void timer_cb(TimerHandle_t xTimer) 
{
    (void)xTimer;
    tel_print_heap();
    tel_print_runtime_stats();  // %CPU por tarea
    tel_print_task_list();      // lista de tareas + stack remanente
}

static void task_fn(void* arg) 
{
    ESP_LOGI(TAG, "arrancando log_task");
    s_timer = osal_timer_create("t_telemetry", 5000, true, timer_cb);
    (void)osal_timer_start(s_timer);

    TickType_t last = 0;
    for (;;) {
        ESP_LOGI(TAG, "heartbeat");
        tel_print_task_stack(TAG, xTaskGetCurrentTaskHandle());
        osal_delay_until_ms(&last, 1000);   // periodo exacto de 1s
    }
}

void log_task_start(UBaseType_t prio, uint32_t stack_words) 
{
    (void)osal_task_create(task_fn, "tLog", stack_words, NULL, prio, NULL);
}
