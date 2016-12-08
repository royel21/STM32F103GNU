/*
 * Analog.h
 *
 *  Created on: Nov 11, 2016
 *      Author: RoyerAriel
 */

#ifndef ANALOG_H_
#define ANALOG_H_




#include "cmsis_device.h"
#include "define.h"

#ifdef __cplusplus
extern "C" {
#endif

/********************  Bits definition for DMA_SxCR register  *****************/
#define DMA_CCR_PL_VH                       ((uint16_t)0x0003000)
#define DMA_CCR_PL_M                        ((uint16_t)0x0001000)
#define DMA_CCR_PL_H                        ((uint16_t)0x0002000)
#define DMA_CCR_MSIZE_8bit                  ((uint16_t)0x0000000)
#define DMA_CCR_MSIZE_16bit                 ((uint16_t)0x0000400)
#define DMA_CCR_MSIZE_32bit                 ((uint16_t)0x0000800)
#define DMA_CCR_PSIZE_8bit                  ((uint16_t)0x0000000)
#define DMA_CCR_PSIZE_16bit                 ((uint16_t)0x0000100)
#define DMA_CCR_PSIZE_32bit                 ((uint16_t)0x0000200)
#define DMA_CCR_DIR_P2M                     ((uint16_t)0x0000000)
#define DMA_CCR_DIR_M2P                     ((uint16_t)0x0000040)
#define DMA_CCR_DIR_M2M                     ((uint16_t)0x0000080)
#define CH00                                 ((uint8_t)0x00)
#define CH01                                 ((uint8_t)0x01)
#define CH02                                 ((uint8_t)0x02)
#define CH03                                 ((uint8_t)0x03)
#define CH04                                 ((uint8_t)0x04)
#define CH05                                 ((uint8_t)0x05)
#define CH06                                 ((uint8_t)0x06)
#define CH07                                 ((uint8_t)0x07)
#define CH08                                 ((uint8_t)0x08)
#define CH09                                 ((uint8_t)0x09)
//	uint16_t adcVal = 0;
void analogReadWithDMAMulti(uint16_t pins, volatile uint16_t *vars, uint8_t size);
uint16_t analogRead(uint16_t);

#ifdef __cplusplus
}
#endif

#endif /* ANALOG_H_ */
