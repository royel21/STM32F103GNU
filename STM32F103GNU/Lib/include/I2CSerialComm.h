/*
 * I2CSerialConm.h
 *
 *  Created on: Jun 18, 2016
 *      Author: Royel
 */

#ifndef I2CSERIALCOMM_H_
#define I2CSERIALCOMM_H_

#include "cmsis_device.h"
#include "define.h"
#include "Util.h"

#define  I2C_SP400K               ((uint32_t)400000)
#define  I2C_SP100K               ((uint32_t)100000)  //I2C Speed 400khz
#define  I2C_WR                   ((uint8_t)0)          /** I2C Write bit **/
#define  I2C_RD                   ((uint8_t)1)          /** I2C Read bit **/

class I2CSerialComm
{
  private:
    uint8_t address;
    I2C_TypeDef *I2Cx;
//    uint16_t SDA;
//    uint16_t CLCK;
//    void pinToggle();
  public:
    I2CSerialComm(I2C_TypeDef *i2c, uint32_t I2C_SPD, uint8_t remap = 0);

    uint8_t I2CScan();

    void setAddress(uint8_t);
    uint8_t Start(uint8_t, uint8_t);

    uint8_t Write(uint8_t);
    void WriteTo(uint8_t, uint8_t);
    void WriteToReg(uint8_t, uint8_t, uint8_t);
    void WriteMultiReg(uint8_t, uint8_t *, uint8_t);
    void WriteMulti(uint8_t, uint8_t *, uint8_t);

    uint8_t ReadData(uint8_t);
    uint8_t ReadFrom(uint8_t, uint8_t);
    void ReadMultiReg(uint8_t, uint8_t, uint8_t *, uint8_t size);

    void Stop();
    void hardReset(void);
};

extern I2CSerialComm I2C1Comm;

#endif /* I2CSERIALCOMM_H_ */
