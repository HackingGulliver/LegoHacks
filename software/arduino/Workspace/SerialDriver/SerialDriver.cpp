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
const int NUM_PINS = 8;
}

void performPWMCycle();
void showRisingBrightness(uint8_t startValue, uint8_t numPins, PWMStateCalculator &calc);

PWMStateCalculator pwmStateCalculator(NUM_PINS);

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
//	showRisingBrightness(0, NUM_PINS, pwmStateCalculator);
//	while (1) {
//		performPWMCycle();
//	}
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
	pwmStateCalculator.tick();
}

void mockPWMCycle() {
	volatile static uint8_t currStep = 0;
	if ((currStep & 7) == 0) {
		writeToShift(currStep, false);
		writeToShift(currStep, false);
		writeToShift(currStep, false);
		writeToShift(currStep, true);
	}
	currStep++;
}

void showRisingBrightness(uint8_t startValue, uint8_t numPins, PWMStateCalculator &calc) {
	float stepWith = float(255 - startValue) / numPins;
	float duty = startValue;

	for (uint8_t i = 0; i < numPins; ++i) {
		calc.setDuty(i, (uint8_t) duty);
		duty += stepWith;
	}
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

void createDutyRange(uint8_t start, uint8_t end, uint8_t numPins, PWMStateCalculator &calc) {
	float stepWith = float(end - start) / numPins;
	float duty = start;

	for (uint8_t i = 0; i < numPins; ++i) {
		calc.setDuty(i, (uint8_t) duty);
		duty += stepWith;
	}

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

// The loop function is called in an endless loop
void loop()
{

	// Benchmarks for creating the data to be sent
#ifndef DEBUG
//	Timer1.attachInterrupt(performPWMCycle);
#endif
	unsigned long int start;
	unsigned long int diff;
	createDutyRange(0, 255, NUM_PINS, pwmStateCalculator);
	pwmStateCalculator.setupFinished();
#ifdef DEBUG
	while (1) {
		performPWMCycle();
	}
#endif
	start = micros();
	pwmStateCalculator.createDataForSteps();
	diff = micros() - start;
	Serial.print("Sortiert:           ");
	Serial.println(diff);
	delay(1000);

	createDutyRange(255, 0, NUM_PINS, pwmStateCalculator);
	pwmStateCalculator.setupFinished();
	start = micros();
	pwmStateCalculator.createDataForSteps();
	diff = micros() - start;
	Serial.print("Umgekehrt sortiert: ");
	Serial.println(diff);
	delay(1000);

	createRandomDuties(NUM_PINS, pwmStateCalculator);
	pwmStateCalculator.setupFinished();
	start = micros();
	pwmStateCalculator.createDataForSteps();
	diff = micros() - start;
	Serial.print("Zufällig:           ");
	Serial.println(diff);
	delay(1000);


	//===============================================
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
	showChaserLight();

}
