#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Hook de overflow de stack (requiere Check for stack overflow = Mode 1/2)
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask;
    ESP_EARLY_LOGE("FAULT", "Stack overflow en tarea: %s", pcTaskName);
    fflush(stdout);
    abort();  // genera backtrace y reinicia según config
}

// Handler para configASSERT()
void vAssertCalled(const char* file, int line, const char* expr)
{
    ESP_EARLY_LOGE("ASSERT", "configASSERT failed: %s (%s:%d)", expr, file, line);
    fflush(stdout);
    abort();
}
