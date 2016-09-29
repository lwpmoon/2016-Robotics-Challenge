#pragma once
#include <LiquidCrystal.h>
#include <string.h>

//LiquidCrystal lcd(13, 12, 11, 10, 1, 0);

class LCDdriver
{
public:
	void initialze();
	void print();
	void clear();
};