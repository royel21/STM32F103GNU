#include <I2CCOM.h>
#include "SPI.h"
#include "MAX7219.h"
#include "Timer.h"
#include "SerialHardware.h"
#include "LCDI2C.h"
#include "I2CCOM.h"
uint8_t max[] =
{ 0x18, 0x3C, 0x7E, 0xDB, 0xFF, 0x24, 0x5A, 0xA5 };

const uint8_t max3[] =
{ 0x18, 0x3C, 0x7E, 0x7E, 0x3C, 0x18, 0xFF, 0xFF };

int main(void)
{
	SPI spi(SPI2);
	MAX7219 matrix(&spi, GPIOB, P12);
//  spi.setBidiMode(SPI_TRANSMIT);
	Serial2.Init(921600);
	LCD_I2C lcd(0x27);
	lcd.Init();
	lcd.print("test1");
//  MAX7219 matrix(&spi);
//  spi.slaveSelect(LOW);
//  spi.send16Byte(0x0B07);
//  spi.slaveSelect(HIGH);
//
//  delayMillis(100);
//
//  Serial2.println("BrightLow:");
//
//  spi.slaveSelect(LOW);
//  spi.send16Byte(0x0A0F);
//  spi.slaveSelect(HIGH);
//
//  Serial2.println("on:");
//
//  spi.slaveSelect(LOW);
//  spi.send16Byte(0x0C01);
//  spi.slaveSelect(HIGH);
//
//  delayMillis(100);
//
//  uint8_t data[] =
//  { 0, 0, 0, 0, 0, 0, 0, 0 };
//  matrix.writeData(data);
//  matrix.setDisplayON(ON);
//  matrix.setScanDigit(8);
//  matrix.setBrightness(15);
//  delayMillis(1000);

//  for (int i = 0; i < 8; i++)
//  {
//
//    //matrix.write(A0F);
//    //matrix.write(B07);
//
//    matrix.write(B07);
//    delayMillis(250);
//    matrix.write(C01);
//    sendData(max2[i]);
//    //delayMicros(20);
//  }
//
//  for (int i = 0; i < 8; i++)
//  {
//
//    //matrix.write(A0F);
//    //matrix.write(B07);
//    matrix.write(B07);
//    matrix.write(C01);
//    sendData(max[i]);
//    delayMillis(250);
//  }
//	GPIO_Config(GPIOB, P05 | P04 | P03, MODE_OUT_50MHZ, CNF_OUT_PP);
	uint8_t bright = 8;
	I2CCom.init();
	while (1)
	{
		Serial2.println("ADDR:", I2CCom.Scan(), HEX);
		delayMillis(100);
//		GPIOB->BSRR |= P05 | P04 | P03;
//
//		delayMillis(1);
//		GPIOB->BRR |= P05 | P04 | P03;
//		delayMillis(1);
//		matrix.write(15, 0xAA);

		if (Serial2.hasData())
		{
			char ch = Serial2.readByte();
			switch (ch)
			{
				case 'a':
				{
					Serial2.print("ALLON:");
					matrix.testAllDigit(ON);
					break;
				}
				case 'b':
				{
					Serial2.print("ALLOFF:");
					matrix.testAllDigit(OFF);
					break;
				}
				case 'c':
				{
					Serial2.print("Mask1:");
					matrix.writeData(max);

					break;
				}
				case 'd':
				{
					Serial2.print("BrightHigh:");
					matrix.setBrightness(bright);
					break;
				}
				case 'e':
				{
					Serial2.print("Scan8Digit:");
					matrix.setScanDigit(7);
					break;
				}
				case 'f':
				{
					Serial2.print("on:");
					matrix.setDisplayON(ON);
					break;
				}

				case '0':
				{
					Serial2.print("clear");
					matrix.clearALL();
					break;
				}
				case '1':
				{
					matrix.write(1, 0x18);
					break;
				}
				case '2':
				{
					matrix.write(2, 0x3C);
					break;
				}
				case '3':
				{
					matrix.write(3, 0x7E);
					break;
				}
				case '4':
				{
					matrix.write(4, 0x7E);
					break;
				}
				case '5':
				{
					matrix.write(5, 0x3C);
					break;
				}
				case '6':
				{
					matrix.write(6, 0x18);
					break;
				}
				case '7':
				{
					matrix.write(7, 0xFF);
					break;
				}
				case '8':
				{
					matrix.write(8, 0xFF);
					break;
				}
				case '9':
				{
					matrix.writeData(max3);
					break;
				}
				case '+':
				{
					matrix.setBrightness(++bright);
					break;
				}
				case '-':
				{
					matrix.setBrightness(--bright);

					break;
				}
			}
			Serial2.WriteByte(ch);
			Serial2.WriteByte('\n');

		}
	}
	return 0;
}

