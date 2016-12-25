#include "Timer.h"
#include "SerialHardware.h"
#include "util.h"

int main(void)
{
  Serial2.Init(115200);
  GPIO_Config(GPIOB, P12 | P13, MODE_OUT_50MHZ, CNF_OUT_PP);
  while (1)
  {
    // GPIOB->BRR |= P12 | P13;
    //delayMicros(1);
    //GPIOB->BSRR |= P12 | P13;
    //long start = micros();
    //micros();
    Serial2.println(millis());
    //delayMicros(1);
  }
  return 0;
}

