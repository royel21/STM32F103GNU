
#include "Timer.h"
#include "SerialHardware.h"
#include "LCDI2C.h"
#include "I2CCOM.h"

int main(void)
{
//  spi.setBidiMode(SPI_TRANSMIT);
  Serial2.Init(115200);
	LCD_I2C lcd(0x27);
	lcd.Init();

  short b = -9000;
	while (1)
	{
    lcd.print("test1", b++);

//		GPIOB->BSRR |= P05 | P04 | P03;
//
//		delayMillis(1);
//		GPIOB->BRR |= P05 | P04 | P03;
//		delayMillis(1);
//		matrix.write(15, 0xAA);


	}
	return 0;
}

