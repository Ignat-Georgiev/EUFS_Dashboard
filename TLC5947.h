// TLC5947.h

#ifndef _TLC5947_h
#define _TLC5947_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class TLC5947 {
public:
	TLC5947(uint16_t n, uint8_t c, uint8_t d, uint8_t l);

	boolean begin(void);

	void setPWM(uint16_t chan, uint16_t pwm);
	void set(uint16_t lednum, uint16_t state);
	void setLED(uint16_t lednum, uint16_t r, uint16_t g, uint16_t b);
	void write(void);
	void clear(void);
	void setPWM(uint16_t pwm);

	uint16_t globalPWM;


private:
	uint16_t *pwmbuffer;
	uint16_t numdrivers;
	uint8_t _clk, _dat, _lat;
};


#endif

