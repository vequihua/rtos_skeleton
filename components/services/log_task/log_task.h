// components/services/log_task/log_task.h
#pragma once
#include <stdint.h>
#include "freertos/FreeRTOS.h"

#ifdef __cplusplus
extern "C" {
#endif
void log_task_start(UBaseType_t prio, uint32_t stack_words);
#ifdef __cplusplus
}
#endif

