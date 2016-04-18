/*
 * PWMStateCalculator.h
 *
 *  Created on: 08.04.2016
 *      Author: thomas
 */

#ifndef PWMSTATECALCULATOR_H_
#define PWMSTATECALCULATOR_H_

#include "Arduino.h"

/**
 * The PWMStateCalculator sends PWM data to a serial device like a shift register (typically 74HC595).
 * For performance reasons this is accomplished via SPI. Currently this class is adapted for an ATMega328. So the SPI pins are:
 * DATA_PIN  11 (MOSI)
 * CLOCK_PIN 13 (SPI Clock)
 * STORAGE_PIN 2 (for transferring shifted data in the 74HC595 to its output pins)
 * (see #defines in cpp file)
 * The data direction for these pins is set in the constructor of this class and must not be changed somewhere else.
 *
 */
class PWMStateCalculator {
public:

	/**
	 * Creates a PWMStateCalculator for the given number of <channels>. The bytes that are sent to a serial device are pre-calculated.
	 * All channels together consume this amount of memory:
	 * numberOfBytes = int(numberOfChannels / 8) + 1  => The number of bytes that are sent for one PWM time slice.
	 * sizeOfCalculateData = (numberOfBytes+1) * (numberOfChannels+1)
	 * sizeOfDutyStorage = numberOfChannels
	 *
	 * Some examples:
	 * 1 channel:  (1+1) * (1+1) + 1 => 5 Bytes
	 * 4 channels: (1+1) * (4+1) + 4 => 14 Bytes
	 * 8 channels: (1+1) * (8+1) + 8 => 26 Bytes
	 * 9 channels: (2+1) * (9+1) + 9 => 39 Bytes
	 * 16 channels: (2+1) * (16+1) + 16 => 67 Bytes
	 * 32 channels: (4+1) * (32+1) + 32 => 197 Bytes
	 * 64 channels: (8+1) * (64+1) + 64 => 649 Bytes
	 * 96 channels: (12+1) * (96+1) + 96 => 1357 Bytes
	 */
	PWMStateCalculator(uint8_t channels);
	virtual ~PWMStateCalculator();

	/**
	 * Sets the duty cycle for the given <channel> to <duty>. A higher duty means "more power"
	 *
	 * uint8_t channel: Index of the channel: 0 - number of channels -1
	 * uint8_t duty: 0 - 255 (where 0 is always off and 255 always on)
	 * Call <setupFinished> for the duty settings to take effect.
	 */
	void setDuty(uint8_t channel, uint8_t duty);

	/**
	 * Must be called after setting the duty cycles of all channels. Otherwise these changes will no be effective.
	 */
	void setupFinished() { 	dutyChanged = true; }

	/**
	 * Must be called from a timer to write out the PWM data to a serial device.
	 * For a 100Hz PWM rate, the timer has to call the method every 39 microseconds.
	 */
	void tick(){
		if (currentStep++ == nextChangingStep) {
			writeData();
		}
	}


private:
	void writeData();
	void restartCycle();
	void createDataForStep(uint8_t duty);
	void setupHardware();

private:
	uint8_t numBytes;		// The number of bytes needed to represent the current PWM state
	uint8_t numChannels;	// The number of PWM channels
	uint8_t currentStep;	// The current step in a whole PWM cycle which consists of 256 steps.
	uint8_t nextChangingStep; // Number of the PWM step when the next data has to be sent.
	boolean dutyChanged;    // <true> after <setupFinished> was called.
	uint8_t nextDutyCalc;


	uint8_t *dataForSteps;	// This array contains all data that has to be sent at certain steps. Its size is (numBytes+1)*(numChannels+1).
	uint8_t *nextData;		// Pointer into the array dataForSteps for the next set of data to send
	uint8_t *duties;		// Duty values for all channels
	uint8_t *endData;		// This pointer marks the end of the precalculated data array.
	uint8_t *nextDutyCalcDestAddr;
};

#endif /* PWMSTATECALCULATOR_H_ */
