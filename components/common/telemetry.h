// components/common/telemetry.h
#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#ifdef __cplusplus
extern "C" {
#endif

void tel_print_heap(void);
void tel_print_task_stack(const char* tag, TaskHandle_t th);
void tel_print_runtime_stats(void);   // %CPU por tarea
void tel_print_task_list(void);       // Lista de tareas + stack remanente

#ifdef __cplusplus
}
#endif
