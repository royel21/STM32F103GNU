#include "Timer.h"
#include "SerialHardware.h"

int main(void)
{
	Serial3.Init(2000000);

  while (1)
  {
		Serial3.println(micros());
		delayMicros(100000);
  }
  return 0;
}

