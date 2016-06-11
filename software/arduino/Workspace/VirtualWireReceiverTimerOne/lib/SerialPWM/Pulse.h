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
	enum Waveform {
		SAW_TOOTH_RISE,
		SAW_TOOTH_FALL,
		TRIANGLE,
		BLINK
	};

	Pulse(uint8_t numChannels, uint32_t pulseWidth, Waveform waveform);
	virtual ~Pulse();

	virtual void tick(unsigned long milliSeconds);

	virtual void setDuty(uint8_t channel, uint8_t duty);

	void changePulseWidth(uint32_t pulseWidth);

private:
	ChannelDuty *channelDuties;
	uint8_t numChannels;
	uint32_t millisOffset;
	uint32_t pulseWidth;  // Pulse width in milliseconds
	float frequencyKHz;   // Frequency in kHz (derived from pulseWidth
	Waveform waveform;

	uint32_t calculateBaseTime(unsigned long milliSeconds);
	float dutyFactorAtBaseTime(uint32_t baseTime);
};

#endif /* PULSE_H_ */
