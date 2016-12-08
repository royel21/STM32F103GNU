/*
 * DS3231.cpp
 *
 *  Created on: Sep 13, 2016
 *      Author: RoyerAriel
 */

#include "DS_RTC.h"

DS_RTC::DS_RTC(uint8_t addr)
{
  rtc_addr = addr;
  I2CCom.init();
}

uint8_t DS_RTC::bcdToDEC(uint8_t val)
{
	return ((val / 16) * 10) + (val % 16);
}

uint8_t DS_RTC::decToBCD(uint8_t val)
{
	return ((val / 10) * 16) + (val % 10);
}

void DS_RTC::setTime(uint8_t *time)
{
	I2CCom.Start(rtc_addr, I2C_WR);
	I2CCom.Write(0x00);
	uint8_t size = 7;
	while (size)
	{
		I2CCom.Write(decToBCD(*time));
		time++;
		size--;
	}
	I2CCom.Stop();
}

void DS_RTC::getTime(uint8_t *time)
{
	I2CCom.ReadMultiReg(rtc_addr, 0x00, time, 7);
	for(int i = 0; i < 7;i++)
	{
		time[i] = bcdToDEC(time[i]);
	}
}

