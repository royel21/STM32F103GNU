//#include "Timer.h"
#include "SerialHardware.h"
//#include "analog.h"
#include "math.h"

int main(void)
{
//  ADC adc(ADC1);
//  adc.setChannel(ADC_CH0);
//  adc.setChannel(ADC_CH1);
//  adc.setChannel(ADC_CH4);
//  adc.startConV();
//  adc.setContMode(ON);
  // adcDMA();
//  adc.setDMA();
  Serial2.Init(115200);
  float t = 16;
  Serial2.println("test", sqrt(t));
  Serial2.println("test", t);
  while (1)
  {
    //  uint32_t start = micros();

    //  delayMillis(150);
  }
  return 0;
}

