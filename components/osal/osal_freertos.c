#include "osal.h"

bool osal_task_create(osal_task_fn fn, const char* name, uint32_t stack_words,
                      void* arg, UBaseType_t prio, osal_task_t* out)
{
    return xTaskCreate(fn, name, stack_words, arg, prio, out) == pdPASS;
}

void osal_delay_ms(uint32_t ms) 
{ 
    vTaskDelay(pdMS_TO_TICKS(ms)); 
}

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

bool osal_notify_give(osal_task_t task) 
{
    BaseType_t hpw = pdFALSE;
    vTaskNotifyGiveFromISR(task, &hpw);
    portYIELD_FROM_ISR(hpw);
    return true;
}

uint32_t osal_notify_take(uint32_t timeout_ms) 
{
    return ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(timeout_ms));
}

osal_timer_t osal_timer_create(const char* name, uint32_t period_ms, bool auto_reload, osal_timer_cb cb) 
{
    return xTimerCreate(name, pdMS_TO_TICKS(period_ms), auto_reload, NULL, cb);
}
bool osal_timer_start(osal_timer_t t) { return xTimerStart(t, 0) == pdPASS; }
bool osal_timer_stop (osal_timer_t t) { return xTimerStop (t, 0) == pdPASS; }
