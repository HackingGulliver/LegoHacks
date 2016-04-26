/*
 * Pulse.cpp
 *
 *  Created on: 19.04.2016
 *      Author: thomas
 */

#include "Pulse.h"

Pulse::Pulse(uint8_t numChannels, uint32_t pulseWidth)
	: numChannels(numChannels)
	, pulseWidth(pulseWidth)
{
	channelDuties = new ChannelDuty[numChannels];
	millisOffset = 0l;
	frequencyKHz = 1.0f / pulseWidth;
}

Pulse::~Pulse() {
	// TODO Auto-generated destructor stub
}

void Pulse::tick(unsigned long milliSeconds) {

	if (millisOffset == 0l) {
		millisOffset = milliSeconds;
	}

	uint32_t timebase = milliSeconds - millisOffset;
	if (timebase > pulseWidth) {
		millisOffset += pulseWidth;
		timebase -= pulseWidth;
	}
	if (timebase >= (pulseWidth >> 1)) {
		timebase = pulseWidth - timebase;
	}
	timebase <<= 1;

	float factor = float(timebase) * frequencyKHz;
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
