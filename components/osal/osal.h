#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/timers.h"
#include "freertos/semphr.h"

#ifdef __cplusplus
extern "C" {
#endif

// Tipos OSAL
typedef TaskHandle_t      osal_task_t;
typedef QueueHandle_t     osal_queue_t;
typedef TimerHandle_t     osal_timer_t;
typedef SemaphoreHandle_t osal_mutex_t;

typedef void (*osal_task_fn)(void*);
typedef void (*osal_timer_cb)(TimerHandle_t);

// ---- Tareas ----
bool        osal_task_create(osal_task_fn fn, const char* name, uint32_t stack_words, void* arg, UBaseType_t prio, osal_task_t* out);
void        osal_delay_ms(uint32_t ms);
void        osal_delay_until_ms(TickType_t* last_wake_tick, uint32_t period_ms);
UBaseType_t osal_task_get_hwm_words(osal_task_t th);   // High-watermark (en words)
TickType_t  osal_tick_count(void);

// ---- Colas ----
osal_queue_t osal_queue_create(uint32_t length, uint32_t item_size);
bool         osal_queue_send(osal_queue_t q, const void* item, uint32_t timeout_ms);
bool         osal_queue_recv(osal_queue_t q, void* item, uint32_t timeout_ms);

// ---- Notificaciones (opcional si las usas) ----
bool     osal_notify_give(osal_task_t task);                         // contexto de tarea
bool     osal_notify_give_from_isr(osal_task_t task);                // contexto ISR
uint32_t osal_notify_take(uint32_t timeout_ms);

// ---- Timers ----
osal_timer_t osal_timer_create(const char* name, uint32_t period_ms, bool auto_reload, osal_timer_cb cb);
bool         osal_timer_start(osal_timer_t t);
bool         osal_timer_stop (osal_timer_t t);

// ---- Mutex ----
osal_mutex_t osal_mutex_create(void);                // mutex con herencia de prioridad
bool         osal_mutex_lock(osal_mutex_t mtx, uint32_t timeout_ms);
bool         osal_mutex_unlock(osal_mutex_t mtx);

osal_mutex_t osal_recursive_mutex_create(void);
bool         osal_recursive_mutex_lock(osal_mutex_t mtx, uint32_t timeout_ms);
bool         osal_recursive_mutex_unlock(osal_mutex_t mtx);

// ---- Utilidad de unidades ----
static inline TickType_t osal_ms_to_ticks(uint32_t ms) { return pdMS_TO_TICKS(ms); }

#ifdef __cplusplus
}
#endif
