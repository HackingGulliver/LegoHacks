// Do not remove the include below
#include "SerialDriver.h"

#define SHIFT_DATA_PIN 4
#define SHIFT_CLOCK_PIN 3
#define SHIFT_STORE_PIN 2



void setup()
{
	pinMode(SHIFT_DATA_PIN, OUTPUT);
	pinMode(SHIFT_CLOCK_PIN, OUTPUT);
	pinMode(SHIFT_STORE_PIN, OUTPUT);

}

//void writeToShift(uint8_t value) {
//	uint8_t oldSREG = SREG;
//	cli();
//
//	// Clock (3): PORTD = 8
//	// Store (2): PORTD = 4
//	// Data (4): PORTD = 16
//
//	uint8_t i = 8;
//	do {
//		if (value & 1) {
//			PORTD = 16; // data = 1, store = 0;
//			PORTD = 24; // data = 1, clock = 1;
//		} else {
//			PORTD = 0;// data = 0, store = 0
//			PORTD = 8; // data = 0, clock = 1
//		}
//		value >>= 1;
//		--i;
//	} while (i);
//	PORTD = 4; // store = 1
//	SREG = oldSREG;
//
//}
void writeToShift(uint8_t value) {
	uint8_t oldSREG = SREG;
	cli();

	// Clock (3): PORTD = 8
	// Store (2): PORTD = 4
	// Data (4): PORTD = 16

	if (value & 1) {
		PORTD = 16; // data = 1, store = 0;
		PORTD = 24; // data = 1, clock = 1;
	} else {
		PORTD = 0;// data = 0, store = 0
		PORTD = 8; // data = 0, clock = 1
	}

	if (value & 2) {
		PORTD = 16; // data = 1, store = 0;
		PORTD = 24; // data = 1, clock = 1;
	} else {
		PORTD = 0;// data = 0, store = 0
		PORTD = 8; // data = 0, clock = 1
	}

	if (value & 4) {
		PORTD = 16; // data = 1, store = 0;
		PORTD = 24; // data = 1, clock = 1;
	} else {
		PORTD = 0;// data = 0, store = 0
		PORTD = 8; // data = 0, clock = 1
	}

	if (value & 8) {
		PORTD = 16; // data = 1, store = 0;
		PORTD = 24; // data = 1, clock = 1;
	} else {
		PORTD = 0;// data = 0, store = 0
		PORTD = 8; // data = 0, clock = 1
	}

	if (value & 16) {
		PORTD = 16; // data = 1, store = 0;
		PORTD = 24; // data = 1, clock = 1;
	} else {
		PORTD = 0;// data = 0, store = 0
		PORTD = 8; // data = 0, clock = 1
	}

	if (value & 32) {
		PORTD = 16; // data = 1, store = 0;
		PORTD = 24; // data = 1, clock = 1;
	} else {
		PORTD = 0;// data = 0, store = 0
		PORTD = 8; // data = 0, clock = 1
	}

	if (value & 64) {
		PORTD = 16; // data = 1, store = 0;
		PORTD = 24; // data = 1, clock = 1;
	} else {
		PORTD = 0;// data = 0, store = 0
		PORTD = 8; // data = 0, clock = 1
	}

	if (value & 128) {
		PORTD = 16; // data = 1, store = 0;
		PORTD = 24; // data = 1, clock = 1;
	} else {
		PORTD = 0;// data = 0, store = 0
		PORTD = 8; // data = 0, clock = 1
	}

	PORTD = 4; // store = 1
	SREG = oldSREG;

}

void pwm(uint8_t duty, uint8_t value) {
	static uint8_t current = 0;
	if (current <= duty) {
		writeToShift(value);
	} else {
		writeToShift(0);
	}
	current++;
}


// The loop function is called in an endless loop
void loop()
{

	while (1) {
		for (uint8_t duty = 255; duty >= 0; --duty) {
			for (uint16_t i = 0; i < 320; ++i) {
				pwm(duty, 0x55);
			}
		}
	}
}
