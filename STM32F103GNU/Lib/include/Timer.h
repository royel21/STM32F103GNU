/*
 * Timer.h
 *
 *  Created on: Dec 29, 2016
 *      Author: Royel
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "cmsis_device.h"

#define TIM_CCMR1_OC1PWM1   ((uint16_t)0x00000060)
#define TIM_CCMR1_OC1PWM2   ((uint16_t)0x00000070)
#define TIM_CCMR1_OC2PWM1   ((uint16_t)0x00006000)
#define TIM_CCMR1_OC2PWM2   ((uint16_t)0x00007000)
#define TIM_CCMR2_OC3PWM1   TIM_CCMR1_OC1PWM1
#define TIM_CCMR2_OC3PWM2   TIM_CCMR1_OC1PWM2
#define TIM_CCMR2_OC4PWM1   TIM_CCMR1_OC2PWM1
#define TIM_CCMR2_OC4PWM2   TIM_CCMR1_OC2PWM2

#define TIM_CH01  (uint8_t)0x0
#define TIM_CH02  (uint8_t)0x1
#define TIM_CH03  (uint8_t)0x2
#define TIM_CH04  (uint8_t)0x3

#define TIM_CountUP    (uint8_t)0x00
#define TIM_CountDown  (uint8_t)0x01

class Timer
{

  private:
    TIM_TypeDef *timer;
  public:
    Timer(TIM_TypeDef *, uint16_t presc = 72, uint16_t autoReload = 20000);
    void start();
    //set the direction  of the counter down or up default up
    void setCountDir(uint8_t dir = 0);
    //set the pre-sclale default 1MHZ count or 1us update
    void setPreScale(uint16_t prescale);
    void setAutoReload(uint16_t f);
    void setPwmCh(uint8_t ch, uint16_t duty);
    void setDuty(uint8_t ch, uint16_t duty);
    void setPwmPolarity(uint32_t ch, uint8_t p);

    uint16_t getCount();
};

#endif /* TIMER_H_ */
