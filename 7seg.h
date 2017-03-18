#include <Arduino.h>
#include <Adafruit_TLC5947.h>

class 7seg{
public:
	7seg(Adafruit_TLC5947 *tlcIN, uint16_t a, uint16_t b, uint16_t c, uint16_t d, uint16_t e,
		uint16_t f, uint16_t g, uint16_t dp) {

		void set(uint16_t dig);
		void test();
		void init();

private:
	Adafruit_TLC5947 *tlc;
	uint16_t prevState;
	uint16_t prevLoop;
	uint16_t A;
	uint16_t B;
	uint16_t C;
	uint16_t D;
	uint16_t E;
	uint16_t F;
	uint16_t G;
	uint16_t DP;
}