#include "Timer.h"
#include "SerialHardware.h"
#include "analog.h"

int main(void)
{
  ADC adc(ADC1);
  Serial2.Init(115200);
  adc.setMultiChMode();
  adc.setChannel(ADC_CH0);
  adc.setChannel(ADC_CH1);
  adc.setChannel(ADC_CH4);

  adc.startMultiCh();
  while (1)
  {
    //adc.startConV();
    Serial2.println("CH0:", adc.getData(0));
    Serial2.println("CH1:", adc.getData(1));
    Serial2.println("CH4:", adc.getData(2));
    //  uint32_t start = micros();

    delayMillis(150);
  }
  return 0;
}

