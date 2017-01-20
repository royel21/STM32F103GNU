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

extern volatile uint32_t t_Millis;
extern volatile uint8_t clock;
extern volatile uint32_t reload;

void Systick_Startup();

void delayMillis(uint32_t);
void delayMicros(uint32_t);

static inline uint32_t getSystemTick()
{
  return SysTick->VAL;
}

static inline uint32_t millis()
{
  return t_Millis;
}

static inline uint32_t micros(void)
{
  uint32_t ms = 0, tick = 0;
  do
  {
    ms = millis();
    tick = getSystemTick();
    asm volatile("nop");
    asm volatile("nop");
  } while (ms != millis());
  return (ms * (uint16_t) 1000) + (reload + (uint8_t) 1 - tick) / clock;
}



#ifdef __cplusplus
}
#endif

#endif /* SYSTIMER_H_ */
