// RPM_Meter.h

#ifndef _RPM_METER_h
#define _RPM_METER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include <Arduino.h>
	#include "TLC5947.h"
#else
	#include "WProgram.h"
#endif

class RPM_Meter {
public:
	RPM_Meter(TLC5947 *tlcIN, uint16_t led1, uint16_t led2, uint16_t led3, uint16_t led4, uint16_t led5, uint16_t led6, uint16_t led7
		, uint16_t led8, uint16_t led9, uint16_t led10);

	boolean begin(void);

	void set(uint16_t rpm);
	void warning();
	void test();


private:
	uint16_t *leds;
	TLC5947 *tlc;
	uint16_t prevState;
};

#endif

