#include "Receiver .h"

beacon::beacon()
{
	location = 0;
	present = false;
}

void beacon::initialize()
{
	Wire.begin();
}

void beacon::updatePresent()
{
	Wire.requestFrom(8, 2);
	MSB = Wire.read();
	LSB = Wire.read();
	int holder = (MSB << 8) | LSB;
	if (holder == -1)present = false;
	else present = true;
}


void beacon::findBeacon()
{
	Wire.requestFrom(8, 2);
	MSB = Wire.read();
	LSB = Wire.read();
	int16_t holder = (MSB << 8) | LSB;//Points from beacon
	//Turn around to creat a heading to follow
	holder = holder - 180;
	if (holder >= 360) holder = holder - 360;
	else if (holder < 0) holder = holder + 360;
	location = holder; //Points to beacon
}

uint16_t beacon::returnLocation()
{
	return location;
}

bool beacon::returnPresent()
{
	return present;
}

