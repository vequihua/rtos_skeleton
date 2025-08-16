idf_component_register(
    SRCS
        log_task/log_task.c
        comm_task/comm_task.c
        sensor_svc/sensor_svc.c
        storage_svc/storage_svc.c
    INCLUDE_DIRS
        "."
    REQUIRES freertos common osal nvs_flash esp_timer
)