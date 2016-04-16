/*
 * PWMStateCalculator.cpp
 *
 *  Created on: 08.04.2016
 *      Author: thomas
 */

#include "PWMStateCalculator.h"
#include <SPI.h>

PWMStateCalculator::PWMStateCalculator(uint8_t channels) {
	numChannels = channels;
	numBytes = ((channels-1) >> 3)+1;
	dataForSteps = new uint8_t[(numBytes+1) * (numChannels+1)];
	duties = new uint8_t[numChannels];

	currentStep = 0;
	nextChangingStep = 0;
	dutyChanged = false;
	nextData = dataForSteps;

}

PWMStateCalculator::~PWMStateCalculator() {
	// TODO Auto-generated destructor stub
}


void PWMStateCalculator::setDuty(uint8_t channel, uint8_t duty){
	if (channel >= numChannels) {
		return;
	}
	duties[channel] = duty;
}

void PWMStateCalculator::writeData() {
	noInterrupts();

	if (nextChangingStep == 0) {
		restartCycle();
	}
#ifndef DEBUG
	PORTD = 0;
#endif
	uint8_t nb = numBytes;
	while (nb--) {
		SPI.transfer(*nextData++);
	}
#ifndef DEBUG
	PORTD = 4; // store = 1
#endif

	if (nextData == endData) {
		nextChangingStep = 0;
	} else {
		nextChangingStep = *nextData++;
	}

	interrupts();
}

void PWMStateCalculator::createDataForSteps() {
	dutyChanged = false;

	uint8_t nextDuty;
	uint8_t duty = 0;

	uint8_t *destAddr = dataForSteps;
	do {
		uint8_t bits = 0;
		*destAddr++ = duty;

		nextDuty = 255;
		for (uint8_t ch = 0; ch < numChannels; ++ch) {
			bits <<= 1;
			if (duties[ch] > duty || duty == 255) {
				bits |= 1;

				if (duties[ch] < nextDuty) {
					nextDuty = duties[ch];
				}
			}
			if ((ch & 0x7) == 0x7) {
				*destAddr++ = bits;
				bits = 0;
			}

		}
		if (numChannels & 0x7) {
			*destAddr++ = bits;
		}

		duty = nextDuty;
	} while (nextDuty != 255);

	endData = destAddr;
}


void PWMStateCalculator::restartCycle() {
	if (dutyChanged) {
		createDataForSteps();
	}
	nextData = dataForSteps;
	nextChangingStep = *nextData++;
}

