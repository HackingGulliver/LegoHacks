/*
 * PWMStateCalculator.cpp
 *
 *  Created on: 08.04.2016
 *      Author: thomas
 */

#include "PWMStateCalculator.h"

PWMStateCalculator::PWMStateCalculator() {
	nextChangingStep = 0;
	currentStep = 0;
	currentState = 0;
}

PWMStateCalculator::~PWMStateCalculator() {
	// TODO Auto-generated destructor stub
}

uint8_t PWMStateCalculator::nextState() {
	uint8_t currStep = currentStep - 1;
	if (currStep != nextChangingStep) {
		return currentState;
	}

	currentState = 0;
	nextChangingStep = 255;

	for (uint8_t i = 0; i < 8; ++i) {
		currentState <<= 1;
		uint8_t duty = duties[i];
		if (currStep < duty) {
			currentState |= 1;
			if (duty < nextChangingStep) {
				nextChangingStep = duty;
			}
		}
	}

	nextChangingStep++;
	return currentState;
}

