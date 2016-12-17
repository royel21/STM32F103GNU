/*
 * SerialHardware.cpp
 *
 *  Created on: Jun 8, 2016
 *      Author: RoyerAriel
 */

#include "SerialHardware.h"
#include "misc.h"
int i = 0;
SerialHardware::SerialHardware(USART_TypeDef *usart)
{
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
  IRQn_Type it = USART2_IRQn;
#ifdef USE_USART1
  if (usart == USART1)
  {
    usartClock = SystemCoreClock / 4;
    USARTx = USART1;
    it = USART1_IRQn;
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRH &= 0xFFFFF00F;
    GPIOA->CRH |= (MODE_OUT_50MHZ | CNF_OUT_AFPP ) | ((MODE_IN | CNF_IN_FLOAT ) << 1 * 4);
  }
#endif

#ifdef USE_USART2
  if (usart == USART2)
  {
    USARTx = USART2;
    it = USART2_IRQn;
    usartClock = SystemCoreClock / 2;

    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    GPIOA->CRL &= 0xFFFF00FF;
    GPIOA->CRL |= ((MODE_OUT_50MHZ | CNF_OUT_AFPP ) << 2 * 4) | ((MODE_IN | CNF_IN_FLOAT ) << 3 * 4);
  }
#endif

#ifdef USE_USART3
  if (usart == USART3)
  {
    usartClock = SystemCoreClock / 2;
    USARTx = USART3;
    it = USART3_IRQn;
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
		GPIOB->CRH &= 0xFFFF00FF;
		GPIOB->CRH |= ((MODE_OUT_50MHZ | CNF_OUT_AFPP ) << 2 * 4)
				| ((MODE_IN | CNF_IN_FLOAT ) << 3 * 4);
  }
#endif

  USARTx->CR1 |= USART_CR1_RXNEIE;
  InterruptEnabler(it, 0, 0);
}

void SerialHardware::setEndCode(char code)
{
  endCode = code;
}

void SerialHardware::Init(uint32_t brr)
{
  USARTx->CR1 |= USART_CR1_TE | USART_CR1_RE;
  uint32_t tmpBRR = 0;
  uint32_t intDV = 0;
  uint32_t fracDV = 0;
  /* Integer part computing in case Oversampling mode is 16 Samples */
  intDV = ((25 * usartClock) / (4 * brr));
  //* Determine the integer part */ (4 * (brr)))
  tmpBRR = (intDV / 100) << 4;
  /* Determine the fractional part */
  fracDV = intDV - (100 * (tmpBRR >> 4));

  tmpBRR |= ((((fracDV * 16) + 50) / 100)) & ((uint8_t) 0x0F);
//
  USARTx->BRR = tmpBRR;
  USARTx->CR1 |= USART_CR1_UE; // USART ENABLE
}

void SerialHardware::WriteByte(const char byte)
{
  while (!(USARTx->SR & USART_SR_TXE))
    ;
  USARTx->DR = byte;
}

char SerialHardware::readByte()
{
  if (tail == head)
    return -1;

  tail = (tail + 1) % BUFFSIZE;
  return buff[tail];
}

void SerialHardware::receiveByteIT()
{
  uint8_t ch = (USARTx->DR & 0xFF);
  uint8_t next = (head + 1) % BUFFSIZE;
  if (next != tail)
  {
    buff[next] = ch;
    head = next;
  }
}
void SerialHardware::println(char var)
{
  WriteByte(var);
  WriteByte('\n');
}

void SerialHardware::println(int var, uint8_t base)
{
  println((int32_t) var, base);
}

void SerialHardware::println(int32_t var, uint8_t base)
{
  print(var, base);
  WriteByte('\n');
}

void SerialHardware::println(uint32_t var, uint8_t base)
{
  print(var, base);
  WriteByte('\n');
}

void SerialHardware::println(double var)
{
  print(var);
  WriteByte('\n');
}

void SerialHardware::println(const char *str)
{
  print(str);
  WriteByte('\n');
}
void SerialHardware::println(const char *str, int var, uint8_t base)
{
  println(str, (int32_t) var, base);
}

void SerialHardware::println(const char *str, int32_t var, uint8_t base)
{
  print(str);
  print(var, base);
  WriteByte('\n');
}

void SerialHardware::println(const char *str, uint32_t var, uint8_t base)
{
  print(str);
  print(var, base);
  WriteByte('\n');
}

void SerialHardware::println(const char *str, double var)
{
  print(str);
  print(var);
  WriteByte('\n');
}

#ifdef USE_USART1
SerialHardware Serial1(USART1);
extern "C" void USART1_IRQHandler()
{
  if (USART1->SR & USART_SR_RXNE)
  {
    Serial1.receiveByteIT();
  }
}
#endif

#ifdef USE_USART2
SerialHardware Serial2(USART2);
extern "C" void USART2_IRQHandler()
{
  if (USART2->SR & USART_SR_RXNE)
  {
    Serial2.receiveByteIT();
  }
}
#endif

#ifdef USE_USART3
SerialHardware Serial3(USART3);
extern "C" void USART3_IRQHandler()
{
  if (USART3->SR & USART_SR_RXNE)
  {
    Serial3.receiveByteIT();
  }
}
#endif

