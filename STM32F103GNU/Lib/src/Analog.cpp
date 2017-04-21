/*
 * Analog.cpp
 *
 *  Created on: Nov 11, 2016
 *      Author: RoyerAriel
 */
#include "Analog.h"
#include "Util.h"
/********************  Bits definition for DMA_SxCR register  *****************/
#define DMA_CCR_PL_VH                       ((uint16_t)0x0003000)
#define DMA_CCR_PL_M                        ((uint16_t)0x0001000)
#define DMA_CCR_PL_H                        ((uint16_t)0x0002000)
#define DMA_CCR_MSIZE_8bit                  ((uint16_t)0x0000000)
#define DMA_CCR_MSIZE_16bit                 ((uint16_t)0x0000400)
#define DMA_CCR_MSIZE_32bit                 ((uint16_t)0x0000800)
#define DMA_CCR_PSIZE_8bit                  ((uint16_t)0x0000000)
#define DMA_CCR_PSIZE_16bit                 ((uint16_t)0x0000100)
#define DMA_CCR_PSIZE_32bit                 ((uint16_t)0x0000200)
#define DMA_CCR_DIR_P2M                     ((uint16_t)0x0000000)
#define DMA_CCR_DIR_M2P                     ((uint16_t)0x0000040)
#define DMA_CCR_DIR_M2M                     ((uint16_t)0x0000080)

ADC::ADC(ADC_TypeDef *ADC)
{
  adc = ADC;
  RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
  adc->CR2 |= ADC_CR2_ADON;
  uint32_t temp = (RCC->CFGR & 0xFFFF3FFF);
  temp |= RCC_CFGR_ADCPRE_DIV6;
  RCC->CFGR = temp;
  //Reset all ADC calibration register and wait to finish
  ADC->CR2 |= ADC_CR2_RSTCAL;
  while (ADC->CR2 & ADC_CR2_RSTCAL)
    ;
  //start ADC calibration and wait to finish
  ADC->CR2 |= ADC_CR2_CAL;
  while (ADC->CR2 & ADC_CR2_CAL)
    ;
}

void ADC::powerOn(uint8_t on)
{
  on ? adc->CR2 |= ADC_CR2_ADON : adc->CR2 &= ~ADC_CR2_ADON;
}

void ADC::setMultiChMode()
{
    //Set DMA
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;
    DMA1_Channel1->CCR |= DMA_CCR1_CIRC | DMA_CCR1_MINC |
    DMA_CCR_PSIZE_16bit | DMA_CCR1_MSIZE_0 | DMA_CCR_PL_VH;
    DMA1_Channel1->CMAR = (uint32_t) &data;
    DMA1_Channel1->CPAR = (uint32_t) &adc->DR;
    //set ADC DMA MODE
    adc->CR1 |= ADC_CR1_SCAN;
    adc->CR2 |= ADC_CR2_CONT;
    adc->CR2 |= ADC_CR2_DMA;
}

void ADC::setChannel(uint8_t ch, uint8_t cycles)
{
  if (ch < 8)
  {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    adc->SQR3 &= ~(ch << (size * 5));
    adc->SQR3 |= ch << (size * 5);
    GPIOA->CRL &= ~(0xF << (ch * 4));
  } else if (ch > 5 && ch < 12)
  {
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    adc->SQR2 &= ~(ch << (size * 5));
    adc->SQR2 |= ch << (size * 5);
    GPIOB->CRL &= ~(0xF << ((ch - 8) * 4));
  }
  adc->SMPR2 &= ~(cycles << (ch * 3));
  adc->SMPR2 |= cycles << (ch * 3);
  if (adc->CR2 & ADC_CR2_CONT)
  size++;
}

void ADC::startMultiCh()
{
  DMA1_Channel1->CNDTR = size;
  DMA1_Channel1->CCR |= DMA_CCR1_EN;
  adc->SQR1 = (size - 1) << 20;
  adc->CR2 |= ADC_CR2_ADON;
  adc->CR2 |= ADC_CR2_SWSTART;
}

uint16_t ADC::getData(uint8_t n)
{
  return data[n];
}

uint16_t ADC::read(uint8_t ch)
{
    setChannel(ch);
    adc->CR2 |= ADC_CR2_ADON;
    adc->CR2 |= ADC_CR2_SWSTART;
    while (!(adc->SR & ADC_SR_EOC))
      ;
      return adc->DR & 0xFFF;
}

