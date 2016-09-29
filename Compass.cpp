#include "Compass.h"

Adafruit_BNO055 bno = Adafruit_BNO055();
LiquidCrystal lcd2(13, 12, 11, 10, 1, 0);

void compass::initialize()
{
	// Initialise the BNO055
	if (!bno.begin(Adafruit_BNO055::OPERATION_MODE_COMPASS))
	{
		//Hold here if BNO is not found
		while (1);
	}
	bno.setExtCrystalUse(true);
	delay(50);
	
}


void compass::calibrate()
{
	//Hold to calibrate the bno
	uint8_t system, gyro, accel, mag = 0;
	while (mag != 3)
	{
		lcd2.clear();
		lcd2.print("Calibrating...");
		delay(100);
		
		lcd2.setCursor(0, 1);
		lcd2.print("Mag: ");
		lcd2.print(mag, DEC);
		delay(500);
		bno.getCalibration(&system, &gyro, &accel, &mag);
	}
	//Wake up BNO by poking it a couple times...
	imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
}

void compass::getCalibration()
{
	//Calibration status
	uint8_t system, gyro, accel, mag = 0;
	bno.getCalibration(&system, &gyro, &accel, &mag);
	Serial.print("CALIBRATION: Sys=");
	Serial.print(system, DEC);
	Serial.print(", ");
	Serial.print(" Gyro=");
	Serial.print(gyro, DEC);
	Serial.print(", ");
	Serial.print(" Accel=");
	Serial.print(accel, DEC);
	Serial.print(", ");
	Serial.print(" Mag=");
	Serial.println(mag, DEC);
}


uint8_t compass::updateHeading()
{
	imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
	heading = euler.x() + 90;
	if (heading >= 360)
	{
		heading = heading - 360;
	}
	return heading;
}

uint8_t compass::directionFinder(uint8_t location)
{
	uint8_t direction = 0; //0 = left
	uint8_t rotation = heading - location;
	if (rotation < 0){ //Correct negative headings 
		rotation = rotation + 360;
	}
	if (rotation > 180){ //Determine direction to turn
		direction = 1;//1 = right
		rotation = 360 - rotation;
	}
	return direction;
}

uint8_t compass::returnHeading()
{
	return heading;
}



compass::compass()
{
	heading = 0;
}
