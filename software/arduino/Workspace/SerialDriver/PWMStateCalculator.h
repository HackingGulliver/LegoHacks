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
	static const uint8_t NUM_CHANNELS = 8;

	PWMStateCalculator();
	virtual ~PWMStateCalculator();

	void setDuty(uint8_t channel, uint8_t duty) {
		if (channel < NUM_CHANNELS) {
			duties[channel] = duty;
		}
	}

	uint8_t nextState();
	boolean tickAndTest() {
		if (currentStep++ == nextChangingStep) {
			return true;
		}
		return false;
	}


private:
	uint8_t duties[NUM_CHANNELS];
	uint8_t currentStep;
	uint8_t nextChangingStep;
	uint8_t currentState;

};

#endif /* PWMSTATECALCULATOR_H_ */
