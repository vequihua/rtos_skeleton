#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/timers.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef TaskHandle_t   osal_task_t;
typedef QueueHandle_t  osal_queue_t;
typedef TimerHandle_t  osal_timer_t;

typedef void (*osal_task_fn)(void*);
typedef void (*osal_timer_cb)(TimerHandle_t);

bool osal_task_create(osal_task_fn fn, const char* name, uint32_t stack_words, void* arg, UBaseType_t prio, osal_task_t* out);
void osal_delay_ms(uint32_t ms);
osal_queue_t osal_queue_create(uint32_t length, uint32_t item_size);
bool osal_queue_send(osal_queue_t q, const void* item, uint32_t timeout_ms);
bool osal_queue_recv(osal_queue_t q, void* item, uint32_t timeout_ms);

bool osal_notify_give(osal_task_t task);
uint32_t osal_notify_take(uint32_t timeout_ms);

// Timers
osal_timer_t osal_timer_create(const char* name, uint32_t period_ms, bool auto_reload, osal_timer_cb cb);
bool osal_timer_start(osal_timer_t t);
bool osal_timer_stop(osal_timer_t t);

#ifdef __cplusplus
}
#endif
