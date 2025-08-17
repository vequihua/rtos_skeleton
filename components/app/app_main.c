#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "config.h"
#include "app_sm.h"
#include "log_task/log_task.h"

static const char* TAG = "app_main";

void app_main(void)
{
    ESP_LOGI(TAG, "Boot!");
    app_sm_init();
    configASSERT( xPortGetFreeHeapSize() > 0 );   // ejemplo simple

    // Política inicial de prioridades/stack (ajustar luego con HW marks)
    log_task_start(PRIO_BAND_NORM, STK_MEDIUM);

    // Aquí luego: comm_task_start(...), sensor_svc_start(...), storage_svc_start(...)
}