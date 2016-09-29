#pragma once
#include <Arduino.h>

class groundIR
{
public:
	groundIR();//default constructor
	groundIR(uint8_t);
	void initialize();
	bool isGroundPres();

private:
	uint8_t sensor;
	uint8_t state;
};