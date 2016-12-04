/*
 * DS3231.h
 *
 *  Created on: Sep 13, 2016
 *      Author: RoyerAriel
 */

#ifndef DS_RTC_H_
#define DS_RTC_H_

#include "I2CSerialComm.h"
#include "define.h"

#define RTC_SECOND      0x00
#define RTC_MINUTE      0x01
#define RTC_HOUR     	0x02
#define RTC_WEEKDAY     0x03
#define RTC_MONTHDAY    0x04
#define RTC_MONTH       0x05
#define RTC_YEAR        0x06

class DS_RTC {

	private:
		uint8_t rtc_addr;
	public:
		DS_RTC(uint8_t);
		uint8_t bcdToDEC(uint8_t);
		uint8_t decToBCD(uint8_t);

		void setTime(uint8_t *);
		void getTime(uint8_t *);

		inline void set(uint8_t min,uint8_t date){ I2C1Comm.WriteToReg(rtc_addr,date,decToBCD(min)); }
		inline uint8_t get(uint8_t time){ return bcdToDEC(I2C1Comm.ReadFrom(rtc_addr,time));}
};

#endif /* DS_RTC_H_ */
