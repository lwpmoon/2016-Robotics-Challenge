/*
 Name:		Prodigal_Son.ino
 Created:	4/6/2016 11:35:43 AM
 Author:	Wesley Perkins
*/
#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <Adafruit_BNO055.h>

#include "motorShield.h"
#include "groundIR.h"
#include "Compass.h"
#include "Receiver .h"
#include "LCDdriver.h"
#include "ultraSonic.h"

compass navigator;
motorShield driver;
groundIR groundEye(2);
beacon scout;//Redo pin asignment to here and so on...
LiquidCrystal lcd(13, 12, 11, 10, 1, 0); // Assign all lcd pins
ultraSonic googlyEyes(3);//Assign Ping to pin 3

uint8_t temp = 0; //Leave this here because I forgot what I was doing with it...
const uint8_t accuracy = 15;//Sets a window (+/-) of accuracy with navigation
const uint8_t range = 1; //Sets range for Ping
const uint8_t rate = 200; //Sets ping refresh rate
const uint8_t SPEED = 75; //Sets speed of the motors

void setup() {
	//Initialise statments 
	//Serial.begin(115200); //Serial  (Can't use with lcd)
	lcd.begin(16, 2);
	lcd.print("Initializing...");
	delay(1000);
	groundEye.initialize(); //Ground sensor
	driver.initialize(); //Motor shield
	navigator.initialize(); //BNO
	scout.initialize(); //Receiver
	//googleyEyes.initialze(); //Ping sensor
	delay(1000);
	lcd.clear();
	//lcd.print("Calibrateing...");

	//navigator.calibrate();//Calibrate BNO

	//Serial.println("Lets GO!!!");
	lcd.print("Lets GO!!!");
	delay(3000);
	
	//googleyEyes;
	while (groundEye.isGroundPres() == false)
	{
		lcd.setCursor(0, 1);
		lcd.print("Put me down!!!");
		//Do nothing
	}
	lcd.clear();
	
}

void loop() {
	while (scout.beaconPresent() == false)
	{
		//Run this loop until beacon signal is received
		driver.stop();
		lcd.clear();
		lcd.blink();
		lcd.print("No beacon signal");
		lcd.setCursor(0, 1);
		lcd.print("in range...");
		delay(1000);
	}
	lcd.clear();
	googlyEyes.updateDistance();
	while (googlyEyes.distanceCM() > range) {
		if (scout.beaconPresent() == true) {
			//get calibration for bno
			//navigator.getCalibration();
			//Where am I pointed?
			//Serial.print("Corrected heading: ");
			//Serial.println(navigator.updateHeading());

			//Make important decisions...
			if (groundEye.isGroundPres() == true) {
				//lcd.clear();
				//Serial.println("I see the ground. Proceeding...");
				navigator.updateHeading();
				scout.findBeacon();
				lcd.home();
				lcd.print("  Me   /   It ");
				lcd.setCursor(0, 1);
				lcd.print(" ");
				if (navigator.returnHeading()< 100)lcd.print("0");
				if (navigator.returnHeading() < 10)lcd.print("0");
				lcd.print(navigator.returnHeading());
				lcd.print("   /  ");
				if (scout.returnLocation() < 100)lcd.print("0");
				if (scout.returnLocation() < 10)lcd.print("0");
				lcd.print(scout.returnLocation());
				//Forward
				if (navigator.returnHeading() <= (scout.returnLocation() + accuracy) && navigator.returnHeading()
					>= (scout.returnLocation() - accuracy)) {
					//Serial.println("Full steam ahead!!!");
					driver.forward(SPEED);
					if (millis() % rate == 0) googlyEyes.updateDistance();
				}
				while (navigator.returnHeading() > (scout.returnLocation() + accuracy) || navigator.returnHeading()
					< (scout.returnLocation() - accuracy)) {
					//lcd.home();
					//lcd.print("Correcting course...");
					//determin correction direction
					if (navigator.directionFinder(scout.returnLocation()) == 0) {
						//Serial.println("Turning Left...");
						driver.turnLeft(SPEED);
						lcd.home();
						lcd.print("  Me   /   It ");
						lcd.setCursor(0, 1);
						lcd.print(" ");
						if (navigator.returnHeading() < 100)lcd.print("0");
						if (navigator.returnHeading() < 10)lcd.print("0");
						lcd.print(navigator.returnHeading());
						lcd.print("   /  ");
						if (scout.returnLocation() < 100)lcd.print("0");
						if (scout.returnLocation() < 10)lcd.print("0");
						lcd.print(scout.returnLocation());
						//googlyEyes.updateDistance();
					}
					else if (navigator.directionFinder(scout.returnLocation()) == 1) {
						//Serial.println("Turning Right...");
						driver.turnRight(SPEED);
						lcd.home();
						lcd.print("  Me   /   It ");
						lcd.setCursor(0, 1);
						lcd.print(" ");
						if (navigator.returnHeading() < 100)lcd.print("0");
						if (navigator.returnHeading() < 10)lcd.print("0");
						lcd.print(navigator.returnHeading());
						lcd.print("   /  ");
						if (scout.returnLocation() < 100)lcd.print("0");
						if (scout.returnLocation() < 10)lcd.print("0");
						lcd.print(scout.returnLocation());
						//googlyEyes.updateDistance();
					}
					navigator.updateHeading();
					scout.findBeacon();
					if (millis() % rate == 0) googlyEyes.updateDistance();
				}
				//Serial.println("Back on course!");
			}
			/*else if (groundEye.isGroundPres() == false) {
				//Stop
				driver.stop();
				Serial.println("This drop is too far for me to possibly survive!");
				delay(500);
				//Backup
				driver.backward();
				delay(2000);
				//Turn Left for 90 degrees
				//Function needs to be added
				driver.turnLeft();
				delay(1500);
				//Forward
				driver.forward();
				if (millis() % rate == 0) googlyEyes.updateDistance();
			}*/
			scout.beaconPresent();
		}
		googlyEyes.updateDistance();
		while (googlyEyes.distanceCM() <= range)
		{
			driver.stop();
			lcd.clear();
			lcd.print("Too close!");
			lcd.setCursor(0, 1);
			lcd.print(googlyEyes.distanceCM());
			lcd.print(" CM");
			delay(rate);
			googlyEyes.updateDistance();
		}
	}
}
