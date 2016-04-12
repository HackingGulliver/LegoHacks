// Do not remove the include below
#include "SerialDriver.h"
#include "PWMStateCalculator.h"

#include <SPI.h>
#include <TimerOne.h>

#define SHIFT_DATA_PIN 11  // MOSI
#define SHIFT_CLOCK_PIN 13 // SPI Clock
#define SHIFT_STORE_PIN 2

void performPWMCycle();

PWMStateCalculator pwmStateCalculator;

void setup() {

	pinMode(SHIFT_STORE_PIN, OUTPUT);

	SPI.begin();
	SPI.beginTransaction(SPISettings(16000000, LSBFIRST, SPI_MODE0));

	Timer1.initialize();
	Timer1.setPeriod(39);
	Timer1.attachInterrupt(performPWMCycle);

	Serial.begin(57600);
}


void writeToShift(uint8_t value, boolean finish) {
#ifndef DEBUG
	PORTD = 0;

	SPI.transfer(value);

	if (finish) {
		PORTD = 4; // store = 1
	}

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
//	for (int i = 0; i <= 255; ++i) {
		uint8_t state = pwmStateCalculator.calculateNextState();
		writeToShift(0, false);
		state = pwmStateCalculator.calculateNextState();
//		writeToShift(0, false);
//		state = pwmStateCalculator.calculateNextState();
//		writeToShift(0, false);
//		state = pwmStateCalculator.calculateNextState();
		writeToShift(state, true);
//	}
}

void showRisingBrightness() {
	pwmStateCalculator.setDuty(0, 255);
	pwmStateCalculator.setDuty(1, 128);
	pwmStateCalculator.setDuty(2, 64);
	pwmStateCalculator.setDuty(3, 32);
	pwmStateCalculator.setDuty(4, 16);
	pwmStateCalculator.setDuty(5, 8);
	pwmStateCalculator.setDuty(6, 4);
	pwmStateCalculator.setDuty(7, 2);
	delay(1000);
}

void showChaserLight() {
	uint8_t duty = 50;
	while (1) {
		for (uint8_t led = 0; led < 8; ++led) {
			pwmStateCalculator.setDuty(led, duty);
			uint8_t nduty = duty;
			for (uint8_t nled = 1; nled < 7; ++nled) {
				nduty = (nduty >> 1); // + (nduty >> 3);
				pwmStateCalculator.setDuty((led - nled) & 0x07, nduty);
			}
			delay(250);
		}
	}
}

// Profile:
// Keine Optimierung:
// 1 Byte senden: 290514
// 2 Byte senden: 115000
// 3 Byte senden: n/a

// The loop function is called in an endless loop
void loop()
{
	showRisingBrightness();

//	showChaserLight();

	uint32_t counter = 0;

	unsigned long inOneSecond = millis() + 1000l;

	Serial.print("Starting...");
	while (millis() < inOneSecond) {
		counter++;
	}

	Serial.println(counter);

}
