#ifndef UTIL_H_
#define UTIL_H_

#include "cmsis_device.h"
#include "define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EXTI_TRG_CHANGE    (uint8_t)0
#define EXTI_TRG_RISING    (uint8_t)1
#define EXTI_TRG_FALLING   (uint8_t)2

void InterruptEnabler(IRQn_Type, uint16_t = 0x0F, uint16_t = 0x0F);

void GPIO_Config(GPIO_TypeDef *port, const uint16_t pins, uint8_t mode, uint8_t cnf = 0);

void EXTI_Configuration(GPIO_TypeDef *port, const uint16_t pins, uint8_t trigger = EXTI_TRG_CHANGE);



#ifdef __cplusplus
}
#endif

#endif
