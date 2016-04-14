/*
 * PWMStateCalculator.cpp
 *
 *  Created on: 08.04.2016
 *      Author: thomas
 */

#include "PWMStateCalculator.h"

PWMStateCalculator::PWMStateCalculator(uint8_t channels) {
	numChannels = channels;
	numBytes = ((channels-1) >> 3)+1;
	dataForSteps = new uint8_t[numBytes * (numChannels+1)];
	changingSteps = new uint8_t[numChannels+1];
	duties = new uint8_t[numChannels];

	currentStep = 0;
}

PWMStateCalculator::~PWMStateCalculator() {
	// TODO Auto-generated destructor stub
}


void PWMStateCalculator::setDuty(uint8_t channel, uint8_t duty){
	if (channel >= numChannels) {
		return;
	}
	duties[channel] = duty;
	createDataForSteps();
}

void PWMStateCalculator::writeData() {
}

void PWMStateCalculator::createDataForSteps() {
	changingSteps[0] = 0;
	memcpy(changingSteps+1, duties, numChannels);

	numChangingSteps = sortChangingStepsAndRemoveDuplicates();
	uint8_t stepIdx = 0;
	for (uint8_t cs = 0; cs < numChangingSteps; ++cs) {
		++stepIdx;
		uint8_t duty = changingSteps[cs];
		createStepData(duty, stepIdx);
	}
}

void PWMStateCalculator::createStepData(uint8_t duty, uint8_t stepIdx) {
	uint8_t *destAddr = dataForSteps + stepIdx * numBytes;

	uint8_t bits = 0;
	for (uint8_t ch = 0; ch < numChannels; ++ch) {
		bits <<= 1;
		if (duties[ch] > duty) {
			bits |= 1;
		}
		if ((ch & 0x7) == 0x7) {
			*destAddr++ = bits;
			bits = 0;
		}
	}
	*destAddr = bits;
}

uint8_t PWMStateCalculator::sortChangingStepsAndRemoveDuplicates() {

	// Sort
	for (uint8_t i = 1; i <= numChannels; ++i) {
	    for (uint8_t k = i; k > 0 && changingSteps[k] < changingSteps[k-1]; k--) {
	    	uint8_t tmp = changingSteps[k];
	    	changingSteps[k] = changingSteps[k-1];
	    	changingSteps[k-1] = tmp;
	    }
	}

	// Remove duplicates
	uint8_t numDifferent = 1;
	uint8_t lastVal = changingSteps[0];
	for (uint8_t i = 1; i <= numChannels; ++i) {
		if (changingSteps[i] != lastVal) {
			lastVal = changingSteps[numDifferent++] = changingSteps[i];
		}
	}
	return numDifferent;
}
