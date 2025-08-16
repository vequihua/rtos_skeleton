#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void tel_print_heap(void);
void tel_print_task_stack(const char* tag, TaskHandle_t th);
void tel_print_runtime_stats(void);