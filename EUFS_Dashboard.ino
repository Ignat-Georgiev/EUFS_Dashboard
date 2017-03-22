#include <Button.h>
#include "sevenSeg.h"
#include "RPM_Meter.h"
#include <Event.h>
#include <Timer.h>
#include <ToggleButton.h>
#include <Adafruit_TLC5947.h>


// pin assignments
uint16_t engineTempLED = 10;
uint16_t oilLED = 11;
int shiftLED = 5;
bool rst = false;
int osci = false;
int brightness = 0;
int brightnessLevels[4] = { 4095 / 4, 4095 / 2, 4095 / 1.25, 4095 };

// Serial data bus information
int rpmSerial = 0;
int shiftSerial = 0;
int gearSerial = 0;
int warningSerial[2];

// LED Driver constructor
#define NUM_TLC 1
#define drvr_clock 9
#define drvr_data 8
#define drvr_lat 3
Adafruit_TLC5947 drvr = Adafruit_TLC5947(NUM_TLC, drvr_clock, drvr_data, drvr_lat);

//	CINSTRUCTUCTORS
RPM_Meter rpm(&drvr, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);
sevenSeg dsp(&drvr, 13, 12, 17, 18, 19, 14, 15, 16);
ToggleButton testBtn(12, HIGH);
Timer testButtonTimer;
Button pwmChanger(11, false, false, 50);


void setup()
{

	Serial.begin(9600);
  pinMode(shiftLED, OUTPUT);

  drvr.begin();
  drvr.clear();

  for (int i = 0; i < 10; i++) {
	  rpm.test();
	  dsp.init();
  }
  drvr.clear();

  // TEST ARRANGEMENTS
  testButtonTimer.oscillate(shiftLED, 500, 1);
  testButtonTimer.every(100, test);
  testButtonTimer.every(400, test2);
  testButtonTimer.every(500, warningTest);

}

void loop()
{
 // // TEST BUTTON ACTIONS
 // testBtn.checkButton();
 // if (testBtn.currentState == true) {
 //   testButtonTimer.update();
 //   rst = true;
 // }
 // else {
	//  // reset only once to avoid problems
	//  if (rst) {
	//	  digitalWrite(shiftLED, 0);
	//	  drvr.clear();
	//	  rst = false;
	//  }
 // }

	//// PWM CHANGER
	pwmChanger.read();
	if (pwmChanger.wasReleased()) {
		drvr.setPWM(brightnessLevels[brightness]);
		if (++brightness == 4)
			brightness = 0;
	}

	// DATA RECEIVER
	// If data is found on serial bus.
	if (Serial.available() > 0) {

		// If initiating character is found, start placing the next characters into state integers.
		if (Serial.peek() == 'f') {
			Serial.read();
			rpmSerial = Serial.parseInt();
			Serial.read();
			shiftSerial = Serial.parseInt();
			Serial.read();
			gearSerial = Serial.parseInt();
			Serial.read();
			warningSerial[0] = Serial.parseInt();
			Serial.read();
			warningSerial[1] = Serial.parseInt();
			Serial.read();
		}

		// If more data is found. Remove it from bus.
		while (Serial.available() > 0) { Serial.read(); }

	}

	rpm.set(rpmSerial);
	dsp.set(gearSerial);
	if (shiftSerial>0)
		digitalWrite(shiftLED, 1);
	else
		digitalWrite(shiftLED, 0);
	if (warningSerial[0] > 0)
		drvr.set(oilLED, 1);
	else
		drvr.set(oilLED, 0);
	if (warningSerial[1] > 0)
		drvr.set(engineTempLED, 1);
	else
		drvr.set(engineTempLED, 0);
	drvr.write();

}

// Nescessery dummy call
void test() {
  rpm.test();
  drvr.write();
}
void test2() {
	dsp.test();
	drvr.write();
}

// Warning LED test
void warningTest() {
  if (osci) {
    drvr.set(engineTempLED, 1);
    drvr.set(oilLED, 0);
    osci = false;
  }
  else {
    drvr.set(oilLED, 1);
    drvr.set(engineTempLED, 0);
    osci = true;
  }
  drvr.write();
}