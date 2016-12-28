#ifndef UTIL_H_
#define UTIL_H_

#include "cmsis_device.h"
#include "define.h"

#ifdef __cplusplus
extern "C" {
#endif

void InterruptEnabler(IRQn_Type, uint16_t = 2, uint16_t = 2);

void GPIO_Config(GPIO_TypeDef *port, const uint16_t pins, uint8_t mode, uint8_t cnf = 0);

#ifdef __cplusplus
}
#endif

#endif
