/*
 * Analog.h
 *
 *  Created on: Nov 11, 2016
 *      Author: RoyerAriel
 */

#ifndef ANALOG_H_
#define ANALOG_H_

#include "cmsis_device.h"
#include "define.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ADC_CH0                                 ((uint8_t)0x00)
#define ADC_CH1                                 ((uint8_t)0x01)
#define ADC_CH2                                 ((uint8_t)0x02)
#define ADC_CH3                                 ((uint8_t)0x03)
#define ADC_CH4                                 ((uint8_t)0x04)
#define ADC_CH5                                 ((uint8_t)0x05)
#define ADC_CH6                                 ((uint8_t)0x06)
#define ADC_CH7                                 ((uint8_t)0x07)
#define ADC_CH8                                 ((uint8_t)0x08)
#define ADC_CH9                                 ((uint8_t)0x09)

#define ADC_C1_5                                ((uint8_t)0x00)
#define ADC_C7_5                                ((uint8_t)0x01)
#define ADC_C13_5                               ((uint8_t)0x02)
#define ADC_C28_5                               ((uint8_t)0x03)
#define ADC_C41_5                               ((uint8_t)0x04)
#define ADC_C55_5                               ((uint8_t)0x05)
#define ADC_C71_5                               ((uint8_t)0x06)
#define ADC_C239_5                              ((uint8_t)0x07)


class ADC
{
  private:
    volatile uint16_t data[9] =
      { };
    uint8_t size = 0;
    ADC_TypeDef *adc;
  public:
    ADC(ADC_TypeDef *ADC);

    void setDMA();

    void powerOn(uint8_t on);

    void setContMode(uint8_t state);

    uint16_t getdata(uint8_t ch);

    void setChannel(uint8_t ch, uint8_t cicles = 0);

    void startConV();
    uint16_t read(uint8_t ch);
};

#ifdef __cplusplus
}
#endif

#endif /* ANALOG_H_ */
