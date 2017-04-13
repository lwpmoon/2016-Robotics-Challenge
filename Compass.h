#pragma once
#include <Wire.h>
#include <Arduino.h>
//#include <Adafruit_BNO055.h>
#include <LiquidCrystal.h>
#include "motorShield.h"
#include <HMC5883L.h>
#include <math.h>

//#include "groundSen.h"

//#define BNO055_SAMPLERATE_DELAY_MS (100)


class compass
{
public:
	compass();
	void initialize();
	void updateHeading();
	int returnHeading();
	int directionFinder(int);
private:
	void readHMC();
	void calibrate();
	void getCalibration();

	float heading, headingDegrees, declinationAngle = (4.0 + (26.0 / 60.0)) / (180 / M_PI);
};
