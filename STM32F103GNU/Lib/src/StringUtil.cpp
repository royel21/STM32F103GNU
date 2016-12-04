/*
 * StringUtil.cpp
 *
 *  Created on: Jun 22, 2016
 *      Author: RoyerAriel
 */

#include "StringUtil.h"

static uint8_t decToStr(int32_t var, char buff[], uint8_t i)
{
	do
	{
		buff[i++] = (char) (var % 10) + '0'; //integer to ANSI
		var /= 10;
	} while (var);
	return i;
}

void ConverToStr(int32_t var, char *str, uint8_t base)
{
  if (var == 0)
  {
    *str++ = '0';
    *str = 0;
    return;
  }
	char numb[12];
	uint8_t i = 0, temp;

	if (base == 10)
	{
		if (var < 0)
		{
			*str++ = '-';
			var *= -1;
		}
		i = decToStr(var, numb, 0);
	} else

	if (base == 16)
	{
		while (var != 0)
		{
			temp = var % 16;
			if (temp < 10)
				temp = temp + 48;
			else
				temp = temp + 55;
			numb[i++] = temp;
			var = var / 16;
		}
	} else

	if (base == 2)
	{
		s32 x;
		if (var <= 0xff)
		{
			x = 0x80;
		} else
		{
			x = 0x8000;
		}
		for (; x > 0; x >>= 1)
		{
			*str++ = (var & x) ? '1' : '0';
		}
		*str = '\0';
		return;
	}

	while (i--)
	{
		*str++ = numb[i];
	}
	*str = '\0';
}

void floatToStr(double floating, char *str)
{
	char numb[16];
	uint8_t i = 0;
	floating += 0.0005;
	if (floating < 0)
	{
		*str++ = '-';
		floating *= -1;
	}

	int integer = (int) floating;
	int dec = (int) ((floating - integer) * 1000);

	if (dec > 0)
	{
		i = decToStr(dec, numb, i);

		if (dec < 100)
			numb[i++] = '0';
		if (dec < 10)
			numb[i++] = '0';
		numb[i++] = '.';
	} else
	{
		numb[i++] = '0';
		numb[i++] = '.';
	}
	i = decToStr(integer, numb, i);

	while (i--)
	{
		*str++ = numb[i];
	}
	*str = '\0';
}
