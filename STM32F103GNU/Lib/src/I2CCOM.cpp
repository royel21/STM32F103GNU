/*
 * I2CSerialComm.cpp
 *
 *  Created on: Jun 18, 2016
 *      Author: Royel
 */

#include <I2CCOM.h>
#include "define.h"
#include "Timer.h"
/*****I2C Flags*****/
#define  I2C_ACK                  ((uint8_t)0)          /** I2C Write bit **/
#define  I2C_NACK                 ((uint8_t)1)
#define  I2C_EVNT_MS              ((uint32_t)0x00030001)  /* BUSY, MSL and SB flag */
#define  I2C_EVNT_M_Tx            ((uint32_t)0x00070082)  /* BUSY, MSL, ADDR, TXE and TRA flags */
#define  I2C_EVNT_M_Rx            ((uint32_t)0x00030002)  /* BUSY, MSL and ADDR flags */
/* Master RECEIVER mode -----------------------------*/
/* --EV7 */
#define  I2C_EVENT_MBRXD          ((uint32_t)0x00030040)  /* BUSY, MSL and RXNE flags */
/* Master TRANSMITTER mode --------------------------*/
/* --EV8 */
#define  I2C_EVENT_MBTXG          ((uint32_t)0x00070080) /* TRA, BUSY, MSL, TXE flags */
/* --EV8_2 */
#define  I2C_EVENT_MBTXD          ((uint32_t)0x00070084)  /* TRA, BUSY, MSL, TXE and BTF flags */

I2CCOM::I2CCOM(I2C_TypeDef *i2c, uint32_t I2C_SPD, uint8_t remap)
{

  address = 0;
  this->I2Cx = i2c;
  ////Connect I2Cx pins to AF
  // configure I2C1
  CLCK = P06;
  SDA = P07;
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
  if (i2c == I2C1)
  {
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    if (remap)
    {
      AFIO->MAPR |= AFIO_MAPR_I2C1_REMAP;
      CLCK = P08;
      SDA = P09;
    }
  } else if (i2c == I2C2)
  {
    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
    this->I2Cx = i2c;
    CLCK = P10;
    SDA = P11;
  }
  GPIO_Config(GPIOB, CLCK | SDA, MODE_OUT_2MHZ, CNF_OUT_AFOD);
  // configure I2C1
  uint16_t freqrange = 0;
  uint16_t result = 0x04;

  /* Get pclk1 frequency value */
  uint32_t pclk1 = (SystemCoreClock / 2);
  /* Set frequency bits depending on pclk1 value */
  freqrange = (uint16_t) (pclk1 / 1000000);
  /* Write to I2C1 CR2 */
  I2Cx->CR2 = freqrange; //tmpreg;

  /* Configure speed in standard mode */
  if (I2C_SPD <= 100000)
  {
    result = (uint16_t) (pclk1 / (I2C_SPD << 1));
    I2Cx->CCR = (result < 0x04) ? 0x04 : result;

  } else /*(I2C_InitStruct->I2C_ClockSpeed <= 400000)*/
  {
    /* Fast mode speed calculate: Tlow/Thigh = 2 */
    I2Cx->CCR = (uint16_t) (pclk1 / (I2C_SPD * 3)) | I2C_CCR_FS;
  }
  I2Cx->TRISE = 0;
  I2Cx->CR1 |= I2C_CR1_ACK | I2C_CR1_PE;
}

void I2CCOM::init()
{
  //I2Cx->CR1 |= ;
}


/* Send the address to the i2c line to ready the Slave */
uint8_t I2CCOM::Start(uint8_t addr, uint8_t direction)
{
  if (I2Cx->SR2 & I2C_SR2_BUSY)
    pinToggle();

  I2Cx->CR1 |= I2C_CR1_START;
  /* Test on EV5 and clear it */
  uint16_t timeout = 250;
  while (!((I2Cx->SR1 & 0x1) && (I2Cx->SR2 & 0x3)) && timeout--)
    ;

  /* Send Slave address for write */
  I2Cx->DR = (addr << 1 | direction);

  return 0;
}

/** Write one byte to the slave device
 * and after that a STOP condition is transmitted
 */
uint8_t I2CCOM::Write(uint8_t data)
{
  int timeout = 500;
  while (!((I2Cx->SR1 & 0x82) && (I2Cx->SR2 & 0x7)) && timeout--)
    ;
  /* Write Data to Slave*/
  I2Cx->DR = data;
  /* Test on EV8 and clear it */

  return 0;
}
void I2CCOM::WriteTo(uint8_t addr, uint8_t data)
{
  Start(addr, I2C_WR);
  Write(data);
  Stop();

}
/** Write one data to a  register */
void I2CCOM::WriteToReg(uint8_t addr, uint8_t reg, uint8_t data)
{
  Start(addr, I2C_WR);
  Write(reg);
  Write(data);
  Stop();
}
/** Write to one register */
void I2CCOM::WriteMultiReg(uint8_t reg, uint8_t *data, uint8_t size)
{
  Start(address, I2C_WR);
  Write(reg);

  while (size)
  {
    Write(*data);
    data++;
    size--;
  }
  Stop();
}
/** Read data from register*/
uint8_t I2CCOM::ReadFrom(uint8_t addr, uint8_t reg)
{
  uint8_t data;

  Start(addr, I2C_WR);

  Write(reg);

  I2Cx->CR1 |= I2C_CR1_STOP;

  while (I2Cx->SR2 != 0)
    ;

  Start(addr, I2C_RD);

  while (!(I2Cx->SR1 & I2C_SR1_ADDR))
    ;

  I2Cx->CR1 &= ~I2C_CR1_ACK;
  I2Cx->SR2;

  while (!(I2Cx->SR1 & I2C_SR1_RXNE))
    ;

  data = I2Cx->DR & 0xFF;

  Stop();
  I2Cx->CR1 |= I2C_CR1_ACK;
  return data;
}

void I2CCOM::ReadMultiReg(uint8_t addr, uint8_t reg, uint8_t *data, uint8_t size)
{
  Start(addr, I2C_WR);

  Write(reg);

  I2Cx->CR1 |= I2C_CR1_STOP;

  while (I2Cx->SR2 != 0)
    ;

  Start(addr, I2C_RD);
  while (!(I2Cx->SR1 & I2C_SR1_ADDR))
    ;
  I2Cx->SR2;

  while (size)
  {

    if (size == 1)
    {
      I2Cx->CR1 &= ~I2C_CR1_ACK;
      I2Cx->SR2;
    }

    if (I2Cx->SR1 & I2C_SR1_RXNE)
    {
      *data++ = I2Cx->DR;
      size--;
    }
  }

  I2Cx->CR1 |= I2C_CR1_STOP;

  while (I2Cx->SR2 != 0)
    ;
  I2Cx->CR1 |= I2C_CR1_ACK;
}
/* Reads one byte from the slave device
 * and doesn't acknowledge the received data
 * after that a STOP condition is transmitted
 */

uint8_t I2CCOM::ReadData(uint8_t nack)
{
  /* Waiting for ADDR condition */
  uint8_t data;
  uint8_t timeout = 255;
  if (!nack)
  {
    return (I2Cx->DR & 0xFF);
  } else
  {
    /* DISABLE ACKNOWLEDGE */
    I2Cx->CR1 &= ~I2C_CR1_ACK;

    while (!(I2Cx->SR1 & I2C_SR1_RXNE) && timeout--)
      I2Cx->SR2;
    Stop();

    data = I2Cx->DR & 0xFF;

    /* ENABLE ACKNOWLEDGE */
    I2Cx->CR1 |= I2C_CR1_ACK;
    return data;
  }
}

/*Trasnmitt a stop condition to the Slave */
void I2CCOM::Stop()
{
  /* Send STOP condition */
  I2Cx->CR1 |= I2C_CR1_STOP;
  uint8_t timeout = 255;
  while ((I2Cx->CR1 & I2C_CR1_STOP) && timeout--)
    ;
}

void I2CCOM::hardReset()
{
  /* Send STOP condition */
  // Stop();
  uint32_t cr2 = I2Cx->CR2;
  uint32_t ccr = I2Cx->CCR;
  I2Cx->CR1 |= I2C_CR1_SWRST;
  I2Cx->CR1 &= ~I2C_CR1_SWRST;
  I2Cx->CR1 = I2C_CR1_ACK | I2C_CR1_PE;
  I2Cx->CR2 = cr2;
  I2Cx->CCR = ccr;
}

uint8_t I2CCOM::Scan()
{
  for (uint8_t i = 37; i < 128; i++)
  {
    Start(i, I2C_WR);
    if (I2Cx->SR1 & I2C_SR1_AF)
    {
      hardReset();
    } else
    {
      Stop();
      return ++i;
    }
  }
  return 0;
}

void I2CCOM::pinToggle()
{
  I2Cx->CR1 &= ~(I2C_CR1_ACK | I2C_CR1_PE);
  GPIO_Config(GPIOB, SDA | CLCK, MODE_OUT_50MHZ);

  for (uint8_t i = 0; i < 8; i++)
  {
    GPIOB->ODR |= CLCK;
    GPIOB->ODR &= ~SDA;
    GPIOB->ODR |= CLCK;
    GPIOB->ODR &= ~CLCK;
    GPIOB->ODR |= SDA;
    GPIOB->ODR |= CLCK;
  }
  GPIOB->BSRR |= SDA | CLCK;
  GPIO_Config(GPIOB, CLCK | SDA, MODE_OUT_2MHZ, CNF_OUT_AFOD);
  I2Cx->CR1 |= I2C_CR1_ACK | I2C_CR1_PE;
}
void I2C1_EV_IRQHandler(void)
{
  switch (I2C_GetLastEvent(I2C1))
  {
    case I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED:
    break;
    case I2C_EVENT_SLAVE_BYTE_RECEIVED:
      // i2c_read_packet[Rx_Index] = I2C_ReceiveData(I2C2); // Store the packet in i2c_read_packet.
      //Rx_Index++;
    break;
    case I2C_EVENT_SLAVE_STOP_DETECTED:
      // Rx_Index = 0;
      // packets_recv_i2c++;
      // i2cProcessPacket();
    break;
    case I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED:
      // I2C_SendData(I2C2, i2c_packet_to_send[0]);
      // Tx_Index++;
    break;
    case I2C_EVENT_SLAVE_BYTE_TRANSMITTED:
      //I2C_SendData(I2C2, i2c_packet_to_send[Tx_Index]);
      //Tx_Index++;
    break;
    case I2C_EVENT_SLAVE_ACK_FAILURE:
      // Tx_Index = 0;
      //  packets_sent_i2c++;
    break;
    default:
    break;
  }
}
I2CCOM I2CCom(I2C1, I2C_SP400K, PINREMAP);
