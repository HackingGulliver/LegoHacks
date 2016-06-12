/*
 * ChannelDuty.h
 *
 *  Created on: 24.04.2016
 *      Author: thomas
 */

#ifndef CHANNELDUTY_H_
#define CHANNELDUTY_H_

#include "Arduino.h"

class ChannelDuty {
public:
	ChannelDuty();

	ChannelDuty(uint8_t channel, uint8_t duty)
		: channel(channel)
		, duty(duty) {}

	uint8_t getChannel() const {
		return channel;
	}

	void setChannel(uint8_t channel) {
		this->channel = channel;
	}

	uint8_t getDuty() const {
		return duty;
	}

	void setDuty(uint8_t duty) {
		this->duty = duty;
	}

private:
	uint8_t channel;
	uint8_t duty;
};

#endif /* CHANNELDUTY_H_ */
