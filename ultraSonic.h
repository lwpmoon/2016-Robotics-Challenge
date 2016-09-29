#pragma once
#include <Arduino.h>

class ultraSonic
{
public:
	void initialize();
	void updateDistance();
	uint8_t distanceCM();
	ultraSonic(uint8_t);
	ultraSonic();

private:
	uint8_t pingPin;
	uint8_t duration, inches, cm;
};