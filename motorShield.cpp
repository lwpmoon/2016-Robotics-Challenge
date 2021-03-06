#include "motorShield.h"

void motorShield::initialize()
{
	pinMode(statpin, OUTPUT);

	// Initialize digital pins as outputs
	for (int i = 0; i<2; i++)
	{
		pinMode(inApin[i], OUTPUT);
		pinMode(inBpin[i], OUTPUT);
		pinMode(pwmpin[i], OUTPUT);
	}
	// Initialize braked
	for (int i = 0; i<2; i++)
	{
		digitalWrite(inApin[i], LOW);
		digitalWrite(inBpin[i], LOW);
	}
}


void motorShield::motorOff(int motor)
{
	// Initialize braked
	for (int i = 0; i<2; i++)
	{
		digitalWrite(inApin[i], LOW);
		digitalWrite(inBpin[i], LOW);
	}
	analogWrite(pwmpin[motor], 0);
}

void motorShield::motorGo(int motor, int direct, int pwm)
{
	if(motor <= 1)
	{
		if (direct <= 4)
		{
			// Set inA[motor]
			if (direct <= 1)
				digitalWrite(inApin[motor], HIGH);
			else
				digitalWrite(inApin[motor], LOW);

			// Set inB[motor]
			if ((direct == 0) || (direct == 2))
				digitalWrite(inBpin[motor], HIGH);
			else
				digitalWrite(inBpin[motor], LOW);

			analogWrite(pwmpin[motor], pwm);
		}
	}
}

void motorShield::turnLeft(int SPEED)
{
	motorGo(0, CCW, SPEED);
	motorGo(1, CCW, SPEED);
}

void motorShield::turnRight(int SPEED)
{
	motorGo(0, CW, SPEED);
	motorGo(1, CW, SPEED);
}

void motorShield::forward(int SPEED)
{
	motorGo(0, CCW, SPEED);
	motorGo(1, CW, SPEED);
}

void motorShield::backward(int SPEED)
{
	motorGo(0, CW, SPEED);
	motorGo(1, CCW, SPEED);
}

void motorShield::stop()
{
	motorOff(0);
	motorOff(1);
}
