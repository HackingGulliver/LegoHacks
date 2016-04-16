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

	void tick(){
		if (currentStep++ == nextChangingStep) {
			writeData();
		}
	}

	void createDataForSteps(); //TODO Just for benchmarking

private:
	void writeData();
	void restartCycle();

private:
	uint8_t numBytes;		// The number of bytes needed to represent the current PWM state
	uint8_t numChannels;	// The number of PWM channels
	uint8_t currentStep;	// The current step in a whole PWM cycle
	uint8_t nextChangingStep;
	boolean dutyChanged;


	uint8_t *dataForSteps;		// This array contains all data that has to be sent at certain steps. Its size is numBytes*numChannels.
	uint8_t *nextData;			// Pointer into the array dataForSteps for the next set of data to send
	uint8_t *duties;			// Duty values for all channels
	uint8_t* endData;
};

#endif /* PWMSTATECALCULATOR_H_ */
