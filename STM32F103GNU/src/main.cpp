// ----------------------------------------------------------------------------
#include "cmsis_device.h"
#include "define.h"
#include "Timer.h"
#include "util.h"
#include "SerialHardware.h"
#include "LCDI2C.h"

int main()
{
  Serial2.Init(921600);
  LCD_I2C lcd(0x27);
  lcd.Init();
  // At this stage the system clock should have already been configured
  // at high speed.
  //GPIO_Config(GPIOA, P06 | P07, MODE_OUT_50MHZ, CNF_OUT_AFOD);
  //lcd.print("stared3");
  // Infinite loop
  // Serial2.println("Adress:0x", I2C1Comm.I2CScan(), HEX);

  uint8_t n = 0;
  while (1)

  {
    lcd.print(n++);

    Serial2.print(n);
    Serial2.println();
    // Serial2.println("hla");
//    if (Serial2.hasData())
//    {
//      Serial2.print(Serial2.readByte());
//    }
//    GPIOC->BSRR |= P13;
//    // delayMillis(500);
//    GPIOC->BRR |= P13;
    // delayMillis(1);
    // Add your code here.
  }
}

