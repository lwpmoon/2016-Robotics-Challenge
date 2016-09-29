#pragma once
#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_BNO055.h>
#include <LiquidCrystal.h>
#include "motorShield.h"
//#include "groundSen.h"

#define BNO055_SAMPLERATE_DELAY_MS (100)


class compass
{
public:
	compass();
	void initialize();
	uint8_t updateHeading();
	uint8_t returnHeading();
	void calibrate();
	void getCalibration();
	uint8_t directionFinder(uint8_t);
private:
	uint8_t heading;
};
