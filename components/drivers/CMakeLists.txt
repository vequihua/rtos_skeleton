idf_component_register(
    SRCS
        i2c_drv/i2c_drv.c
        uart_drv/uart_drv.c
        gpio_keys/gpio_keys.c
    INCLUDE_DIRS
        "."
    REQUIRES driver
)