#pragma once
#include <Arduino.h>
#include <Wire.h>

class beacon
{
public:
	beacon();
	void initialize();
	void updatePresent();
	void findBeacon();
	uint16_t returnLocation();
	bool returnPresent();

private:
	bool present;
	uint16_t location;
	int MSB, LSB;
};