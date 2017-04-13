#include "RPM_Meter.h"

RPM_Meter::RPM_Meter(TLC5947 *tlcIN, uint16_t led1, uint16_t led2, uint16_t led3, uint16_t led4, uint16_t led5, uint16_t led6, uint16_t led7
	, uint16_t led8, uint16_t led9, uint16_t led10) {
	leds = (uint16_t *)malloc(480);
	memset(leds, 0, 480);
	leds[0] = led1;
	leds[1] = led2;
	leds[2] = led3;
	leds[3] = led4;
	leds[4] = led5;
	leds[5] = led6;
	leds[6] = led7;
	leds[7] = led8;
	leds[8] = led9;
	leds[9] = led10;
	tlc = tlcIN;
	prevState = 0;
}

void RPM_Meter::set(uint16_t rpm) {
	for (int i = 0; i < 10; i++) {
		if (i < rpm)
			tlc->set(leds[i], 1);
		else
			tlc->set(leds[i], 0);
	}
//	tlc->write();
}

void RPM_Meter::test() {

	if (prevState == 10) {
		set(0);
		prevState = 0;
	}
	else {
		prevState++;
		set(prevState);
	}
}

void RPM_Meter::warning() {
	set(10);
	delay(1000);
	set(0);
}
