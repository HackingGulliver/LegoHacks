// Do not remove the include below
#include "SerialDriver.h"
#include <PWMController.h>
#include <Pulse.h>
#include <RGBLed.h>

#ifndef DEBUG
#include <TimerOne.h>
#endif

const uint8_t NUM_PINS = 8;

void showRisingBrightness(uint8_t startValue, uint8_t numPins, PWMStateCalculator &calc);

#ifndef DEBUG
void setup() {

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
	calc.allDutiesSet();
	delay(1000);
}

void showBrightness(uint8_t brightness, uint8_t numPins, PWMStateCalculator &calc) {
	for (uint8_t i = 0; i < numPins; ++i) {
		calc.setDuty(i, (uint8_t) brightness);
	}
	calc.allDutiesSet();
	delay(1000);
}


void createRandomDuties(uint8_t numPins, PWMStateCalculator &calc) {

	srand(17);
	for (uint8_t i = 0; i < numPins; ++i) {
		calc.setDuty(i, (uint8_t) rand());
	}

}

/*
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
*/

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

/*
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
*/

/*
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
*/

// The loop function is called in an endless loop
void loop()
{
//Timer3.initialize(1000);
	 // benchmarkCreateData();

//	rgbTest();
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

	PWMController pwmController(NUM_PINS, 100);

	Pulse pulse(6, 1000, Pulse::TRIANGLE);
	pulse.chain(&pwmController);
	pwmController.addTimedPowerController(&pulse);

	RGBLed rgbLed(NUM_PINS-1, NUM_PINS-2, NUM_PINS-3);
	rgbLed.chain(&pulse);
	rgbLed.setColor(255, 128, 128);

	RGBLed rgbLed2(NUM_PINS-4, NUM_PINS-6, NUM_PINS-8);
	rgbLed2.chain(&pulse);
	rgbLed2.setColor(64, 128, 255);

	uint32_t differentPWM = benchmark();

	pulse.changePulseWidth(500);
	uint32_t samePWM = benchmark();

	pulse.changePulseWidth(250);
	samePWM += benchmark();

	pulse.changePulseWidth(1000);
	samePWM += benchmark();

	Serial.println();
	Serial.print("Leerer Timer: ");
	Serial.println((float) emptyTimer / noTimer);
	Serial.print("Unterschiedliche PWMs: ");
	Serial.println((float) differentPWM / noTimer);
	Serial.print("Gleiche PWMs: ");
	Serial.println((float) samePWM / (3 * noTimer));
	Serial.println();

	while (1) {
		rgbLed.setColor(rand(), rand(), rand());
		pulse.changePulseWidth(1000);
		delay(1000);
	}

}
