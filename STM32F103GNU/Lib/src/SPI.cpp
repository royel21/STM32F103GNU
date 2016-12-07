/*
 * SPI.cpp
 *
 *  Created on: Sep 21, 2016
 *      Author: RoyerAriel
 */

#include "SPI.h"

SPI::SPI(SPI_TypeDef *spi, uint8_t remap)
{
	PORT = 0;
	PIN = 0;

	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	if (spi == SPI1)
	{
		RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
		this->SPIx = SPI1;
		if (remap)
		{
			AFIO->MAPR |= AFIO_MAPR_SPI1_REMAP;
			GPIO_Config(GPIOB, P03 | P04 | P05, MODE_OUT_50MHZ, CNF_OUT_AFPP);
		} else
		{
			GPIO_Config(GPIOA, P05 | P06 | P07, MODE_OUT_50MHZ, CNF_OUT_AFPP);
		}
	} else if (spi == SPI2)
	{
		this->SPIx = SPI2;
		RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
		GPIO_Config(GPIOB, P13 | P14 | P15, MODE_OUT_50MHZ, CNF_OUT_AFPP);
	}
	SPIx->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_MSTR;
	SPIx->CR1 |= SPI_CR1_SPE;
}

void SPI::setBaudRateControl(uint8_t brc)
{
	SPIx->CR1 &= ~(7 << 3);
	SPIx->CR1 |= (brc << 3);
}

void SPI::setBidi(uint8_t enable, uint8_t dir)
{
	if (enable)
	{
		SPIx->CR1 |= SPI_CR1_BIDIMODE;                                   // set bidirectional enable
		dir ? SPIx->CR1 |= SPI_CR1_BIDIOE : SPIx->CR1 &= ~SPI_CR1_BIDIOE; // if dir = 1 transmit only else receive only
	} else
	{
		SPIx->CR1 &= ~(SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE);
	}
}

void SPI::setCPHA(uint8_t cpha)
{
	cpha ? SPIx->CR1 |= SPI_CR1_SPE | SPI_CR1_CPHA : SPIx->CR1 &= ~SPI_CR1_CPHA;
}

void SPI::setCPOL(uint8_t cpol)
{
	cpol ? SPIx->CR1 |= SPI_CR1_CPOL : SPIx->CR1 &= ~SPI_CR1_CPOL;
}

void SPI::setDataF(uint8_t dataf)
{
	dataf ? SPIx->CR1 |= SPI_CR1_DFF : SPIx->CR1 &= ~SPI_CR1_DFF;
}

void SPI::setCSPin(GPIO_TypeDef *port, uint16_t pin)
{
	GPIO_Config(port, pin, MODE_OUT_50MHZ, CNF_OUT_PP);
	PORT = port;
	PIN = pin;
	port->BSRR |= pin;
}

void SPI::chipSelect(uint8_t ss)
{
#ifdef STM32F4
	ss ? PORT->BSRRL |= PIN : PORT->BSRRH |= PIN;
#endif
#ifdef STM32F1
	ss ? PORT->BSRR |= PIN : PORT->BRR |= PIN;
#endif

}

uint8_t SPI::send8Byte(uint8_t byte)
{
	while (!(SPIx->SR & SPI_SR_TXE))
		;
	SPIx->DR = byte;
	byte = SPIx->DR & 0xFFFF;

	while ((SPIx->SR & SPI_SR_RXNE) == RESET)
		;
	return byte;
}

uint16_t SPI::send16Byte(uint16_t word)
{

	while (!(SPIx->SR & SPI_SR_TXE))
		;
	SPIx->DR = word;
	word = SPIx->DR & 0xFFFF;
	while ((SPIx->SR & SPI_SR_RXNE) == RESET)
		;
	return word;
}
