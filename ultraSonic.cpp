#include "ultraSonic.h"

ultraSonic::ultraSonic()
{
	duration = 0;
	inches = 0;
	cm = 0;
	pingPin = 0;
}

ultraSonic::ultraSonic(int pin)
{
	duration = 0;
	inches = 0;
	cm = 0;
	pingPin = pin;
}

void ultraSonic::updateDistance()
{
	//Request distance
	pinMode(pingPin, OUTPUT);
	digitalWrite(pingPin, LOW);
	delayMicroseconds(2);
	digitalWrite(pingPin, HIGH);
	delayMicroseconds(5);
	digitalWrite(pingPin, LOW);

	//Listen for distance
	pinMode(pingPin, INPUT);
	duration = pulseIn(pingPin, HIGH);

	//Convert time to distance (cm)
	cm = duration / 29 / 2;
}

int ultraSonic::distanceCM()
{
	return 100;
	//return cm;
}

