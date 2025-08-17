#pragma once
#include "freertos/FreeRTOS.h"

#ifdef __cplusplus
extern "C" {
#endif
void vAssertCalled(const char* file, int line, const char* expr);
#ifdef __cplusplus
}
#endif

// Redefine macro a nuestro handler
#ifdef configASSERT
#undef configASSERT
#endif
#define configASSERT(x) do { if ((x) == 0) vAssertCalled(__FILE__, __LINE__, #x); } while(0)
