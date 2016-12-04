/*
 * LCDI2C.h
 *
 *  Created on: Jun 29, 2016
 *      Author: RoyerAriel
 */

#ifndef LCDI2C_H_
#define LCDI2C_H_

#include "I2CSerialComm.h"
#include "Timer.h"
#include "define.h"
#include "Printer.h"

// commands
#define LCD_CLEARDISPLAY             (uint8_t)0x01
#define LCD_RETURNHOME               (uint8_t)0x02
#define LCD_ENTRYMODESET             (uint8_t)0x04
#define LCD_DISPLAYCONTROL           (uint8_t)0x08
#define LCD_CURSORSHIFT              (uint8_t)0x10
#define LCD_FUNCTIONSET              (uint8_t)0x20
#define LCD_SETCGRAMADDR             (uint8_t)0x40
#define LCD_SETDDRAMADDR             (uint8_t)0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT               (uint8_t)0x00
#define LCD_ENTRYLEFT                (uint8_t)0x02
#define LCD_ENTRYSHIFTINCREMENT      (uint8_t)0x01
#define LCD_ENTRYSHIFTDECREMENT      (uint8_t)0x00

// flags for display on/off control
#define LCD_DISPLAYON                (uint8_t)0x04
#define LCD_DISPLAYOFF               (uint8_t)0x00
#define LCD_CURSORON                 (uint8_t)0x02
#define LCD_CURSOROFF                (uint8_t)0x00
#define LCD_BLINKON                  (uint8_t)0x01
#define LCD_BLINKOFF                 (uint8_t)0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE              (uint8_t)0x08
#define LCD_CURSORMOVE               (uint8_t)0x00
#define LCD_MOVERIGHT                (uint8_t)0x04
#define LCD_MOVELEFT                 (uint8_t)0x00

// flags for function set
#define LCD_8BITMODE                 (uint8_t)0x10
#define LCD_4BITMODE                 (uint8_t)0x00
#define LCD_2LINE                    (uint8_t)0x08
#define LCD_1LINE                    (uint8_t)0x00
#define LCD_5x10DOTS                 (uint8_t)0x04
#define LCD_5x8DOTS                  (uint8_t)0x00

// flags for backlight control
#define LCD_BACKLIGHT                (uint8_t)0x08 //0000 1000
#define LCD_NOBACKLIGHT              (uint8_t)0x00

#define EnON                         (uint8_t)0b00000100  // Enable bit
#define Rw                           (uint8_t)0b00000010  // Read/Write bit
#define RsData                       (uint8_t)1  // Register select bit
#define RsCmd                        (uint8_t)0  // Register select bit

class LCD_I2C: public Printer
{
	private:
		uint8_t cmd;
		uint8_t blackLightState;
		uint8_t address;
		void pulseEnable();
		void Write4Bits(uint8_t);
	public:

    LCD_I2C(uint8_t);

		void WriteByte(const char);

    void Init();
		void WriteCmd(uint8_t);

		void Clear();
		void Cursor(uint8_t);
		void Blink();
		void CursorPos(uint8_t, uint8_t);
		void autoScroll(uint8_t);
		void blackLight(const uint8_t);
};

#endif /* LCDI2C_H_ */
