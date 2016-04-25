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

}

Pulse::~Pulse() {
	// TODO Auto-generated destructor stub
}

void Pulse::tick(unsigned long milliSeconds) {

	uint32_t period = 2000;
	uint8_t precision = 12;

	uint32_t factor = ((milliSeconds % period)<<precision) / period;
	uint32_t duty;
	for (uint8_t i = 0; i < numChannels; ++i) {
		if (channelDuties[i].getChannel() != 255) {
			duty = (channelDuties[i].getDuty() * factor) >> precision;
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
