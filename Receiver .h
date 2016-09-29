#pragma once
#include <Arduino.h>
#include <Wire.h>

class beacon
{
public:
	beacon();
	void initialize();
	bool beaconPresent();
	void findBeacon();
	uint16_t returnLocation();

private:
	uint16_t location;
	uint8_t MSB, LSB;
};