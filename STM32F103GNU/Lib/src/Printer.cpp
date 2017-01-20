/*
 * Printer.cpp
 *
 *  Created on: Jun 30, 2016
 *      Author: RoyerAriel
 */

#include "Printer.h"

void Printer::print(char ch)
{
  WriteByte(ch);
}

void Printer::print(uint8_t ch, uint8_t base)
{
  print(int32_t(ch), base);
}
void Printer::print(int var, uint8_t base)
{
  print((int32_t) var, base);
}

void Printer::print(double var)
{
  char str[12];
  floatToStr(var, str);
  print(str);
}

void Printer::print(int32_t var, uint8_t base)
{
  char str[12];
  ConverToStr(var, str, base);
  print(str);
}
void Printer::print(uint32_t var, uint8_t base)
{
  char str[12];
  ConverToStr(var, str, base);
  print(str);
}

void Printer::print(const char *str)
{
  while (*str != 0)
  {
    print(*str);
    str++;
  }

}

void Printer::print(const char *str1, char var)
{
  print(str1);
  WriteByte(var);
}

void Printer::print(const char *str1, int var, uint8_t base)
{
  print(str1, (int32_t) var, base);
}

void Printer::print(const char *str1, int32_t var, uint8_t base)
{
  print(str1);
  print(var, base);
}
void Printer::print(const char *str1, uint32_t var, uint8_t base)
{
  print(str1);
  print(var, base);
}
void Printer::print(const char *str1, double var)
{
  print(str1);
  print(var);
}
