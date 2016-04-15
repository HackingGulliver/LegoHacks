/*
 * PWMStateCalculator.h
 *
 *  Created on: 08.04.2016
 *      Author: thomas
 */

#ifndef PWMSTATECALCULATOR_H_
#define PWMSTATECALCULATOR_H_

#include "Arduino.h"

class PWMStateCalculator {
public:
	PWMStateCalculator(uint8_t channels);
	virtual ~PWMStateCalculator();

	void setDuty(uint8_t channel, uint8_t duty);
	void setupFinished() { 	dutyChanged = true; }

	void tick();

private:
	void writeData();
	void createDataForSteps();
	void createStepData(uint8_t duty, uint8_t stepIdx);
	uint8_t sortChangingStepsAndRemoveDuplicates();
	void writeToShift(uint8_t value, boolean finish);

private:
	uint8_t numBytes;		// The number of bytes needed to represent the current PWM state
	uint8_t numChannels;	// The number of PWM channels
	uint8_t numChangingSteps;
	uint8_t currentStep;	// The current step in a whole PWM cycle
	boolean dutyChanged;


	uint8_t *changingSteps;	// Array of step indices, when changing data has to be sent
	uint8_t *nextChangingStep; 	// Pointer at the current position in the array changingSteps
	uint8_t *dataForSteps;		// This array contains all data that has to be sent at certain steps. Its size is numBytes*numChannels.
	uint8_t *nextData;			// Pointer into the array dataForSteps for the next set of data to send
	uint8_t *duties;			// Duty values for all channels
};

#endif /* PWMSTATECALCULATOR_H_ */
