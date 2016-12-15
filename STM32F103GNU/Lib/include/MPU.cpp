/*
 * MPU.cpp
 *
 *  Created on: Dec 13, 2016
 *      Author: RoyerAriel
 */

#include <MPU.h>

MPU::MPU(I2C_TypeDef *i2c, uint8_t addr)
{
  TWOWIRE = i2c;
  this->addr = addr;

}

void MPU::wakeUp()
{

}
