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

/*ADC class read pin from GPIOA pin 0..7 and GPIOB pin 0,1
 * are channel 0...9 this class can be use with or without DMA
 * for use without DMA use read(ch) with the specific channel
 * for to use dma
 * first   set up multi-channel mode
 * second  set the channel
 * third   start the conversion
 * four    get the data converted with getData(n) n = order 0 to last set up channel
 */
class ADC
{
  private:
    volatile uint16_t data[9] =
      { };
    uint8_t size = 0;
    ADC_TypeDef *adc;
  public:
    ADC(ADC_TypeDef *ADC);
    //power on or off ADC peripheral
    void powerOn(uint8_t on);
    // set scan and continuous mode for dma
    void setMultiChMode();
    //get the data in multi-channel mode
    uint16_t getData(uint8_t n);
    /*set the channel to be read by DMA
     * ch channel to use from 0..9
     * cycles by default 1.5 adc cycles
     */
    void setChannel(uint8_t ch, uint8_t cycles = 0);
    //start the conversion of for DMA mode
    void startMultiCh();
    /*read individual channel without DMA
     * by the fault 1.5 cycles
     */
    uint16_t read(uint8_t ch);
};

#ifdef __cplusplus
}
#endif

#endif /* ANALOG_H_ */
