#include <Timer.h>
#include <ToggleButton.h>
#include <Adafruit_TLC5947.h>

Timer testButtonTimer;


int shiftLED = 5;

ToggleButton testBtn(12, HIGH);

// LED Driver constructor
#define NUM_TLC 1
#define drvr_clock 9
#define drvr_data 8
#define drvr_lat 3
Adafruit_TLC5947 drvr = Adafruit_TLC5947(NUM_TLC, drvr_clock, drvr_data, drvr_clock);


void setup()
{

	Serial.begin(115200);
	drvr.begin();
	pinMode(shiftLED, OUTPUT);
	testButtonTimer.oscillate(shiftLED, 500, 1);
	testButtonTimer.every(1000, RPMtest);

	drvr.setLED(2, 1);
	drvr.setLED(3, 1);
	drvr.setLED(4, 1);
	drvr.setLED(16, 1);
	drvr.setLED(19, 1);
	drvr.setLED(21, 1);

}

void loop()
{
	testBtn.checkButton();
	drvr.write();


	if (testBtn.currentState == true) {
		testButtonTimer.update();
		drvr.setLED(2, 1);
		drvr.setLED(3, 1);
		drvr.setLED(4, 1);
	}
	else {
		digitalWrite(shiftLED, 0);
		drvr.setLED(2, 1);
		drvr.setLED(3, 1);
		drvr.setLED(4, 1);
	}

}

void RPMtest() {
	drvr.setLED(2, 0);
	testButtonTimer.after(100, f1);
	testButtonTimer.after(400, f2);
}

void f1() {
	drvr.setLED(3, 0);
}

void f2() {
	drvr.setLED(4, 0);
}
