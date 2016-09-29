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

	void turnRight(uint8_t);
	void turnLeft(uint8_t);
	void forward(uint8_t);
	void backward(uint8_t);
	void stop();

	void motorOff(uint8_t);
	void motorGo(uint8_t, uint8_t, uint8_t);

private:
	uint8_t inApin[2] = { 7, 4 };  // INA: Clockwise input
	uint8_t inBpin[2] = { 8, 9 }; // INB: Counter-clockwise input
	uint8_t pwmpin[2] = { 5, 6 }; // PWM input
	uint8_t cspin[2] = { 2, 3 }; // CS: Current sense ANALOG input
	uint8_t enpin[2] = { 0, 1 }; // EN: Status of switches output (Analog pin)

	uint8_t statpin = 13;
};