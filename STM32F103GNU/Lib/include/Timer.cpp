/*
 * Timer.cpp
 *
 *  Created on: Dec 29, 2016
 *      Author: Royel
 */

#include <Timer.h>

Timer::Timer(TIM_TypeDef *tim, uint16_t preScale, uint16_t autoReload)
{
  timer = tim;
  //Timer peripheral Clock Bit0:1
  if (tim == TIM1)
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
  else if (tim == TIM2)
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  else if (tim == TIM3)
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
  else if (tim == TIM4)
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
  //Timer Pre-Scale register
  tim->PSC = preScale;
  //Timer auto-reload register
  tim->ARR = autoReload;
}

void Timer::start()
{
  /*TimerControl register 1
   * Counter enable                       Bit0:1
   * AutoReload pre-load                  Bit7:1
   */
  timer->CR1 |= TIM_CR1_CEN | TIM_CR1_ARPE;
}

void Timer::setCountDir(uint8_t dir)
{
  (dir == TIM_CountUP ) ? timer->CR1 |= TIM_CR1_DIR : timer->CR1 &= ~TIM_CR1_DIR;
}

void Timer::setPreScale(uint16_t prescale)
{
  timer->PSC = prescale;
}

void Timer::setAutoReload(uint16_t autoReload)
{
  timer->ARR = autoReload;
}

void Timer::setPwmCh(uint8_t ch, uint16_t duty)
{
  switch (ch)
  {
    case TIM_CH01 :
    {
      timer->CCMR1 |= TIM_CCMR1_OC1PE | TIM_CCMR1_OC1PWM1;  //set the pwm mode
      timer->CCR1 = duty;                                  //set the duty cycle
      timer->CCER |= TIM_CCER_CC1E;                        // enable the pwm output 1
      return;
    }
    case TIM_CH02 :
    {
      timer->CCMR1 |= TIM_CCMR1_OC2PE | TIM_CCMR1_OC2PWM1;  //set the pwm mode
      timer->CCR2 = duty;                                  //set the duty cycle
      timer->CCER |= TIM_CCER_CC2E;                        // enable the pwm output 2
      return;
    }
    case TIM_CH03 :
    {
      timer->CCMR1 |= TIM_CCMR2_OC4PE | TIM_CCMR2_OC4PWM1;   //set the pwm mode
      timer->CCR3 = duty;                                   //set the duty cycle
      timer->CCER |= TIM_CCER_CC3E;                         // enable the pwm output 3
      return;
    }
    case TIM_CH04 :
    {
      timer->CCMR2 |= TIM_CCMR2_OC4PE | TIM_CCMR2_OC4PWM1;   //set the pwm mode
      timer->CCR4 = duty;                                   //set the duty cycle
      timer->CCER |= TIM_CCER_CC4E;                         // enable the pwm output 4
      return;
    }
  }
}

void Timer::setPwmPolarity(uint32_t ch, uint8_t p)
{
  p == 0 ? timer->CCER |= 2 << ch * 4 : timer->CCER &= ~(2 << ch * 4);  //set the duty cycle
}

void Timer::setDuty(uint8_t ch, uint16_t duty)
{
  switch (ch)
  {
    case TIM_CH01 :
    {
      timer->CCR1 = duty;  //set the duty cycle
      return;
    }
    case TIM_CH02 :
    {
      timer->CCR2 = duty;  //set the duty cycle
      return;
    }
    case TIM_CH03 :
    {
      timer->CCR3 = duty;  //set the duty cycle
      return;
    }
    case TIM_CH04 :
    {
      timer->CCR4 = duty;  //set the duty cycle
      return;
    }
  }
}
uint16_t Timer::getCount()
{
  return timer->CNT;
}
