/*
 * MAX7219.cpp
 *
 *  Created on: Nov 30, 2016
 *      Author: RoyerAriel
 */

#include "MAX7219.h"

#define NO_OP         (uint8_t)0x00
#define DECODEM       (uint8_t)0x09
#define INTENSITY     (uint8_t)0x0A
#define SCANLIMIT     (uint8_t)0x0B
#define SHUTDOWN      (uint8_t)0x0C
#define DISPLAYTEST   (uint8_t)0x0F
/*
 * spi SPI class Object
 * port GPIO port
 * pin pin for chip select
 *initialize spi with
 */
MAX7219::MAX7219(SPI *spi, GPIO_TypeDef *port, uint16_t pin)
{
	this->SPIx = spi;
	spi->setCSPin(port, pin);
#ifdef STM32F4
	spi->setBaudRateControl(SPI_DIV16);

#endif
#ifdef STM32F1
	spi->setBaudRateControl(SPI_DIV8);
#endif
	spi->setDataF(SPI_DATA16);

}

/* Write one 16bit of data
 * addr register address
 * data Data to write
 */
void MAX7219::write(uint8_t addr, uint8_t data)
{
	SPIx->chipSelect(LOW);
	SPIx->send16Byte((addr << 8) | data);
	SPIx->chipSelect(HIGH);
}

/* Write data to the segment from 1 to size
 * addr register address
 * data Data to write
 * Size the count of data. by default is 8
 */
void MAX7219::writeData(const uint8_t *data, uint8_t size)
{
	for (uint8_t i = 0; i < size; i++)
	{
		write(i + 1, data[i]);
	}
}
// set the brightness intensity
void MAX7219::setBrightness(uint8_t b)
{
	if (b > 15 && b < 0)
	write(INTENSITY, b);
}
// set the number of digit to scan
void MAX7219::setScanDigit(uint8_t d)
{
	write(SCANLIMIT, d);
}
// set the all the digit on or off
void MAX7219::setDisplayON(uint8_t state)
{
	write(SHUTDOWN, state);
}
// test all the digit
void MAX7219::testAllDigit(uint8_t state)
{
	write(DISPLAYTEST, state);
}
// turn off or the digit
void MAX7219::clearALL()
{
	for (uint8_t i = 0; i < 8; i++)
	{
		write(i + 1, 0);
	}
}
