/**
 *
 * Anleitung zum Einrichten des Debuggers: http://blog.baeyens.it/#post23
 */


// Do not remove the include below
#include "Stepper.h"


const int NUM_STEPS = 100;

const int DELAY = 2;

const int STEP_PIN = 13;
const int DIR_PIN = 12;
const int ENABLE_PIN = 11;

const int MS1_PIN = 7;
const int MS2_PIN = 6;
const int MS3_PIN = 5;

enum Direction {
	COUNTER_CLOCKWISE = HIGH,
	CLOCKWISE = LOW
};

enum StepMode {
	FULL = 0,
	HALF = 4,
	QUARTER = 2,
	EIGHTH = 6,
	SIXTEENTH = 7
};

void stepMode(StepMode stepMode) {
	digitalWrite(MS1_PIN, stepMode & 0x04 ? HIGH : LOW);
	digitalWrite(MS2_PIN, stepMode & 0x02 ? HIGH : LOW);
	digitalWrite(MS3_PIN, stepMode & 0x01 ? HIGH : LOW);
}

void enable(boolean doEnable) {
	digitalWrite(ENABLE_PIN, doEnable ? LOW : HIGH);
}

void direction(Direction direction) {
	digitalWrite(DIR_PIN, direction);
}

void step(uint16_t delayMs) {
	digitalWrite(STEP_PIN, LOW);
	digitalWrite(STEP_PIN, HIGH);
	delayMicroseconds(delayMs);
}

void steps(uint32_t numSteps, uint16_t delayMicroSec){
	for (uint32_t i = 0; i < numSteps; ++i) {
		step(delayMicroSec);
	}
}

void accelerate(uint32_t numSteps, uint16_t minDelayMicroSec, uint16_t maxDelayMicroSec) {
	int16_t delayDiff = maxDelayMicroSec - minDelayMicroSec;
	float currentDelay = minDelayMicroSec;
	float inc = float(delayDiff) / numSteps;

	for (uint32_t i = 0; i < numSteps; ++i) {
		step(currentDelay);
		currentDelay += inc;
	}
}

//The setup function is called once at startup of the sketch
void setup()
{
	  // initialize digital pin 13 as an output.
	  pinMode(STEP_PIN, OUTPUT);
	  pinMode(DIR_PIN, OUTPUT);
	  pinMode(ENABLE_PIN, OUTPUT);

	  pinMode(MS1_PIN, OUTPUT);
	  pinMode(MS2_PIN, OUTPUT);
	  pinMode(MS3_PIN, OUTPUT);

}

// The loop function is called in an endless loop
void loop()
{
	enable(true);
	direction(CLOCKWISE);

	stepMode(SIXTEENTH);
	long stepsPerFull = 16;
	uint16_t destDelayMicroSec = 2500 / stepsPerFull;
	uint16_t startDelayMicroSec = 100000 / stepsPerFull;

	uint16_t totalSteps = 2050;
	uint16_t accelSteps = 200;
//	while (true) {
		direction(CLOCKWISE);
//		steps(2037, delayMicroSec);
		accelerate(accelSteps * stepsPerFull, startDelayMicroSec, destDelayMicroSec);
		steps((totalSteps - 2 * accelSteps) * stepsPerFull, destDelayMicroSec);
		accelerate(accelSteps * stepsPerFull, destDelayMicroSec, startDelayMicroSec);
//		delayMicroSec -= 50;
		direction(COUNTER_CLOCKWISE);
//		steps(2037, delayMicroSec);
		accelerate(accelSteps * stepsPerFull, startDelayMicroSec, destDelayMicroSec);
		steps((totalSteps - 2 * accelSteps) * stepsPerFull, destDelayMicroSec);
		accelerate(accelSteps * stepsPerFull, destDelayMicroSec, startDelayMicroSec);

		/*
		delay(1000);
		direction(COUNTER_CLOCKWISE);
		steps((24 * 8 * 3 * 10) / 6, 1);
		delay(1000);
*/
//	}

	enable(false);
	delay(1000);
	enable(true);
/*
	steps(NUM_STEPS*100, DELAY);
	delay(500);

	stepMode(HALF);
	steps(NUM_STEPS * 2, DELAY);
	delay(500);

	stepMode(QUARTER);
	steps(NUM_STEPS * 4, DELAY);
	delay(500);

	stepMode(EIGHTH);
	steps(NUM_STEPS * 8, DELAY);
	delay(500);

	stepMode(SIXTEENTH);
	steps(NUM_STEPS * 16, DELAY);
	delay(500);

	direction(COUNTER_CLOCKWISE);
	steps(100, DELAY);
//	enable(false);

	stepMode(EIGHTH);
	while(true) {
		direction(CLOCKWISE);
		steps(NUM_STEPS, DELAY);
		direction(COUNTER_CLOCKWISE);
		steps(NUM_STEPS, DELAY);
	}
*/
}

#ifdef DEBUG
void delayMicroseconds(unsigned int us) {

}
#endif
