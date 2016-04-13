// Do not remove the include below
#include "SerialDriver.h"
#include "PWMStateCalculator.h"

#ifndef DEBUG
#include <SPI.h>
#include <TimerOne.h>
#endif

#define SHIFT_DATA_PIN 11  // MOSI
#define SHIFT_CLOCK_PIN 13 // SPI Clock
#define SHIFT_STORE_PIN 2
namespace {

const int MICROSEC_PER_AT_100HZ = 39;

}

void performPWMCycle();
void showRisingBrightness();

PWMStateCalculator pwmStateCalculator1;
PWMStateCalculator pwmStateCalculator2;
PWMStateCalculator pwmStateCalculator3;
PWMStateCalculator pwmStateCalculator4;

#ifndef DEBUG
void setup() {

	pinMode(SHIFT_STORE_PIN, OUTPUT);

	SPI.begin();
	SPI.beginTransaction(SPISettings(16000000, LSBFIRST, SPI_MODE0));

	Timer1.initialize();
	Timer1.setPeriod(MICROSEC_PER_AT_100HZ);
//	Timer1.attachInterrupt(performPWMCycle);

	Serial.begin(57600);
}
#else
void setup() {
	showRisingBrightness();
	while (1) {
		performPWMCycle();
	}
}
#endif

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
	uint8_t state;
	bool change1 = pwmStateCalculator1.tickAndTest();
	bool change2 = pwmStateCalculator2.tickAndTest();
	bool change3 = pwmStateCalculator3.tickAndTest();
	bool change4 = pwmStateCalculator4.tickAndTest();
	if (change1 || change2 || change3 || change4) {
		state = pwmStateCalculator4.nextState();
		writeToShift(state, false);
		state = pwmStateCalculator3.nextState();
		writeToShift(state, false);
		state = pwmStateCalculator2.nextState();
		writeToShift(state, false);
		state = pwmStateCalculator1.nextState();
		writeToShift(state, true);
	}
}

void showRisingBrightness(uint8_t startValue, PWMStateCalculator &calc) {
	calc.setDuty(0, startValue + 255);
	calc.setDuty(1, startValue + 128);
	calc.setDuty(2, startValue + 64);
	calc.setDuty(3, startValue + 32);
	calc.setDuty(4, startValue + 16);
	calc.setDuty(5, startValue + 8);
	calc.setDuty(6, startValue + 4);
	calc.setDuty(7, startValue + 2);
	delay(1000);
}

void showBrightness(int brightness, PWMStateCalculator &calc) {
	calc.setDuty(0, brightness);
	calc.setDuty(1, brightness);
	calc.setDuty(2, brightness);
	calc.setDuty(3, brightness);
	calc.setDuty(4, brightness);
	calc.setDuty(5, brightness);
	calc.setDuty(6, brightness);
	calc.setDuty(7, brightness);
	delay(1000);
}

void showChaserLight() {
	uint8_t duty = 50;
	while (1) {
		for (uint8_t led = 0; led < 8; ++led) {
			pwmStateCalculator1.setDuty(led, duty);
			uint8_t nduty = duty;
			for (uint8_t nled = 1; nled < 7; ++nled) {
				nduty = (nduty >> 1); // + (nduty >> 3);
				pwmStateCalculator1.setDuty((led - nled) & 0x07, nduty);
			}
			delay(250);
		}
	}
}

uint32_t benchmark() {
	//	showChaserLight();
	uint32_t counter = 0;
	unsigned long inOneSecond = millis() + 1000l;
	Serial.print("Starting...");
	while (millis() < inOneSecond) {
		counter++;
	}
	Serial.println(counter);
	return counter;
}

// Profile: Eine Sekunde Counter hoch zählen und dabei die Zeit für die Sekunde vergleichen
// Keine Optimierung (100Hz):
// 1 Byte senden: 290514
// 2 Byte senden: 115000
// 3 Byte senden: n/a
// Optimierung (100Hz):
// 1 Byte senden: 433000
// 2 Byte senden: 414000
// 3 Byte senden: 389000
// 4 Byte senden: 308000
// Optimierung (200Hz):
// 4 Byte senden: 114000
// Optimierung (250Hz):
// 4 Byte senden: 11000 (Performance grenzwertig)
// Optimierung 1 Byte senden
// 300Hz: 260000
// 325Hz: 239000
// 350Hz: 215000
// 385Hz: 190000
// 420Hz: 158000
// 470Hz: 115000
// 535Hz: 63000

void emptyFunction() {

}

// The loop function is called in an endless loop
void loop()
{
	// Benchmark without timer
	uint32_t noTimer = benchmark();

	// Benchmark with empty timer
	Timer1.attachInterrupt(emptyFunction);
	uint32_t emptyTimer = benchmark();

	// Benchmark with PWM timer
	Timer1.detachInterrupt();
	Timer1.attachInterrupt(performPWMCycle);

	showRisingBrightness(0, pwmStateCalculator1);
	showRisingBrightness(20, pwmStateCalculator2);
	showRisingBrightness(40, pwmStateCalculator3);
	showRisingBrightness(60, pwmStateCalculator4);
	uint32_t differentPWM = benchmark();

	showBrightness(10, pwmStateCalculator1);
	uint32_t samePWM = benchmark();
	showBrightness(5, pwmStateCalculator1);
	samePWM += benchmark();
	showBrightness(0, pwmStateCalculator1);
	samePWM += benchmark();

	Serial.println();
	Serial.print("Leerer Timer: ");
	Serial.println((float) emptyTimer / noTimer);
	Serial.print("Unterschiedliche PWMs: ");
	Serial.println((float) differentPWM / noTimer);
	Serial.print("Gleiche PWMs: ");
	Serial.println((float) samePWM / (3 * noTimer));
	Serial.println();

	showChaserLight();

}
