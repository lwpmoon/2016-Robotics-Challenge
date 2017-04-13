#pragma once
#include <Arduino.h>

class groundIR
{
public:
	groundIR();//default constructor
	groundIR(int);
	void initialize();
	bool isGroundPres();

private:
	int sensor;
	int state;
};