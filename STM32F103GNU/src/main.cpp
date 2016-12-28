#include "Timer.h"
#include "SerialHardware.h"
#include "util.h"
#include "cmsis_device.h"
#include "I2CCOM.h"

//
volatile int32_t startOne;
volatile int32_t pulseOne;

volatile int32_t startTwo;
volatile int32_t pulseTwo;

volatile int32_t startThree;
volatile int32_t pulseThree;

volatile int32_t startFour;
volatile int32_t pulseFour;

#define EXTI_TRG_CHANGE    (uint8_t)0
#define EXTI_TRG_RISING    (uint8_t)1
#define EXTI_TRG_FALLING   (uint8_t)2

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

extern "C" void EXTI15_10_IRQHandler(void)
{
  uint32_t us = micros();
  if (EXTI->PR & EXTI_PR_PR12)
  {
    if (GPIOB->IDR & P12)
    {
      startOne = us;
    } else
    {
      pulseOne = us - startOne;
    }
    EXTI->PR = EXTI_PR_PR12;
  }

  else if (EXTI->PR & EXTI_PR_PR13)
  {
    if (GPIOB->IDR & P13)
    {
      startTwo = us;
    } else
    {
      pulseTwo = us - startTwo;
    }
    EXTI->PR = EXTI_PR_PR13;
  }

  else if (EXTI->PR & EXTI_PR_PR10)
  {
    if (GPIOB->IDR & P10)
    {
      startThree = us;
    } else
    {
      pulseThree = us - startThree;
    }
    EXTI->PR = EXTI_PR_PR10;
  }

  else if (EXTI->PR & EXTI_PR_PR11)
  {
    if (GPIOB->IDR & P11)
    {
      startFour = us;
    } else
    {
      pulseFour = us - startFour;
    }
    EXTI->PR = EXTI_PR_PR11;
  }
  //Serial2.println(micros() - us);
}

int main(void)
{
  Serial2.Init(115200);
  EXTI_Configuration(GPIOB, P10 | P11 | P12 | P13, EXTI_TRG_CHANGE);
  //GPIO_Config(GPIOB, P12 | P13, MODE_OUT_50MHZ, CNF_OUT_PP);
  // uint32_t lng = 4000000000;
  while (1)
  {

    Serial2.print("A:", pulseOne);
    Serial2.print(" B:", pulseTwo);
    Serial2.print(" C:", pulseThree);
    Serial2.println(" D:", pulseFour);
    //delayMicros(50000);
    //Serial2.println("ADD:0x", I2CCom.Scan(0x69), HEX);
    // delayMicros(10000);
//    Serial2.println(t_millis());
    // t_delayMillis(1000);
    //delayMillis(50);
    // GPIOB->BRR |= P12 | P13;
    //delayMicros(1);
    //GPIOB->BSRR |= P12 | P13;
//    long start = micros();
//    //uint32_t test = lng / 10000;
//    Serial2.println(micros() - start);
    //delayMicros(1);
  }
  return 0;
}

