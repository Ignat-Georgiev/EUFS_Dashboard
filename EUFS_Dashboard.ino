#include <Event.h>
#include <Timer.h>
#include <ToggleButton.h>
#include <Adafruit_TLC5947.h>
#include "RPM_Meter.h"
//#include "7seg.h"

Timer testButtonTimer;
int shiftLED = 5;
//int rpm[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
ToggleButton testBtn(12, HIGH);
bool rst = false;
int osci = false;

// LED Driver constructor
#define NUM_TLC 1
#define drvr_clock 9
#define drvr_data 8
#define drvr_lat 3
Adafruit_TLC5947 drvr = Adafruit_TLC5947(NUM_TLC, drvr_clock, drvr_data, drvr_lat);

//	RPM CINSTRUCTUCTOR

RPM_Meter rpm(&drvr, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9);


// FUNC HEADERS
//void RPMtest();
//void setRPM(uint16_t n);
//void clearLED();
//void setGear(uint16_t gear, boolean dot = false);



void setup()
{

  Serial.begin(19200);
  drvr.begin();
  drvr.clear();
  pinMode(shiftLED, OUTPUT);

  // TEST ARRANGEMENTS
  testButtonTimer.oscillate(shiftLED, 500, 1);
  testButtonTimer.every(100, RPMtest);
  testButtonTimer.every(200, warningTest);

}

void loop()
{
  // TEST BUTTON ACTIONS
  testBtn.checkButton();
  if (testBtn.currentState == true) {
    testButtonTimer.update();
    rst = true;
  }
  else {
    // reset only once to avoid problems
    if (rst) {
      digitalWrite(shiftLED, 0);
      drvr.clear();
      rst = false;
    }
  }

}

// Nescessery dummy call
void RPMtest() {
  rpm.test();
}

void warningTest() {
  if (osci) {
    drvr.set(10, 1);
    drvr.set(11, 0);
    osci = false;
  }
  else {
    drvr.set(10, 0);
    drvr.set(11, 1);
    osci = true;
  }
}



//void RPMtest() {
//	for (int i = 0; i <= 10; i++) {
//		setRPM(i);
//		delay(100);
//	}
//}
//
//void setRPM(uint16_t n) {
//	for (int i = 0; i < 10; i++){
//		if (i < n)
//			drvr.set(rpm[i], 1);
//		else
//			drvr.set(rpm[i], 0);
//	}
//	drvr.write();
//}
//
//void clearLED() {
//	for (int i = 0; i < 24; i++) {
//		drvr.set(i, 0);
//	}
//	drvr.write();
//}
//
//void setGear(uint16_t gear, boolean dot) {
//	switch (gear) {
//	case 0:
//		break;
//	case 1:
//		break;
//	case 2:
//		break;
//	case 3:
//		break;
//	case 4:
//		break;
//	case 5:
//		break;
//	case 6:
//		break;
//	case 7:
//		break;
//	case 8:
//		break;
//	case 9:
//		break;
//	}
//}
