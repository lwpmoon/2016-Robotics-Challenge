#pragma once
#include <Arduino.h>
#include <stdint.h>

#define BRAKEVCC 0
#define CW   1
#define CCW  2
#define BRAKEGND 3
#define CS_THRESHOLD 100

class motorShield
{
public:
	void initialize();

	void turnRight(int);
	void turnLeft(int);
	void forward(int);
	void backward(int);
	void stop();

	void motorOff(int);
	void motorGo(int, int, int);

private:
	int inApin[2] = { 7, 4 };  // INA: Clockwise input
	int inBpin[2] = { 8, 9 }; // INB: Counter-clockwise input
	int pwmpin[2] = { 5, 6 }; // PWM input
	int cspin[2] = { 2, 3 }; // CS: Current sense ANALOG input
	int enpin[2] = { 0, 1 }; // EN: Status of switches output (Analog pin)

	int statpin = 13;
};