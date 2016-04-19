/*
 * PWMController.h
 *
 *  Created on: 18.04.2016
 *      Author: thomas
 */

#ifndef PWMCONTROLLER_H_
#define PWMCONTROLLER_H_

#include "Arduino.h"
#include "PowerController.h"
#include "PWMStateCalculator.h"

/**
 * This class is the main controller for all PWM outputs. It controls the timer that calls the controller in regular intervals
 * and contains the PWMStateCalculator that calculates all data that is sent to a serial device.
 */
class PWMController : public PowerController {
public:

	PWMController(uint8_t channels, uint8_t frequency = 100);
	virtual ~PWMController();

	void setDuty(uint8_t channel, uint8_t duty) {
		pwmStateCalculator->setDuty(channel, duty);
	}
	void allDutiesSet() {
		pwmStateCalculator->allDutiesSet();
	}

private:
	void tick();
	static void timerCallback();
	static void timedPowerControllerCallback();
	void initStateCalculator(uint8_t channels);
	void initTimer(uint8_t frequency);

	static PWMController *instance;


	PWMStateCalculator *pwmStateCalculator;
};

#endif /* PWMCONTROLLER_H_ */
