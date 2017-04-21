#include "SysTimer.h"
#include "SerialHardware.h"
//#include "util.h"

//uint32_t count = 0;
int main(void)
{
  Serial2.Init(115200);
//  //EXTI_Configuration(GPIOB, P10 | P11 | P12 | P13, EXTI_TRG_CHANGE);
  GPIO_Config(GPIOC, P13, MODE_OUT_50MHZ, CNF_OUT_PP);
  //uint32_t lng = 4000000000;
  while (1)
  {
    long start = micros();
    delayMicros(100000);
    Serial2.println(micros() - start);
    if (GPIOC->IDR & P13)
    {
      GPIOC->BSRR = P13;
    } else

      GPIOC->BRR = P13;

  }
  return 0;
}

