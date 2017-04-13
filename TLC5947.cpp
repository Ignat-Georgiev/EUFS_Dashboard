// 
// 
// 

#include "TLC5947.h"

TLC5947::TLC5947(uint16_t n, uint8_t c, uint8_t d, uint8_t l) {
	numdrivers = n;
	_clk = c;
	_dat = d;
	_lat = l;
	globalPWM = 4095;

	//pwmbuffer = (uint16_t *)calloc(2, 24*n);
	pwmbuffer = (uint16_t *)malloc(2 * 24 * n);
	memset(pwmbuffer, 0, 2 * 24 * n);
}

void TLC5947::write(void) {
	digitalWrite(_lat, LOW);
	// 24 channels per TLC5974
	for (int16_t c = 24 * numdrivers - 1; c >= 0; c--) {
		// 12 bits per channel, send MSB first
		for (int8_t b = 11; b >= 0; b--) {
			digitalWrite(_clk, LOW);

			if (pwmbuffer[c] & (1 << b))
				digitalWrite(_dat, HIGH);
			else
				digitalWrite(_dat, LOW);

			digitalWrite(_clk, HIGH);
		}
	}
	digitalWrite(_clk, LOW);

	digitalWrite(_lat, HIGH);
	digitalWrite(_lat, LOW);
}



void TLC5947::setPWM(uint16_t chan, uint16_t pwm) {
	if (pwm > 4095) pwm = 4095;
	if (chan > 24 * numdrivers) return;
	pwmbuffer[chan] = pwm;
}

void TLC5947::set(uint16_t lednum, uint16_t state) {
	if (state == 1)
		setPWM(lednum, globalPWM);
	else
		setPWM(lednum, state);
}


void TLC5947::setLED(uint16_t lednum, uint16_t r, uint16_t g, uint16_t b) {
	setPWM(lednum * 3, r);
	setPWM(lednum * 3 + 1, g);
	setPWM(lednum * 3 + 2, b);
}

void TLC5947::clear() {
	for (int i = 0; i < 24; i++) {
		pwmbuffer[i] = 0;
	}
	write();
}

void TLC5947::setPWM(uint16_t pwm) {
	globalPWM = pwm;
}


boolean TLC5947::begin() {
	if (!pwmbuffer) return false;

	pinMode(_clk, OUTPUT);
	pinMode(_dat, OUTPUT);
	pinMode(_lat, OUTPUT);
	digitalWrite(_lat, LOW);

	return true;
}


