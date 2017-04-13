#pragma once
#include <Arduino.h>

class ultraSonic
{
public:
	void initialize();
	void updateDistance();
	int distanceCM();
	ultraSonic(int);
	ultraSonic();

private:
	int pingPin;
	int duration = 0, inches = 0, cm = 0;
};