/*
 * Pulse.h
 *
 *  Created on: 19.04.2016
 *      Author: thomas
 */

#ifndef PULSE_H_
#define PULSE_H_

#include "TimedPowerController.h"
#include "ChannelDuty.h"

class Pulse: public TimedPowerController {

public:
	Pulse(uint8_t numChannels);
	virtual ~Pulse();

	virtual void tick(unsigned long milliSeconds);

	virtual void setDuty(uint8_t channel, uint8_t duty);

private:
	ChannelDuty *channelDuties;
	uint8_t numChannels;
	uint32_t millisOffset;
};

#endif /* PULSE_H_ */
