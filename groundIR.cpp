#include "groundIR.h"

groundIR::groundIR()
{
	sensor = -1;
	state = -1;
}


groundIR::groundIR(uint8_t pin)
{
	sensor = pin;
	state = -1;
}

void groundIR::initialize()
{
	pinMode(sensor, INPUT);
}


bool groundIR::isGroundPres()
{
	//If it sees the groundEye 0 will return
	if (digitalRead(sensor) == 0) return true;
	else if (digitalRead(sensor == 1)) return false;
}
