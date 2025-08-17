#include "osal.h"

// ----- Tareas -----
bool osal_task_create(osal_task_fn fn, const char* name, uint32_t stack_words, void* arg, UBaseType_t prio, osal_task_t* out)
{
    return xTaskCreate(fn, name, stack_words, arg, prio, out) == pdPASS;
}

void osal_delay_ms(uint32_t ms) 
{ 
    vTaskDelay(pdMS_TO_TICKS(ms)); 
}

void osal_delay_until_ms(TickType_t* last_wake_tick, uint32_t period_ms) 
{
    if (*last_wake_tick == 0) 
    { 
        *last_wake_tick = xTaskGetTickCount(); 
    }
    vTaskDelayUntil(last_wake_tick, pdMS_TO_TICKS(period_ms));
}

UBaseType_t osal_task_get_hwm_words(osal_task_t th) 
{
    return uxTaskGetStackHighWaterMark(th);
}

TickType_t osal_tick_count(void) 
{ 
    return xTaskGetTickCount(); 
}

// ----- Colas -----
osal_queue_t osal_queue_create(uint32_t length, uint32_t item_size) 
{
    return xQueueCreate(length, item_size);
}

bool osal_queue_send(osal_queue_t q, const void* item, uint32_t timeout_ms) 
{
    return xQueueSend(q, item, pdMS_TO_TICKS(timeout_ms)) == pdTRUE;
}

bool osal_queue_recv(osal_queue_t q, void* item, uint32_t timeout_ms) 
{
    return xQueueReceive(q, item, pdMS_TO_TICKS(timeout_ms)) == pdTRUE;
}

// ----- Notificaciones -----
bool osal_notify_give(osal_task_t task) 
{
    // Para contexto de tarea
    xTaskNotifyGive(task);
    return true;
}

bool osal_notify_give_from_isr(osal_task_t task) 
{
    // Para contexto ISR
    BaseType_t hpw = pdFALSE;
    vTaskNotifyGiveFromISR(task, &hpw);
    portYIELD_FROM_ISR(hpw);
    return true;
}

uint32_t osal_notify_take(uint32_t timeout_ms) 
{
    return ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(timeout_ms));
}

// ----- Timers -----
osal_timer_t osal_timer_create(const char* name, uint32_t period_ms, bool auto_reload, osal_timer_cb cb) 
{
    return xTimerCreate(name, pdMS_TO_TICKS(period_ms), auto_reload, NULL, cb);
}
bool osal_timer_start(osal_timer_t t) 
{ 
    return xTimerStart(t, 0) == pdPASS; 
}

bool osal_timer_stop (osal_timer_t t) 
{ 
    return xTimerStop (t, 0) == pdPASS; 
}

// ----- Mutex -----
osal_mutex_t osal_mutex_create(void) 
{
    return xSemaphoreCreateMutex();             // con herencia de prioridad
}

bool osal_mutex_lock(osal_mutex_t mtx, uint32_t timeout_ms) 
{
    return xSemaphoreTake(mtx, pdMS_TO_TICKS(timeout_ms)) == pdTRUE;
}

bool osal_mutex_unlock(osal_mutex_t mtx) 
{
    return xSemaphoreGive(mtx) == pdTRUE;
}

osal_mutex_t osal_recursive_mutex_create(void) 
{
    return xSemaphoreCreateRecursiveMutex();
}

bool osal_recursive_mutex_lock(osal_mutex_t mtx, uint32_t timeout_ms) 
{
    return xSemaphoreTakeRecursive(mtx, pdMS_TO_TICKS(timeout_ms)) == pdTRUE;
}

bool osal_recursive_mutex_unlock(osal_mutex_t mtx) 
{
    return xSemaphoreGiveRecursive(mtx) == pdTRUE;
}
