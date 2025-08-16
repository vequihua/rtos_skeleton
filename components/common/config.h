#pragma once

// Bandas de prioridad (ejemplo; ajustar en README_RTOS.md)
#define PRIO_BAND_CRIT   (configMAX_PRIORITIES-1)
#define PRIO_BAND_HIGH   (configMAX_PRIORITIES-3)
#define PRIO_BAND_NORM   (configMAX_PRIORITIES-5)
#define PRIO_BAND_LOW    (tskIDLE_PRIORITY + 1)

// Tamaños de stack base (palabras, no bytes, en FreeRTOS)
#define STK_SMALL   (2048/sizeof(StackType_t))
#define STK_MEDIUM  (3072/sizeof(StackType_t))
#define STK_LARGE   (4096/sizeof(StackType_t))