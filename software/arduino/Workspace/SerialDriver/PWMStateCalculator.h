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

	uint8_t calculateNextState();

private:
	uint8_t duties[NUM_CHANNELS];
	uint8_t currentStep;

};

#endif /* PWMSTATECALCULATOR_H_ */
