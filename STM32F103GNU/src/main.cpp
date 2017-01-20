//#include <SysTimer.h>
//#include "SerialHardware.h"
//#include "util.h"
//
//volatile int32_t startOne;
//volatile int32_t pulseOne;
//
//volatile int32_t startTwo;
//volatile int32_t pulseTwo;
//
//volatile int32_t startThree;
//volatile int32_t pulseThree;
//
//volatile int32_t startFour;
//volatile int32_t pulseFour;
////
////
//extern "C" void EXTI15_10_IRQHandler(void)
//{
//  uint32_t us = 0; //micros();
//  if (EXTI->PR & EXTI_PR_PR12)
//  {
//    if (GPIOB->IDR & P12)
//    {
//      startOne = us;
//    } else
//    {
//      pulseOne = us - startOne;
//    }
//    EXTI->PR = EXTI_PR_PR12;
//  }
//
//  else if (EXTI->PR & EXTI_PR_PR13)
//  {
//    if (GPIOB->IDR & P13)
//    {
//      startTwo = us;
//    } else
//    {
//      pulseTwo = us - startTwo;
//    }
//    EXTI->PR = EXTI_PR_PR13;
//  }
//
//  else if (EXTI->PR & EXTI_PR_PR10)
//  {
//    if (GPIOB->IDR & P10)
//    {
//      startThree = us;
//    } else
//    {
//      pulseThree = us - startThree;
//    }
//    EXTI->PR = EXTI_PR_PR10;
//  }
//
//  else if (EXTI->PR & EXTI_PR_PR11)
//  {
//    if (GPIOB->IDR & P11)
//    {
//      startFour = us;
//    } else
//    {
//      pulseFour = us - startFour;
//    }
//    EXTI->PR = EXTI_PR_PR11;
//  }
//  //Serial2.println(micros() - us);
//}

//uint32_t count = 0;
int main(void)
{
//  Serial2.Init(921600);
//  //EXTI_Configuration(GPIOB, P10 | P11 | P12 | P13, EXTI_TRG_CHANGE);
//  GPIO_Config(GPIOC, P13, MODE_OUT_50MHZ, CNF_OUT_PP);
  //uint32_t lng = 4000000000;
  while (1)
  {
    // long start = micros();
    // delayMicros(250000);
    //Serial2.println(micros() - start);
//    Serial2.print("A:", pulseOne);
//    Serial2.print(" B:", pulseTwo);
//    Serial2.print(" C:", pulseThree);
//    Serial2.println(" D:", pulseFour);
//    delayMillis(4);

//Serial2.println("ADD:0x", I2CCom.Scan(0x69), HEX);
    // delayMicros(10000);
//    Serial2.println(t_millis());
    // t_delayMillis(1000);
    //delayMillis(50);
    // GPIOB->BRR |= P12 | P13;
    //delayMicros(1);
    //GPIOB->BSRR |= P12 | P13;
//    long start = micros();
//    delayMicros(10000);
//    Serial2.println(micros() - start);
    //delayMicros(1);
  }
  return 0;
}

