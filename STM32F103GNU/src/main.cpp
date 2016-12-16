#include "Timer.h"
#include "SerialHardware.h"

int main(void)
{
	Serial2.Init(115200);

  while (1)
  {
		uint32_t start = micros();
		Serial2.println("C");
		Serial2.println("Micros:", micros() - start);
		delayMillis(100);
  }
  return 0;
}

