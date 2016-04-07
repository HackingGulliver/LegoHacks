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

void fastDigitalWrite(uint8_t pin, uint8_t value) {
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	volatile uint8_t *out;

	if (port == NOT_A_PIN) return;

	out = portOutputRegister(port);

	uint8_t oldSREG = SREG;
	cli();

	if (value == LOW) {
		*out &= ~bit;
	} else {
		*out |= bit;
	}

	SREG = oldSREG;
}

void writeToShift(uint8_t value) {
	fastDigitalWrite(SHIFT_STORE_PIN, LOW);
	for (int i = 0; i < 8; ++i) {
		fastDigitalWrite(SHIFT_DATA_PIN, value & 1);
		fastDigitalWrite(SHIFT_CLOCK_PIN, HIGH);
		fastDigitalWrite(SHIFT_CLOCK_PIN, LOW);
		value >>= 1;
	}
	fastDigitalWrite(SHIFT_STORE_PIN, HIGH);
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
