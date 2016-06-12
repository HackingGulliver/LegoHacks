/*
 * Pulse.cpp
 *
 *  Created on: 19.04.2016
 *      Author: thomas
 */

#include "Pulse.h"

Pulse::Pulse(uint8_t numChannels, uint32_t pulseWidth, Waveform waveform)
	: numChannels(numChannels)
	, pulseWidth(pulseWidth)
	, waveform(waveform)
{
	channelDuties = new ChannelDuty[numChannels];
	millisOffset = 0l;
	frequencyKHz = 1.0f / pulseWidth;
}

Pulse::~Pulse() {
	// TODO Auto-generated destructor stub
}

/**
 * The baseTime is a value for milliseconds between the start of a period and its end.
 * So its value is always between 0 and <pulseWidth>. It indicates where we are currently located
 * in the waveform that will be generated.
 *
 * @param milliSeconds
 *   Current system time in milliseconds which is taken as basis for calculating the baseTime.
 *
 */
uint32_t Pulse::calculateBaseTime(unsigned long milliSeconds) {
	if (millisOffset == 0l) {
		millisOffset = milliSeconds;
	}
	uint32_t baseTime = milliSeconds - millisOffset;
	if (baseTime > pulseWidth) {
		millisOffset += pulseWidth;
		baseTime -= pulseWidth;
	}
	return baseTime;
}

/**
 * Calculates the factor for the duty value at the given baseTime. The factor depends on the
 * baseTime and the selected waveform.
 */
float Pulse::dutyFactorAtBaseTime(uint32_t baseTime) {
	if (waveform == TRIANGLE) {
		if (baseTime >= (pulseWidth >> 1)) {
			baseTime = pulseWidth - baseTime;
		}
		baseTime <<= 1;
	} else if (waveform == SAW_TOOTH_RISE) {
		// nothing to do
	} else if (waveform == SAW_TOOTH_FALL) {
		baseTime = pulseWidth - baseTime;
	} else if (waveform == BLINK) {
		baseTime = baseTime >= (pulseWidth >> 1) ? pulseWidth : 0;
	}

	return float(baseTime) * frequencyKHz;
}

void Pulse::tick(unsigned long milliSeconds) {

	uint32_t baseTime = calculateBaseTime(milliSeconds);

	float factor = dutyFactorAtBaseTime(baseTime);

	float duty;
	for (uint8_t i = 0; i < numChannels; ++i) {
		if (channelDuties[i].getChannel() != 255) {
			duty = channelDuties[i].getDuty() * factor;
			chainedController->setDuty(channelDuties[i].getChannel(), duty);
		}
	}
	allDutiesSet();
}

void Pulse::setDuty(uint8_t channel, uint8_t duty) {
	for (uint8_t i = 0; i < numChannels; ++i) {
		if (channelDuties[i].getChannel() == channel || channelDuties[i].getChannel() == 255) {
			channelDuties[i].setChannel(channel);
			channelDuties[i].setDuty(duty);
			break;
		}
	}
}

void Pulse::changePulseWidth(uint32_t pulseWidth) {
	this->pulseWidth = pulseWidth;
	frequencyKHz = 1.0f / pulseWidth;
	millisOffset = 0l;
}
