/*
 * MPU.h
 *
 *  Created on: Dec 13, 2016
 *      Author: RoyerAriel
 */

#ifndef INCLUDE_MPU_H_
#define INCLUDE_MPU_H_
#include "cmsis_device.h"

//macro definitions

#define MPU_SELF_TEST_X        (uint8_t)0x0D   //
#define MPU_SELF_TEST_Y        (uint8_t)0x0E   //
#define MPU_SELF_TEST_Z        (uint8_t)0x0F   //
#define MPU_SELF_TEST_A        (uint8_t)0x10   //
/*This register configures the external Frame Synchronization
 * (FSYNC) pin sampling and the Digital Low Pass Filter (DLPF)
 * setting for both the gyroscopes and accelerometers.
 */
#define MPU_CONFIG             (uint8_t)0x1A
/*This register is used to trigger gyroscope self-test and configure the gyroscopes’ full scale range.\
 * YG_ST   bit7
 * ZG_ST   bit6
 * XG_ST   bit5
 * FS_SEL  bi3-bit4
 */
#define MPU_GYR_CFG            (uint8_t)0x1B
/*This register is used to trigger accelerometer self-test and configure the accelerometer full scale range.
 * XA_ST     bit7
 * YA_ST     bit6
 * ZA_ST     bit5
 * AFS_SEL   bi3-bit4
 -*/
#define MPU_ACC_CFG            (uint8_t)0x1C
#define MPU_FIFO_EN            (uint8_t)0x26   //
#define MPU_INT_PIN_CFG        (uint8_t)0x37   //
#define MPU_INT_ENABLE         (uint8_t)0x38   //
#define MPU_INT_STATUS         (uint8_t)0x3A   //
#define MPU_ACC_DATA           (uint8_t)0x3B   //
#define MPU_TEMP_DATA          (uint8_t)0x41   //start address of the tempture sensor data
#define MPU_GY_DATA            (uint8_t)0x43   //start address of the gyro data
#define MPU_PWR_MGMT_1         (uint8_t)0x6B   //
#define MPU_PWR_MGMT_2         (uint8_t)0x6C   //
#define MPU_FIFO_COUNTH        (uint8_t)0x72   //
#define MPU_FIFO_COUNTL        (uint8_t)0x73   //
#define MPU_FIFO_R_W           (uint8_t)0x74   //
#define MPU_WHO_AM_I           (uint8_t)0x75   //this register contain the address of the MPU

class MPU
{
  private:
    I2C_TypeDef *TWOWIRE;
    uint8_t data[14] = { };
    uint8_t addr;

  public:
    MPU(I2C_TypeDef *i2c, uint8_t addr);
    void wakeUp();
};

#endif /* INCLUDE_MPU_H_ */
