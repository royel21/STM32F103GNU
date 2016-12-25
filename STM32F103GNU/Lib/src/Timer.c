/*
 * Timer.cpp
 *
 *  Created on: Nov 14, 2016
 *      Author: RoyerAriel
 */

#include "Timer.h"
#define NVIC_PriorityGroup_4         ((uint32_t)0x300)
volatile uint32_t Millis;

volatile uint8_t clock = 0;

void Systick_Startup()
{
  clock = SystemCoreClock / 1000000;
  if (SysTick_Config(SystemCoreClock / 1000)) //1ms per interrupt
    while (1)
      ;
  //set systick interrupt priority
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4); //4 bits for preemp priority 0 bit for sub priority
  NVIC_SetPriority(SysTick_IRQn, 0); //i want to make sure systick has highest priority amount all other interrupts
  Millis = 0;    //reset Millis
}

uint32_t micros(void)
{
  return (Millis * 1000) + ((1000 - SysTick->VAL) / clock);
}

uint32_t millis(void)
{
  return Millis;
}

void delayMillis(uint32_t nTime)
{
  uint32_t curTime = Millis;
  while ((Millis - curTime) < nTime)
    ;
}

void delayMicros(uint32_t nTime)
{
  uint32_t curTime = micros();
  while ((micros() - curTime) < nTime)
    ;
}

void SysTick_Handler(void)
{
  Millis++;
}

