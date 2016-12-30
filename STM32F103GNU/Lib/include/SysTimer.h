/*
 * Timer.h
 *
 *  Created on: Nov 14, 2016
 *      Author: RoyerAriel
 */

#ifndef SYSTIMER_H_
#define SYSTIMER_H_

#include "cmsis_device.h"
#ifdef __cplusplus
extern "C" {
#endif

void Systick_Startup();
uint32_t micros(void);
uint32_t millis(void);
void delayMillis(uint32_t);
void delayMicros(uint32_t);

#ifdef __cplusplus
}
#endif

#endif /* SYSTIMER_H_ */
