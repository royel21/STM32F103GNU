/*
 * Analog.cpp
 *
 *  Created on: Nov 11, 2016
 *      Author: RoyerAriel
 */
#include "Analog.h"
#include "Util.h"


void analogReadWithDMAMulti(uint16_t pins, volatile uint16_t *vars, uint8_t size)
{
  RCC->AHBENR |= RCC_AHBENR_DMA1EN;
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
  //DMA Config
////  DMA1_Stream0->CR |= DMA_SxCR_CIRC | DMA_SxCR_MINC |
////  DMA_SxCR_PSIZE_16bit | DMA_SxCR_MSIZE_0 | DMA_SxCR_PL_VH;
////
////  DMA2_Stream0->M0AR = (uint32_t) &vars[0];
////
////  DMA2_Stream0->PAR = (uint32_t) &ADC1->DR;
////
////  DMA2_Stream0->NDTR = size;
////
////  DMA2_Stream0->CR |= DMA_SxCR_EN;
////
////  InterruptEnabler(DMA2_Stream0_IRQn, 0, 0);
////
////  int8_t order = 0;
////  for (uint8_t pin = 0; pin < 16; pin++)
////  {
////    if ((pins & (1 << pin)))
////    {
////      if (pin < 6)
////      {
////        ADC1->SQR3 |= pin << (order * 5);
////        GPIOA->MODER |= (3 << (pin * 2));
////      } else if (pin > 5 && pin < 12)
////      {
////        ADC1->SQR2 |= pin << (order * 5);
////        if (pin < 7)
////        {
////          GPIOA->MODER |= (3 << (pin * 2));
////        } else if (pin == 8 || pin == 9)
////        {
////          RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
////          GPIOB->MODER |= 3 << ((pin - 8) * 2);
////        } else
////        {
////          RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
////          GPIOC->MODER |= 3 << ((pin - 9) * 2);
////        }
////      } else
////      {
////        ADC1->SQR1 |= pin << (order * 5);
////        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
////        GPIOC->MODER |= 3 << ((pin - 9) * 2);
////      }
////      order++;
////    }
//  }
//  ADC->CCR |= ADC_CCR_ADCPRE;
//  //ADC Config
//  ADC1->CR1 |= ADC_CR1_SCAN;
//  ADC1->CR2 |= ADC_CR2_DMA | ADC_CR2_DDS | ADC_CR2_CONT;
//  ADC1->SQR1 |= (size - 1) << 20;
//  //Enable ADC conversion
//  ADC1->CR2 |= ADC_CR2_ADON;
//  ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint16_t analogRead(uint16_t ch)
{
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
  uint16_t var = 0;
//  if (ch < 7)
//  {
//    GPIOA->MODER |= (3 << (ch * 2));
//  } else if (ch == 8 || ch == 9)
//  {
//    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
//    GPIOB->MODER |= 3 << ((ch - 8) * 2);
//  } else
//  {
//    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
//    GPIOC->MODER |= 3 << ((ch - 9) * 2);
//  }
//
//  ADC1->SMPR2 = ADC_SMPR2_SMP0_0;
//  ADC1->SQR3 = ch;
//  ADC1->CR2 = ADC_CR2_ADON;
//  ADC1->CR2 |= ADC_CR2_SWSTART; //Start the conversion
//  while (!(ADC1->SR & ADC_SR_EOC))
//    ; //Processing the conversion
//
//  var = ADC1->DR & 0x0fff;
//  RCC->APB2ENR &= ~RCC_APB2ENR_ADC1EN;
//  ADC1->CR2 = ADC1->SMPR2 = 0x00;

  return var; //Return the converted var
}


