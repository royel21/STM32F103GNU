/*
 * Util.cpp
 *
 *  Created on: Nov 8, 2016
 *      Author: RoyerAriel
 */
#include "Util.h"
#include "misc.h"
/*Configure the GPIO MODE and CNF + CLOCK
 * 1:GPIO PORT
 * 2:GPIO ORE PINS  EJ PXX | PXX
 * 3:GPIO Mode MODE_XX
 * 4:GPIO CNF
 */

void GPIO_Config(GPIO_TypeDef *port, const uint16_t pins, uint8_t mode, uint8_t cnf)
{

	if (port == GPIOA)
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	else if (port == GPIOB)
		RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	else if (port == GPIOC)
		RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	else if (port == GPIOD)
		RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;

	uint8_t pin = 0x00;
	while (pins >> pin)
	{
		if ((pins & (1 << pin)))
		{
			uint32_t temp = 0;
			if (pin < 8)
			{
				temp = port->CRL;
				temp &= ~(0xF << pin * 4);
				temp |= (uint32_t) ((mode | cnf) << (pin * 4));
				port->CRL = temp;
			} else
			{
				temp = port->CRH;
				temp &= ~(0xF << (pin - 8) * 4);
				temp |= (uint32_t) ((mode | cnf) << (pin - 8) * 4);
				port->CRH = temp;
			}
		}
		pin++;
	}
}

/** Enable the selected interrupt
 * 1:IRQn_Type
 * 2:Priority
 * 3:SubPriority
 */
void InterruptEnabler(IRQn_Type irq, uint16_t priority, uint16_t subPriority)
{
	uint8_t tmppriority = 0x00, tmppre = 0x00, tmpsub = 0x0F;

	/* Compute the Corresponding IRQ Priority --------------------------------*/
	tmppriority = (0x700 - ((SCB->AIRCR) & (uint32_t) 0x700)) >> 0x08;
	tmppre = (0x4 - tmppriority);
	tmpsub = tmpsub >> tmppriority;

	tmppriority = priority << tmppre;
	tmppriority |= (uint8_t) (subPriority & tmpsub);

	tmppriority = tmppriority << 0x04;

	NVIC->IP[irq] = tmppriority;

	/* Enable the Selected IRQ Channels --------------------------------------*/
	NVIC->ISER[irq >> 0x05] = (uint32_t) 0x01 << (irq & (uint8_t) 0x1F);
}


void EXTI_Configuration(GPIO_TypeDef *port, const uint16_t pins, uint8_t trigger)
{
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
  uint8_t portLine = 0;
  if (port == GPIOA)
  {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  } else if (port == GPIOB)
  {
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    portLine = 1;
  } else if (port == GPIOC)
  {
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    portLine = 2;
  } else if (port == GPIOD)
  {
    portLine = 3;
    RCC->APB2ENR |= RCC_APB2ENR_IOPDEN;
  }

  uint8_t pin = 0x00;
  while (pins >> pin)
  {
    if ((pins & (1 << pin)))
    {
      uint32_t temp = 0;
      if (pin < 8)
      {
        temp = port->CRL;
        temp &= ~(0xF << pin * 4);
        temp |= (uint32_t) ((MODE_IN | CNF_IN_FLOAT ) << (pin * 4));
        port->CRL = temp;
      } else
      {
        temp = port->CRH;
        temp &= ~(0xF << (pin - 8) * 4);
        temp |= (uint32_t) ((MODE_IN | CNF_IN_FLOAT ) << (pin - 8) * 4);
        port->CRH = temp;
      }
      AFIO->EXTICR[pin >> 0x02] &= ~((portLine) << (0x04 * (pin & (uint8_t) 0x03)));
      AFIO->EXTICR[pin >> 0x02] |= (portLine) << (0x04 * (pin & (uint8_t) 0x03));
      switch (pin)
      {
        case 0:
        {
          InterruptEnabler(EXTI0_IRQn);
          break;
        }
        case 1:
        {
          InterruptEnabler(EXTI1_IRQn);
          break;
        }
        case 2:
        {
          InterruptEnabler(EXTI2_IRQn);
          break;
        }
        case 3:
        {
          InterruptEnabler(EXTI3_IRQn);
          break;
        }
        case 4:
        {
          InterruptEnabler(EXTI4_IRQn);
          break;
        }
        case 5 ... 9:
        {
          InterruptEnabler(EXTI9_5_IRQn);
          break;
        }
        case 10 ... 15:
        {
          InterruptEnabler(EXTI15_10_IRQn);
          break;
        }
      }
    }

    pin++;
  }
  EXTI->PR = EXTI_Line12;
  //GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource12);
  EXTI->IMR &= ~pins;
  EXTI->FTSR &= ~pins;
  EXTI->RTSR &= ~pins;

  EXTI->IMR |= pins;
  EXTI->RTSR |= pins;
  EXTI->FTSR |= pins;
  if (trigger == EXTI_TRG_FALLING)
  {
    EXTI->FTSR |= pins;
  } else if (trigger == EXTI_TRG_RISING)
  {
    EXTI->RTSR |= pins;
  } else
  {
    EXTI->RTSR |= pins;
    EXTI->FTSR |= pins;
  }

  //clear pending interrupt flag

}
