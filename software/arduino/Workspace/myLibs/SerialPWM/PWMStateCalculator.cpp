/*
 * PWMStateCalculator.cpp
 *
 *  Created on: 08.04.2016
 *      Author: thomas
 */

#include "PWMStateCalculator.h"
#include <SPI.h>

#define SHIFT_DATA_PIN 11  // MOSI
#define SHIFT_CLOCK_PIN 13 // SPI Clock
#define SHIFT_STORE_PIN 2  // move shifted data to 74HC595 outputs
#define PORT_FOR_STORE_PIN PORTD
#define STORE_PIN_SET_BITS 0x04 // The value 4 corresponds to pin 2 in PORTD of an ATMega 328

/**
 * The PWMStateCalculator calculates the complete data that is sent to a serial device, each time a PWM state changes i.e. when a pin
 * has to change its state. The after the setup is finished (the duty has been set for all channels), the data is calculated. Afterward,
 * in the periodic calls from a timer, the data is simply sent from an internal array i.e. <dataForSteps>.
 *
 * <dataForSteps> has the following layout:
 *
 *     step indices | bytes to send in a step
 *                  |    _____/\______
 *                  v   /             \
 *                 +---+---+---+---+---+
 *                 | 0 |   |   |   |   |
 *                 +---+---+---+---+---+
 *                 | 10|   |   |   |   |
 *                 +---+---+---+---+---+
 *                 | 42|   |   |   |   |
 *                 +---+---+---+---+---+
 *                 |192|   |   |   |   |
 *                 +---+---+---+---+---+
 * In this example there may be up to 32 channels that are represented in 4 Bytes. The only present duty cycles in these channels are
 * 0 (optional, because this is always needed), 10, 42 and 192.
 */
PWMStateCalculator::PWMStateCalculator(uint8_t channels) {
	setupHardware();
	numChannels = channels;
	numBytes = ((channels-1) >> 3)+1;
	dataForSteps = new uint8_t[(numBytes+1) * (numChannels+1)];
	duties = new uint8_t[numChannels];
	memset(duties, 0, numChannels);

	currentStep = 0;
	nextChangingStep = 0;
	dutyChanged = false;
	nextData = dataForSteps;
	nextDutyCalc = 255;

}

PWMStateCalculator::~PWMStateCalculator() {
	// TODO Auto-generated destructor stub
}

void PWMStateCalculator::setupHardware() {
	pinMode(SHIFT_STORE_PIN, OUTPUT);
#ifndef DEBUG
	SPI.begin();
	SPI.beginTransaction(SPISettings(16000000, LSBFIRST, SPI_MODE0));
#endif
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
	if (nextDutyCalc != 255) {
		createDataForStep(nextDutyCalc);
	}
#ifndef DEBUG
	PORT_FOR_STORE_PIN &= ~STORE_PIN_SET_BITS;
#endif
	uint8_t nb = numBytes;
	while (nb--) {
		SPI.transfer(*nextData++);
	}
#ifndef DEBUG
	PORT_FOR_STORE_PIN |= STORE_PIN_SET_BITS;
#endif

	if (nextData == endData) {
		nextChangingStep = 0;
	} else {
		nextChangingStep = *nextData++;
	}

	interrupts();
}

void PWMStateCalculator::createDataForStep(uint8_t duty) {
	dutyChanged = false;

	if (duty == 0) {
		nextDutyCalcDestAddr = dataForSteps;
		*nextDutyCalcDestAddr++ = duty;
		endData = dataForSteps;
	}
	uint8_t bits = 0;

	nextDutyCalc = 255;

	uint8_t ch = 0;
	while (ch < numChannels) {
		uint8_t nextChunkSize = (ch + 8 > numChannels) ? numChannels - ch : 8;
		while (nextChunkSize--) {
			bits >>= 1;
			if (duties[ch] > duty || duty == 255) {
				bits |= 128;

				if (duties[ch] < nextDutyCalc) {
					nextDutyCalc = duties[ch];
				}
			}
			++ch;
		}
		*nextDutyCalcDestAddr++ = bits;
		bits = 0;
	}

	if (nextDutyCalc == 255) {
		endData = nextDutyCalcDestAddr;
	} else {
		*nextDutyCalcDestAddr++ = nextDutyCalc;
	}
}


void PWMStateCalculator::restartCycle() {
	if (dutyChanged) {
		nextDutyCalc = 0;
	}
	nextData = dataForSteps;
	nextChangingStep = *nextData++;
}

