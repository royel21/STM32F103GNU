// ----------------------------------------------------------------------------
#include "cmsis_device.h"
#include "define.h"
#include "Timer.h"
#include "util.h"
#include "SerialHardware.h"
#include "SPI.h"

int main()
{

  SPI spi(SPI1);
  spi.start(SPI_BRRDIV8);
  spi.softPin(GPIOB, P04);
  spi.setDataF(SPI_DATA16);

//  GPIO_Config(GPIOB, 0xFFFF, MODE_OUT_50MHZ);
//  GPIOB->BSRR |= 0xFFFF;
//  Serial2.Init(921600);

  while (1)
  {

    spi.chipSelect(LOW);
    spi.send16Byte(0x0F01);
    spi.chipSelect(HIGH);
    delayMillis(500);
    spi.chipSelect(LOW);
    spi.send16Byte(0x0F00);
    spi.chipSelect(HIGH);
    delayMillis(500);
//

//    GPIOB->BRR |= 0xFFFF;
//    delayMillis(500);
//    GPIOB->BSRR |= 0xFFFF;
//    delayMillis(500);
  }

}

