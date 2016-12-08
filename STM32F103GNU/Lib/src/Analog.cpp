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
	DMA1_Channel1->CCR |= DMA_CCR1_CIRC | DMA_CCR1_MINC |
	DMA_CCR_PSIZE_16bit | DMA_CCR1_MSIZE_0 | DMA_CCR_PL_VH;

	DMA1_Channel1->CMAR = (uint32_t) &vars[0];

	DMA1_Channel1->CPAR = (uint32_t) &ADC1->DR;

	DMA1_Channel1->CNDTR = size;

	DMA1_Channel1->CCR |= DMA_CCR1_EN;

	InterruptEnabler(DMA1_Channel1_IRQn, 0, 0);

	int8_t order = 0;
	for (uint8_t pin = 0; pin < 16; pin++)
	{
		if ((pins & (1 << pin)))
		{
			if (pin < 8)
			{
				ADC1->SQR3 |= pin << (order * 5);
				GPIOA->CRL &= ~(0xF << (pin * 4));
			} else if (pin > 5 && pin < 12)
			{
				ADC1->SQR2 |= pin << (order * 5);
				GPIOB->CRL &= ~(0xF << ((pin - 8) * 4));
			}
			order++;
		}
	}
	//ADC Config
	ADC1->CR1 |= ADC_CR1_SCAN;
	//ADC1->CR2 |= ADC_CR2_DMA | ADC_CR2_DDS | ADC_CR2_CONT;
	ADC1->SQR1 |= (size - 1) << 20;
	//Enable ADC conversion
	ADC1->CR2 |= ADC_CR2_ADON;
	ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint16_t analogRead(uint16_t ch)
{
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	uint16_t var = 0;
	if (ch < 8)
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		uint32_t temp = GPIOA->CRL;
		temp &= ~(0x0F << (ch * 4));
		GPIOA->CRL = temp;
	} else
	{
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
		uint32_t temp = GPIOB->CRL;
		temp &= ~(0x0F << (ch - 8) * 4);
		GPIOB->CRL = temp;
	}

	ADC1->SMPR2 = ADC_SMPR2_SMP0_0;
	ADC1->SQR3 = ch;
	ADC1->CR2 = ADC_CR2_ADON;
	ADC1->CR2 |= ADC_CR2_SWSTART; //Start the conversion
	while (!(ADC1->SR & ADC_SR_EOC))
	;//Processing the conversion

	var = ADC1->DR & 0x0fff;
	RCC->APB2ENR &= ~RCC_APB2ENR_ADC1EN;
	ADC1->CR2 = ADC1->SMPR2 = 0x00;

	return var;//Return the converted var
}

