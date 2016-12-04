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
  this->SPIx = spi;
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
  if (spi == SPI1)
  {
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
    if (remap)
    {
      GPIO_Config(GPIOB, P13 | P14 | P15, MODE_OUT_50MHZ, CNF_OUT_AFPP);
    } else
    {
      GPIO_Config(GPIOA, P05 | P06 | P07, MODE_OUT_50MHZ, CNF_OUT_AFPP);
    }
  } else if (spi == SPI2)
  {
    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
    GPIO_Config(GPIOB, P13 | P14 | P15, MODE_OUT_50MHZ, CNF_OUT_AFPP);
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

void SPI::softPin(GPIO_TypeDef *port, uint16_t pin)
{
  // GPIO_Config(port, pin, MODE_OUT, PULL_UP);
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

void SPI::start(uint8_t bidi, uint8_t brr)
{
//	//SPIx->CR1 |= (br << 3) | SPI_CR1_DFF;
//	SPIx->CR1 |= (brr < 3) | SPI_CR1_SSM | SPI_CR1_SSI;
//	SPIx->CR1 |= SPI_CR1_MSTR | SPI_CR1_SPE;
  if (bidi)
  {
    SPIx->CR1 |= SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE;
  }
  SPIx->CR1 |= SPI_CR1_SSM | SPI_CR1_SSI | (brr << 3) | SPI_CR1_MSTR | SPI_CR1_DFF;
  SPIx->CR1 |= SPI_CR1_SPE;
}

uint8_t SPI::send8Byte(uint8_t Byte)
{

  SPIx->DR = Byte;
  while ((SPIx->SR & SPI_SR_TXE) == RESET)
    ;
  while ((SPIx->SR & SPI_SR_RXNE) == RESET)
    ;
  return SPIx->DR & 0xFF;
}

uint16_t SPI::send16Byte(uint16_t word)
{

  ;
  SPIx->DR = word;
  while ((SPIx->SR & SPI_SR_TXE) == RESET)
    if (!(SPIx->CR1 & SPI_CR1_BIDIMODE))
      while ((SPIx->SR & SPI_SR_RXNE) == RESET)
        ;
  return SPIx->DR & 0xFFFF;
}
