/*
 * Pulse.cpp
 *
 *  Created on: 19.04.2016
 *      Author: thomas
 */

#include "Pulse.h"

Pulse::Pulse(uint8_t numChannels)
	: numChannels(numChannels)
{
	channelDuties = new ChannelDuty[numChannels];
	millisOffset = 0l;

}

Pulse::~Pulse() {
	// TODO Auto-generated destructor stub
}

void Pulse::tick(unsigned long milliSeconds) {

	const uint32_t period = 1000;
	const uint32_t periodHalf = period/2;
	const float rp = 1.0f / period;
	if (millisOffset == 0l) {
		millisOffset = milliSeconds;
	}

	uint32_t timebase = milliSeconds - millisOffset;
	if (timebase > period) {
		millisOffset += period;
		timebase -= period;
	}
	if (timebase >= periodHalf) {
		timebase = period - timebase;
	}
	timebase <<= 1;

	float factor = float(timebase) * rp;
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
