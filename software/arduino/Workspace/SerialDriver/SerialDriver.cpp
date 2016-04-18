// Do not remove the include below
#include "SerialDriver.h"
#include "PWMStateCalculator.h"

#ifndef DEBUG
#include <TimerOne.h>
#endif

namespace {

const int MICROSEC_PER_AT_100HZ = 39;
const int NUM_PINS = 8;
}

void performPWMCycle();
void showRisingBrightness(uint8_t startValue, uint8_t numPins, PWMStateCalculator &calc);

PWMStateCalculator pwmStateCalculator(NUM_PINS);

#ifndef DEBUG
void setup() {

	Timer1.initialize();
	Timer1.setPeriod(MICROSEC_PER_AT_100HZ);
//	Timer1.attachInterrupt(performPWMCycle);

	Serial.begin(57600);
}
#else
void setup() {
//	showRisingBrightness(0, NUM_PINS, pwmStateCalculator);
//	while (1) {
//		performPWMCycle();
//	}
}
#endif


void performPWMCycle() {
	pwmStateCalculator.tick();
}

void createDutyRange(uint8_t start, uint8_t end, uint8_t numPins, PWMStateCalculator &calc) {
	float stepWith = float(end - start) / numPins;
	float duty = start;

	for (uint8_t i = 0; i < numPins; ++i) {
		calc.setDuty(i, (uint8_t) duty);
		duty += stepWith;
	}
}

void showRisingBrightness(uint8_t startValue, uint8_t numPins, PWMStateCalculator &calc) {
	createDutyRange(0, 255, numPins, calc);
	calc.setupFinished();
	delay(1000);
}

void showBrightness(uint8_t brightness, uint8_t numPins, PWMStateCalculator &calc) {
	for (uint8_t i = 0; i < numPins; ++i) {
		calc.setDuty(i, (uint8_t) brightness);
	}
	calc.setupFinished();
	delay(1000);
}


void createRandomDuties(uint8_t numPins, PWMStateCalculator &calc) {

	srand(17);
	for (uint8_t i = 0; i < numPins; ++i) {
		calc.setDuty(i, (uint8_t) rand());
	}

}

void showChaserLight() {
	uint8_t duty = 255;
	while (1) {
		for (uint8_t led = 0; led < NUM_PINS; ++led) {
			pwmStateCalculator.setDuty(led, duty);
			uint8_t nduty = duty;
			for (uint8_t nled = 1; nled < NUM_PINS-1; ++nled) {
				nduty = (nduty >> 1); // + (nduty >> 3);
				uint8_t pin;
				if (nled > led) {
					pin = NUM_PINS - (nled - led);
				} else {
					pin = led - nled;
				}
				pwmStateCalculator.setDuty(pin, nduty);
			}
			pwmStateCalculator.setupFinished();
			delay(100);
		}
	}
}

uint32_t benchmark() {
	uint32_t counter = 0;
	unsigned long inOneSecond = millis() + 1000l;
	Serial.print("Starting...");
	while (millis() < inOneSecond) {
		counter++;
	}
	Serial.println(counter);
	return counter;
}


void emptyFunction() {

}

void benchmarkCreateData() {
	unsigned long int start;
	unsigned long int diff;
	createDutyRange(0, 255, NUM_PINS, pwmStateCalculator);
	pwmStateCalculator.setupFinished();
	start = micros();
//	pwmStateCalculator.createDataForSteps();
	diff = micros() - start;
	Serial.print("Sortiert:           ");
	Serial.println(diff);
	delay(1000);
	createDutyRange(255, 0, NUM_PINS, pwmStateCalculator);
	pwmStateCalculator.setupFinished();
	start = micros();
//	pwmStateCalculator.createDataForSteps();
	diff = micros() - start;
	Serial.print("Umgekehrt sortiert: ");
	Serial.println(diff);
	delay(1000);
	createRandomDuties(NUM_PINS, pwmStateCalculator);
	pwmStateCalculator.setupFinished();
	start = micros();
//	pwmStateCalculator.createDataForSteps();
	diff = micros() - start;
	Serial.print("Zufällig:           ");
	Serial.println(diff);
	delay(1000);
}


void rgbTest() {

	showBrightness(0, NUM_PINS, pwmStateCalculator);
#ifdef DEBUG
	while (1) {
		pwmStateCalculator.setDuty(0, 1);
		pwmStateCalculator.setupFinished();
		performPWMCycle();
	}
#endif
#ifndef DEBUG
	Timer1.attachInterrupt(performPWMCycle);
#endif
	const uint8_t red = 7;
	const uint8_t green = 6;
	const uint8_t blue = 5;
	pwmStateCalculator.setDuty(red, 10);
	pwmStateCalculator.setDuty(green, 0);
	pwmStateCalculator.setDuty(blue, 0);
	pwmStateCalculator.setupFinished();
	delay(1000);
	pwmStateCalculator.setDuty(red, 0);
	pwmStateCalculator.setDuty(green, 10);
	pwmStateCalculator.setDuty(blue, 0);
	pwmStateCalculator.setupFinished();
	delay(1000);
	pwmStateCalculator.setDuty(red, 0);
	pwmStateCalculator.setDuty(green, 0);
	pwmStateCalculator.setDuty(blue, 10);
	pwmStateCalculator.setupFinished();
	delay(1000);

	pwmStateCalculator.setDuty(blue, 0);

	while (1) {
		pwmStateCalculator.setDuty(7,1);
		pwmStateCalculator.setupFinished();
		delay(100);
	}

//	while (1) {
//		for (uint8_t r = 0; r < 255; ++r) {
//			pwmStateCalculator.setDuty(red, r);
//			pwmStateCalculator.setupFinished();
//			delay(10);
//		}
//		for (uint8_t r = 255; r > 0; --r) {
//			pwmStateCalculator.setDuty(red, r);
//			pwmStateCalculator.setupFinished();
//			delay(10);
//		}
//	}

	while (1) {
		const uint8_t maxBright = 15;
		for (uint8_t r = 0; r < maxBright; ++r) {
			for (uint8_t g = 0; g < maxBright; ++g) {
				for (uint8_t b = 0; b < maxBright; ++b) {

					pwmStateCalculator.setDuty(red, r);
					pwmStateCalculator.setDuty(green, g);
					pwmStateCalculator.setDuty(blue, b);
					pwmStateCalculator.setupFinished();
					delay(10);
				}
			}
		}
	}
}

// The loop function is called in an endless loop
void loop()
{

	 // benchmarkCreateData();

	rgbTest();
	// Benchmark without timer
#ifndef DEBUG
	Timer1.detachInterrupt();
#endif
	uint32_t noTimer = benchmark();

	// Benchmark with empty timer
#ifndef DEBUG
	Timer1.attachInterrupt(emptyFunction);
#endif
	uint32_t emptyTimer = benchmark();

	// Benchmark with PWM timer
#ifndef DEBUG
	Timer1.detachInterrupt();
	Timer1.attachInterrupt(performPWMCycle);
#endif

	showRisingBrightness(0, NUM_PINS, pwmStateCalculator);
	uint32_t differentPWM = benchmark();

	showBrightness(10, NUM_PINS, pwmStateCalculator);
	uint32_t samePWM = benchmark();
	showBrightness(5, NUM_PINS, pwmStateCalculator);
	samePWM += benchmark();
	showBrightness(0, NUM_PINS, pwmStateCalculator);
	samePWM += benchmark();

	Serial.println();
	Serial.print("Leerer Timer: ");
	Serial.println((float) emptyTimer / noTimer);
	Serial.print("Unterschiedliche PWMs: ");
	Serial.println((float) differentPWM / noTimer);
	Serial.print("Gleiche PWMs: ");
	Serial.println((float) samePWM / (3 * noTimer));
	Serial.println();

	for (int pin = 0; pin < NUM_PINS; ++pin) {
		for (uint8_t i = 0; i < 255; ++i) {
			pwmStateCalculator.setDuty(pin, i);
			pwmStateCalculator.setupFinished();
			delay(1);
		}
	}

	showBrightness(0, NUM_PINS, pwmStateCalculator);


	showChaserLight();

}
