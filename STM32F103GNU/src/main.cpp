#include "Timer.h"
#include "SerialHardware.h"
#include "analog.h"

int main(void)
{
	ADC adc(ADC1);
	Serial2.Init(921600);
	Serial2.println("test");
	while (1)
	{
		float var = 0;
		long start = micros();
		var = adc.read(CH0);
		Serial2.println("Stop:", micros() - start);
		Serial2.println("Volt:", (var * (3.3 / 4095)) + 0.077);

		delayMillis(200);
	}
	return 0;
}

