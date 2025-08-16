// components/common/telemetry.c
#include "telemetry.h"
#include "esp_log.h"
#include "esp_heap_caps.h"
#include "esp_timer.h"     // requiere REQUIRES esp_timer en CMake
#include <stdio.h>

static const char* TAG = "telemetry";

void tel_print_heap(void) 
{
    multi_heap_info_t info;
    heap_caps_get_info(&info, MALLOC_CAP_8BIT);
    ESP_LOGI(TAG, "Heap: free=%u, largest=%u, total=%u, min_free=%u",
             (unsigned)info.total_free_bytes,
             (unsigned)info.largest_free_block,
             (unsigned)(info.total_allocated_bytes + info.total_free_bytes),
             (unsigned)info.minimum_free_bytes);
}

void tel_print_task_stack(const char* tag, TaskHandle_t th) 
{
    if (!th) th = xTaskGetCurrentTaskHandle();
    UBaseType_t hw = uxTaskGetStackHighWaterMark(th);
    ESP_LOGI(TAG, "Stack HW %s: %u words (~%u bytes)",
             tag, (unsigned)hw, (unsigned)(hw*sizeof(StackType_t)));
}

void tel_print_runtime_stats(void) 
{
#if ( configGENERATE_RUN_TIME_STATS == 1 )
    static char buf[1024];
    vTaskGetRunTimeStats(buf);     // requiere configUSE_TRACE_FACILITY + GENERATE_RUN_TIME_STATS
    ESP_LOGI(TAG, "Run-time stats:\n%s", buf);
#else
    ESP_LOGW(TAG, "Run-time stats disabled");
#endif
}

void tel_print_task_list(void) 
{
#if ( configUSE_TRACE_FACILITY == 1 )
    static char buf[1024];
    vTaskList(buf);                // requiere configUSE_TRACE_FACILITY
    ESP_LOGI(TAG, "Task list:\n%s", buf);
#else
    ESP_LOGW(TAG, "Trace facility disabled");
#endif
}
