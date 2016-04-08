// Do not remove the include below
#include "SerialDriver.h"
#include "PWMStateCalculator.h"

#define SHIFT_DATA_PIN 4
#define SHIFT_CLOCK_PIN 3
#define SHIFT_STORE_PIN 2

PWMStateCalculator pwmStateCalculator;

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
void writeToShift(uint8_t value, boolean finish) {
#ifndef DEBUG
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

	if (finish) {
		PORTD = 4; // store = 1
	}

	SREG = oldSREG;
#endif
}

void pwm(uint8_t duty, uint8_t value) {
	static uint8_t current = 0;
	if (current <= duty) {
		writeToShift(value, true);
	} else {
		writeToShift(0, true);
	}
	current++;
}

void performPWMCycle() {
	for (int i = 0; i <= 255; ++i) {
		uint8_t state = pwmStateCalculator.calculateNextState();
//		writeToShift(0, false);
//		state = pwmStateCalculator.calculateNextState();
//		writeToShift(0, false);
//		state = pwmStateCalculator.calculateNextState();
//		writeToShift(0, false);
//		state = pwmStateCalculator.calculateNextState();
		writeToShift(state, true);
	}
}

// The loop function is called in an endless loop
void loop()
{
	pwmStateCalculator.setDuty(0,255);
	pwmStateCalculator.setDuty(1,128);
	pwmStateCalculator.setDuty(2,64);
	pwmStateCalculator.setDuty(3,32);
	pwmStateCalculator.setDuty(4,16);
	pwmStateCalculator.setDuty(5,8);
	pwmStateCalculator.setDuty(6,4);
	pwmStateCalculator.setDuty(7,2);
	for (uint16_t i = 0; i < 1000; ++i) {
		performPWMCycle();
	}
	uint8_t duty = 255;
	while (1) {

		for (uint8_t led = 0; led < 8; ++led) {
			pwmStateCalculator.setDuty(led, duty);
			uint8_t nduty = duty;
			for (uint8_t nled = 1; nled < 7; ++nled) {
				nduty = (nduty >> 1);// + (nduty >> 3);
				pwmStateCalculator.setDuty((led-nled) & 0x07, nduty);
			}
			for (int cycles = 0; cycles < 10; ++cycles) {
				performPWMCycle();
			}
		}

	}
}
