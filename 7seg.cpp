#include "7seg.h"

7seg::7seg(Adafruit_TLC5947 *tlcIN, uint16_t a, uint16_t b, uint16_t c, uint16_t d, uint16_t e,
	uint16_t f, uint16_t g, uint16_t dp) {
	A = a;
	B = b;
	C = c;
	D = d;
	E = e;
	F = f;
	G = g;
	DP = dp
	tlc = tlcIN;
	prevState = 0;
	prevLoop = A;
}

void 7seg::set(uint16_t dig) {
	switch (dig)
	{
	case 0:	tlc.set(A, 1);
			tlc.set(B, 1);
			tlc.set(C, 1);
			tlc.set(D, 1);
			tlc.set(E, 1);
			tlc.set(F, 1);
		break;

	case 1:	tlc.set(B, 1);
			tlc.set(C, 1);
		break;

	case 2:	tlc.set(A, 1);
			tlc.set(B, 1);
			tlc.set(G, 1);
			tlc.set(D, 1);
			tlc.set(E, 1);
		break;

	case 3:	tlc.set(A, 1);
			tlc.set(B, 1);
			tlc.set(C, 1);
			tlc.set(D, 1);
		break;

	case 4:	tlc.set(B, 1);
			tlc.set(C, 1);
			tlc.set(F, 1);
			tlc.set(G, 1);
		break;

	case 5:	tlc.set(A, 1);
			tlc.set(C, 1);
			tlc.set(D, 1);
			tlc.set(G, 1);
			tlc.set(F, 1);
		break;

	case 6:	tlc.set(A, 1);
			tlc.set(G, 1);
			tlc.set(C, 1);
			tlc.set(D, 1);
			tlc.set(E, 1);
			tlc.set(F, 1);
		break;

	case 7:	tlc.set(A, 1);
			tlc.set(B, 1);
			tlc.set(C, 1);
		break;

	case 8:	tlc.set(A, 1);
			tlc.set(B, 1);
			tlc.set(C, 1);
			tlc.set(D, 1);
			tlc.set(E, 1);
			tlc.set(F, 1);
			tlc.set(G, 1);
		break;

	case 9:	tlc.set(A, 1);
			tlc.set(B, 1);
			tlc.set(C, 1);
			tlc.set(D, 1);
			tlc.set(G, 1);
			tlc.set(F, 1);
		break;

	default:	tlc.set(DP, 1);
		break;
	}
}

7seg::test() {
	if (prevState == 11) {
		set(0);
		prevState = 0;
	}
	else {
		prevState++;
		set(prevState);
	}
}

7seg::init() {
	if (prevLoop == dp) {
		tlc.set(A);
		prevLoop = A;
	}
	else {
		prevLoop++;
		set(prevLoop);
	}
}