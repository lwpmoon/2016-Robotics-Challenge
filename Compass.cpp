#include "Compass.h"
#include <math.h>


//Adafruit_BNO055 bno = Adafruit_BNO055();
//LiquidCrystal lcd2(13, 12, 11, 10, 1, 0);
HMC5883L mag;

void compass::initialize()
{
	while (!mag.begin())
	{
		Serial.println("Could not find a valid HMC5883L sensor, check wiring!");
		delay(500);
	}
	delay(50);

	mag.setRange(HMC5883L_RANGE_1_3GA);

	// Set measurement mode
	mag.setMeasurementMode(HMC5883L_CONTINOUS);

	// Set data rate
	mag.setDataRate(HMC5883L_DATARATE_30HZ);

	// Set number of samples averaged
	mag.setSamples(HMC5883L_SAMPLES_8);

	// Set calibration offset. See HMC5883L_calibration.ino
	mag.setOffset(0, 0);
	
}


#pragma region BNO
//void compass::calibrate()
//{
//	//Hold to calibrate the bno
//	int system, gyro, accel, mag = 0;
//	while (mag != 3)
//	{
//		//lcd2.clear();
//		//lcd2.print("Calibrating...");
//		delay(100);
//		
//		//lcd2.setCursor(0, 1);
//		//lcd2.print("Mag: ");
//		//lcd2.print(mag, DEC);
//		delay(500);
//		//bno.getCalibration(&system, &gyro, &accel, &mag);
//	}
//	//Wake up BNO by poking it a couple times...
//	//imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
//}

//void compass::getCalibration()
//{
//	//Calibration status
//	int system, gyro, accel, mag = 0;
//	bno.getCalibration(&system, &gyro, &accel, &mag);
//	Serial.print("CALIBRATION: Sys=");
//	Serial.print(system, DEC);
//	Serial.print(", ");
//	Serial.print(" Gyro=");
//	Serial.print(gyro, DEC);
//	Serial.print(", ");
//	Serial.print(" Accel=");
//	Serial.print(accel, DEC);
//	Serial.print(", ");
//	Serial.print(" Mag=");
//	Serial.println(mag, DEC);
//}  
#pragma endregion

void compass::readHMC()
{
	Vector norm = mag.readNormalize();
	heading = atan2(norm.YAxis, norm.XAxis);
	heading += declinationAngle;
}

void compass::updateHeading()
{
	readHMC();
	/*if (heading >= 360)
	{
		heading = heading - 360;
	}*/

	if (heading < 0)
	{
		heading += 2 * PI;
	}

	if (heading > 2 * PI)
	{
		heading -= 2 * PI;
	}
	headingDegrees = heading * 180 / M_PI;
}

int compass::directionFinder(int location)
{
	int direction = 0; //0 = left
	int rotation = heading - location;
	if (rotation < 0){ //Correct negative headings 
		rotation = rotation + 360;
	}
	if (rotation > 180){ //Determine direction to turn
		direction = 1;//1 = right
		rotation = 360 - rotation;
	}
	return direction;
}

int compass::returnHeading()
{
	return headingDegrees;
}

compass::compass()
{
	heading = 0;
	headingDegrees = 0;
}
