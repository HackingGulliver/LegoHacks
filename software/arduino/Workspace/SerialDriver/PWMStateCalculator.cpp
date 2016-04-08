/*
 * PWMStateCalculator.cpp
 *
 *  Created on: 08.04.2016
 *      Author: thomas
 */

#include "PWMStateCalculator.h"

PWMStateCalculator::PWMStateCalculator() {
	// TODO Auto-generated constructor stub

}

PWMStateCalculator::~PWMStateCalculator() {
	// TODO Auto-generated destructor stub
}

uint8_t PWMStateCalculator::calculateNextState() {
	uint8_t state = 0;

	for (uint8_t i = 0; i < 8; ++i) {
		state <<= 1;
		if (currentStep < duties[i]) {
			state |= 1;
		}
	}

	++currentStep;
	return state;
}
