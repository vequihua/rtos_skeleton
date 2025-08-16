idf_component_register(
    SRCS
        app_main.c
        app_sm.c
    INCLUDE_DIRS
        "."
    REQUIRES freertos osal services drivers common
)