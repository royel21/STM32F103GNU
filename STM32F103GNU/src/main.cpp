#include "SysTimer.h"
#include "SerialHardware.h"
//#include "util.h"

//uint32_t count = 0;
int main(void)
{
  Serial2.Init(460800);
//  //EXTI_Configuration(GPIOB, P10 | P11 | P12 | P13, EXTI_TRG_CHANGE);
  GPIO_Config(GPIOC, P13, MODE_OUT_50MHZ, CNF_OUT_PP);
  uint32_t lng = 0;
  while (1)
  {
    //long start = millis();
    delayMillis(1);
    Serial2.println("Hundreds of Hundreds of microsecond timer test in Time:",
        lng++);
    if (GPIOC->IDR & P13)
    {
      GPIOC->BSRR = P13;
    } else

      GPIOC->BRR = P13;

  }
  return 0;
}

